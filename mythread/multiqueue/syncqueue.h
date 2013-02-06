#ifndef QUEUE_H
#define QUEUE_H

#include <boost/thread.hpp>
#include <deque>

using namespace std;

template <typename T>
class SyncQueue {
private:
  std::deque<T> m_queue;
  boost::mutex m_mutex;
  boost::condition_variable m_cond;
 
public:
  void Enqueue(T data) {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_queue.push_back(data);
    m_cond.notify_one();
  }
      
  // Get data from the queue. Wait for data if not available
  T Dequeue() {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    while (m_queue.empty()) m_cond.wait(lock);
    T ret = m_queue[0]; 
    m_queue.pop_front(); 
    return ret;
  }
};

#endif //QUEUE_H
