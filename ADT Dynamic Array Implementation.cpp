// Implmentation of Dynamic ADT Array Stack

//header files
#include<iostream>
#include<fstream>
#include<cstring>
#include<assert.h>
using namespace std;
//class definition
template<class T>
class dynArrStack{
private:
	static const int deCap = 30;
	int top;
	T* items;
public:
	dynArrStack();
	dynArrStack(const dynArrStack<T> & rhs); //copy constructor
	~dynArrStack() { delete[] items; }
	bool isEmpty() const;
	bool push(const T & nEntry);
	bool pop();
	dynArrStack& PostFix(char c []);
	T peek() const;
	void Display();
};
//class implementations
template<class T>
dynArrStack<T>::dynArrStack(){
	items = new T[deCap];
	top = -1;
}
template<class T>
dynArrStack<T>::dynArrStack(const dynArrStack<T> & rhs){
	top = rhs.top;
	items = new T[top+1];
	for (int i = 0; i < top+1; i++)
		items[i] = rhs[i];
}
template<class T>
bool dynArrStack<T>::isEmpty() const{

	return top < 0;

}
template<class T>
bool dynArrStack<T> ::push(const T& nEntry){

	bool result = false;

	if (top < deCap - 1) {

		top++;

		items[top] = nEntry;

		result = true;

	}

	return result;

}
template<class T>
bool dynArrStack<T> ::pop() {

	bool result = false;

	if (!isEmpty()){

		top--;

		result = true;

	}

	return result;

}
template<class T>
T dynArrStack<T> ::peek() const {

	assert(!isEmpty());

	return items[top];

}
template<class T>
void dynArrStack<T>::Display(){
	cout << "Stack:" << endl;
	for (int i = 0; i < top + 1; i++)
		cout << items[i] << endl;
}
template<class T>
dynArrStack<T>& dynArrStack<T>::PostFix(char s[]){
	
	double temp1, temp2;
	for (int i = 0; i <strlen(s); i++){
		
		if (s[i] == 'q')
			break;
		if (isdigit(s[i]))
			push(static_cast<double>(s[i]-48));
		if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '/'){
			temp1 = peek();
			pop();
			temp2 = peek();
			pop();
		}
		if (s[i] == '+')
			push(temp1 + temp2);
		if (s[i] == '-')
		push(temp2 - temp1);
		
		if (s[i] == '*')
			push(temp1 * temp2);
		if (s[i] == '/')
	 push(temp2 / temp1);
		
		continue;
	}
	Display();
	return *this;
}







//driver code
int main(){
	char exp[30];
	dynArrStack<double> d1;
	cout << "Welcome to the PostFix Expression Simulator!!" << endl;
	cout << "Please enter a postfix expression.. Please enter q for end of expression" << endl;
	cin.getline(exp, 30);
	d1.PostFix(exp);
	return 0;
}
