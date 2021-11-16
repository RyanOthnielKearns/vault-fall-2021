#CS #CS110 #lecture-notes 
See [[Lecture 16 Slides - Multithreading and Networking.pdf|slides]] and [[CS 110 Lecture 16 Notes - Multithreading and Networking (2021-10-27).pdf|handwritten notes]]
2021-10-27
___
# Semaphores, cont.
Continuing from [[CS 110 Lecture 15 Notes - Multithreading, Condition Variables, and Semaphores (2021-10-25).pdf|last lecture]]
- not yet in g++ and clang10 (but should be in 2021)
- can imitate multiprocessing mode & signal that I've gotten to some point in my execution
	- "pass a baton in a relay race"
	- like in trace assignment:
		- parent: `waitpid(pid, NULL, WUNTRACED);`
		- child: `raise(SIGSTOP);`
- The reader-writer example from [[202111151356 CS 110 Lecture 15 Notes - Multithreading, Condition Variables, and Semaphores (2021-10-25)|lecture 15]] is actually covered in [[CS 110 Lecture 16 Notes - Multithreading and Networking (2021-10-27).pdf|this lecture's handwritten notes]]

# Load Balancer example
- `myth-buster` code on slides
	- uses a `semaphore` to limit the number of threads
	- each signal is called like `permits.signal(on_thread_exit);`, which schedules the signal when the thread's execution terminates (since semaphore is tracking num. active threads)
- sequential vs. concurrent versions
	- most of the time on myth is spent *waiting to be scheduled* or establishing a network connection
		- multithreading aligns the dead times for each network connection so they can happen in parallel
	- this allows the number of threads per CPU to be higher than w/ more CPU-intensive multithreading applications