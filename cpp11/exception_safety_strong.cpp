/*
 * A strong guarantee version
 */

/*
 * Standard Helper Functions
 */

// construct() constructs a new object in
// a given location using an initial value
template <class T1, class T2>
void construct( T1* p, const T2& value ) {
    new (p) T1(value);
}

// destroy() destroys an object or a range of objects
template <class T>
void destroy( T* p ) {
    p->~T();
}

template <class FwdIter>
void destroy( FwdIter first, FwdIter last ) {
    while( first != last ) {
        destroy( &*first );
        ++first;
    }
}

// swap() just exchanges two values
template <class T>
void swap( T& a, T& b ) {
    T temp(a);
    a = b;
    b = temp;
}

template <class T>
class StackImpl {
/*????*/: // "implemented in terms of" relation with Stack.
          // if private inheritaed by Stack, then should be protected
          // if included as a private member in Stack, then should be public
    StackImpl(size_t size=0):
        v_(static_cast<T*> (
                size == 0 ? nullptr : operator new(sizeof(T)*size)) //<- won't call ctor of T!
        ),
        vsize_(size),
        vused_(0)
    {}

    ~StackImpl() {
        destroy(v_, v_+vused_); // this can't throw
        operator delete( v_ );
    }

    void Swap(StackImpl& other) throw() { //<-- nothrow guarantee! foundamental to the whole StakeImpl!
        swap( v_, other.v_ );
        swap( vsize_, other.vsize_ );
        swap( vused_, other.vused_ );
    }

    T* v_; // ptr to a memory area big enough for 'vsize_' T's # of T's actually in use
    size_t vsize_;
    size_t vused_;

    // no copying allowed
    StackImpl( const StackImpl& ) = delete;
    StackImpl& operator=( const StackImpl& ) = delete;
};

template<class T>
class Stack : private StackImpl<T> {
public:
    Stack(size_t size = 0): StackImpl<T>(size) {}
    ~Stack() {}

    Stack(const Stack& other):
        StackImpl<T>(other.vused_) // memory allocation
    {
        while(vused_ < other.vused_) {
            construct(v_+vused_, other.v_[vused_]);
            ++vused_;
        }
    }

    Stack<T>& operator= (const Stack<T>& other) {
        Stack tmp(other);
        Sway(tmp);
        return *this;
    }

};
