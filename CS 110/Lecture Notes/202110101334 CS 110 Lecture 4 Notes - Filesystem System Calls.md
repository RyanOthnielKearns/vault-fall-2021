#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 4 Slides - Filesystem System Calls.pdf|slides]] and [[2021-09-27 Lecture Notes.pdf|handwritten notes]]
___
# Unix Filesystems
- `.` is the current directory
- `..` is the parent directory
- **File permissions** string: 10-digit octal `drwxr-xr-x`
	- `d` = directory
	- `r` = read permission
	- `w` = write permission
	- `x` = execute permission
	- After first `d` or `-`, remaining 9 digits split into 3 groups of 3 permissions sets:
		1. file owner permissions
		2. group permissions (e.g. Stanford)
		3. other (worldwide) permissions
	- use base 8:
		- `rwx r-x r-x`
		- `111 101 101`
		- `7   5   5  `
		- permission number 755

## System Calls
- requests to open files, read files, extend heap, etc. go through **system calls**
- system calls interact directly with OS on your behalf
- OS **kernel** executes code of system call
### `open`
```
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```
- flags should be bitwise `OR`'d together
	- include 1 of the following flags:
		- `O_RDONLY` for read only
		- `O_WRONLY` for write only
		- `O_RDWR` for read and write
	- also:
		- `O_CREAT`: create file if doesn't exist
			- when using, include third argument to specify file's permission set
		- `O_EXCL`: mandate file be created from scratch -- fail if file exists
- example: `int fd = open(kFilename, O_WRONLY | O_CREAT | O_EXCL, 0664);`

### `close`
Companion system call to open that releases the provided file descriptor returned by `int open(...)`
- closing file descriptors allows future open calls and other syscalls to use them

### `read`
```
ssize_t read(int fd, char buf[], size_t len);
```
- blocks execution until at least 1 byte available to read
- returns 0 when no more bytes to read (e.g. reached end of file or descriptor was closed)

### `write`
```
ssize_t write(int fd, char buf[], size_t len);
```
*May return a value less than `len`*!! In this case system couldn't write all bytes at once for some reason
- See code on [[Lecture 4 Slides - Filesystem System Calls.pdf|slides]] (slide 8) that handles this condition with a `while(true)` loop

## The File Descriptor Abstraction
- low-level access to data streams -- no higher-level data structures
	- very fast
- `FILE` points and C++ `iostream`s work well when working with standard output, standard input, and local files
	- Not so good with bytestreams from network connections
- `STDIN_FILENO`: built-in constant for 0, the descriptor normally linked to standard input
- `STDOUT_FILENO`: constant for 1, the descriptor bound to standard output

## Filesystem Data Structures
![[filesystem-data-structure.png]]
all of these are kernel-resident, so the user doesn't have direct access, only through syscalls
### Process Control Blocks
- stored in the **process table**
- stores **descriptor table**
	- maintains set of descriptors (indices to descriptor table)
		- these link to **open file table** entries
	- reserved descriptors
		- 0 -> standard input
		- 1 -> standard output
		- 2 -> standard error
### Open File Table
- singular system-wide table
- each entry tracks:
	- `mode`: reading, writing, or both
	- `cursor`: position within the file payload
	- `refcount`: number of descriptors across all processes referring to that entry (since file table entries are shared by all processes)
	- `vnode`
### Vnode Table
a `vnode` is a structure for static info about a file resource
- file type (regular file, directory, symlink, terminal)
- refcount
- (maybe) copy of the inode that resides on the filesystem
- basically an "inode cache"

singular, system-wide vnode table