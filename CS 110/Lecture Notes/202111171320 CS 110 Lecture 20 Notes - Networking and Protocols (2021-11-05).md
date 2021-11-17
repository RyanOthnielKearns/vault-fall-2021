#CS #CS110 #lecture-notes 
See [[Lecture 20 Slides - Networking and Protocols.pdf|slides]]
___
# Simple Networking Code Examples
## 1st Example: Simple Server
```
int main(-->) {
	int server = createServerSocket(12347); // port number, like a telephone extension
	while (true) {
		int client = accept(server, NULL, NULL);
		publishTime(client);
	}
}
```
- we have free range to reserve ports from 1024 to the max number for an insigned short
- `int server` points to the local IP address / port pair comprising the "*server descriptor*"
- `accept` blocks until some client attempts connecting to the IP addr / port pair
	- the 2nd and 3rd arguments can be used to surface info about who connected to you
- server can't die unless you CTRL-C it
- if `publishTime(client)` is time consuming (e.g. nontrivial computational result), interferes w/ server's ability to `accept` new connections
	- standard is to sneak in some kind of threading (`ThreadPool`)
	- replace with `pool.schedule([client]() { publishTime(client); });`
		- need `client` in the capture clause to know who you're interacting with
		- has to be 0-arg fxn
		- puts obligation on `publishTime` to be thread-safe

## 2nd Example: Programmatically Connecting to Server
high level idiom for how to interact with a server:
```
int main(-->) {
	int client = createClientSocket(
		"myth64.stanford.edu", 12347
	);
	sockbuf sb(client); // provides buffers, so we don't have to read one character at a time
	iosockstream ss(&sb); // "layered" over sb
	string response;
	getline(ss, response);
	cout << response << endl;
	return 0;
}
```
- `createClientSocket`: literally dialing a phone number
- `ss`: can call `getline`, `<<`, `>>` on

## Connecting to google
```
$ telnet www.google.com 80
GET / HTTP/1.1
Host: www.google.com

[google spits back a bunch of HTML / JS]
```

# Protocols
- HTTP is not free text! has to conform to conversation grammar
- network protocols are codified using **Requests for Comments (RFCs)**

## HTTP Requests
- client speaks first
- blank line indicates that client is done talking -- request is complete
- line 1: request line / start line
	1. **verb**
		- `GET`: request info from the server (read-only)
		- `POST`: upload information to the server, w/ expectation that server stores it
			- adding info that won't be in the URL, because too personal (e.g. username/password), or too lengthy
		- `HEAD`: like `GET`, but response should *only* contain the metadata w/o payload
			- metadata often includes info about how recently the document changed -- bit of an if guard, to check whether it's worth it to get the full payload
	2. **request path**
		- e.g. `/search?q=cats&tbm=isch`
	3. what protocol **version** we want to use
- following the first line: 0 or more request header lines (key/value pairs like `Host: www.google.com`)
	- have to communicate `Content-Length: XX` when sending a post request, so server can know when it's done reading data
- if client includes a payload with their request, it can be inline after the blank line after the request

## HTTP Responses
```
HTTP/1.1 200 OK
Date: ...
Server: ...
Cache-Control: ... (tells browser whether or not to cache response)
...

[payload]
```
- first line: HTTP version + HTTP status code
	- also `404 Not Found` and `500 Internal Server Error`
		- generally 400s mean client made a mistake, 300s are kinds of redirection, and 500s mean server made a mistake
- cookies: shared global variables

## Emulation of `wget`
- analagous to `curl`
- given a URL, downloads a single document and saves a copy to the working dir
- `parseURL` method dissects the supplied URL to surface *host* and *pathname* components
- `pullContent` manages the networking using host + pathname

```
sockbuf sb(client);
iosockstream ss(&sb);
issueRequest(ss, components.first, components.second);
skipToPayload(ss);
savePayload(ss, getFileName(components.second));
```