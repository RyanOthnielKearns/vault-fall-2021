barrier::barrier(size_t value): count(value) {}

void barrier::up() {
  lock_guard<mutex> lg(m);
  count++;
}

void barrier::down() {
  lock_guard<mutex> lg(m);
  if (count > 0) count--;
  if (count == 0) cv.notify_all();
}

void barrier::wait() {
  lock_guard<mutex> lg(m);
  while (count > 0) cv.wait(m);
}
