#ifndef LINKED_CALC_HPP
#define LINKED_CALC_HPP

#include <iostream>
#include <cmath>    //used in convertToFloat

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

// LinkedCalc class
template <typename T>
class LinkedCalc {
public:
    LinkedCalc();
    ~LinkedCalc();
    void insert(const T& value);
    bool validateExpression() const;
    float evaluateExpression() const;

private:
    Node<T>* head;
    bool isDigit(const T& c) const;
    bool isOpr(const T& c) const;
    float convertToFloat(Node<T>*& current) const;
    float evalElem(float left, Node<T>*& current) const;
};



#endif // LINKED_CALC_HPP
