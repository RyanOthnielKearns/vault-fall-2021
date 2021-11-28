#Stanford #Stanford-Fall-2021 #CS #CS110 #lecture-notes 
See [[Lecture 22 Slides - More Network System Calls.pdf|slides]]
2021-11-10
___
Today: data structures & Linux library functions "in the wild"
- Linux has to translate btwn hostnames and IP addresses
	- `struct hostent *gethostbyname(const char *name);`
		- used much more often
	- `struct hostent *gethostbyaddr(const char *addr, int len)`;
		- have to be clear how long the `addr` is using `len`, because it's not null-terminated
```
struct in_addr {
	int sin_addr;
};

struct hostent {
	char *h_name; // c string for host name
	char **h_aliases; // NULL-term char * array (0 or more additional names mapping to the same IP addresses)
	int h_addrtype; // AF_INET, AF_INET6 ("address family internet")
	int h_length; // 4 or 16 (number of bytes)
	char **h_addr_list; // struct in_addr ** -- 1 or more IP addresses associated with this name / aliases... should be a void **
};
```

```
static void publishInfo(const char *host) {
	struct hostent *he = gethostbyname(host);
	if (he == NULL) return;
	cout << "Name: " << he->h_name << endl;
	struct in_addr **addresses = (struct in_addr **) he->h_addr_list;
	while (*addresses != NULL) {
		char str[16];
		cout << "+ " << inet_ntop(AF_INET, *addresses, str, 16) << endl;
		addresses++;
	}
}
```
# IPv6 Resolution
- we've already almost run out of IPv4 addresses on the global internet
	- by contrast, $2^{64}$ available IPv6 addresses, which are 128 bits
	- `gethostbyname2` can handle IPv6 address-name resolution (IPv6 "compliant")

Data structures to model IP addr / port pairs:
```
struct sockaddr {
	unsigned short sa_family;
	char ss_data[14];
}

struct sockaddr_in { // short for "internet"
	unsigned short sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	unsigned char sin_zero[8]; // just padding
}

struct sockaddr_in6 { // for IPv6
	...
}
```
- all data structures designed in pure C, before object-orientation
	- `sockaddr_in6` is a bit bigger
	- base address of the entire struct is most always the base address of the first field in the struct
		- should always start with `AF_INET` or `AF_INET6`, or something is wrong
		- the best C can do to imitate classes / subclasses
			- method receiving struct can just check first 2 bytes, and if `AF_INET6`, can manually hard-cast internally to a `sockaddr_in6`
			- "type polymorphism" that you see in object-oriented languages

# `createClientSocket`
if this succeeds:
1. we've passed in a legitimate host
2. we've given a valid port number for that host
```
int createClientSocket(const string& host, short port) {
	struct hostent *he = gethostbyname(host.c_str());
	if (he == NULL) return -1;
	
	// now, build sockaddr_in data structure
	sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET; // self-identifying tag, "I am an IPv4-oriented struct"
	address.sin_port = htons(port); // "host to network short" -- network byte-order is distinct from both big and little endian, can be flipped like a switch
	address.sin_addr = *(struct in_addr *)(he->h_addr_list[0]); // originally type char *
	int s = socket(AF_INET, SOCKSTREAM, 0); // SOCKSTREAM sort of means "give me reliable packet transfer"
	connect(s, (struct sockaddr *) &address, sizeof(address)); // no overloaded version of connect! implemented to accept a generic pointer and then do the "polymorphism" discussed above
	return s;
}
```

# `createServerSocket`
- have to create a local socket unlike other descriptors! we pass it to `accept`, not `read`/`write`
- IP addr that's relevant is the local host address!
- `bind` system call: reserves a socket and associates `s` w/ a local IP address / port pair --> translates to a "listening" socket endpoint (that can be a server socket)
- server socket able to maintain a queue of 128 pending client requests -- anything beyond that gets passed a "connection reset" error

Going forward... distributed systems and network architectures
- MapReduce!