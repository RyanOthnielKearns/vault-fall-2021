#Stanford #Stanford-Fall-2021 #CS #CS110 #lecture-notes 
See [[Lecture 21 Slides - Networks, Servers, System Calls.pdf|slides]]
2021-11-08
___
# `web-get`
[[202111171320 CS 110 Lecture 20 Notes - Networking and Protocols (2021-11-05)|Last Friday]], implemented a simple web utility (`wget` / `curl`)
- `$ wget http://www.yahoo.com` -- saves to `index.html`
- Jerry's implementation: `./web-get`
```
int main(int argc, char *argv[]) {
	pullContent(parseURL(argv[1]));
	return 0;
}

// returns <host, path> pair
static pair<string, string> parseURL(const string& url) {
	:) // CS 106B
}

// umbrella over all of the networking
static void pullContent(const pair<string, string>& p) {
	const string& host = p.first;
	const string& path = p.second;
	
	int client = createClientSocket(host, 80); // 80 is the HTTP web port number
	assert(client >= 0);
	sockbuf sb(client); // destructor closes client
	iosockstream ss(&sb); // iostream from C++ for socket / pair endpoints
	issueRequest(ss, host, path);
	
	// now in "read mode"
	skipToPayload(ss);
	savePayload(ss, getFileName(path));
}
```
- now we want to implement the three functions at the end of `pullContent`:
```
static void issueRequest(iosockstream& ss, const string& host, const string& path) {
	ss << "GET " << path << " HTTP/1.1\r\n";
	ss << "Host: " << host << "\r\n"; // only key-value pair required in HTTP/1.1 request
	ss << "\r\n";
	ss.flush();
}
```
- if you don't `ss.flush()`, your GET request text might just be sitting in a local buffer and not sent out to the network

```
static void skipToPayload(iosockstream& ss) {
	string line;
	do { // know that there's going to be at least one line!
		getline(ss, line);
	} while (!line.empty() && line != "\r");
}

static void savePayload(iosockstream& ss, const string& filename) {
	ofstream outfile(filename, ios::binary);
	size_t numBytes = 0;
	while (!ss.fail()) {
		char buffer[1024];
		ss.read(buffer, 1024); // object-oriented version of read system call
		numBytes += ss.gcount(); // provides number of bytes transferred by last interesting method call
		outfile.write(buffer, ss.gcount());
	}
	cout << numBytes << " bytes read." << endl;
}
```
- `ios::binary` means don't do anything clever with newline endings, just take everything verbatim

# Next example: API
- API: remote function exection via speaking HTTP
	- **Application Programming Interface (API)**: set of library functions one can use to build a larger piece of software

## `scrabble-word-finder-server`
```
int main(int argc, char **argv) {
	short port = extractPort(argv[1]);
	int server = createServerSocket(port);
	
	// multi-threaded!
	ThreadPool pool(14);
	while(true) {
		int client = accept(server, NULL, NULL);
		pool.schedule([client]() {
			publishScrabbleWords(client);
		});
	}
	return 0; // server designed to be ctrl-C'd if it's being brought down
}

static void publishScrabbleWords(int client) {
	sockbuf sb(client);
	iosockstream ss(&sb);
	string letters = getLetters(ss);
	skipHeader(ss);
	subprocess_t sp = subprocess({"./swf", letters.c_str(), NULL}, false, true);
	vector<string> words;
	pullFormableWords(words, sp.ingestfd);
	waitpid(sp.pid, NULL, 0);
	issueResponse(ss, words);
}
```
- `getLetters`: reads in first line from the request, e.g. `GET /lexical HTTP/1.1` and surfaces `lexical`
- the `false, true` at the end of `subprocess`: we're not wanting to redirect input to the process, but we do want to redirect it's output
- Jerry added some things that real API servers would do:
	- caching -- holds a map from strings to vectors of strings
		- also requries cache lock! `mutex cacheLock;`
	- code is in the [[Lecture 21 Slides - Networks, Servers, System Calls.pdf|slides]]

Next time: system calls that ship with Linux for doing this stuff (`createClientSocket` is something Jerry wrote for CS110...)