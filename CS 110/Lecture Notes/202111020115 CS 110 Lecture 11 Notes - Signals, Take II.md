#CS #CS110 #lecture-notes 
See [[Lecture 11 Slides - Signals, Take II.pdf|slides]] and [[2021-10-15 Lecture Notes.pdf|handwritten notes]]
2021-10-15
___
# Signals, Cont.
[[202111020114 CS 110 Lecture 10 Notes - Signals, Take I|Last lecture]]: signals
- for OS to tell process that something important happened
	- normally because the *process* did something bad
	- signal handler examines the state of the process to see what happened
- recall **asynchronous signals**
	- typically result from something external to process
	- typically handled on context switch (e.g. process hops on/off CPU)
	- difficult to use, and can be invoked at really bad times
		- **reentrant**: process is capable of calling itself recursively
			- `printf` calls `vsprintf`, which is not reentrant -- this can make asynchronous signal handling very dangerous with `printf`
		- can rarely predict when signal will arrive, and whether handler will execute during a window where memory space is inconsistent / incompatible
		- signal handler implementations should restrict themselves to only *signal-handler-safe functions*
			- very few `libc` functions in the list (and no `stdlibc++` functions)

## Solution for Signal Handling
- instead of signal handlers, handle all asynchronous signals of interest in main flow of execution
1. build set `sigset_t monitoredSignals` of signals we'd like to monitor
	- this set can travel through the `main` execution flow and always represent the set of signals we're paying attention to
2. inform OS to suspend delivery of these signals until further notice
	- `sigprocmask(SIG_BLOCK, &monitoredSignals, NULL);`
	- don't want any signals we're monitoring to invoke built-in behavior --> instead these signals are "deferred" or "pending"
3. call `sigwait`, which halts program execution until one of the signals being monitored arrives
```
int delivered;
sigwait(&monitoredSet, &delivered);
```
- at this point you can process the signal *inline* (*synchronously*)

### Reimagining the Disneyland example
Paying attention to two signal types:
1. `SIGCHLD`: OS delivers a `SIGCHLD` when children processes finish
2. `SIGALRM`: rely on `SIGALRM`s at 5-second intervals; otherwise `snooze(5)` around a `sigwait` call would interfere with our bookkeeping of number of children processes that have finished

```
static const size_t kNumChildren = 5;
static void constructMonitoredSet(sigset_t& monitored, const vector& signals) {
	sigemptyset(&monitored);
	for (int signal: signals) sigaddset(&monitored, signal);
}

static void blockMonitoredSet(const sigset_t& monitored) {
	sigprocmask(SIG_BLOCK, &monitored, NULL);
}

static void unblockMonitoredSet(const sigset_t& monitored) {
	sigprocmask(SIG_UNBLOCK, &monitored, NULL);
}

int main(int argc, char *argv[]) {
	cout << "Let my five children play while I take a nap." << endl;
	sigset_t monitored;
	constructMonitoredSet(monitored, {SIGCHLD, SIGALRM});
	blockMonitoredSet(monitored);
	for (size_t kid = 1; kid <= kNumChildren; kid++) {
		pid_t pid = fork();
		if (pid == 0) {
			unblockMonitoredSet(monitored); // lift block on signals, child may rely on them
			sleep(3 * kid); // sleep emulates "play" time
			cout << "Child " << kid << " tires... returns to dad." << endl;
			return 0;
		}
	}
	
	size_t numDone = 0;
	bool dadSeesEveryone = false;
	letDadSleep();
	while (!dadSeesEveryone) {
		int delivered;
		sigwait(&monitored, &delivered);
		switch (delivered) {
			case SIGCHLD:
				numDone = reapChildProcesses(numDone);
				break;
			case SIGALRM:
				wakeUpDad(numDone);
				dadSeesEveryone = numDone == kNumChildren;
				break;
		}
	}
	cout << "All children accounted for. Good job, dad!" << endl;
	return 0;
}
```

- Implementation of `reapChildProcesses` is the same as in the [[202111020114 CS 110 Lecture 10 Notes - Signals, Take I|previous lecture]]
- Keep looping and `sigwait`ing until we're confident dad as counted to 5
- `switch` on why `sigwait` returned and react accordingly at each iteration
- relies on `setAlarm`, `letDadSleep`, and `wakeUpDad` which rely on `setitimer` (see [[Lecture 11 Slides - Signals, Take II.pdf|lecture slides]] for implementation)