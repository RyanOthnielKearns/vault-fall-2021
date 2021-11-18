#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
# Overview
- discussing Unix v6 file system design principles
	- assign2 is a variant of it
	- filepath resolution -- v. similar to resolving domain names for IP addresses

# File Systems
contiguous stretch of memory to store info
- like RAM!
	- info in RAM is byte-addressable: must read 8-bits at a time
	- default memory units in hard drives are **sectors** ("sector-addressable")
		- ~512 bytes (but not always)
		- must read/write all 512 at once
![[sector-conceptually.png]]
- drives export an API (hardware API) (software abstraction)
	- we need to take this system and "invent" document storage
```
class Drive {
public:
	size_t getNumSectors() const;
	void readSector(size_t num, void *data) const;
	void writeSector(size_t num, const void *data);
}
```
- **sector** = physical storage unit on hard drive
	- related: **block**: comprised of one or more sectors (FS does operations in terms of these)
	- in Unix v6 each block is 1 sector, so interchangable

## Structure
![[file-system-structure.png]]
### Metadata
- **boot block**: block 0
	- contains info about hard drive used when booting the OS
- **superblock**: block 1
	- contains info about file system overlaying hard drive, like inode size etc.
- **inode table**: stores info about each file stored in the FS
	- starts at block 2
	- inodes are 32 bytes -> inode table block stores 16 inode entries side-by-side

### File contents
- files stored in 512 byte (block size) quantums
	- last block to store file is partial if size is not multiple of 512, but can determine # of meaningful bytes from file size (`size % 512`)
#### inodes
```
struct inode {
	size_t size;
	ushorts blocknums[8];
	byte type;
}
```
- 32-byte data structures that store metainfo about single files
	- file owner
	- file permissions
	- file size
	- etc.
	- sequence of blocks storing payload
	- why not the filename?
		- filenames are long (incl absolute path, e.g. `/usr/class/cs110/staff/master_repos/assign1/imdb.cc`)
##### Direct vs. Indirect addressing
- using 8 block numbers, maximum file size is `8 * 512 = 4096` bytes
- instead: **singly-indirect addressing**: each inode block number points to a block containing blocknums of the file payload
	- 8 singly-indirect blocks ->
		- each singly-indirect block holds `512 / 2 = 256` block numbers (if block numbers stored with 2 bytes, like unsigned shorts) ->
			- max file size: `8 * 256 * 512 = 1,048,576` bytes = `1` MB
- look at bitflag stored in inode to check whether addressing scheme is "small" (all direct addressing) or "big"
- Unix v6 has 8th block number store a **doubly-indirect** block number: points to a block of `512 / 2 = 256` singly-indirect blocks
	- makes total file size: `(7 * 256 * 512) + (1 * 256^2 * 512) = 34,471,936` bytes = `34` MB

#### Directories
- just like files
- payload: 16-byte entries forming a table mapping names to **inode numbers** (positions in the inode table)
	- 14 bytes for file name, 2 for inode number (unsigned short)
	- inode number to block number: `SECTOR_NUM = (INODE_NUM - 1) / 16`
		- 16 inodes per block (of size 512)
		- inode numbers start at 1, not 0 (root dir `/` has inode number 1)