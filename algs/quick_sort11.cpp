#include <utility>
#include <vector>
#include <iostream>
using namespace std;

template<class IterT>
IterT partition(IterT data_begin, IterT data_end) {
    typename IterT::value_type pivot = *(data_end-1);

    IterT j = data_begin - 1;
    for (IterT i = data_begin; i != data_end; ++i) {
        if (*i < pivot) {
            ++j;
            swap(*j, *i);
        }
    }

    ++j;
    swap(*j, *(data_end - 1));
    return j;
}

template<class IterT>
void quickSort(IterT data_begin, IterT data_end) {
    // sort elements in [data_begin, data_end)
    if (data_end - data_begin <2)
        return;

    auto pit = partition(data_begin, data_end);
    quickSort(data_begin, pit);
    quickSort(pit+1, data_end);
}

int main () {
    vector<int> test {4,5,1,6,2, 4325,2352345, 2340,2354985};
    quickSort(test.begin(), test.end());
  
    for (auto i : test)
        cout << i << " ";
    cout << endl; 
  
    return 0;
}
