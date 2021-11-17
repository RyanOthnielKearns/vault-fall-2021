#CS #CS110 #lecture-notes 
See [[Lecture 19 Slides - Introduction to Networks, Clients and Servers.pdf|lecture slides]]
___
Today: **networking**
- really teach networking from a system perspective
	- about parallelism; harnessing the power of a machine's multiple CPU
	- networking = interesting systems programming model
- IP addresses, hostnames, etc. -- but in a more formal context

# Introduction to Networking
- every computer has a unique IP address on a network
	- e.g. `171.64.64.136` (called *dotted quad* expression)
		- each number between 0-255
		- stored inside of 4-byte integer
	- other types of IP addresses (b/c $2^{32}$ unique IP addresses is no longer a large number when it comes to number of unique devices)
		- e.g. 64-bit addresses (**IP v6** address)
- **Domain Name System (DNS)**: maps human-readable names (`web.stanford.edu`) to IP addresses
	- throwback to [[202110051757 CS 110 assign2 Overview Notes|assignment 2]]: absolute path names like `/usr/class/cs110/www/index.html`
		- convert human-readable path to the unique number identifying this resource to the system
		- had to start by finding the resource number for `/` (resolution alg. bootstraps from root dir w/ inode number `1`)
		- very similar algorithm in DNS -- starting with `.edu` / `.com` domain names, then `stanford.edu`, then finds e.g. `math.stanford.edu` (each token is handed off to another web server for further resolution)
	- can lookup using `dig` ("domain information groper") CLI tool

## Servers
- **server**: providing a service
	- clients rely on this service (client <> server handoff)
	- we run servers on a computer -- ppl can connect w/ computer and interact with the server
		- servers bind to a specific **port number** (0-5000)
			- think of IP address as a building address, and a port number as their room number within the building
			- or: like a telephone extension
			- or: as *virtual process IDs* that the server associates w/ the process ID for the relevant process for the server application
		- first 1024 port numbers are *reserved* (e.g. port 80 is the port that web servers bind them to)
			- SSH servers: port 22

## Important POV
Networking is little more than *remote function call and return*
- Various function-call-and-return models we're already familiar with:
	1. **Traditional** function call and return (a la CS 107)
		- modularity & stability -- *very little* in this function call and return model!
		- you can get away with nefarious pointer arithmetic across stack frames, e.g.
	2. Call and return model for **system calls**
		- user stack vs. kernel stack
		- better modularity & security than the traditional function call and return model!
	3. **Subprocess / execvp fork**: another call and return model: as with the `sort()` example where new processes were spawned off
	4. **Networking**: another: network connection established between your laptop running Chrome and a Google server in Mountain View
		- modular and secure! :)
- hyperlink is a function call!
	- function you're calling is `search`, in the Google library on a server in Mountain View
	- parameters have to be expressed as a string serialization of hash table entries (in the hyperlink)
	- return value is returned as a string, in a format that's predictable / parsable (the JS / HTML returned from the function call)

## Creating a Server
- **socket**: like a plug in the wall, sources data (like electricity)
	- some transportation architecture "behind the wall" that gets you your data
	- can read from and write to **socket endpoint**
	- fundamentally a *bidirectional pipe* -- print to either end to be read on the other end
		- bridges processes between computers
		- file descriptors: source/sink of bytes to publish data to other sources (files, but also servers on the other ends of sockets)

```
int server = createServerSocket(12345);
while (true) {
	int client = accept(server, NULL, NULL);
}
```
- `accept` is like waiting by the phone -- returns when something connects up to the socket the file descriptor `server` is pointing to
	- return value of `accept` (on the server-side of things) -- a read/write descriptor, one end of a bidirectional pipe
- when networking is involved: *need* to make sure write calls actually succeed and write everything you want (as we did with read/write w/ local file descriptors -- more important here)
	- we're now more likely to need to `write` multiple times

### `iosockstream`
- abstract C++ classes
	- `istream` --> `ifstream` (istream linked to a local file)
	- `ostream` -> `ofstream` (ostream linked to a local file)
	- `iostream`
- `iosockstream`: iostream layering over descriptors that are sockets
	-	writing with the `iosockstream`:
```
sockbuf sb(client); // takes ownership over client descriptor
iosockstream ss(&sb); // now ss is the 'new' cout and cin combined
ss << strToWrite << endl;
```

### ThreadPooling
- some servers will take longer to complete their service than our demo one (`publishTime(client);`)
	- could take a couple seconds to complete!
	- if server is preoccupied w/ a computation for a single connection, *cannot* be "waiting by the phone" for new connections
	- introducing threading to "take more incoming calls"
		- `pool.schedule([client]() { publishTime(client); });`
		- handle server-side implenentation in parallel, so main thread can "put their ear back to the phone"
- "connection reset" error in browsers: means server is overwhelmed with requests to the `accept` call and is just now dropping requests