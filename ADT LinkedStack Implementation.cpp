//Matthew Henschke
//Lab 5
#include<iostream>
#include<stdexcpt.h>
using namespace std;

//class definitions

//node class
template<class T>
struct Node{

	T item;
	Node<T> * next;
	Node() { item = 0; next = nullptr; }
	Node(T i){ item= i; next = nullptr; }
	Node(T i, Node<T> * Ptr){ item = i; next = Ptr; }
};

//ADT linked-stack class
template<class T>
class lkdStack{
private:
	Node<T>* topPtr;
	
public:
	lkdStack();
	lkdStack(const lkdStack<T>& rhs);
	~lkdStack();
	bool push(const T& anEntry);
	bool isEmpty() const;
	bool pop();
	T peek() const;
	T peek2() const;
	void Display();
	

};

//exception class
class PrecondViolatedExcep :logic_error{
        public:
	PrecondViolatedExcep(const string & s);
	
};

//method implementations

PrecondViolatedExcep::PrecondViolatedExcep(const string & s):logic_error("Precondition Violated Exception: " + s){
 
}
template<class T>
lkdStack<T>::lkdStack() :topPtr(nullptr){}
template<class T>
lkdStack<T>::lkdStack(const lkdStack<T>& rhs){
	Node<T> * rcurr = rhs.topPtr;
	if (rcurr == nullptr)
		topPtr = nullptr;
		
	else{
		topPtr = new Node<T>();
		topPtr->item = rcurr->item;
		Node<T>* nChain = topPtr;
		rcurr = rcurr->next;
		while (rcurr != nullptr){
			Node<T>*n = new Node<T>(rcurr->item);
			nChain->next = n;
			nChain = nChain->next;
			rcurr = rcurr->next;
		}
		nChain->next = nullptr;
	}
}
template<class T>
bool lkdStack<T>::push(const T& anEntry){
	Node<T>* nPtr = new Node<T>(anEntry, topPtr);
	topPtr = nPtr;
	nPtr = nullptr;
	return true;
}
//deletes top member of stack
template<class T>
bool lkdStack<T>::pop(){
	bool result = false;
	if (!isEmpty()){
		Node<T> * nDel = topPtr;
		topPtr = topPtr->next;
		nDel->next = nullptr;
		delete nDel;
		nDel = nullptr;
		result = true;
	}
	return result;
}
//checks to see if stack is empty
template<class T>
bool lkdStack<T>::isEmpty() const{
	return topPtr == nullptr;
}
//exception peek function 1
template<class T>
T lkdStack<T>::peek() const throw (PrecondViolatedExcep){
	if (isEmpty())
		throw PrecondViolatedExcep("peek() called with empty stack");
	else
		return topPtr->item;
}
template<class T>
T lkdStack<T> ::peek2() const throw (PrecondViolatedExcep){
	int counter = 0;
	Node<T>* curr = topPtr;
	while (curr != nullptr){
		counter++;
		curr = curr->next;
	}
	if (counter < 2)
	throw PrecondViolatedExcep("peek2() called with stack that has less than two items");
	else
		return topPtr->next->item;
}

//destructor
template<class T>
lkdStack<T>:: ~lkdStack(){
	while (!isEmpty())
		pop();
}
//display function
template<class T>
void lkdStack<T>::Display(){
	Node<T> * curr = topPtr;
	cout << "Stack:" << endl;
	while (curr != nullptr){
		cout << curr->item << endl;
		curr = curr->next;
	}

}
//driver code

int main(){
	lkdStack<int> num;
	
	try{

		cout << "\nPeek returns " << num.peek();
	}
	catch (PrecondViolatedExcep p){
		cout << "Peek cannot be called with empty stack" << endl;
	     }
		 
	try{
		cout << "\nPeek 2 returns " << num.peek2() << endl;
			  
			 
	}
	catch (PrecondViolatedExcep p){
		cout << "Peek2 cannot be called because stack has less than two items" << endl;
	}
	cout << endl;
	
	return 0;
}