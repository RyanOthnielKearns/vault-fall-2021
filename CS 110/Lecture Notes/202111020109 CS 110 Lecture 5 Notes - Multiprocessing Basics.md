#CS #CS110 #lecture-notes 
See [[Lecture 5 Slides - Multiprocessing Basics.pdf|slides]] and [[2021-09-29 Lecture Notes.pdf|handwritten notes]]
2021-09-29
___
# System Calls
- **System calls** (syscalls): functions that user programs invoke to interact with OS, core to OS execution
	- `open`/`read`/`write`/`close`/etc.
	- Execute in a "privileged" or "superhuman" mode to access things hidden from user code --> OS needs different *call and return model*
- Each process operates as if it owns all of main memory
	- 64-bit addressing means $2^{64}-1$ bits to address -- way more than any program would actually use
	- Top 1/2 to 1/4 of address space relegated to OS for system call info
		- Sits above user code segment (e.g. data --> heap --> user stack blocks)
			- Recall that user stack grows "downwards," away from protected system call space
				- User function call and return protocol does not privatize memory used by functions
				- Stack frames can use pointer arithmetic to advance beyond their frames, examining or updating the data in their callers
				- Privacy issue to have system call functions exhibit this behavior...
		- Cannot dereference *any* pointer up here -- private to the OS
			- Activation records for system calls cannot be exposed or accessible to user programming
			- Means system call functions need to be executed in a "superuser" mode

# Creating and Coordinating Processes
Now: **multiprocessing**: OS does things concurrently

## `fork`
- New system call to spawn new processes
	- Called once, returned twice
- Works in tandem with `getpid` and `getppid`
```
int main(int argc, char *argv[]*) {
	printf("Greetings from process %d! (parent %d)\n", getpid(), getppid());
	pid_t pid = fork();
	assert(pid >= 0);
	printf("Bye-bye from process %d! (parent %d)\n", getpid(), getppid());
	return 0;
}
___
Greetings from process 29686! (parent 29351)
Bye-bye from process 29686! (parent 29351)
Bye-bye from process 29687! (parent 29686)
```
- `fork` synthesizes a nearly identical copy of the parent process for the child process, which picks up right after the `fork();` line
	- All data / stack / heap / text
	- All open file descriptors replicated
		- Reference counts within the relevant open file table entries are promoted
	- Returns `0` within the child process, and the child's PID in the parent
	- No *default* sharing of data between the two processes, though this can be set up before calling `fork()`

## `waitpid`
- `pid_t waitpid(pid_t pid, int *status, int options);`
- donates child process-oriented resources back to the system
```
int main(int argc, char *argv[]) {
	printf("Before.\n");
	pid_t pid = fork();
	printf("After.\n");
	if (pid == 0) {
		printf("I am the child, parent will wait for me.\n");
		return 110;
	} else {
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			printf("Child exited with status %d.\n", WEXITSTATUS(status));
		} else {
			printf("Child terminated abnormally.\n");
		}
		return 0;
	}
}
___
Before.
After.
After.
I am the child, parent will wait for me.
Child exited with status 110.
```