#ifndef STRONG_STACK_V1_HPP
#define STRONG_STACK_V1_HPP
/*
 * Strong exception guarantee version #1
 */
#include "stack_impl.hpp"

#define PROTECTED_IMPL

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

    void Push(const T& t) {
        if(vused_ == vsize_) { // grow if necessary
            Stack temp(vsize_*2+1);
            while(temp.Count() < vused_) {
                temp.Push(v_[temp.Count()]);
            }
            temp.Push(t);
            Swap(temp);
        } else {
            construct(v_+vused_, t);
            ++vused_;
        }
    }

    T& Top() {
        if( vused_ == 0 ) {
            throw "empty stack";
        }
        return v_[vused_-1];
    }

    void Pop() {
        if( vused_ == 0 ) {
            throw "pop from empty stack";
        } else {
            --vused_;
            destroy( v_+vused_ );
        }
    }
};

#endif //STRONG_STACK_V1_HPP
