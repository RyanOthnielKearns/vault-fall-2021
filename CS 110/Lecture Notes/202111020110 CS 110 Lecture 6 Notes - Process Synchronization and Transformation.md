#CS #CS110 #lecture-notes 
See [[Lecture 6 Slides - Process Synchronization and Transformation.pdf|slides]] and [[2021-10-01 Lecture Notes.pdf|handwritten notes]]
2021-10-01
___
# System Calls
From [[202111020109 CS 110 Lecture 5 Notes - Multiprocessing Basics|last time]]:
- `fork`
	- not a blocking system call
	- process can `fork` multiple times, provided it reaps the child processes (in any order)
		- a **zombie** is a child process that has terminated without being reaped by the parent process
	- implies a *deep* clone -- even the random number seed will be the same!
- `waitpid`
	- used to block a process until a child process finishes (or stops, or continues)
	- called like `waitpid(pid, &status, 0);`
		- `int status` is a 32-bit vector including things like exit status
			- can pass `NULL` if info not needed
		- returns pid of the process that successfully exited, or -1 if it fails
		- when -1 is passed for `pid`, we wait for *any* child as it exits
	- deallocates a zombie's process control block and removes all traces from OS

## `execvp`
- `int execvp(const char *path, char *argv[]);`
	- `path` and `argv[0]` generally the same thing
- effectively reboots a process to run a different program from scratch
	- child is completely "cannibalized" w/ new stack, heap, etc. and entry into executable's main frame
- returns -1 if the executable fails
- *does not return* if the executable succeeds, because *there's nothing to return to*
	- everything from the original child has been killed off, including the call to `execvp` itself

```
static void mysystem(char *command) {
	pid_t pid = fork();
	if (pid == 0) {
		char *arguments[] = {"/bin/sh", "-c", command, NULL};
		execvp(arguments[0], arguments);
		printf("Failed to invoked /bin/sh to execute the supplied command.\n");
		exit(0);
	}
	int status;
	waitpid(pid, &status, 0);
}
```
- don't bother checking the return value of `execvp` -- if it returns at all, it will be -1