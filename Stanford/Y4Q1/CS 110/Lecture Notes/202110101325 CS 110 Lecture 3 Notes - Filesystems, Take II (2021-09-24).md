#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
# Design Principles
## Modularity & Layering
### Modularity
- larger system divides into smaller subsystems, which divide into smaller sub-subsystems

### Layering
- modular layout is heirarchical
- each layer only interfaces with layer above it
	- meaning: module at layer `n` should only have to utilize functionality from layer `n-1`

### Examples
- file system
	- symbolic link layer
	- absolute path name layer
	- path name layer
	- file name layer
	- inode number layer
	- file layer
	- block layer
- compilers like g++
- computer networks with TCP/IP

## Naming & Name Resolution
- **names** refer to system resources
- **name resolution**: converting between human-readable names and machine-friendly ones

___
Note: the [[2021-09-24 Lecture Notes.pdf|handwritten lecture notes]] for this lecture contain a lot of work pertaining to the [[202110101242 CS 110 Lecture 2 Notes - Filesystems, Take I (2021-09-22)|previous lecture concepts]], because we ran overtime that lecture.