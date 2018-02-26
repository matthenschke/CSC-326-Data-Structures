
//SAFE ARRAY IMPLEMENTATION

#include<iostream>
using namespace std;
const int dSize = 10; //default size for default ctor
//class definitions
template <class T>
class SA{
private:
	T* pT;
	int lIdx; //low index
	int hIdx; //high index
public:
    SA();
	SA(int n);
	SA(int l, int h);
	SA(const SA & arr);
	SA& operator= (const SA& rhs);
	~SA() { delete[] pT; }
	T& operator [] (int offset) {  return pT[offset]; }	//write
	const T& operator[] (int offset) const { return pT[offset]; }  //read
 int getSize() const{ return hIdx - lIdx + 1; }
friend ostream& operator << (ostream& out, SA<T>& arr);
};

//sample class to test safe array implementation
class Cat{
public:
	Cat();
	Cat(int a);
	~Cat() {}
	int getAge() const{ return age; }
private:
	int age;

};
//method implementations for SA
template <class T>
SA<T>::SA() :lIdx(0), hIdx(9){
	pT = new T[dSize];
	
}
template <class T>
SA<T>::SA(int n) : lIdx(0), hIdx(n - 1){
	pT = new T[hIdx - lIdx + 1];
}
template <class T>
SA<T>::SA(int l, int h) : lIdx(l), hIdx(h){
	
	pT = new T[hIdx - lIdx + 1];
	}


template <class T>
SA<T>::SA(const SA& rhs): lIdx(rhs.lIdx), hIdx(rhs.hIdx)
{
	
	int s = (rhs.getSize());
		pT = new T[s];
	for (int i = 0; i < s; i++)
		pT[i] = rhs[i];
}
template <class T>
SA<T>& SA<T>:: operator =(const SA<T>& rhs){
	
	if (this == &rhs)
		return *this;
	else{
		delete [] pT;
		int s = rhs.getSize();
		this->lIdx = rhs.lIdx;
		this->hIdx = rhs.hIdx;
		pT = new T[s];
		for (int i = 0; i < this->getSize(); i++)
			pT[i] = rhs[i];
		return *this;

	}
}
template <class T>
ostream& operator << (ostream& out, SA<T>& arr){
	
	out << arr.pT;
	return out;
}
//method implementations for cat class
Cat::Cat(){
	age = 5;
	
}
Cat::Cat(int a) : age(a){}
	

//driver code
int main(){
	
	{
cout << "\t\t Integer Type Template" << endl;
	SA<int>iArray(3, 11);
	for (int i = 0; i < iArray.getSize(); i++){
		iArray[i] = i*i;
		cout << "iArray[ " << i << "] = " << iArray[i] << endl;
	}
	SA<int>iArray1;
	iArray1 = iArray;
	cout << endl;
	for (int i = 0; i < iArray1.getSize(); i++)
		cout << "iArray1[ " << i << "] = " << iArray1[i] << endl;
}
		//testing double type
	{      cout << "\n\t\t Double Type Template" << endl;
	SA<double>dArray;
	dArray[0] = 5.33;
	for (int i = 1; i < dArray.getSize(); i++)
		dArray[i] = dArray[i - 1] + 3.2331;
	SA<double>dArrcpy = dArray;
	for (int i = 0; i < dArrcpy.getSize(); i++)
		cout << "dArrcpy[ " << i << " ] = " << dArrcpy[i] << endl;
}
	
		//testing Cat type
	{
		cout << "\n\t\t Cat Type Template" << endl;
		SA<Cat>cArray(12);
		Cat *pCat;
		for (int i = 0; i < cArray.getSize(); i++){
			pCat = new Cat(i + 2);
			cArray[i] = *pCat;
			cout << "Cat " << i + 1 << " is " << cArray[i].getAge() << " years old." << endl;
			delete pCat;
		}
		cout << "\n2nd array of Cats" << endl;
		cout << endl;
		SA<Cat>cArray1 = cArray;
		for (int i = 0; i < cArray1.getSize(); i++)
			cout << "Cat " << i + 1 << " is " << cArray1[i].getAge() << " years old." << endl;

	}
	return 0;
}
