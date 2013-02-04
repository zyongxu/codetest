/*
 * Encapsulate the thread management into 
 * the worker class. So that the caller (main())
 * doesn't need to take care of thread creation
 */

#include <iostream>
#include <boost/thread.hpp>

class Worker {
public:
    // m_thread is the state of "not-a-thread" until we call start()
    Worker() {}

    void start(int N) {
        // create the thread, with parameters passed in
        // the instance pointer ("this" in this example) is the 
        // first parameter by default requirement
        m_Thread = boost::thread(&Worker::processQueue, this, N);
    }

    void join() {
        m_Thread.join();
    }
    
    void processQueue(unsigned N) {
        float ms = N * 1e3;
        boost::posix_time::milliseconds workTime(ms);

        std::cout << "Worker: started, will work for "
                  << ms << "ms"
                  << std::endl;

        // We're busy, honest!
        boost::this_thread::sleep(workTime);

        std::cout << "Worker: completed" << std::endl;
    }

private:
    boost::thread m_Thread;
};

int main(int argc, char* argv[]) {
    std::cout << "main: startup" << std::endl;
    // the thread is not started yet
    Worker worker;

    // the thread starts afther worker.start() is called!
    worker.start(3);
    std::cout << "main: waiting for thread" << std::endl;
    worker.join();
    std::cout << "main: done" << std::endl;

    return 0;
}
