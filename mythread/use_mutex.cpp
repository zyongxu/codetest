/* compile with linking to boost_thread:
 *    g++ use_mutex.cpp -lboost_thread
 */

#include <iostream>
#include <string>
#include <boost/thread.hpp>

using namespace std;

class Num {
public:
  Num(): num_(0) {}

  void operator() () {
    m_.lock();
    num_++;
    cout << boost::this_thread::get_id() <<": "<< num_ << endl;
    m_.unlock();
  }

  const int num() const { return num_; }

private:
  int num_;
  /* WARNING: by having the mutex as a member variable,
   * the object of this class becomes NON-copyable!!!
   */
  boost::mutex m_;
};

/* a warper which is not necessary.. */
void threadfunc (Num &n) {
  n();
}

int main () {
  Num obj;
  cout << obj.num() << endl;

  /* USE boost::ref to pass by the object by reference, when the actual
   * parameter expecting pass by value
   *
   * boost::bind warps a function call with arguments to a non-input call
   */
  boost::thread myt1(boost::bind(threadfunc, boost::ref(obj)));
  boost::thread myt2(boost::ref(obj));
  myt1.join();
  myt2.join();

  cout << "final result = " << obj.num() << endl;
  return 0;
}

