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
        int i = 0;
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
    //to be implemented
}

