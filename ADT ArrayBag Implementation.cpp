/*Implementation of ADT Array Bag 
 with methods such as Union, Intersection, and Difference*/

#include<iostream>
#include<vector>
using namespace std;
template<class T>
//class definition
class ArrayBag{
private:
	static const int deCap = 60;
	T items[deCap];
	int ic;
	int max;
	int getIdxof(const T & target) const;
public:
	ArrayBag();	
	int getCurrentSize() const { return ic; }
	bool isEmpty() const { return ic == 0; }
	bool add(const T& newEntry);
	bool remove(const T& anEntry);
	void clear(){ ic = 0; }
	bool contains(const T& anEntry) const;
	int getFreqOf(const T& anEntry) const;
	vector<T> toVector() const;
	void Display();

	   ArrayBag& Union(const ArrayBag& anEntry);
	 ArrayBag& Intersection(const ArrayBag& anEntry);
	ArrayBag& Difference(const ArrayBag& anEntry);
	
};
//class method implementations
template<class T>
int ArrayBag<T>::getIdxof(const T& target) const{
	bool found = false;
	int result = -1;
	int idx = 0;
	while (!found && idx < ic){
		found = items[idx] == target;
		if (found)
			result = idx;
		else
			idx++;
	}
	return result;
}
template< class T>
ArrayBag<T> :: ArrayBag() : ic(0), max(deCap) {}
template<class T>
bool ArrayBag<T>::add(const T& newEntry){
	bool hasRoom = (ic < max);
	if (hasRoom){
		items[ic] = newEntry;
		ic++;
	}
	return hasRoom;
}
template<class T>
vector<T> ArrayBag<T> ::toVector() const{
	vector<T> bagContents;
	for (int i = 0; i < ic; i++)
		bagContents.push_back(items[i]);
	return bagContents;
}
template<class T>
int ArrayBag<T> ::getFreqOf(const T& anEntry) const {
	int freq = 0; int curIdx = 0;
	while (curIdx < ic) {
		if (items[curIdx] == anEntry)
			freq++;
		curIdx++;
	}
	return freq;
}
template<class T>
void ArrayBag<T>::Display(){
	for (int i = 0; i < getCurrentSize(); i++)
		cout << items[i] << " ";
	          cout << endl;
}
template<class T>
bool ArrayBag<T> ::contains(const T& anEntry) const {
	bool found = false; int curIdx = 0;
	while (!found && curIdx < ic) {
		if (anEntry == items[curIdx])
			found = true;
		curIdx++;
	}
	return found;
}
template<class T>
bool ArrayBag<T>::remove(const T& anEntry){
	int locatedIdx = getIdxof(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIdx > -1);
	if (canRemoveItem){
		ic--;
		items[locatedIdx] = items[ic];
	}
	return canRemoveItem;
}
template<class T>
 ArrayBag<T>& ArrayBag<T>::Union(const ArrayBag<T>&anEntry){
	 ArrayBag<T> Bag;
	if (!anEntry.isEmpty() && anEntry.getCurrentSize() < deCap){
		for (int i = 0; i < anEntry.getCurrentSize(); i++){
			if (this->getCurrentSize() == deCap)
				break;
			else
				Bag.add(anEntry.items[i]);

		}
		
	}
	for (int i = 0; i < this->getCurrentSize(); i++)
		Bag.add(this->items[i]);
	Bag.Display();
	return Bag;
}

template<class T>
 ArrayBag<T>& ArrayBag<T>::Intersection(const ArrayBag<T>& anEntry)  {
	int intersect = 0;
	ArrayBag<T> Bag;
	for (int i = 0; i < this->getCurrentSize(); i++)
		Bag.add(this->items[i]);
	
	if (!anEntry.isEmpty() && Bag.getCurrentSize() < deCap){
		for (int i = 0; i < anEntry.getCurrentSize(); i++){
			if (Bag.getCurrentSize() == deCap)
				break;
			if (anEntry.contains(Bag.items[i])){
				if (Bag.getFreqOf(Bag.items[i]) >  anEntry.getFreqOf(Bag.items[i])){
					intersect = Bag.getFreqOf(Bag.items[i]) - anEntry.getFreqOf(Bag.items[i]);
					for (int j = 0; j < intersect; j++)
						Bag.remove(Bag.items[i]);

				}
				else if (Bag.getFreqOf(Bag.items[i]) < anEntry.getFreqOf(Bag.items[i]))
					continue;

				else{
					continue;
					
				}
			}
			else
				Bag.remove(Bag.items[i]);
		}
	}
		
	Bag.Display();
	return Bag;
}

template<class T>
ArrayBag<T>& ArrayBag<T>::Difference(const ArrayBag<T> & anEntry){
	int difference;
	ArrayBag<T> Bag;
for (int i = 0; i < this->getCurrentSize(); i++)
       Bag.add(this->items[i]);
T item = ' ';
	if (!isEmpty() && Bag.getCurrentSize() < deCap){
		for (int i = 0; i < anEntry.getCurrentSize(); i++){
			if (Bag.getCurrentSize() == deCap)
				break;
			if (Bag.items[i] == item)
				continue;
			
			if (anEntry.contains(Bag.items[i])){
				if (Bag.getFreqOf(Bag.items[i]) >  anEntry.getFreqOf(Bag.items[i])){
					difference = anEntry.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
					for (int j = 0; j < difference; j++)
						Bag.remove(Bag.items[i]);
					
				}
				else if (Bag.getFreqOf(Bag.items[i]) < anEntry.getFreqOf(Bag.items[i])){
					difference = Bag.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
				for (int j = 0; j < difference; j++)
					Bag.remove(Bag.items[i]);
				 
			}
				else{
					difference = Bag.getFreqOf(Bag.items[i]);
					item = Bag.items[i];
					for (int j = 0; j < difference; j++)
						Bag.remove(items[i]);
					
				}
			}
			else
				Bag.remove(Bag.items[i]);
			


		}
	}
	Bag.Display();
	return Bag;
}



//driver code
int main(){
	cout << "Integer Type" << endl;
	int Arsize = 10;
	ArrayBag<int>intAR;
     ArrayBag<int>intAR1;
	for (int i = 0; i < Arsize; i++)
		intAR.add(i+1);
	for (int i = 0; i < Arsize; i++)
		intAR1.add(i*i);
	cout << "IntAR members:" << endl;
	intAR.Display();
	cout << "IntAR1 members: " << endl;
	intAR1.Display();
	cout << "Intersection: " << endl;
	intAR.Intersection(intAR1);
	cout << "Union: " << endl;
	intAR.Union(intAR1);
	cout << "Difference: " << endl;
	intAR.Difference(intAR1);
	cout << endl;
	cout << "String Class" << endl;
	ArrayBag<char>cAR;
	ArrayBag<char>cAR1;
	Arsize = 12;
	for (int i = 0; i < Arsize; i++)
		cAR.add('a');
	for (int i = 0; i < Arsize; i++)
		cAR1.add('a' + i);
	cout << "cAR members: " << endl;
	cAR.Display();
	cout << "cAR1 members: " << endl;
	cAR1.Display();
	cout << "Intersection: " << endl;
	cAR.Intersection(cAR1);
	cout << "Union: " << endl;
	cAR.Union(cAR1);
	cout << "Difference: " << endl;
	cAR.Difference(cAR1);
	
}