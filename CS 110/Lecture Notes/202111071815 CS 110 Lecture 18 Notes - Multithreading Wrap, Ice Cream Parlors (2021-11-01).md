#CS #CS110 #lecture-notes 
2021-11-01
___
# Agenda
- instead of a slide deck this lecture goes off of [[Multithreading and Synchronization Redux.pdf|singular handout]]
- top level conceit: simulation of an ice cream parlor
	- the cast
		- `customers` (2 or 15)
			- come in knowing they'll order 1-4 ice cream cones
				- hire 1 employee for each ice cream cone
		- `clerk` threads (2 to 8, or 15 to 60 --> determined at runtime by customers)
			- grandchildren of the program (b/c customers spawn them)
			- don't just make ice cream cones -- have to make manager happy
		- `cashier` (singular)
		- `manager`: needs to approve each ice cream cone before given to a customer
			- only allows 1 clerk inside office at any moment

# Ice cream parlor
## `main` function
```
int main(-->) {
	thread customers[15];
	size_t numConesNeeded = 0; // pre-compute total number of ice cream cones, tell manager, and tell customers
	for (size_t i = 0; i < 15; i++) {
		size_t numCones = randInt(1, 4);
		customers[i] = thread(customer, i, numCones);
		numConesNeeded += numCones;
	}
	// now have number of cones to share w/ manager thread, so they know how many ice cream cones to approve before going home
	thread m(manager, numConesNeeded);
	thread c(cashier);
	// now all 17 threads are flying!
	for (thread &t: customers) t.join();
	c.join();
	m.join();
	return 0;
}
```
- to implement now:
	- `customer`
		- these threads will spawn `clerk` threads! grandchildren
	- `manager`
	- `cashier`

## `customer` thread routine
```
static void customer(size_t id, size_t numCones) {
	// between 1 and 4 threads, each of which runs the clerk routine
	thread clerks[numCones]; // dynamically-size array... using makefile flags :)
	for (size_t i = 0; i < numCones; i++) {
		clerks[i] = thread(clerk, id, i); // i is the "cone ID"
	}
	browse(); // customer kills time
	for (thread &t : clerks) t.join();
	
	// not writing rest of thread routine yet -- will manage customer-cashier interaction
	size_t place = checkout.nextPlaceInLine++; // like a deli ticker -- doesn't change as customers move through the line
	checkout.numCustomersWaiting.signal();
	checkout.customers[place].wait(); // waiting for cashier to tell customer that they can leave the store
}
```

## `clerk` thread
- must be prepared to make cones forever until approved
- only 1 clerk can communicate w/ manager at a time (mutex!!!)
	- critical region here w/ manager interaction
	- manager needs to be woken up
```
static void clerk(size_t custID, size_t coneID) {
	bool approved = false;
	// do what it does until it has approval
	while (!approval) {
		makeCone(custID, coneID); // args just for printing things out
		// now, knock on the managers door
		// defined global record for manager interaction
		inspection.available.lock();
		inspection.requested.signal();
		inspection.finished.wait(); // 2 lines only useful as "baton-passing" e.g. assuming manager is waiting on requested and will signal finished when done
		
		approved = inspection.passed; // can only look at boolean while have lock on the available mutex in inspection
		inspection.available.unlock(); // leaving the office
	}
}
```

### global data structure
```
struct inspection {
	mutex available; // initially unlocked
	semaphore requested; // initially 0
	semaphore finished;
	bool passed; // initialization does not matter
};
```
- `passed` populated w/ T/F by manager (so clerk in the manager's office can read it)
- `available`: identify which clerk in the manager's office
- two semaphore are to manage the rendezvous btwn two threads

## `manager` thread
```
static void manager(size_t numConesNeeded) {
	size_t numAttempted = 0;
	size_t numApproved = 0;
	while (numApproved < numConesNeeded) {
		inspection.requested.wait(); // wait until clerk asks for manager's time
		inspection.passed = randChance(0.1); // plant boolean in struct
		inspection.finished.signal(); // these 3 lines executed while clerk in office
		numAttempted++;
		if (inspection.passed) numApproved++; // nothing wrong with two threads reading a shared global value if we know it can't be changed
	}
	printStats(numAttempted, numApproved);
}
```
... now fill out rest of customer thread!

## another global data structure
```
struct checkout {
	checkout(): nextPlaceInLine(0) {}
	atomic<size_t> nextPlaceInLine;
	semaphore customers[15]; // all initialized 0
	semaphore numCustomersWaiting; // 0 -- how many customers in line
}
```
- `atomic`: atomic wrapper for `++` and `--` that will declare a mutex when necessary
- constructors in structs -- b/c structs and classes basically the same thing in C++, except default in classes is private instead of public

## `cashier` routine
```
static void customer() {
  for (size_t i = 0; i < 15; i++) {
    checkout.numCustomersWaiting.wait();
	ringUp(i);
	checkout.customers[i].signal();
  }
}
```