//Implementation of Dynamic ArrayList

#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
//class definitions

//exception class definition
class PrecondViolatedExcept : public logic_error{
public:
PrecondViolatedExcept(const string& message = " ");
};

//ArrayList class definition
template<class T>
class DynArrList{
private:
	int static const deCap = 10;
T* items;
int ic;
int maxItems;
public:
DynArrList();
DynArrList(const DynArrList<T> & rhs);
DynArrList& operator = (const DynArrList<T> & rhs);
~DynArrList();
bool isEmpty() const;
int getLength() const;
bool insert(int newPos, const T & nEntry);
bool remove(int pos);
void clear();
void Display();
T getEntry(int pos) const throw (PrecondViolatedExcept);
T replace(int pos, const T & nEntry) throw (PrecondViolatedExcept);
};


//arraylist method implementations
PrecondViolatedExcept::PrecondViolatedExcept(const string & s) :logic_error("Precondition Violated Exception: " + s){

}
template<class T>
DynArrList<T>:: ~DynArrList(){
	delete[] items;
}
template<class T>
DynArrList<T>::DynArrList() {
ic = 0;
maxItems = deCap;
items = new T[maxItems + 1];
}
template<class T>
DynArrList<T>::DynArrList(const DynArrList<T> & rhs){
ic = rhs.ic;
maxItems = rhs.maxItems;
items = new T[maxItems+1];
for (int i = 1; i <= ic; i++)
items[i] = rhs.items[i];

}
template<class T>
bool DynArrList<T>::isEmpty() const{
return ic == 0;
}
template<class T>
int DynArrList<T>::getLength() const{
return ic;
}
template<class T>
bool DynArrList<T>::insert(int nPos, const T& nEntry){
	
	if (ic == maxItems){
		T* oldItems = items;
		maxItems = maxItems * 2;
		items = new T[maxItems + 1];
		for (int i = 1; i <= ic; i++)
			items[i] = oldItems[i];
		delete[] oldItems;
	}
bool ableToInsert = (nPos >= 1) && (nPos <= ic + 1) && (ic < maxItems);
if (ableToInsert){
for (int i = ic; i >= nPos; i--)
items[i + 1] = items[i];
items[nPos] = nEntry;
ic++;
}

return ableToInsert;
}
template<class T>
T  DynArrList<T>::getEntry(int pos) const throw(PrecondViolatedExcept){
bool ableToGet = (pos >= 1) && (pos <= ic);
if (ableToGet)
return items[pos];
else{
string message = "getEntry() called with empty list or invalid position";
throw(PrecondViolatedExcept(message));
}

}
template<class T>
DynArrList<T>& DynArrList<T>::operator = (const DynArrList<T> & rhs){
	if (this == &rhs)
		return *this;
	else{
		delete[] items;
		ic = rhs.ic;
		maxItems = rhs.maxItems;
		items = new T[maxItems + 1];
		for (int i = 1; i <= rhs.ic; i++)
			items[i] = rhs.items[i];
		return *this;
	}
}
template<class T>
void DynArrList<T>::clear(){
ic = 0;
}

template<class T>
bool DynArrList<T>::remove(int pos){
	
bool ableToRemove = (pos >= 1) && (pos <= ic);
if (ableToRemove){
for (int i = pos; i < ic; i++)
items[i] = items[i + 1];
ic--;

}
if (ic == (deCap / 2)){
	double count = ic*(1.0 / 4.0);
	double it = ic -count;
	for (int i = ic; i > static_cast<int>(it); i--)
		remove(i);
}

return ableToRemove;
}
template<class T>
void DynArrList<T>::Display(){
	cout << "List: " << endl;
	for (int i = 1; i <= ic; i++)
		cout << items[i] << " ";
}
template<class T>
T DynArrList<T>::replace(int pos, const T& nEntry) throw(PrecondViolatedExcept){
bool ableToReplace = (pos >= 1) && (pos <= ic);
if (ableToReplace){
T oldEntry = items[pos];
items[pos] = nEntry;
return oldEntry;
}
else{
	string message = "replace() called with an empty list or invalid position";
throw(PrecondViolatedExcept(message));
}
}


//Driver code
int main(){
	DynArrList<int> l1;
	DynArrList<int> l2;
	try{
		l2.getEntry (10);
	}
	catch (PrecondViolatedExcept p){
		cout << p.what() << endl;
	}
	
	for (int i = 1; i <= 10; i++)
		l1.insert(i, 5 * i);
	for (int j = 10; j >= 5; j--)
		l1.remove(j);


	l1.Display();
	
	return 0;
}