// .h
class SliverPool {
public:
  SliverPool(size_t numThreads = 4): pool(numThreads) {}
  void schedule(const function<bool(size_t)>& sliver, 
                const function<void(size_t)>& oncomplete) { 
    schedule(sliver, oncomplete, 0); 
  }
  void wait() { pool.wait(); }
  
private:
  ThreadPool pool;
  void schedule(const function<bool(size_t)>& sliver, 
                const function<void(size_t)>& oncomplete, 
                size_t pass);
};

// .cc

void SliverPool::schedule(const function<bool(size_t)>& sliver, 
                          const function<void(size_t)>& oncomplete,
                          size_t pass) {
  pool.schedule([this, sliver, oncomplete, pass](){
    bool shouldContinue = sliver(pass);
    if (shouldContinue) schedule(&sliver, &oncomplete, pass + 1);
    else oncomplete(pass);
  });
}
