#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 14 Slides - Threads, Deadlock, Condition Variables.pdf|slides]] and [[2021-10-22 Lecture Notes.pdf|handwritten notes]]
2021-10-22
___
# More on Mutexes
began [[202111151153 CS 110 Lecture 13 Notes - Threads and Mutexes (2021-10-20)|last lecture]]
- mutual exclusion: a "synchronization primitive"
- like a lock on an open door

```
mutex m;
m.lock();
[critical region]
[...]
[critical region]
m.unlock();
```
- at `m.unlock()` -- another thread waiting on `m.lock()` at this point can proceed, "taking the lock"
	- this does not depend on which thread arrived at the lock first! maintained as a set, not a queue, of waiting threads
- typically named like `mutex varBeingProtectedLock;`
- pass mutexes *by reference*
	- `ref(mLock)` in thread constructor and `mutex& mLock` in function signature
- **deadlock**: all threads are "stuck" (maybe at an `m.lock()`) and the program cannot proceed
- point of a mutex is to prevent a thread from getting a stale old value of a variable
	- not necessary if all threads only *reading* the variable!
- **goal**: make the critical region *as small as possible* while maintaining that the solution works

# The Dining Philosophers Problem
- canonical multiprocessing example about deadlock and how to avoid it
	- Five philosophers sit around a table, each in front of a big plate of spaghetti.
	- A single fork (utensil, not system call) is placed between neighboring philosophers.
	- Each philosopher comes to the table to think, eat, think, eat, think, and eat. That's three square meals of spaghetti after three extended think sessions.
	- Each philosopher keeps to himself as he thinks. Sometime he thinks for a long time, and sometimes he barely thinks at all.
	- After each philosopher has thought for a while, he proceeds to eat one of his three daily meals. In order to eat, he must grab hold of two forks—one on his left, then one on his right. With two forks in hand, he chows on spaghetti to nourish his big, philosophizing brain. When he's full, he puts down the forks in the same order he picked them up and returns to thinking for a while.

## Deadlock threat
- if all five philosophers pick up their left forks, they are left forever waiting on the right fork to become available
![[philosophers-deadlock.png]]
- one way to check for concurrency issues: *you should be able to put `sleep()` calls anywhere in a thread routine and not introduce problems*
	- `sleep()` calls like this aren't creating problems, rather *exposing* them

### Preventing deadlock
- implant directives to limit the number of threads competing for a shared resource (like forks)
	- a **permission slip** or **permit**
	- it's impossible for 3 philosophers to be eating at once --> impose a limit of 2 eating at a time
	- also, could let 4 philosophers (at most) grab forks, knowing that at least one would succeed in grabbing both
		- *rationale*: implant the *minimal* amount of bottlenecking needed to remove deadlock

## Coding the Dining Philosophers Problem
- model philosophers as an array of `thread`s
- model forks as array of `mutex`es
	- rely on `mutex::lock` to model a thread-safe grab, and `mutex::unlock` to model a thread-safe release
- introduce the permit using a counter (`permits`) and companion mutex (`permitsLock`) for safe incrementing / decrementing
	- permits are manipulated using functions `waitForPermission` and `grantPermission`
```
static void waitForPermission(size_t& permits, mutex& permitsLock) {
	while (true) {
		permitsLock.lock();
		if (permits > 0) break;
		permitsLock.unlock();
		sleep_for(10);
	}
	permits--;
	permitsLock.unlock();
}

static void grantPermission(size_t& permits, mutex& permitsLock) {
	permitsLock.lock();
	permits++;
	permitsLock.unlock();
}
```
- giving a permission slip back (`grantPermission`) is straightforward
- implementation of `waitForPermission` is awkward -- relies on **busy waiting**, taking short naps until we see a permit is available
	- would be better if the thread could sleep until we knew a permit was available
		- a thread calling `grantPermission` could notify it
		- requires a new concurrency directive for thread communication, analagous to signals and `sigwait`

# Condition Variables (`condition_variable_any` class)
```
class condition_variable_any {
public:
	void wait(mutex& m);
	template  void wait(mutex& m, Pred pred);
	void notify_one();
	void notify_all();
};
```

With condition variables, we can modify the `waitForPermission` and `grantPermission` implentations to remove the reliance on busy waiting
```
static void waitForPermission(size_t& permits, condition_variable_any& cv, mutex& m) {
	lock_guard<mutex> lg(m);
	while (permits == 0) cv.wait(m);
	permits--;
}

static void grantPermission(size_t& permits, condition_variable_any& cv, mutex& m) {
	lock_guard<mutex> lg(m);
	permits++;
	if (permits == 1) cv.notify_all();
}
```
- `lock_guard`: convenience class
	- constructor calls `lock` on the supplied mutex
	- destructor calls `unlock` on the same mutex
	- used to ensure mutex is released no matter how the function exits (useful if the control flow is sophisticated)
- in `grantPermission`: thread-safe increment `permits`
	- if `permits` *was* 0: possible other threads were waiting on it (w/ `cv.wait(m)`) -- so wake them up with `cv.notify_all()`
- `waitForPermission` requires a `while` loop instead of an `if` test
	- possible that the permit made available is immediately consumed by the thread that just returned it
	- generally: just because the thread awoke from `cv.wait(m)`, doesn't always mean that the condition has become true
- when the thread manager wakes up a thread sleeping on `cv.wait(m)`, it mandates that the thread *reacquire the lock on `m`*
- when going to sleep with `cv.wait(m)`, thread manager has the thread release the lock on `m`
- `wait` template method: these two are equivalent:
	1. `while (!(permits > 0)) cv.wait(m);`
	2. `cv.wait(m, [&permits] { return permits > 0; });`

# Semaphores
- tracking a resource count in dining philosophers example: done w/ combination of `size_t`, `condition_variable_any`, and `mutex`
- **`semaphore`** class generalizes this behavior

```
semaphore::semaphore(int val): value(val) {}

void semaphore::wait() {
	lock_guard<mutex> lg(m);
	cv.wait(m, [this] { return value > 0; })
	value--;
}

void semaphore::signal() {
	lock_guard<mutex> lg(m);
	value++;
	if (value == 1) cv.notify_all();
}
```
- `semaphore::wait` $\approx$ `waitForPermission`
- `semaphore::signal` $\approx$ `grantPermission`
- `cv.wait` includes `[this]` as capture clause
	- the anonymous predicate function supplied to `wait` is *just a regular function* -- not entitled to examine the `private` state of the `semaphore` object
	- `this` effectively converts the `bool`-returning function to a `bool`-returning `semaphore` method