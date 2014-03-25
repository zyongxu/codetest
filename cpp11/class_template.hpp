/*
 * the example of what a well-designed class must have
 * [required]: "= default", "= delete", or implement
 * [optional]: increase the flexibility of the class
 */

class CT {
public:
/*
 * Ctors and dtor
 */
    // #1. [required]default ctor, mark ctors explicit when possible!
    explicit CT();

    // #2. [required]copy ctor
    CT(const CT& other);

    // #3. [required]move ctor, "const T&&" doesn't make sence!
    CT(CT&& other);

    // #4. [required]copy assignment operator
    CT& operator= (const CT& ct);

    // #5. [required]move assignment operator
    CT& operator= (CT&& ct);

    // #6. [required]dtor, RAII
    ~CT();

    // #7. [optional] generalized copy ctor, copy from other types
    // NOTE: CT<CT>(const CT&) is NOT *the* copy ctor! CT(const CT&) is!
    // A copy constructor can NEVER be generated from templates
    template<typename T>
    CT(const T& other);

    // #8. [optional]generalized copy assignment operator
    template<typename T>
    CT& operator= (const T& other);

    // #9. [optional]prefect-forwarding ctor
    template<typename... T>
    explicit CT(T&&... t) {        // use explicit to prevent unexpected type conversion
        CT(std::forward<T>(t)...); // forward<T> == static_cast<T&&>
    }

    // #10. [optional]prefect-forwarding assighnment operator
    template<typename T>
    CT& operator= (T&& t);

    /*
     * ps. overload resolution, and binding choice:
     * 1. function is preferred to template function
     * 2. non-const is preferred to const
     */

/*
 * canonical forms of operators
 */
    CT& operator+= (const CT& other) {
        // increment
        return *this;
    }

    //PREincrement, returns ref to non-const
    CT& operator++() {
        //...
        return *this;
    }

    //POSTincrement return const value. Not allowing
    //changes to the returned object
    //should be implemented in terms of preincrement
    const CT operator++(int) {
        CT tmp(*this);
        ++*this;
        return tmp;
    }

    // helper function for stream
    ostream& print(ostream& os) const {
        return os << ...;
    }
};

// op should be implemented in terms of op=
// it should NOT be a member method!
const CT operator+(const CT& a, const CT& b ) {
    CT temp(a);
    temp += b;
    return temp;
}

// operator<< should NOT be a member function
ostream& operator<< (ostream& os, const CT& ct) {
    return ct.print(os);
}
