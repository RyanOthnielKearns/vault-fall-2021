#CS #CS110 #lecture-notes 
See [[Lecture 8 Slides - Pipes and Interprocess Communication, Take I.pdf|slides]] and [[2021-10-06 Lecture Notes.pdf|handwritten notes]]
# `pipe`
- from [[202111020111 CS 110 Lecture 7 Notes - Understanding execvp|last lecture notes]], too
- on `fork`, child inherits a properly wired file descriptor 1 (`STDOUT`) linked to the terminal
	- even on `exevcp` this file descriptor is preserved so the child process can print to the terminal screen
	- fd 0 --> `stdin`
	- fd 1 --> `stdout`
	- fd 2 --> `stderr`
	- Each of these ^ closed automatically when process exits
- can think of a pipe as a "virtual file" where data published to the write end (`fds[1]`) can by read from the read end (`fds[0]`)
	- pipe populates the vnode table with a buffer, trying to make pipe look like a regular file
	- vnode table entry operates as a "function lookup table" (for `read()` and `write()`) with some associated metadata
- *always remember to close access to pipe endpoints that aren't needed*
	- cleans up system resources
	- makes clear what a given process expects to do with the pipe (e.g. is it just reading? close the write end)
	- example from `subprocess` implementation:
		- parent closes writing file descriptor, reducing refcount to 0, to signify that no data will be written to that pipe again
		- this sends `EOF` to the child process reading data from the pipe

## Shell pipes
The `|` in terminal commands
- Allows standard ouput of the first process to feed standard input of the subsequent one
- `$ echo -e "peach\npear\napple" | sort | grep ea`
![[cs110-pipe-example.png]]
- `pipe` system call built to address this need!

# `dup2`
- `int dup2(int source, int target);`
- Rewires the `target` descriptor so it references the same open file table entry that `source` does
- Returns value of `target` or -1 if there was an error
- Traditional example:
```
dup2(fds[0], STDIN_FILENO);
close(fds[0]);
```
- this rewires STDIN to point to where `fds[0]` was pointing (the read end of some pipe)
	- the fact that file descriptor 0 (`stdin`) was rewired under the hood isn't visible to any function utilizing it (e.g. `scanf`, `getline`, `getc`, etc.)

![[cs110-dup2-pipe.png]]]