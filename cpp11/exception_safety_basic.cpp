/*
 * A basic guarantee version
 */
#include <stdexcept>
using namespace std;

template<class T>
class Stack<T> {
public:
    /*
     * Default ctor and dtor
     */
    Stack():
        v_(new T[vsize_]), // dtor of T will be called, and mem will
        vsize_(10),        // be freed if operator new [] () throws
        vused_(0)
    {}

    ~Stack() {
        delete [] v_;
    }

    /*
     * Copy ctor and copy assignment operator
     */
    Stack(const Stack& other):
        v_(NewCopy(other.v_, other.vsize_, other.vused_)),
        vsize_(other.vsize_),
        vused_(other.vused_)
    {}

    Stack<T>& operator=(const Stack<T>& other) {
        if( this != &other ) {
            T* v_new = NewCopy(other.v_,
                               other.vsize_,
                               other.vsize_);
            delete[] v_; // this can't throw
            v_ = v_new;  // take ownership
            vsize_ = other.vsize_;
            vused_ = other.vused_;
        }
        return *this; // safe, no copy involved
    }

    /*
     * Take all code that might throw exception and do all that work
     * safely off to the side. Then update the state with nonthrowing
     * operations
     */
    T* NewCopy(const T* src,
               size_t   srcsize,
               size_t   destsize) {
        assert(destsize >= srcsize);
        T* dest = new T[destsize];
        try {
            copy( src, src+srcsize, dest );
        } catch(...) {
            delete[] dest; // this can't throw
            throw; // rethrow original exception
        }
        return dest;
    }

    /*
     * Member methods which modify the state of the object
     */
    void push(const T& t) {
        if( vused_ == vsize_ ) { // grow if necessary by some grow factor
            size_t vsize_new = vsize_*2+1;
            T* v_new = NewCopy(v_, vsize_, vsize_new);
            delete[] v_; // this can't throw
            v_ = v_new;  // take ownership
            vsize_ = vsize_new;
        }
        v_[vused_] = t;
        ++vused_;
    }

    /*
     * this is not exception-safe: T pop();
     * return by value is a bad choice, because the copy of returned value may fail
     *
     * and this is is troublesome working: void pop(T& result);
     *
     * The real problem is: pop() actually has two responsibilities -- to pop the top
     * element, and to return the just-popped value.
     *
     * To solve that: Always endeavor to give each piece of code—each module,
     *                each class, each function—a single, well-defined responsibility
     */
    template<class T>
    T& Stack<T>::top() {
        if( vused_ == 0) {
            throw "empty stack";
        }
        return v_[vused_-1];
    }

    template<class T>
    void Stack<T>::pop() {
        if( vused_ == 0) {
            throw "pop from empty stack";
        }
        else {
            --vused_;
        }
    }

private:
    T* v_;
    size_t vsize_;
    size_t vused_; // # of T's actually in use
};
