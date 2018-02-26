
//Tree implementations
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cassert>
using namespace std;

class PreCondViolatedExcept : public logic_error
{
public:
	PreCondViolatedExcept(const string& message = "");
};
PreCondViolatedExcept::PreCondViolatedExcept(const string& message) : logic_error("Precondition Violated Exception: " + message)
{
}

template<class T>
class BNode{
public:
	T item;
	BNode<T> * lchild;
	BNode<T>* rchild;
	BNode() : lchild(NULL), rchild(NULL){}
	BNode(const T& anItem) : item(anItem), lchild(NULL), rchild(NULL){}
	BNode(const T& anItem, BNode<T>* left, BNode<T>* right) :item(anItem), lchild(left), rchild(r){}
	bool isLeaf() const;

};
template<class T>
class Tree {
	BNode<T>* root;
	int gHeiHlp(BNode<T>* subTr) const;
	 int gNumOfNodesHlp(BNode<T>* subTr) const;
	 BNode<T>* balancedAdd(BNode<T>* subtree, BNode<T>* nNode);
	 void preOrder(void visit(T&), BNode<T>* tr) const;
	 BNode<T>*cpyTree(const BNode<T>* oldRt) const;
	 void destroyTree(BNode<T>*&subTr);
	 BNode<T>*bstAdd(BNode<T>*& subTr, BNode<T>* nNode);
	 BNode<T>* bstFind(BNode<T>*& subTr, const T& tgt) const; //search
	 BNode<T>* bstRmvVal(BNode<T>*& subTr, const T& tgt, bool & success);
	 BNode<T>* bstRmvNode(BNode<T>* ndPtr);
	 BNode<T>*bstRmvLftmstNode(BNode<T>*& subTr, T& inSnc);
	

	 
public:
	Tree() : root(NULL){}
	Tree(const T& rtItem);
	Tree(const T& rtItem, const BNode<T>* ltr, const BNode<T> * rtr);
   Tree(const Tree<T> & rhs);
	~Tree();
	bool isEmpty() const;
	int gHei() const;
	int gNumofNodes() const;
	T gRtData() const throw(PreCondViolatedExcept);
	void sRtData(const T& nData);
	bool add(const T& nData);
	void preTrav(void visit(T&)) const;
	
	
	
};



