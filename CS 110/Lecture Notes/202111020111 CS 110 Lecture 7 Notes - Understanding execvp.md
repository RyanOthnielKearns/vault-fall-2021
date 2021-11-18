#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 7 Slides - Understanding execvp.pdf|slides]] and [[2021-10-04 Lecture Notes.pdf|handwritten notes]]
# Process Transformation
## `simplesh`
- implementation of a shell with the `fork`, `waitpid`, and `execvp` system calls
	- uses a read-eval-print loop (**REPL**), typically responding by *forking off child processes*
		- don't want to kill of terminal session when command is issued!
	- trailing `&` to a command means "run this in the background," giving you the command prompt immediately back

```
int main(int argc, char *argv[]) {
	while (true) {
		char command[kMaxCommandLength + 1]; // room for \0 as well
		readCommand(command, kMaxCommandLength);
		char *arguments[kMaxArgumentCount + 1];
		int count = parseCommandLine(command, arguments, kMaxArgumentCount);
		if (count == 0) continue;
		if (strcmp(arguments[0], "quit") ==) break; // hardcoded builtin to exit shell
		bool isbg = strcmp(arguments[count - 1], "&") == 0;
		if (isbg) arguments[--count] = NULL; // overwrite "&"
		pid_t pid = fork();
		if (pid == 0) execvp(arguments[0], arguments);
		if (isbg) { // background process, don't wait for child to finish
			printf("%d %s\n", pid, command);
		} else { // otherwise block until child process is complete
			waitpid(pid, NULL, 0);
		}
	}
	printf("\n");
	return 0;
}
```

## `xargs`
- useful when one program is needed to programmatically generate the argument vector for a second
- reads tokens from stdin -> appends tokens read to original argument list -> executes full list of arguments

Coded in C++:
```
int main(int argc, char *argv[]) {
	vector tokens;
	pullAllTokens(cin, tokens);
	char *xargsv[argc + tokens.size()];
	for (size_t i = 0; i < argc - 1; i++)
		xargsv[i] = argv[i + 1];
	for (size_t i = 0; i < tokens.size(); i++)
		xargsv[argc - 1 + i] = (char *) tokens[i].c_str();
	xargsv[argc + tokens.size() - 1] = NULL;
	execvp(xargsv[0], xargsv);
	cerr << xargsv[0] << ": command not found, so xargs can't do its job!" << endl;
	return 0;
}
```
- `execvp` called without `fork`!
	- this is because `xargs` is substituted by `argv[1]`, the command we really want to run -- everything before this point is just argument vector construction

# Interprocess Communication
## `pipe`
- `int pipe(int fds[]);`
	- takes an uninitialized array of 2 ints
	- populates file descriptors s.t. everything *written* to `fds[1]` can be *read* from `fds[0]`
		- this resource is like an unnamed file that only the OS / `pipe` know about
- useful for allowing parent processes to communicate with children
	- file descriptor table cloned across fork boundaries *and* preserved by `execvp` calls --> open file table entries referenced by `pipe` endpoints in both parent and child
	- anything printed to `fds[1]` readable from `fds[0]` in *both parent and child*
		- similarly, both parent and child able to publish text to their copies of `fds[1]`

```
int main(int argc, char *argv[]) {
	int fds[2];
	pipe(fds);
	pid_t pid = fork();
	if (pid == 0) {
		close(fds[1]);
		char buffer[6];
		read(fds[0], buffer, sizeof(buffer)); // assume one call is enough
		printf("Read from pipe bridging processes: %s.\n", buffer);
		close(fds[0]);
		return 0;
	}
	close(fds[0]);
	write(fds[1], "hello", 6);
	waitpid(pid, NULL, 0);
	close(fds[1]);
	return 0;
}
```
- make sure to close all write endpoints to pipes if not being used! otherwise read end will never know whether to expect more text