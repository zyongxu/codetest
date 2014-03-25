#include <iostream>
using namespace std;

struct X {
    char c;
    struct XImpl;
    XImpl* pimpl_;
};

struct X::XImpl {
    char c;
};

int main() {
    cout << sizeof(X::XImpl) << endl
        << sizeof(X) << endl;
}
