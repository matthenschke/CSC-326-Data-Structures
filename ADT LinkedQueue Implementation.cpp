//lkdQueue Implementation with palindrome methods using Linked Stack

#include<iostream>
#include<assert.h>
#include<string>
#include<cstring>
using namespace std;
template<class T>



//class definitions
//Node struct
struct Node{

	T item;
	Node<T> * next;
	Node() { item = 0; next = nullptr; }
	Node(T i){ item = i; next = nullptr; }
	Node(T i, Node<T> * Ptr){ item = i; next = Ptr; }
};

//lkdStack class definition
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
	void Display();
};


//LkdQueue class definition
template<class T>
class lkdQueue{
private:
	Node<T>* Front;
	Node<T>* Back;

public:
	lkdQueue();
	lkdQueue(const lkdQueue<T> & rhs);
	~lkdQueue();
	bool isEmpty() const;
	bool enqueue(const T& anEntry);
	bool dequeue();
	T peekFront() const;
	void Display();

};
//lkdStack function implmentations
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
T lkdStack<T>::peek() const{
	assert(!isEmpty());
	return topPtr->item;
}
//destructor
template<class T>
lkdStack<T>:: ~lkdStack(){
	while (!isEmpty())
		pop();
}
template<class T>
void lkdStack<T>::Display(){
	Node<T> * curr = topPtr;
	cout << "Stack:" << endl;
	while (curr != nullptr){
		cout << curr->item << " ";
		curr = curr->next;
	}
	cout << endl;
}

//lkdQueue Implementations
template<class T>
lkdQueue<T>::lkdQueue(){
	Front = nullptr;
	Back = nullptr;
}
template<class T>
lkdQueue<T>::lkdQueue(const lkdQueue<T>& rhs){
	Node<T>* rcurr = rhs.Front;
	if (rcurr == nullptr){
		Front = nullptr;
		Back = nullptr;
	}
	else{

		Front = new Node<T>();
		Front->item = rcurr->item;
		rcurr = rcurr->next;
		Node<T> * nchain = Front;
		while (rcurr != nullptr){
			Node<T> * newNode = new Node<T>(rcurr->item);
			nchain->next = newNode;
			nchain = nchain->next;
			rcurr = rcurr->next;
		}
		nchain->next = nullptr;
		Back = nchain;
	}
}
template<class T>
lkdQueue<T>:: ~lkdQueue(){
	Node<T> * curr = Front;
	while (curr != Back){
		Node<T> * prev = curr->next;
		delete curr;
		curr = prev;
		prev = nullptr;
		
	}
	
	
	delete curr;
	curr = nullptr;
	Front = nullptr;
	Back = nullptr;
}
template<class T>
bool lkdQueue<T>::isEmpty() const{
	return Front == nullptr;
}
template<class T>
bool lkdQueue<T>::enqueue(const T& anEntry){
	Node<T> * nn = new Node<T>(anEntry);
	if (isEmpty())
		Front = nn;
	else
		Back->next = nn;
	Back = nn;
	return true;
}
template<class T>
bool lkdQueue<T>::dequeue(){
	bool result = false;
	if (!isEmpty()){
		Node<T>* ndel = Front;
		if (Front == Back){
			Front = nullptr;
			Back = nullptr;
		}
		else
			Front = Front->next;
		ndel->next = nullptr;
		delete ndel;
		ndel = nullptr;
		result = true;
	}

	return result;
}
template<class T>
T lkdQueue<T>::peekFront() const{
	assert(!isEmpty());
	return Front->item;
}

template<class T>
void lkdQueue<T>::Display(){
	Node<T> * curr = Front;
	cout << "Queue: ";
	while (curr != Back){
		cout << curr->item << " ";
		curr = curr->next;
	}
	cout << Back->item << endl;
}

 
bool letterPalindrome(char c[], lkdQueue<char>& q, lkdStack<char>& s ){
	bool isPalindrome = true;
	
	for (int i = 0; i < strlen(c); i++){
		if (c[i] == '\'' || c[i] == ' ' || c[i] == '.' || c[i] == '?' || c[i] == '!')
			continue;
		else{
			s.push(c[i]);
			q.enqueue(c[i]);
		}
	}
	while (!q.isEmpty() && (!s.isEmpty())){
		if ((s.peek() == q.peekFront()) || (toupper(s.peek()) == q.peekFront()) || (toupper(q.peekFront()) == s.peek())){
			s.pop();
			q.dequeue();
		}
		else {
			isPalindrome = false;
			break;
		}

	}
	if (isPalindrome)
		cout << "The word is a Palindrome" << endl;
	else
		cout << "The word is not a Palindrome" << endl;

	return isPalindrome;
}

bool wordPalindrome(char c[], lkdQueue<char>& q, lkdStack<char>& s){
	bool isPalindrome = true; 
	for (int i = 0; i < strlen(c); i++){
		if (c[i] == '\'' || c[i] == ' ' || c[i] == '.' || c[i] == '?' || c[i] == '!')
			continue;
		else{
			s.push(c[i]);
			q.enqueue(c[i]);
		}
	}
	
	while (!q.isEmpty() && (!s.isEmpty())){
		if ((s.peek() == q.peekFront()) || (toupper(s.peek()) == q.peekFront()) || (toupper(q.peekFront()) == s.peek())){
			s.pop();
			q.dequeue();
		}
		else {
			isPalindrome = false;
			break;
		}
	}
	
	if (isPalindrome)
		cout << "The word is a Palindrome" << endl;
	else
		cout << "The word is not a Palindrome" << endl;
	return isPalindrome;
}


//Driver Code
int main(){
	lkdQueue<char> c1;
	lkdStack<char> s1;
	char c[100];
	cout << "Welcome to the Palindrome Checker!! " << endl;
	cout << "Please enter a phrase or a word" << endl;
	cin.getline(c, 100);
	cout << "The phrase you entered is: ";
	for (int i = 0; i < strlen(c); i++)
		cout << c[i];
	cout << endl;
	bool hasSpaces = false;
	for (int i = 0; i < strlen(c); i++){
		if (c[i] == ' '){
			hasSpaces = true;
			break;
		}
		else continue;
	}
	if (hasSpaces = false)
		letterPalindrome(c, c1, s1 );
	else
		wordPalindrome(c, c1,s1);
		



	return 0;
}