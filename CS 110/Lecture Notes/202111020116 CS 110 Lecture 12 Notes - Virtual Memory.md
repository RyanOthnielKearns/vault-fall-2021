#CS #CS110 #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 12 Slides - Virtual Memory.pdf|slides]] and [[2021-10-18 Lecture Notes.pdf|handwritten notes]]
2021-10-18
___
# Virtual Memory
**Main memory**: an organized array of contiguous bytes
- Physical hardware
- OS / user processes store data / code
- **physical addressing**: standard addr scheme for single process, older machines
	- process more or less owns *all* of memory when running
- what if multiple processes are running?
	- two or more processes operate as if they own all of memory --> physical addressing not possible
	- CPU / OS jointly treat processes' addresses as *virtual*
		- convert virtual addresses to physical ones before accessing RAM
![[cs110-virtual-addr-mapping.png]]
- **Memory management unit** (MMU) converts (virtual address, pid) pair into physical address in main memory (size dictated by how much RAM you have)
- why not just assume infinite physical memory and allocate contiguous portions of physical memory for each virtual address space?
	1. no computer has $2^{64} = 18.4$ exabytes of storage -- amount that is implied with 64-bit architectures (meaning 64-digit pointers)
	2. vast majority of any single virtual address space is unused
	- instead: only map virtual addresses that are part of *segments*
		- only the virtual addresses contributing to a process's runtime

## Virtual Memory Support
- scheme is very similar to file systems, though unit of storage is a **page** rather than block
	- typically 4096 bytes
- OS stores **Page Table** of virtual-to-physical page mappings in kernel portion of process's virutal address space
	- each mapping stored in **page table entry**
	- Address translation managed by the MMU on the CPU
		- computed with bitwise operations `<<`, `&`, `|`, `>>`
			- MMU can do this extremely fast
- Advantageous viewpoint:
	- view *hard drive* as *physical memory*
	- view *main memory* as *cache* storing pages from disk being currently accessed
	- executables are stored on disk and loaded into main memory when a process runs one
- as main memory becomes saturated, OS will *evict* inactive pages and flush to hard drive, using *swap files*

# Gentle Introduction to Threads
- **thread**: an independent execution sequence within a single process
	- two or more functions can run simultaneously via **threading** in the same process
	- "lightweight processes"
- process stack segment divided into multiple miniature stacks
- text, data, and heap segments are shared between thread processes
	- pro: easier to support communication between threads!
	- con: no memory protection
		- race conditions / deadlock threats
		- bugs hard to reproduce b/c thread scheduling is unpredictable

```
static void recharge() {
	cout << oslock << "I recharge by spending time alone." << endl << osunlock;
}

static const size_t kNumIntroverts = 6;
int main(int argc, char *argv[]) {
	cout << "Let's hear from " << kNumIntroverts << " introverts." << endl;
	thread introverts[kNumIntroverts]; // declare array of empty thread handles
	for (thread& introvert: introverts)
		introvert = thread(recharge); // move anonymous threads into empty handles
	for (thread& introvert: introverts)
		introvert.join();
	cout << "Everyone's recharged!" << endl;
	return 0;
}
```
- `thread::operator=(thread&& other)` transplants contents of the right thread onto the left
	- fully guts the right thread as if it were zero-arg constructed
	- basically swaps left and right threads
- `join` method is to threads what `waitpid` is to processes
	- `main` uses `join`s to block until all child threads exit
- thread routines can accept any number of arguments using variable argument lists
	- supported in C++ via *variadic templates*