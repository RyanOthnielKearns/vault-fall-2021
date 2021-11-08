#CS #CS110 #lecture-notes 
2021-10-29
___
# Agenda
- mostly done with multithreading today
- reading for `assign5` after this
- finishing up mythbuster example
	- multithreading is a great candidate for the myth example b/c most of the dead time establishing network connection is done in parallel
	- how to make it faster? how does threading part actually work?

# `myth-buster` example
- main functions are very 106b-y

## `compileCS110ProcessCountMap` method
```
static void compileCS110ProcessCountMap(const unordered_set<string>& sunets, map<int, int>& counts) {
	vector<thread> threads;
	mutex countsLock;
	for (size_t i = 0; i < 16; i++) {
		int num = 51 + i;
		threads.push_back(
			thread([num, &sunet, &counts, &countsLock](){
				int count = getNumProcesses(num, sunets);
				if (count >= 0) { // a sort of error-checking on getNumProcesses
					lock_guard<mutex> lg(countsLock);
					counts[num] = count; // map itself is not inherently thread-safe!
				}
			}
		);
	}
	
	for (thread &t: threads) t.join();
}
```
- `unordered_set` is a C++ hash set
- relying on library function: `int getNumProcesses(int num, const unordered_set<string>& sunets)`
	- taking this for granted -- returns number of processes owned by particular user
- obviously load-balancing like this won't work if sequential on *actual* server farms, which have 10k's of machines -- would take hours to find the least loaded machine
- going to schedule 16 threads
	- all threads are going to compete to update the map for the particular myth machine number they're working with --> have to guard surgery on the shared variable w/ a mutex
- these threads can run more-or-less in parallel and it won't be a problem (since there are 16 of them)
	- but... suppose there are 16 million machines: this solution would create 16 million threads, will scale badly
	- why not introduce 16 million threads? cordons off a portion of the stack segment to store that thread's state -- and OS doesn't want to deal with that many threads
	- limit on most machines is about 500... that will totally overwhelm compute power available
		- ok to have 2x, 4x, 8x threads per CPU if *most* of their time is going to be spent off-CPU as a blocked thread
			- **"network-bound computation"**
			- in **"cpu-bound computation"**, this number of threads per CPU *won't actually save time*

## Multithreading implementation changes
- would like to limit the number of threads that can exist at any one point
- add `semaphore permits(8);`
- now: in the method above:

```
for (size_t i = 0; i < 16000; i ++) {
	int num = 10001 + i;
	permits.wait();
	threads.push_back(
		thread([&]() {
			int count = getNumProcesses(num, sunets);
			if (count >= 0) {
				lock_guard<mutex> lg(countsLock);
				counts[num] = count;
			}
			// not worried about exception-safe threads here, but something to think about...
			permits.signal(); // done in the thread routine!
			// space right here where threads could signal w/o deallocating, meaning theoretically more than 8 threads could exist at a time --> permits.signal(on_thread_exit); instead (not used in any assignment)
		})
	);

	// joining
}
```
- the `thread([&](){})` construction is capturing *everything* in the scope by reference -- not something you generally want to do, but for brevity...
	- including `permits` semaphore
- better than `on_thread_exit` solution: data structure we will be building for assign5
	- very unusual to hand-roll your own thread objects, joining, etc. -- there are pre-built library fxns for this
	- don't *actually* create 16,000 (or million) thread objects! 1 for each fxn to be executed
		- solution: **ThreadPool**

## ThreadPool
- create finite number of threads that are scheduled
	- advertise to some "primary agent" that they're done so they can be recycled
- generalization of factorization farm that uses threads instead of processes

```
class ThreadPool {
public:
	ThreadPool(size_t numThreads); // small for cpu-bound computations, larger for network ones
	void schedule(const std::function<void(void)>& thunk);
	void wait();
	~ThreadPool();
}
```
- thunk = any function that can be executed without argument
- `wait` stalls until every thunk that has been scheduled has executed to completion
	- destructor also calls `wait` before destructing -- pool won't be destroyed w/o waiting on everything scheduled