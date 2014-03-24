#include <iostream>

class Str {
private:
    char *data;

public:
    Str(const char *p) {
        size_t size = strlen(p) + 1;
        data = new char[size];
        memcpy(data, p, size);
    }

    /* 
     * The move ctor
     * with rvalue ref (to detect rvalue, and "steal" resource)
     * Since rvalues are anonymous temp objects, which will
     * be destroied at the next semicolon, we don't have to
     * deep copy it!
     */
    Str(Str &&that) {
        data = that.data;
        /* set that.data = 0 so that the dtor of that
         * cannnot delete the memory pointed by data
         */
        that.data = 0;
    }

    /*
     * C++ allows one to manage the memory on his own.
     * Merely calling 'new' is not managing memory.
     * One must follow the "rule of three"!
     * 1) dtor
     */
    ~Str() {
        delete [] data;
    }

    /*
     * 2) copy ctor
     */
    Str (const Str &that) {
        size_t size = strlen(taht.data) + 1;
        char *tmp = data;
        data = new char[size];
        memcpy(data, that.data, size);
        delete [] tmp;
    }

    /*
     * 3) assignment copy ctor
     * use the copy-and-swap to be exception safe
     * Leveraging exising ctor and func to implement
     *
     * The compiler will choose whether to invoke
     * copy ctor or move ctor based on the type of 'that'
     * if the Str object 'that' is a
     *    lvalue: copy ctor (deep copy)
     *    rvalue: move ctor (steal resource)
     */
    Str &operator = (Str that) {
        std::swap(data, that.data);
        return *this;
    }
};

int main() {

    return 0;
}
