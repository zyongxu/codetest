/*
 * The compiler firewall and pimpl idiom
 *
 * About what should goes into that XImpl* impl_:
 * Put all nonvirtual private members into XImpl. After all, in C++,
 * the phrase "client code shouldn't and doesn't care about these
 * parts" is spelled "private"—and privates are always hidden
 *
 * pimpl has two overhead in performance:
 *  1. the pimpl_ requires memory allocation, which is slow
 *  2. calling funcs in XImpl by pimpl_->xxx() has a indirection
 *
 * As with any other optimization, use Pimpls in general and
 * Fast Pimpls in particular only after profiling and experience
 * prove that the extra performance boost is really needed in your situation
 *
 * Stack allocation is much faster since all it really does is move the stack pointer.
 * Using memory pools, you can get comparable performance out of heap allocation,
 * but that comes with a slight added complexity and its own headaches.
 */

class X {
    // public and protected members
private:
    struct XImpl; // forward declaration
    XImpl* pimpl_; // <-- a pointer! in memory management, it's an member object
};

// in file x.cpp
struct X::XImpl {
    // private members are fully hidden, can be
    // changed at will without recompiling clients
};

/*
 * performance cost of the Pimpl Idiom:
 * 1. Each construction/destruction must allocate/deallocate memory.
 * 2. Each access of a hidden member can require at least one extra indirection.
 *
 * To reduce the performance overhead, here is the "Fast Pimpl" idiom
 */

class FixedAllocator {
public:
    static FixedAllocator& Instance();
    void* Allocate( size_t );
    void  Deallocate( void* );
private:
    /*...singleton implementation, typically
     * with easier-to-manage statics than
     * the templated alternative above...*/
};

struct FastArenaObject {
    static void* operator new( size_t s ) {
        return FixedAllocator::Instance()->Allocate(s);
    }
    static void operator delete( void* p ) {
        FixedAllocator::Instance()->Deallocate(p);
    }
};

class X {
    /*...*/
    struct XImpl;
    XImpl* pimpl_; //<-- pimpl
};

/* implemented as a Fast Pimpl */
struct X::XImpl : FastArenaObject {
    /*...private stuff here...*/
};
