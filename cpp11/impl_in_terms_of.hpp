/*
 * For "implemented-in-terms-of" relationship, containment (member object)
 * is preferred to private inheritance, here is how:
 */
template <class T, class Impl = MyList<T>> // the default impl: implement set (MySet) in terms of list (MyList)
class MySet3 {
public:
    bool   Add( const T& );           // calls impl_.Insert()
    T      Get( size_t index ) const; // calls impl_.Access()
    size_t Size() const;              // calls impl_.Size()

private:
    Impl impl_; // encapsulate common funcs and logics in Impl
                // guarantee exception safety, and prevent resource leak
};

/*
 * The memory management implemetation to be used by multiple
 * client classes/functions
 */
template <class T>
class MyList {
public:
    bool   Insert( const T&, size_t index );
    T      Access( size_t index ) const;
    size_t Size() const;

private:
    T*     buf_;
    size_t bufsize_;
};

/*
 * ps.
 * private inheritance is almost the same as containment,
 * but it introduces tighter coupling than containment,
 * and expose the protected members to the derived class.
 *
 * Only use private inheritance when there are virtual funcs
 * need to be overrided
 */
