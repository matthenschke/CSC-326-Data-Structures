//Implementation of ADT Linked Set
#include<iostream>
#include<vector>
using namespace std;


//node struct
template <class T>
struct Node{
	T item;
	Node<T> * next;
	Node() { item = 0; next = nullptr; }
	Node(T i){ item = i; next = nullptr; }
	Node(T i, Node<T> * Ptr){ item = i; next = Ptr; }
};


//LKD Set Class Definition
template <class T>
class lkdSet{
private:
	Node<T> * head;
	int ic;
public:
	lkdSet();
	lkdSet(const lkdSet<T>& rhs);
	~lkdSet();
	bool isEmpty() const;
	bool add(const T & anEntry);
	bool remove(const T & anEntry);
	bool contains(const T& anEntry) const;
	Node<T>* getPtrTo(const T & anEntry) const;
	int getSize() const;
	void clear();
	vector<T> toVector() const;
	void Display();
};


//LKD Set method implementations
template <class T>
lkdSet<T>::lkdSet(){
	ic = 0;
	head = nullptr;
}
template <class T>
lkdSet<T>::lkdSet(const lkdSet<T>& rhs){
	ic = rhs.ic;
	Node<T> * rcurr = rhs.head;
	if (rcurr == nullptr)
		head = nullptr;
	else{

		head = new Node<T>();
		head->item = rcurr->item;
		Node<T> * curr = head;
		rcurr = rcurr->next;
		while (rcurr != nullptr){
			Node<T> * nchain = new Node<T>(rcurr->item);
			curr->next = nchain;
			curr = curr->next;
			rcurr = rcurr->next;
		}
		curr->next = nullptr;
	}
}
template <class T>
bool lkdSet<T>::contains(const T & anEntry) const{
	return getPtrTo(anEntry) != nullptr;
}
template <class T>
lkdSet<T>:: ~lkdSet(){
	clear();
}
template <class T>
bool lkdSet<T>::isEmpty() const{
	return ic == 0;
}
template <class T>
bool lkdSet<T>:: add(const T & anEntry){
	bool canAdd = !contains(anEntry);
	if (canAdd){
		Node<T> * nn = new Node<T>();
		nn->item = anEntry;
		nn->next = head;
		head = nn;
		ic++;
	}


	return canAdd;
}
template <class T>

bool lkdSet<T>:: remove (const T & anEntry){
	Node<T> * entry = getPtrTo(anEntry);
	bool canRemove = !isEmpty() && (entry != nullptr);
		if (canRemove){
			entry->item = head->item;
			Node<T>* delPtr = head;
			head = head->next;
			delPtr->next = nullptr;
			delete delPtr;
			delPtr = nullptr;
			ic--;
		}
	return canRemove;
}
template <class T>
Node<T>* lkdSet<T>::getPtrTo(const T & anEntry) const{
	bool found = false;
	Node<T> * curr = head;
	while (!found && (curr != nullptr)){
		if (anEntry == curr->item)
			found = true;
		else
			curr = curr->next;
	}
	return curr;

}
template <class T>
int lkdSet<T>::getSize() const{
	return ic;
}
template <class T>
void lkdSet<T>::clear(){
	Node<T> * curr = head;
	Node<T> * prev;
	while (curr != nullptr){
		prev = curr->next;
		delete curr;
		curr = prev;
		
	}
	ic = 0;
	head = nullptr;
}
template <class T>
vector<T> lkdSet<T>::toVector() const{
	vector<T> bag;
	Node<T> * curr = head;
	int ct = 0;
	while (curr != nullptr && (ct < ic)){
		bag.push_back(curr->item);
		curr = curr->next;
		ct++;
	}
	return bag;
}
template <class T>
void lkdSet<T> ::Display(){
	Node<T> * curr = head;
	while (curr != nullptr){
		cout << curr->item << " ";
		curr = curr->next;
	}
}
//driver code
int main(){
	lkdSet<int> set1;
	set1.add(1);
	set1.add(2);

	cout << set1.getSize() << endl;
	set1.Display();
	return 0;
}