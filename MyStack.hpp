#pragma once

#ifndef MYSTACK_H
#define MYSTACK_H

#include <stack>
#include <iostream>
#include "Move.hpp"

// o clasa wrapper template pentru stack, ca sa fac pop-ul sa returneze elementul din varf
template <typename T>
class MyStack {
private:
    std::stack<T> stk;
public:

    // functii template ("toate functiile unei clase template sunt la randul lor functii template")
    void push(T x) { stk.push(x); };
    T pop() { T x = stk.top(); stk.pop(); return x; };
};

// specializare pt stack de moves - folosit doar in main ca sa pot afisa toate mutarile dintr-un meci
template<>
class MyStack<Move> {
private:
    std::stack<Move> stk;
public:
    void push(Move mv) { stk.push(mv); };
    void print() { while(stk.size()) { std::cout << stk.top(); stk.pop(); }}
};

#endif