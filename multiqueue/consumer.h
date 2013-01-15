#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <string>
#include <boost/thread.hpp>

#include "syncqueue.h"

using namespace std;

class Consumer {
private:
  int m_id; // The id of the consumer
  SyncQueue<string>* m_queue; // The queue to use
 
public:
  Consumer(int id, SyncQueue<string>* queue) {
    m_id=id;
    m_queue=queue;
  }
  
  // The thread function reads data from the queue
  void operator () () {
    while (true) {
      // Get the data from the queue and print it
      cout<<"Consumer "<<m_id<<" consumed: "
        << static_cast<string>(m_queue->Dequeue()) <<endl;
     
      // Make sure we can be interrupted
      boost::this_thread::interruption_point();
    }
  }
};

#endif //CONSUMER_H
