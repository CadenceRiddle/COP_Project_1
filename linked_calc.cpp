/*
Program that validates and evaluates a given expression in the form of a LinkedCalc class. 
Modified from linked_calc.cpp and linked_calc.hpp provided in Project files.

By Cadence Riddle and Sheng Rao
*/

#include "linked_calc.hpp"


// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr) {}

// Destructor to deallocate memory
template <typename T>
LinkedCalc<T>::~LinkedCalc() {
    Node<T>* current = head;
        Node<T>* nextNode;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
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
bool LinkedCalc<T>::isDigit(const T& c) const {
    return (c >= '0' && c <= '9') ;
}

// Helper function to determine if a character is an operator
template <typename T>
bool LinkedCalc<T>::isOpr(const T& c) const {
    return (c == '/' || c == '*' || c == '+' || c == '-') ;
}

template <typename T>
bool LinkedCalc<T>::validateExpression() const {
    Node<T>* current = head;
    T curr;
    bool radix = false;   
    while(current != nullptr) {
        curr = current->data;
        if(isDigit(curr)) {
            
        } else if(isOpr(curr)) {
            radix = false;  //reset two decimal points in a single operand flag
            if(current->next == nullptr || !isDigit(current->next->data)) return false; //not a digit after an operator
            if(isOpr(current->next->data)) return false;   //two consecutive operators
        } else if(curr == '.') {
            if(radix) return false; //two decimal points in a single operand, includes two in a row
            radix = true;
        } else return false; //not digit, operator, or decimal point
        
        current = current->next;
    }

    
    return true;    //all checks passed without failure, return true
}   



// Function to evaluate the expression represented by the linked list
// Starts the recursive function evalElem(), which should eat up the entire expression
//and return the proper float.
//A null/empty head returns 0.
template <typename T>
float LinkedCalc<T>::evaluateExpression() const {
    Node<T>* current = head;
    float left = convertToFloat(current);
    return evalElem(left, current);
}

//convertToFloat() eats up current Nodes until it points to nullptr or operator
//if it is passed a nullptr as current, it returns 0.
template <typename T>
float LinkedCalc<T>::convertToFloat(Node<T>*& current) const {
    float integ = 0, frac = 0;
    int i = 1;  //for evaluating frac
    while(current && isDigit(current->data)) {  //while loop evaluates number as integer, read from left to right
        integ *= 10;
        integ += current->data - '0';
        current = current->next;
    }   //after while ends, current is nullptr or nondigit
    if(!current) return integ;  //at this return, current is nullptr
    else if(current->data == '.') {
        current = current->next;    //eat the dot and advance
        while(current && isDigit(current->data)) {  //while loop evaluates number as fractional part
            frac += (current->data - '0')/pow(10, i++);
            current = current->next;
        }
        
    }
    return integ + frac;    //at this return, current is either nullptr or operator(by process of elimination)
}

//expected: left is left operand (either passed or calculated), current either points to nullptr or operator
template <typename T>
float LinkedCalc<T>::evalElem(float left, Node<T>*& current) const {
    
    if(!current) return left;   //current is nullptr, end recursion

    T op1 = current->data;  //current is not nullptr, then current is operator followed by another operand
    current = current->next;    //read operator and advance

    float right = convertToFloat(current);  //the only thing that can follow an operator is the right operand

    // ^ after convertToFloat on right operand, current points to nullptr or an operator
    if(!current) {  //no second operator, end recursion, return operated left/right
        if(op1 == '/') {
            return left/right;
        } else if(op1 == '*') {
            return left*right;
        } else if(op1 == '+') {
            return left+right;
        } else if(op1 == '-') {
            return left-right;
        }
    } else {   //second operator exists
        T op2 = current->data;  //read but do not advance, preserve current pointing to operator

        //  Order of operations: 1. Divide 2. Multiply 3. Add 4. Subtract
        //All from left to right.
        if(op1 == '/') {
            return evalElem(left/right, current);
        } else if(op1 == '*') {
            if(op2 == '/') {
                return left * evalElem(right, current);
            } else {
                return evalElem(left*right, current);
            }
        } else if(op1 == '+') {
            if(op2 == '/' || op2 == '*') {
                return left + evalElem(right, current);
            } else {
                return evalElem(left+right, current);
            }
        } else if(op1 == '-') {
            if(op2 == '/' || op2 == '*' || op2 == '+') {
                return left - evalElem(right, current);
            } else {
                return evalElem(left-right, current);
            }
        }
    }
    //an uncovered case if it reaches this point (likely unknown operator), throw exception?
    return 0;
}

