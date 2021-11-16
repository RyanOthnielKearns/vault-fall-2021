const static int kNumContainersToMove = 300;
const static int kNumEmptyContainers = 70;

int main(int argc, char *argv[]) {
  RandomGenerator rgen; 
  vector<thread> threads;
  int totalRocketCapacity = 0;

  for (int i = 0; i < kNumContaineresToMove; i++) {
     // create technician threads
     threads.push_back(thread(technician));
  }

  while (totalRocketCapacity < kNumContainersToMove) { 
    // create astronaut threads
    int thisRocketHolds = rgen.getNextInt(10, kNumEmptyContainers);
    totalRocketCapacity += thisRocketHolds;
    threads.push_back(thread(astronaut, thisRocketHolds));
  }

  for (thread& t: threads) t.join();
  return 0;
}

// simulation functions already written for you
static void organize(); // for technician, to fill container with stuff
static void refuel();   // for astronaut, to prepare rocket
static void fly();      // for astronaut, fly to Mars
static void unpack();   // for martian, to unload container contents
