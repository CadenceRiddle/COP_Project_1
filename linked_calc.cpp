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
bool LinkedCalc<T>::isDigit(const T& c) {
    return (c >= '0' && c <= '9') ;
}

template <typename T>
bool LinkedCalc<T>::validateExpression() {


    int count = 0;  //declares variable to determine size for dynamic array

    Node<T>* curr = head;   //uses node to traverse list to find size of count
    while(curr!=nullptr){
        count++;
        curr = curr->next;
    };

    T* arr = new T[count];  //uses the name node to create a new array to store the data of the list
    curr = head;
    for(int i = 0; i < count; i++){
        arr[i] = curr->data;
        curr = curr->next;
    }


    if(count % 2 == 1){ //if the array length is even, then there is too many or too few operators and digits for an expression
        for(int j = 0; j < count; j++){
            if(j % 2 == 0){                 //since the digits occur every even index, if the index is even and not a number then it is not a valid expression
                if(!isDigit(arr[j])){
                    return false;
                }
            }
            else{         //checks if the odd indexes are one of the following conditions
                if(!(arr[j] == '+' || arr[j] == '-' || arr[j] == '*' || arr[j] == '/' || (arr[j] == '.' && isDigit(arr[j+1])))
                ){
                    return false;
                }
            }
        }
    }
    else{
        return false;
    };

    return true;    //returns true on default
}   



// Function to evaluate the expression represented by the linked list
template <typename T>
float LinkedCalc<T>::evaluateExpression() {
    Node<T>* current = head;
    float left = convertToFloat(current);
    return evalElem(left, current);
}

//convert() eats up current Nodes until it points to nullptr or operator
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
    return integ + frac;    //at this return, current is either nullptr or operator(by process of elimination)
}

//expected: left is left operand (either passed or calculated), current either points to nullptr or operator
template <typename T>
float LinkedCalc<T>::evalElem(float left, Node<T>*& current) {
    
    if(!current) return left;   //current is nullptr, end recursion

    T op1 = current->data;  //current is not nullptr, then current is operator followed by another operand
    current = current->next;    //read operator and advance

    float right = convertToFloat(current);

    if(!current) {  //no second operator, end recursion
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
                return evalElem(left - right, current);
            }
        }
    }
    return 0;
}

