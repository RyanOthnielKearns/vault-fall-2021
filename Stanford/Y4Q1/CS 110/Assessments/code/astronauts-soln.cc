// declare your global variables here
mutex launchpadLock;
semaphore containers(kNumEmptyContainers);
size_t numContainersRemaining = kNumContainersToMove;
mutex numContainersLock;
size_t currentRocketCapacity = 0;
mutex rocketCapacityLock;
condition_variable_any rocketReady;
semaphore liftoff(0);

void technician() {
    // wait until astronaut says there is a rocket ready for loading
    rocketCapacityLock.lock();
    while(currentRocketCapacity == 0) rocketReady.wait(rocketCapacityLock);
    rocketCapcityLock.unlock();

    // grab an empty container
    containers.wait();
    organize();

    // record container, decrementing
    rocketCapacityLock.lock();
    numContainersLock.lock();
    currentRocketCapacity--;
    numContainersRemaining--;

    if (currentRocketCapacity == 0 || numContainersRemaining == 0) liftoff.signal();
    rocketCapacityLock.unlock();
    numContainersLock.unlock();
}

void astronaut(int capacity) {
  // first, get ahold of the launch pad
  launchpadLock.lock();

  refuel();

  // tell technicians there is a rocket ready for loading
  rocketCapacityLock.lock();
  currentRocketCapacity = capacity;
  rocketCapacityLock.unlock();

  // notify as many technicians as you're going to need
  for (size_t i = 0; i < capacity; i++) rocketReady.notify_one();

  // wait to be told to lift off
  liftoff.wait();
  launchpadLock.unlock();

  fly();

  // now on mars, spawn martians to unpack containers
  vector<thread> martians;
  for (size_t i = 0; i < capacity; i++) martians.push_back(thread(martian));
  for (thread& t : martians) t.join();
}

void martian() {
  unpack();
  containers.signal();
}
