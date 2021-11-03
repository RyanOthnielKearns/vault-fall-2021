#CS #CS110 #lecture-notes 
See [[Lecture 9 Slides - Pipes and Interprocess Communication, Take II.pdf|slides]] and [[2021-10-08 Lecture Notes.pdf|handwritten notes]]
# Interprocess Communication, Cont.
## `dup`
Different system call from `dup2`
- `int dup(int source);`
- Allocates a new descriptor to reference the same file session as source
- With `dup2`, you decide the target descriptor number

## `pipeline` example
A binary Unix pipeline
- `void pipeline(char *argv1[], char *argv2[], pid_t pids[]);`
	- `argv1` and `argv2` are `NULL`-terminated argument vectors
	- `pids` is the base addr of an array of length 2
```
void pipeline(char *argv1[], char *argv2[], pid_t pids[]) {
	int fds[2];
	pipe(fds);
	pids[0] = fork();
	if (pids[0] == 0) {
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execvp(argv1[0], argv1);
	}
	close(fds[1]); // was only relevant to first child, so close before second fork
	pids[1] = fork();
	if (pids[1] == 0) {
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		execvp(argv2[0], argv2);
	}
	close(fds[0]);
}
```
- two child processes are  created to run executables identified by `argv1` and `argv2`
- `pipe` call must come before the `fork` calls, because pipe endpoints need to exist when children are created
- first child
	- closes `fds[0]` immediately, since it's not needed
	- `fds[1]` is closed after `dup2` rewires the child's standard output to that location (write end of the pipe)
- parent can close `fds[1]` before the second child since it won't use it
- second child
	- standard input rewired to the read end of the pipe (`fds[0]`), which is then closed

## `O_CLOEXEC` flag
Given to `pipe2` as in `pipe2(fds, O_CLOEXEC)`
- lots of close calls in the `pipeline` example
- with this flag, fds marked as "self-closing on `execvp` boundaries"

# Preamble to Signals
- processes start, cycle on/off CPU, and terminate
- can also be paused at arbitrary points! using **job control signals**
	- used programmatically to synchronize between processes

## `SIGSTOP`/`SIGCONT`
- `SIGSTOP` pauses a process, `SIGCONT` continues it
```
// Pause PID 1234
kill(1234, SIGSTOP;
// Resume PID 1234
kill(1234, SIGCONT);
```

## With `waitpid`
`waitpid` can be used to observe when a program changes job control states (exits / crashes / stops / continues)
- managed with `flags` parameter
	- `WUNTRACED`: tells `waitpid` to return when process in wait set continues or exits
		- `pid_t pid = waitpid(-1, &status, WUNTRACED);`
	- `WCONTINUED`: tells `waitpid` to return when process in wait set either continues or exits
		- `pid_t pid = waitpid(-1, &status, WCONTINUED);`
	- For any state change whatsoever: pass `WUNTRACED | WCONTINUED`