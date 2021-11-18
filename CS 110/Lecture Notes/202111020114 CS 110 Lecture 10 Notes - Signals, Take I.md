#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 10 Slides - Signals, Take I.pdf|slides]] and [[2021-10-11 Lecture Notes.pdf|handwritten notes]]
2021-10-11
___
# Introduction to Signals
- **signal**: a small message that notifies a process that an event occurred
	- higher-level software form -- *exceptional control flow*
- e.g. dereferencing a `NULL` pointer sends a `SIGSEGV` signal
- each signal represented internally with a number
- also used to expose lower-level hardware exceptions to user processes

## Signal Types
- `$ kill -TSTP [pid#]`: temporary stop (like ^Z, stops without terminating)
- `$ kill -CONT [pid#]`: continue
- `$ kill -INT [pid#]`: interrupt (like ^C)
- `SIGFPE`: floating point signal (for integer / FP divide by 0) that immediately terminates the program
- `SIGPIPE`: when process attempts to publish to write end of pipe after read end has been closed
- `SIGILL`: process attempts to execute an illegal assembly code instruction
- `SIGALRM`: for when user program sets times like with `setitimer`
- `SIGCHLD`: OS sends to parent if child process stops, ends, restarts, etc.

## Signal Handlers
ordinary functions run when signals come in
- some signals handled **synchronously**
	- installed signal handler executed *immediately*
	- generally process has done something bad to iself (div0, null ptr, etc.)
	- called "traps"
- other signals handled **asynchronously**
	- generated outside of the process, no clear emergency w/in process
	- e.g. CTRL-C to create a SIGINT
	- often generated when target process is off CPU --> signal handler executed as soon as process gets back on the CPU
	- called "interrupts"
- take a single argument (the signal being handled)
```
static void handleSIGSEGV(int sig) {
	assert(sig == SIGSEGV);
	cout << "There's no recovering from this." << endl;
	exit(139); // as per https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples
} // SIGSEGV handlers should still end the program.

int main(int argc, char *argv[]) {
	signal(SIGSEGV, handleSIGSEGV);
	*(int *)NULL = 110;
	return 0;
}
```

## `SIGCHLD`
- important for multiprocessing!
- by default, ignored (we've been ignoring it in previous `fork` examples...)
- allows forked child processes to run in the background while the parent does meaningful work, w/o blocking with a `waitpid` call
	- but parent process is still required to reap child process resources
	- parent typically registers custom `SIGCHLD` handler
		- almost always include calls to `waitpid` to surface pids of child processes that have changed state (`waitpid` isn't really optional!)
- PCB contains return info when a process returns from `main`

### Disneyland example
```
static const size_t kNumChildren = 5; // constant
static size_t numDone = 0;            // global variable!

int main(int argc, char *argv[]) {
	cout << "Let my five children play while I take a nap." << endl;
	signal(SIGCHLD, reapChildProcesses);
	for (size_t kid = 1; kid <= kNumChildren; kid++) {
		pid_t pid = fork();
		if (pid == 0) {
			sleep(3 * kid); // sleep emulates "play" time
			cout << "Child " << kid << " tires... returns to dad." << endl;
			return 0;
		}
	}

	while (numDone < kNumChildren) {
		cout << "At least one child still playing, so dad nods off." << endl;
		snooze(5); // signal-safe version of sleep
		cout << "Dad wakes up! ";
	}
	
	cout << "All children accounted for. Good job, dad!" << endl;
	return 0;
}
```
- `reapChildProcesses` designed to handle each `SIGCHLD` signal delivered as child process exits
- signal prototype doesn't allow for state to be shared via params, so we have to use global vars

```
static void reapChildProcesses(int unused) {
	waitpid(-1, NULL, 0);
	numDone++;
}
```
- problem? CPU maintains `SIGCHLD` to be handled as `bool`, not `int` (or count in general)
	- so we can't just wait for 1 to finish
	- if multiple finish at the same time, we will only see one!

```
static void reapChildProcesses(int unused) {
	while (true) {
		waitpid(-1, NULL, 0);
		if (pid < 0) break;
		numDone++;
	}
}
```
- further improving -- can we tell `waitpid` to reap child that have exited but *return without blocking*, even if more children are running?

```
static void reapChildProcesses(int unused) {
	while (true) {
		waitpid(-1, NULL, WNOHANG);
		if (pid <= 0) {
			assert(pid == 0 || errno == ECHILD);
			break;
		}
		numDone++;
	}
}
```
- if calling process has no more children, `waitpid` returns -1 and sets `errno` to `ECHILD`

### `SIGCHLD` Handlers
- Generally have the `while (true)` loop structure shown above
- a return value of -1 generally means "no more child processes left"
- a return value of 0 means there are other child processes, but we're returning instead because of `WNOHANG`
	- `waitpid` flags `WUNTRACED | WCONTINUED | WNOHANG` asks `waitpid` to return info about a child process that has changed state *at all*, but do so *without blocking*

## `kill` and `raise`
- `int kill(pid_t pid, int sig);`
	- Send another process a signal
- `int raise(int sig);`
	- Send yourself a signal
	- also `kill(getpid(), sig);`
- when pid is positive, the target is the process with that pid
- when pid is negative < -1, the targets are processes within the process group $abs(\texttt{pid})$

## Signal Handling Drawbacks
- signal handlers difficult to use properly
- can be invoked at really bad times (e.g. mid-`malloc` call, or accessing a complex data structure)