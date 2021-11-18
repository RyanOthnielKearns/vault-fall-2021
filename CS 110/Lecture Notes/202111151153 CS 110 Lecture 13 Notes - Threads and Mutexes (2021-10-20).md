#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 13 Slides - Threads and Mutexes.pdf|slides]] and [[2021-10-20 Lecture Notes.pdf|handwritten notes]]
2021-10-20
___
# Introduction to Threads
- compare to processes, which are:
	- completely isolated from each other unless both processes buy into it / there is some user config w/ piping
- **thread**: an independent execution flow within a process
	- often spawned to subdivide to collectively solve a larger problem
	- each execution can agree where global variables are / update complex data structures together
		- running in the same virtual address space
			- data integrity issues! race conditions!
	- processes' stack segment divided into miniature substacks
	- constructor `thread()` takes at least the name of the function to run in the thread
	- `t.join()`: the "blocking method" like `waitpid` -- halts until this thread is ready to "join back" w/ main execution thread
		- otherwise, the whole process might be destroyed while child threads are still runnning

## Greeters example
```
thread greeters[6];
for (size_t i = 0; i < 6; i++) {
	greeters[i] = thread(greet, i+1); // 2nd arg to thread constructor!
}

static void greet(size_t id) {
	for (size_t i = 0; i < id; i++) {
		cout << oslock << "Greeter # " << id << " says hello!" << endl << osunlock;
	}
}
```
- use the `oslock` and `osunlock` pattern because `cout` and the `<<` operator are not thread-safe

## Airline tickets example
- `size_t numTickets = 250;` is the *database* -- where workers consult whether there are tickets left to sell
- `agents[i] = thread(agent, 101 + i, ref(numTickets));`
	- using `ref()` -- have to be explicit that this variable is passed by reference in thread constructor
### Race Condition Issue
```
while (numTickets > 0) {
	handleCall();
	numTickets--;
...
```
- separation between these 2 lines (checking and decrementing `numTickets`) is not **thread-safe** -- possible to sell a ticket that isn't actually available
	- thread might be swapped off CPU after evaluating `numTickets > 0`, and other threads might swap on and do the same thing, over-committing number of tickets to be sold
	- called a **critical region** in multithreading parlance
	- `numTickets--;` by itself isn't even thread-safe
		- C++ statements aren't inherently **atomic** -- result in multiple (atomic) assembly code instructions
	- must guarantee that no other thread can even *examine* the value of `numTickets` if another thread is staged to modify it
		- solution? concurrency directive that prevents more than 1 thread from occupying a critical region at a time (the **mutex**)

# Mutexes
```
class mutex {
public:
	mutex(); // constructs the mutex to be in an unlocked state
	void lock(); // acquires the lock on the mutex, blocking until it's unlocked
	void unlock(); // releases the lock and wakes up another threads trying to lock it
};
```
- contraction of the words *mutual* and *exclusion*
- used to *mark the boundaries of critical regions*
	- **critical region**: a stretch of code where only 1 thread is allowed to be at any one moment
- constructor `mutex()`: initialized mutex in *unlocked* state
- `lock()` method eventually acquires lock on the mutex
	- if mutex is in a locked state, calling `lock()` will suspend the thread until the thread holding the lock releases it with `unlock()`

## When do you need a mutex?
1. When there are multiple threads *writing* to a variable
2. When there is a thread *writing* and one or more threads *reading*
3. *Not* when there are only readers!