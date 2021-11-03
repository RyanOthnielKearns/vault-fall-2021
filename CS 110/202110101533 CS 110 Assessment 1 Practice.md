# Question 1
## Attempt
```
int read_line(int fd, char *buf, int buf_len) {
     // reads up to and including a newline (or EOF) from fd
     // replaces newline with null terminator
     // only reads up to buf_len - 1 bytes
     // @param fd: the file descriptor to read from
     // @param buf: the buffer to populate
     // @param buf_len: the size of the buffer
     // @return: the number of bytes read, not including
     //          the newline. Can be 0 if at end of file

	ssize_t bytesRead = read(fd, buf, buf_len);
	if (bytesRead == 0) return bytesRead;
	strsep(&buf, "\n");
	return bytesRead;
}
```
## Answer
```
int read_line(int fd, char *buf, int buf_len) {
    int bytes_read = 0;
    while (bytes_read < buf_len - 1) {
        int actually_read = read(fd, buf + bytes_read, 1);
        if (actually_read == 0 || buf[bytes_read] == '\n') break;
        bytes_read++;
    }
    buf[bytes_read] = '\0';
    return bytes_read;
}
```
==Forgot the `while` loop component -- remember to continue until you assert that you read everything you needed to!==
- this solution also reads one byte at a time to ensure that each can be manually checked to be `\n`

# Question 2
## a)
### Attempt
Suppose we choose to store entries in a directory in sorted order. This has the benefit of reducing name-lookup from a linear to a binary search problem, which means a reduction from linear time lookup to logarithmic time. At the same time, adding entries to the directory will no longer be a constant time operation, and will instead take linear time as you need to move directory entries if they're lexographically greater than the entry you're trying to add.
### Answer
A benefit is quicker lookup of an entry, as we can use binary search to search for an entry name rather than looping over each entry. A drawback is when we add or rename directory entries, we must potentially re-sort the elements, which is extra work as opposed to the unsorted version.
## b)
### Attempt
One benefit is that with more block numbers, more files get to count as "small," so we reduce our reliance on indirect block numbers which take up additional space in the hard drive in the "payload" section after the inode table. A drawback is that inodes are now larger in size, meaning you can fit fewer per sector and will probably have to increase the size of the inode table, reducing the overall size available to store payloads.
### Answer
One benefit of this is files are stored more directly, as we can fit more block numbers directly (or indirectly) in an inode. A drawback of this is more space may be taken up on disk by non-file data.
## c)
### Attempt
- 0 - 255 (assuming block indices are stored with 2 bytes each)
- `7 * 256` - `7*256 + (256^2)-1`
### Answer
The first singly-indirect block in this case would hold file block numbers 0 - 255, inclusive. The doubly-indirect block in this case would hold block numbers 7 * 256 through 7 * 256 + 256 * 256 - 1, inclusive.
# Question 3
## a)
### Attempt
```
/* Function: writeBuf
 * ------------------
 * Writes the contents of buf with size len to the file descriptor fdOut
 * @param fdOut - the file descriptor where the data will be written
 * @param buf - the buffer to write
 * @param len - the number of bytes in the buffer
 */
void writeBuf(int fdOut, char *buf, ssize_t len) {
    ssize_t bytesWritten = 0;
	while (bytesWritten < len) {
		bytesWritten += write(fdOut, buf + bytesWritten, len - bytesWritten);
		
	}
	close(fdOut);
	return 0;
} 
```
### Answer
```
void writeBuf(int fdOut, char *buf, ssize_t len) {
    ssize_t bytesWritten = 0;
    while (bytesWritten < len) {
        bytesWritten += write(fdOut, buf + bytesWritten, len - bytesWritten);
    }
}
```
## b)
### Attempt
```
/* Function: dualEcho
 * ------------------
 * Writes all input from fdIn to both fdOut1 and fdOut2
 * @param fdIn - the file descriptor to read from (until EOF)
 * @param fdOut1 - the first output file descriptor (ignore if -1)
 * @param fdOut2 - the second output file descriptor (ignore if -1)
 */
void dualEcho(int fdIn, int fdOut1, int fdOut2) {
    ssize_t bytesRead;
	char buf[1];
	while((bytesRead = read(fdIn, &buf, 1)) != 0) {
		if (fdOut1 != -1) {
			ssize_t bytesWritten = 0;
			while (bytesWritten < 1)
				bytesWritten = writeBuf(fdOut1, &buf, 1);
		}
		if (fdOut2 != -1) {
			ssize_t bytesWritten = 0;
			while (bytesWritten < 1)
				bytesWritten = writeBuf(fdOut2, &buf, 1);
		}
	}
}
```
### Answer
```
void dualEcho(int fdIn, int fdOut1, int fdOut2) {
    // read from fdIn and echo to fdOut1 and fdOut2
    // if either fdOut1 or fdOut2 are -1, don't write
    char buf[1024];
    while (true) {
        ssize_t bytesRead = read(fdIn, buf, sizeof(buf));
        if (bytesRead <= 0) break;
        if (fdOut1 != -1) {
            writeBuf(fdOut1, buf, bytesRead);
        }
        if (fdOut2 != -1) {
            writeBuf(fdOut2, buf, bytesRead);
        }
    }
}
```
- you don't need `char buf[]` to only have size 1, because you will read everything you can and only write that amount by specifying `bytesRead`
- also handle the case that `bytesRead` returns < 0, not just 0, in the event of an error to break

# Question 4