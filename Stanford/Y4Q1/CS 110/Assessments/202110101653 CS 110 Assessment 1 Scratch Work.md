#CS #CS110 #midterm #exam
# Q1
The last-modified timestamp is only update for assign1 and not the parent directory, solutions, because only the payload for assign1 had to change. Creating search-helper.cc required there to be an addition to the assign1 file payload (since a directory is "just" a file) -- specifically, a row for this new directory entry and corresponding inode number was appended. In solutions, by contrast, the immediate file contents are the exact same, so there is no modification needed to the solutions file payload.

# Q2
The d_name property for struct direntv6 objects is a char array of length 14, which limits the length of file or directory names to at most 14 characters. "antiferromagnetism" is 18 characters. The match is produced when the line

strncmp(dirEnt->d_name, name, MAX_COMPONENT_LENGTH) == 0)

returns true for the 14-character directory entry name "antiferromagne" (since strncmp stops comparing at character 14 defined by the macro MAX_COMPONENT_LENGTH).

# Q3
Each directory has a payload containing some number of struct direntv6 entries: Directory "doris/turned" would have 3 struct direntv6 entries: - d_name = ".\0"; d_inumber = 2017 (inode number for "doris/turned") - d_name = "..\0"; d_inumber = 2016 (inode number for "doris") - d_name = "five\0"; d_inumber = 2018 (inode number for "doris/turned/five") Next, directory "doris/turned/five" would also have 3 directory entries: - d_name = ".\0"; d_inumber = 2018 (inode number for "doris/turned/five") - d_name = "..\0"; d_inumber = 2017 (inode number for "doris/turned") - d_name = "today\0"; d_inumber = 2019 (inode number for "doris/turned/five/today") Finally, directory "doris/turned/five/today" would have 2 directory entries: - d_name = ".\0"; d_inumber = 2019 (inode number for "doris/turned/five/today") - d_name = "..\0"; d_inumber = 2018 (inode number for "doris/turned/five")

# Q4
- The pathname layer would not have to change with either proposal, provided the behavior of the directory-level method directory_findname and struct direntv6 was the same.
- The directory layer would obviously have to change with both, since the search part of directory_findname should be modified for the new storage formats (i.e. no longer search linearly).
- The file layer would not change meaningfully since file payloads (including directory payloads, though changed) would still be accessed from blocks in the same way.
- The inode layer would not change

The file descriptor table <> open file table separation is beneficial because there is a many-one mapping between open file descriptors across different processes and open file entries. For example, all processes open file descriptors to standard inputs, output, and error using fd's 0, 1, and 2, so a shared open file table lets them all alias the same open file entries. This also simplifies how refcounts for open file entries are updated and how multiple processes can write to the same session, like both make and g++ writing to the same terminal window.

The open file table <> vnode table separation is also beneficial because of a many-one mapping. For example, two file descriptors might open the same file resource (and thus vnode entry) in different modes, like one reading and one writing. Also, terminals have vnode entries, so stdin, stdout, and stderr file descriptors should all point to that same resource. Finally, since vnodes cache inode data in-memory, separating these tables reduces memory usage by allowing different open file entries to alias the same underlying resource without unnecessary copying.