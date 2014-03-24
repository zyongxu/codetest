/*
 * the example of what a well-designed class must have
 * [required]: "= default", "= delete", or implement
 * [optional]: increase the flexibility of the class
 */

class CT {
public:
    // #1. [required]default ctor
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
};
