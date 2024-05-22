#include "linked_calc.hpp"

// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr) {}

// Destructor to deallocate memory
template <typename T>
LinkedCalc<T>::~LinkedCalc() {
//to be implemented
}

// Function to insert a new node at the end of the linked list
template <typename T>
void LinkedCalc<T>::insert(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Helper function to determine if a character is a digit
template <typename T>
bool LinkedCalc<T>::isDigit(const T& c) {
    return (c >= '0' && c <= '9') ;
}

template <typename T>
bool LinkedCalc<T>::validateExpression() {
    //to be implemented
    return true;
}


// Function to evaluate the expression represented by the linked list
template <typename T>
float LinkedCalc<T>::evaluateExpression() {
    Node<T>* current = head;
    float left = convertToFloat(current);
    return evalElem(left, current);
}

template <typename T>
float LinkedCalc<T>::convertToFloat(Node<T>*& current) {
    float integ = 0, frac = 0;
    int i = 1;
    while(current && isDigit(current->data)) {
        integ *= 10;
        integ += current->data - '0';
        current = current->next;
    }   //after while, current is nullptr or nondigit
    if(!current) return integ;  //at this return, current is nullptr
    else if(current->data == '.') {
        current = current->next;
        while(current && isDigit(current->data)) {
            frac += (current->data - '0')/pow(10, i++);
            current = current->next;
        }
        
    }
    return integ + frac;    //at this return, current is either nullptr or operator
}

template <typename T>
float LinkedCalc<T>::evalElem(float left, Node<T>*& current) {
    
    if(!current) return left;

    T op1 = current->data;
    
    current = current->next;
    float right = convertToFloat(current);

    if(current) {   //second operator exists
        
    } else {
        if(op1 == '/') {

        } else if(op1 == '*') {

        } else if(op1 == '+') {

        } else if(op1 == '-') {

        }
    }
    return 0;
}

