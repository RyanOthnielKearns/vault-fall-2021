#CS110 #CS #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 15 Slides - Multithreading, Condition Variables, and Semaphores.pdf|slides]] and [[CS 110 Lecture 15 Notes - Multithreading, Condition Variables, and Semaphores (2021-10-25).pdf|handwritten notes]]
2021-10-25
___
# Dining Philosophers Problem, Cont.
Continuing from last 2 lectures ([[202111151153 CS 110 Lecture 13 Notes - Threads and Mutexes (2021-10-20)|13]] and [[202111151222 CS 110 Lecture 14 Notes - Threads, Deadlock, Condition Variables (2021-10-22)|14]])
- issue with current solution: **deadlock**
	- introduced "permit" or "permission slip" notion
		- given 4 permits: `numForks - 1`, e.g. as high as possible w/o introducing deadlock
		- you're not allowed to do the job of the thread manager and decide how threads are scheduled (unless you "know more" than the OS)
## `condition_variable_any`
- `condition_variable_any` was introduced to remove reliance on busy waiting in the `waitForPermission` method
	- we wanted something equivalent to `sleep_until(permits > 0);`..., got that with `cv.wait(m);`
	- designed to monitor the truth / falsity of a condition you need in order to proceed
	- `void notify_one();`: if there are multiple threads embedded in a wait call, pick one *at random* and allow it to proceed
		- think of these like push notifications to your phone
	- `cv.wait(m)`: don't want to go to sleep holding a lock! `wait` unlocks it for you
		- CPU intelligently removes lock when thread is swapped off CPU -- the thread thinks it always has permission
## `lock_guard`s
- `lock_guard<mutex> lg(m);`
	- used in place of `m.lock();` for more complex threading examples
	- no way to leave the function w/o unlocking, because of the way the destructor is defined
## `semaphore`s
- a class for the wait for / grant permission functionality
	- a wait & notify mechanism
	- a generic "resource counter" class

```
class semaphore {
public:
	semaphore(int count); // num available resources
	void wait(); // decrements count
	void signal(); // increments and notifies all
private:
	int count;
	mutex m;
	condition_variable_any cv;
}
```
- `wait` and `signal` used to support a new concurrency directive: **thread rendezvous**
	- a generalization of `thread::join`: allows one thread to stall (via `wait`) until another thread `signal`s
		- often `signal`ing thread just prepared some data that `wait`ing thread needed
	- example from [[Lecture 15 Slides - Multithreading, Condition Variables, and Semaphores.pdf|slides]]: reader / writer with finite circular buffer
		- without thread rendezvous:
			- nothing to inform the reader that the slot it wants to read has meaningful data written yet
			- nothing to prevent the writer from overwriting content that has yet to be read
		- solution: maintain two semaphores
			- `emptyBuffers`, initialized to 8, tracks number of slots that can be written to w/o clobbering as yet unread data
				- writer `wait`s on `emptyBuffers` to make sure space is available to write
				- reader `signal`s `emptyBuffers` when it's read
			- `fullBuffers`, initialized to 0, tracks number of slots that contain data that can be safely read
				- writer `signal`s `fullBuffers` when it writes
				- reader `wait`s on `fullBuffers` to make sure there is data to be safely read

```
static void writer(char buffer[], semaphore& full, semaphore& empty) {
	cout << oslock << "Writer: ready to write." << endl << osunlock;
	for (size_t i = 0; i < 320; i++) { // 320 is 40 cycles around the circular buffer of length 8
		char ch = prepareData();
		empty.wait(); // don't try to write to a slot unless you know it's empty
		buffer[i % 8] = ch;
		full.signal(); // signal reader there's more stuff to read
		cout << oslock << "Writer: published data packet with character '" << ch << "'." << endl;
	}
}

static void reader(char buffer[], semaphore& full, semaphore& empty) {
	cout << oslock << "\t\tReader: ready to read." << endl << osunlock;
	for (size_t i = 0; i < 320; i++) { // 320 is 40 cycles around the circular buffer of length 8
		full.wait(); // don't try to read from a slot unless you know it's full
		char ch = buffer[i % 8];
		empty.signal(); // signal writer there's a slot that can receive data
		processData(ch);
		cout << oslock << "\t\tReader: consumed data packet " << i << " with character '" << ch << "'."
	}
}
```

## Multithreading directives
1. Do minimal amount of work needed to remove deadlock
2. Try to lock down resources (critical regions) for as narrow a time window as possible