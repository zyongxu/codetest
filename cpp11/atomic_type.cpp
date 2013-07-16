#include <atomic>
#include <iostream>
using namespace std;

int main() {
    std::atomic<int> atm_idx;
    if (atm_idx.is_lock_free())
        cout<<"atomic<int> is lockfree"<<endl;
    else
        cout<<"atomic<int> is NOT lockfree"<<endl;
    return 0;
}