//Tree Implementations
template<class T>
bool BNode<T>::isLeaf() const{
	return (lchild == nullptr) && (rchild == nullptr);
}
template<class T>
Tree<T>::Tree(const T& rtItem){
	root = new BNode<T>(rtItem);
}
template<class T>
Tree<T>::Tree(const T& rtItem, const BNode<T>* ltr, const BNode<T> * rtr){
	root = new BNode<T>(rtItem, ltr, rtr);
}
template<class T>
Tree<T>::Tree(const Tree<T> & rhs){
	root = cpyTree(rhs.root);
}
template<class T>
Tree<T>::~Tree(){
	destroyTree(root);
}
template<class T>
T Tree<T> ::gRtData() const throw (PreCondViolatedExcept){
	if (isEmpty())
		throw PrecondViolationExcep("the tree is empty");
	return root->item;
}
template <class T>
void Tree<T>::sRtData(const T& nData){
	if (isEmpty())
		root = new BNode<T>(nData);
	else
		root->item = nData;
}
template<class T>
bool Tree<T>:: isEmpty() const{
	return root == nullptr;
}
template<class T>
int Tree<T>::gHeiHlp(BNode<T> * subTr) const{
	if (subTr == nullptr)
		return 0;
	else
		return 1 + max(gHeiHlp(subTr->lchild), gHeiHlp(subTr->rchild));
}
template<class T>
int Tree<T>::gNumOfNodesHlp(BNode<T>* subTr) const{
	if (subTr == nullptr)
		return 0;
	else
		return 1 + gNumOfNodesHlp(subTr->lchild) + gNumOfNodesHlp(subTr->rchild);

}
template<class T>
int Tree<T>::gHei() const{
	return gHeiHlp(root);
}
template<class T>
int Tree<T>::gNumofNodes() const{
	return gNumofNodesHlp(root);
}
template<class T>
BNode<T>* Tree<T>::cpyTree(const BNode<T>* oldRt) const{
	BNode<T>* cTr = NULL;
	if (oldRt != nullptr){
		cTr = new BNode<T>(oldRt->item);
		cTr->lchild = cpyTree(oldRt->lchild);
		cTr->rchild = cpyTree(oldRt->rchild);
	}
	return cTr;
}
template<class T>
void Tree<T>::destroyTree(BNode<T>*&subTr){
	if (subTr != nullptr){
		destroyTree(subTr->lchild);
		destroyTree(subTr->rchild);
		 subTr = nullptr;
		
	}
}
template<class T>
BNode<T>* Tree<T>::bstAdd(BNode<T>*& subTr, BNode<T>* nNode){
	if (subTr == NULL)
		return nNode;
	else if (subTr->item == nNode->item)
		return subTr;

	else if (subTr->item > nNode->item){
		BNode<T> * temp = bstAdd(subTr->lchild, nNode);
		subTr->lchild = temp;
	}
	else{
		BNode<T>* temp = bstAdd(subTr->rchild, nNode);
		subTr->rchild = temp;
	}
		return subTr;
	
}
template<class T>
BNode<T>* Tree<T>::bstFind(BNode<T>*& subTr, const T& tgt) const{
	if (subTr == nullptr)
		return nullptr;
	else if (subTr->item == tgt)
		return subTr;
	else if (subTr->item > tgt)
		return bstFind(subTr->lchild, tgt);
	else
		return bstFind(subTr->rchild, tgt);
}
template<class T>
BNode<T>* Tree<T>::bstRmvVal(BNode<T>*& subTr, const T& tgt, bool & success){
	if (subTr == nullptr)
		success = false;
	else if (subTr->item == tgt){
		subTr = bstRmvNode(subTr);
		success = true;
	}
	else if (subTr->item > tgt){
		BNode<T>* temp = bstRmvVal(subTr->lchild, tgt, success);
		subTr->lchild = temp;
	}
	else{
		BNode<T>* temp = bstRmvVal(subTr->rchild, tgt, success);
		subTr->rchild = temp;
	}
	return subTr;
}
template<class T>
BNode<T>* Tree<T>::bstRmvNode(BNode<T>* ndPtr){
	if (ndPtr->isLeaf()){
		delete ndPtr;
		return ndPtr;
	}
	else if (ndPtr->lchild == NULL){
		BNode<T>*nd2Connect = ndPtr->rchild;
		delete ndPtr;
		ndPtr = NULL;
		return nd2Connect;

	}
	else{
		T ndVal;
		ndPtr->rchild = bstRmvLftmstNode(ndPtr->rchild, ndVal);
		ndPtr->item = ndVal;
		return ndPtr;


	}
}
template<class T>
BNode<T>* Tree<T>::bstRmvLftmstNode(BNode<T>*& subTr, T& inSnc){
	if (subTr->lchild == NULL){
		inSnc = subTr->item;
		return bstRmvNode(subTr);
	}
	else {
		subTr->lchild = bstRmvLftmstNode(subTr->lchild, inSnc);
		return subTr;
	}
}

template<class T>
void Tree<T>::preOrder(void visit(T&), BNode<T>* tr) const{
	if (tr != nullptr) {
		T it = tr->item;
		visit(it);
		preOrder(visit, tr->lchild);
		preOrder(visit, tr->rchild);
	}

}

template<class T>
BNode<T>* Tree<T>::balancedAdd(BNode<T>* subtree, BNode<T>* nNode){
	if (subtree == nullptr)
		return nNode;
	else
	{
		BNode<T>* leftPtr = subtree->lchild;
		BNode<T>* rightPtr = subtree->rchild;
		if (gHeiHlp(leftPtr) > gHeiHlp(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, nNode);
			subtree->rchild = rightPtr;
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, nNode);
			subtree->lchild = leftPtr;
			return subtree;
		}
	}
}
template<class T>
void print(T& x){
	cout << x << " ";
}
template<class T>
bool Tree<T>::add(const T& nData)
{
	BNode<T>* nNode = new BNode<T>(nData);
	root = bstAdd(root, nNode);
	return true;
}
template<class T>
void Tree<T>::preTrav(void visit(T&)) const{
	preOrder(visit, root);
}
