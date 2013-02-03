#ifndef PRODUCER_H
#define PRODUCER_H

#include <iostream>
#include <sstream>
#include <string>
#include <boost/thread.hpp>

#include "syncqueue.h"

using namespace std;

class Producer
{
private:
  int m_id; // The id of the producer
  SyncQueue<string>* m_queue; // The queue to use
 
public:
  Producer(int id, SyncQueue<string>* queue) {
    m_id=id;
    m_queue=queue;
  }
   
  // The thread function fills the queue with data
  void operator () () {
    int data=0;
    while (true) {
      // Produce a string and store in the queue
      stringstream ss;
      ss<<"Producer: "<<m_id<<", data: "<<(data++)<<endl;
      m_queue->Enqueue(ss.str());
      cout<<ss.str()<<endl;
       
      // Sleep one second
      boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
  }
};

#endif //PRODUCER_H
