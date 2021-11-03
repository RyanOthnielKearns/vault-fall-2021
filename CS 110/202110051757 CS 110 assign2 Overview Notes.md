#CS #CS110 #assignment-overview
- to modify:
	- `inode.[ch]`
	- `file.[ch]`
	- `directory.[ch]`
	- `pathnum.[ch]`
- `unixfilesystems.[ch]` contains some useful constants you'll want to use
- inode layer
	- `inode.[ch]` and `ino.h`
	- `inode_iget`
		- searches inode table for inode number `inumber`, then places a copy of inode in the space addressed by `inp`
		- return 0 on success, -1 on error
		- hints
			- use `unixfilesystem` constants like inode size, location of starting inode sector
			- declare array of `struct inode` to pass to `diskimg_readsector`
	- `inode_indexlookup`
		- returns blocknumber of the inode's block of data number `fileBlockIndex`
		- must manage singly indirect and doubly indirect block numbers
		- hints
			- indirect block numbers contain 256 two-byte integers (use `uint16_t` type)
			- single and doubly indirect blocks have the same execution that should be replicated
		- large file: 7 singly indirect, 1 doubly indirect
		- small file: all direct
- file layer
	- `file.[ch]`
	- implement `file_getblock`
		- populates buffer `buf` with contents of block number `fileBlockIndex` of file at inode `inumber`
		- return number of meaningful bytes in that block that contribute to the payload of a file
			- will be 512 unless returning size of last (non-saturated) block, then less than 512
			- not the same as return val from `diskimg_readsector`, which will be 512 even if not all bytes are meaningful -- need to find file size and calculate

==at this point: try `./diskimageaccess -i <diskimagepath>` to verify inode tests pass==
- filename layer
	- `directory.[ch]`
	- gets info about single directory entry
	- `directory_findname`
		- look in directory at inode `dirinumber` for a directory entry that matches file name called `name`, then place directory entry in the space addressed by `dirent` (if it does find a matching entry)
		- hints
			- declare array of `struct direntv6`s instead of `char` array of length 512
			- use `strncmp` instead of `strcmp` because some directory names aren't `\0`-terminated
- pathname layer
	- `pathname.[ch]`
	- lookup file by absolute pathname
	- `pathname_lookup`
		- loop through each token in `pathname` until it finds the token at the end of the path
		- return inode number of final token
		- hints
			- iterative solution using `strlen`, `strcpy`, `strsep`, `directory_findname`

==at this point: try `./diskimageaccess -ip <diskimagepath>` to verify all tests tests pass==

- tests to be sure
	- don't use dynamic memory allocation
	- look at manpages
	- ==be sure valgrind runs without error!==