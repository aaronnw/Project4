# include <iostream>
using namespace std;
int ASCIIOFFSET = 48;
///Vector class to create and manage resizable arrays
template<class DT>
class vector {
	template<class T>
	friend ostream& operator<< (ostream& s, vector<T>& ac); //Overloaded ostream operator
private:
	DT* arrayOfDT;
	int numElements;
	int capacity;
	const int multiplier = 2;
	const int defaultCapacity = 50;
public:
	vector(); //Default constructor
	vector(int c); //Initializer constructor
	vector(const vector<DT>& ac); // Copy constructor
	~vector(); // Destructor
	void operator= (const vector<DT>& ac); //Overloaded assignment operator
	DT&  operator[](int i); //Overloaded [] operator
	void add(const DT& x); //Adds a new datatype
	void insertAt(int i, DT& x); //Insert an element at a given index
	void removeAt(int i); //Remove an element at a given index
	void expand(); //Expand the array capacity
	void empty(); //Empty the array
	int getCapacity(); //Return the array capacity
	int getSize(); //Return the array size
	DT* toArray(); //Returns an array of the contents of the current length
	bool contains(DT x); //Returns a value based on the vector contents
};

///////////////////////////////////////////////////////////////////////////////////////
///Cell object holding a pointer to a value and a pointer to another cell
template <class	DT>
class Cell {
	template<class T>
	friend ostream& operator<< (ostream& s, Cell<T>& c); //Overloaded ostream operator
protected:
	DT* _value;	//Value stored in the cell
	Cell<DT>* _right; //Pointer to the next cell
public:
	//All required methods	
	Cell(); //Default constructor
	Cell(DT* v); //Initializer
	Cell(const Cell<DT>& c);//Copy constructor
	~Cell();//Destructor
	void operator= (const Cell<DT>& c);//Overloaded assignment operator
	Cell<DT>* getRight(); //Return the pointer to the right cell
	void setRight(Cell<DT>* cellPointer); //Set the pointer to the right cell
	DT getValue();
};

///////////////////////////////////////////////////////////////////////////////////////
///Cell node holding a pointer to an info object and a pointer to the first cell
template <class	DT1, class	DT2>
class CellNode {
	template<class T1, class T2>
	friend ostream& operator<< (ostream& s, CellNode<DT1, DT2>& cn); //Overloaded ostream operator
protected:
	DT1* _info; //The info for the cell node
	Cell<DT2>* _myCell;  //Pointer to the first cell
public:
	//All required methods	
	CellNode();//Default constructor
	CellNode(DT1* i, Cell<DT2>* c);//Initializer
	CellNode(const CellNode<DT1, DT2>& cn);//Copy constructor
	~CellNode();//Destructor
	Cell<DT2>* getFirstCell(); //Return a pointer to the first cell
	DT1* getInfo(); //Return a pointer to the info
	void operator= (const CellNode<DT1, DT2>& c);//Overloaded assignment operator
	bool CellNode<DT1, DT2>::contains(int key);//Checks to see if the cell node contains a key
};

///////////////////////////////////////////////////////////////////////////////////////
///Master cell holding a vector list of cell nodes
template <class	DT1, class	DT2>
class MasterCell {
	template<class T1, class T2>
	friend ostream& operator<< (ostream& s, MasterCell<T1, T2>& mc); //Overloaded ostream operator
protected:
	CellNode<DT1, DT2>*	_myCellNodes;
	int numNodes;
public:
	//All required methods
	MasterCell();//Default constructor
	MasterCell(CellNode<DT1, DT2> cn);//Initializer
	MasterCell(const MasterCell<DT1, DT2>& mc);//Copy constructor
	~MasterCell();//Destructor
	void addCellNode(DT1* info, Cell<DT2>* cell); //Add a cell node to the master cell
	void operator= (const MasterCell<DT1, DT2>& mc);//Overloaded assignment operator
	CellNode<DT1, DT2>* getCellNodes(); //Return a pointer to the first cell node
	int getNumNodes() const; //Return the number of nodes in the master celltemplate<class DT1, class DT2>
	vector<vector<char>> findKeywords(int key); //Returns a list of info variables corresponding to cell nodes containing a key

	//Given two inputs, return an appropriate list of integers based on the values held in the master cell
	vector<int> And(char* input1, char* input2);
	vector<int> And(vector<int> input1, char* input2);
	vector<int> And(vector<char> input1, vector<char> input2);
	vector<int> And(vector<int> input1, vector<char> input2);
	vector<int> OR(char* input1, char* input2);
	vector<int> OR(vector<char> input1, vector<char> input2);
	vector<int> OR(vector<int> input1, char* input2);
	vector<int> OR(vector<int> input1, vector<char> input2);
	vector<int> ExclusiveOR(char* input1, char* input2);
	vector<int> ExclusiveOR(vector<char> input1, vector<char> input2);
	vector<int> ExclusiveOR(vector<int> input1, char* input2);
	vector<int> ExclusiveOR(vector<int> input1, vector<char> input2);

};

///////////////////////////////////////////////////////////////////////////////////////
//Vector methods 

///Default constructor
template<class DT>
vector<DT>::vector() {
	numElements = 0;
	capacity = defaultCapacity;
	arrayOfDT = new DT[capacity];
}
///Initializer constructor
template<class DT>
vector<DT>::vector(int c) {
	numElements = 0;
	capacity = c;
	arrayOfDT = new DT[capacity];
}
///Copy constructor
template<class DT>
vector<DT>::vector(const vector<DT>& ac) {
	numElements = ac.numElements;
	capacity = ac.capacity;
	arrayOfDT = new DT[capacity];
	for (int i = 0; i < capacity; i++) {
		arrayOfDT[i] = ac.arrayOfDT[i];
	}
}
///Destructor
template<class DT>
vector<DT>::~vector() {
	delete[] arrayOfDT;
}
///Overloaded assignment operator
template<class DT>
void vector<DT>::operator= (const vector<DT>& ac) {
	arrayOfDT = new DT[ac.capacity];
	for (int i = 0; i < ac.capacity; i++) {
		arrayOfDT[i] = ac.arrayOfDT[i];
	}
	numElements = ac.numElements;
	capacity = ac.capacity;
}
///Overloaded square bracket operator
template<class DT>
DT& vector<DT>::operator[](int i) {
	//TODO if ((i < 0) || (i >= (capacity - 1))) throw errors;
	return arrayOfDT[i];
}
///Add an element to the end of the array
template<class DT>
void vector<DT>::add(const DT & x) {
	//If there is room, add to the end of current array
	if (numElements < capacity) {
		arrayOfDT[numElements] = x;
		numElements++;
	}
	else {
		expand();
		add(x);
	}
}
///Insert an element into the array
template<class DT>
void vector<DT>::insertAt(int i, DT & x) {
	if ((numElements < capacity) && (i < capacity)) {
		for (int k = (numElements + 1); k > i; k--) {
			arrayOfDT[k] = arrayOfDT[k - 1];
		}
		arrayOfDT[i] = x;
		numElements++;
	}
	else {
		expand();
		insertAt(i, x);
	}
}
///Remove an element from a given index
template<class DT>
void vector<DT>::removeAt(int i) {
	for (i; i < (numElements); i++) {
		arrayOfDT[i] = arrayOfDT[i + 1];
	}
	numElements--;
	//error input
}
///Increase the size of the array
template<class DT>
void vector<DT>::expand() {
	//Create a copy of the current array with a larger capacity
	DT* newArray = new DT[capacity * multiplier];
	for (int i = 0; i < capacity; i++) {
		newArray[i] = arrayOfDT[i];
	}
	delete[] arrayOfDT;
	arrayOfDT = newArray;// new DT[capacity];

	capacity = capacity * multiplier;

}
///Show the array as empty
template<class DT>
void vector<DT>::empty() {
	numElements = 0;
}
///Return the capacity
template<class DT>
int vector<DT>::getCapacity() {
	return capacity;
}
///Return the number of elements
template<class DT>
int vector<DT>::getSize() {
	return numElements;
}
template<class DT>
DT * vector<DT>::toArray() {
	return arrayOfDT;
}
template<class DT>
bool vector<DT>::contains(DT x) {
	for (int i = 0; i < numElements; i++) {
		if (arrayOfDT[i] == x) {
			return true;
		}
	}
	return false;
}
///Overloaded ostream operator
template<class T>
ostream& operator<< (ostream& s, vector<T>& ac) {
	for (int i = 0; i < ac.getSize(); i++) {
		s << ac[i];
	}
	return s;

}

///////////////////////////////////////////////////////////////////////////////////////
//Cell Methods
///Default constructor
template<class DT>
Cell<DT>::Cell() {
	DT* _value = nullptr;
	Cell<DT>* _right = nullptr;
}
///Initializer
template<class DT>
Cell<DT>::Cell(DT* v) {
	_value = v;
	_right = nullptr;
}
///Copy constructor
template<class DT>
Cell<DT>::Cell(const Cell<DT>& c) {
	_value = c._value;
	_right = c._right;
}
///Destructor
template<class DT>
Cell<DT>::~Cell() {
}
///Overloaded assignment operator
template<class DT>
void Cell<DT>::operator=(const Cell<DT>& c) {
	_value = c._value;
	_right = c._right;
}

template<class DT>
Cell<DT>* Cell<DT>::getRight() {
	return _right;
}

template<class DT>
void Cell<DT>::setRight(Cell<DT>* cellPointer) {
	_right = cellPointer;
}

template<class DT>
DT Cell<DT>::getValue() {
	return *_value;
}

///////////////////////////////////////////////////////////////////////////////////////
//Cell Node Methods

///Default constructor
template<class DT1, class DT2>
CellNode<DT1, DT2>::CellNode() {
	DT1* _info = nullptr; //The info for the cell node
	Cell<DT2>* _myCell = nullptr;  //Pointer to the first cell
}
///Initializer
template<class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(DT1* i, Cell<DT2>* c) {
	_info = i;
	_myCell = c;
}
///Copy constructor
template<class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(const CellNode<DT1, DT2>& cn) {
	_info = cn._info;
	_myCell = cn._myCell;
}
///Destructor
template<class DT1, class DT2>
CellNode<DT1, DT2>::~CellNode() {
}

template<class DT1, class DT2>
Cell<DT2>* CellNode<DT1, DT2>::getFirstCell() {
	return _myCell;
}
template<class DT1, class DT2>
DT1 * CellNode<DT1, DT2>::getInfo() {
	return _info;
}
///Overloaded assignment operator
template<class DT1, class DT2>
void CellNode<DT1, DT2>::operator=(const CellNode<DT1, DT2>& cn) {
	_info = cn._info;
	_myCell = cn._myCell;
}

template<class DT1, class DT2>
bool CellNode<DT1, DT2>::contains(int key) {
	for (Cell<DT2>* c = _myCell; c != nullptr; c = c->getRight()) {
		if (intMatch(c->getValue(), key)) {
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
//Master Cell Methods

template<class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell() {
	numNodes = 0;
	CellNode<DT1, DT2>*	_myCellNodes = nullptr;
}

template<class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(CellNode<DT1, DT2> cn) {
	numNodes = 1;
	_myCellNodes = new CellNode<DT1, DT2>[1];
	_myCellNodes[0] = cn;
}

template<class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(const MasterCell<DT1, DT2>& mc) {
	*this = mc;
}

template<class DT1, class DT2>
MasterCell<DT1, DT2>::~MasterCell() {
}

template<class DT1, class DT2>
void MasterCell<DT1, DT2>::addCellNode(DT1* info, Cell<DT2>* cell) {
	CellNode<DT1, DT2>* tmp = _myCellNodes;
	_myCellNodes = new CellNode<DT1, DT2>[numNodes + 1];
	for (int i = 0; i < numNodes; ++i) {
		_myCellNodes[i] = tmp[i];
	}
	_myCellNodes[numNodes] = CellNode<DT1, DT2>(info, cell);
	numNodes++;
	if (_myCellNodes)
		delete[] tmp;
}

template<class DT1, class DT2>
void MasterCell<DT1, DT2>::operator=(const MasterCell<DT1, DT2>& mc) {
	//_myCellNodes = mc._myCellNodes;
	numNodes = mc.numNodes;
	_myCellNodes = new CellNode<DT1, DT2>[numNodes];
	for (int i = 0; i < numNodes; ++i) {
		_myCellNodes[i] = mc._myCellNodes[i];
	}
}

template<class DT1, class DT2>
CellNode<DT1, DT2>* MasterCell<DT1, DT2>::getCellNodes() {
	return _myCellNodes;
}

template<class DT1, class DT2>
int MasterCell<DT1, DT2>::getNumNodes() const {
	return numNodes;
}
///////////////////////////////////////////////////////////////////////////////////////
//Project 4 methods

//Return a list of info variables corresponding to cell nodes containing the key
template<class DT1, class DT2>
vector<vector<char>> MasterCell<DT1, DT2>::findKeywords(int key) {
	vector<vector<char>> matchingNodes;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
	//For searching through the whole list	
	//If the cell node contains the key add its info to the list
		if (_myCellNodes[i].contains(key)) {
			matchingNodes.add(*_myCellNodes[i].getInfo());
		}
/*
//For searching only the first value
		if (intMatch((*_myCellNodes[i].getFirstCell()).getValue(), key)) {
			matchingNodes.add(*_myCellNodes[i].getInfo());
		}	*/
	}

	return matchingNodes;
}

//AND methods with different parameters
//Return all integers common to two keywords

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::And(char* input1, char* input2) {
	vector<char> keyword1 = inputStringToVector(input1);
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> commonIntegers;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through first node checking to see if the second has any integers in commmon
	for (Cell<DT2>* c = cn1.getFirstCell(); c != nullptr; c = c->getRight()) {
		if (cn2.contains(vectorCharToInt((*c).getValue()))) {
			commonIntegers.add(vectorCharToInt((*c).getValue()));
		}
	}
	return commonIntegers;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::And(vector<char> input1, vector<char> input2) {
	vector<int> commonIntegers;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), input1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through first node checking to see if the second has any integers in commmon
	for (Cell<DT2>* c = cn1.getFirstCell(); c != nullptr; c = c->getRight()) {
		if (cn2.contains(vectorCharToInt((*c).getValue()))) {
			commonIntegers.add(vectorCharToInt((*c).getValue()));
		}
	}
	return commonIntegers;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::And(vector<int> input1, char* input2) {
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> commonIntegers;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through first node checking to see if the second has any integers in commmon
	for (Cell<DT2>* c = cn2.getFirstCell(); c != nullptr; c = c->getRight()) {
		if (input1.contains(vectorCharToInt((*c).getValue()))) {
			commonIntegers.add(vectorCharToInt((*c).getValue()));
		}
	}
	return commonIntegers;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::And(vector<int> input1, vector<char> input2) {
	vector<int> commonIntegers;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through first node checking to see if the second has any integers in commmon
	for (Cell<DT2>* c = cn2.getFirstCell(); c != nullptr; c = c->getRight()) {
		if (input1.contains(vectorCharToInt((*c).getValue()))) {
			commonIntegers.add(vectorCharToInt((*c).getValue()));
		}
	}
	return commonIntegers;
}

//OR methods with different parameters
//Return all integers in either of two keywords

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::OR(char* input1, char* input2) {
	vector<char> keyword1 = inputStringToVector(input1);
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> intList;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both nodes, only adding one of each integer
	for (Cell<DT2>* c1 = cn1.getFirstCell(); c1 != nullptr; c1 = c1->getRight()) {
		if (!cn2.contains(vectorCharToInt(c1->getValue()))) {
			intList.add(vectorCharToInt(c1->getValue()));
		}
	}
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		intList.add(vectorCharToInt(c2->getValue()));
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::OR(vector<char> input1, vector<char> input2) {
	vector<int> intList;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), input1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both nodes, only adding one of each integer
	for (Cell<DT2>* c1 = cn1.getFirstCell(); c1 != nullptr; c1 = c1->getRight()) {
		if (!cn2.contains(vectorCharToInt(c1->getValue()))) {
			intList.add(vectorCharToInt(c1->getValue()));
		}
	}
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		intList.add(vectorCharToInt(c2->getValue()));
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::OR(vector<int> input1, char* input2) {
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> intList;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both nodes, only adding one of each integer
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!input1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	for (int i = 0; i < input1.getSize(); i++) {
		intList.add(input1[i]);
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::OR(vector<int> input1, vector<char> input2) {
	vector<int> intList;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both nodes, only adding one of each integer
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!input1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	for (int i = 0; i < input1.getSize(); i++) {
		intList.add(input1[i]);
	}
	return intList;
}

//XOR methods with different parameters
//Return all integers unique between two keywords

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::ExclusiveOR(char* input1, char* input2) {
	vector<char> keyword1 = inputStringToVector(input1);
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> intList;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both lists, only adding integers that do not exist in the other
	for (Cell<DT2>* c1 = cn1.getFirstCell(); c1 != nullptr; c1 = c1->getRight()) {
		if (!cn2.contains(vectorCharToInt(c1->getValue()))) {
			intList.add(vectorCharToInt(c1->getValue()));
		}
	}
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!cn1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::ExclusiveOR(vector<char> input1, vector<char> input2) {
	vector<int> intList;
	CellNode<DT1, DT2> cn1;
	CellNode<DT1, DT2> cn2;
	bool cn1Found = false;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), input1)) {
			cn1 = _myCellNodes[i];
			cn1Found = true;
		}
		else if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both lists, only adding integers that do not exist in the other
	for (Cell<DT2>* c1 = cn1.getFirstCell(); c1 != nullptr; c1 = c1->getRight()) {
		if (!cn2.contains(vectorCharToInt(c1->getValue()))) {
			intList.add(vectorCharToInt(c1->getValue()));
		}
	}
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!cn1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::ExclusiveOR(vector<int> input1, char* input2) {
	vector<char> keyword2 = inputStringToVector(input2);
	vector<int> intList;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), keyword2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both lists, only adding integers that do not exist in the other
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!input1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	for (int i = 0; i < input1.getSize(); i++) {
		if (!cn2.contains(int[i])) {
			intList.add(input1[i]);
		}
	}
	return intList;
}

template<class DT1, class DT2>
vector<int> MasterCell<DT1, DT2>::ExclusiveOR(vector<int> input1, vector<char> input2) {
	vector<int> intList;
	CellNode<DT1, DT2> cn2;
	bool cn2Found = false;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (stringMatch(*_myCellNodes[i].getInfo(), input2)) {
			cn2 = _myCellNodes[i];
			cn2Found = true;
		}
	}
	//Iterate through both lists, only adding integers that do not exist in the other
	for (Cell<DT2>* c2 = cn2.getFirstCell(); c2 != nullptr; c2 = c2->getRight()) {
		if (!input1.contains(vectorCharToInt(c2->getValue()))) {
			intList.add(vectorCharToInt(c2->getValue()));
		}
	}
	for (int i = 0; i < input1.getSize(); i++) {
		if (!cn2.contains(input1[i])) {
			intList.add(input1[i]);
		}
	}
	return intList;
}

///////////////////////////////////////////////////////////////////////////////////////
//Overloaded ostream operators

template<class T>
ostream& operator<< (ostream& s, Cell<T>& c) {
	if (c._value != nullptr) {
		s << *c._value;
	}
	return s;

}

template<class T1, class T2>
ostream& operator<< (ostream& s, CellNode<T1, T2>& cn) {
	if (cn.getInfo() != nullptr) {
		s << *cn.getInfo() << ',' << ' ';
	}
	for (Cell<T2>* cell = (cn.getFirstCell()); cell != nullptr; cell = ((*cell).getRight())) {
		s << *cell << ' ';
	}
	return s;
}

template<class T1, class T2>
ostream& operator<< (ostream& s, MasterCell<T1, T2>& mc) {
	CellNode<T1, T2>* nodeList = mc.getCellNodes();
	for (int i = 0; i < mc.getNumNodes(); i++) {
		cout << nodeList[i];
		cout << endl;
	}
	return s;

}

///////////////////////////////////////////////////////////////////////////////////////

//Converts a vector of type character into an int
int vectorCharToInt(vector<char> charForm) {
	int sum = 0;
	int multiplier = 1;
	int length = charForm.getSize();
	for (int i = (length - 1); i >= 0; i--) {
		sum += (charForm[i] - ASCIIOFFSET) * multiplier;
		multiplier *= 10;
	}
	return sum;
}
//Converts a string to an vector of type character
vector<char> inputStringToVector(char* inputString) {
	vector<char> resultVector;
	int i = 0;
	while (inputString[i] != NULL) {
		resultVector.add(inputString[i]);
		i++;
	}
	return resultVector;
}
//Compares a vector of type character to an int
bool intMatch(vector<char> charForm, int i) {
	if (vectorCharToInt(charForm) == i) {
		return true;
	}
	return false;
}
//Compares two strings
bool stringMatch(vector<char> string1, vector<char> string2) {
	if (string1.getSize() != string2.getSize()) {
		return false;
	}
	for (int i = 0; i < string1.getSize(); i++) {
		if (string1[i] != string2[i]) {
			return false;
		}
	}
	return true;
}
//Display a a list of ints in a specific format
void displayIntList(vector<int> listOfInts) {
	if (listOfInts.getSize() == 1) {
		cout << listOfInts[0];
	}
	else if(listOfInts.getSize() >1) {
		cout << listOfInts[0];
		for (int i = 1; i < listOfInts.getSize(); i++) {
			cout << ", " << listOfInts[i];
		}
	}
	cout << endl;
}
//Main method
int main() {
	char blank = ' ';
//	int noItems; --Removed for project 4 based on example
	char c;
	int numCellNodes = 0;
	int count = 0;
	int linecount = 0;
	int noItems;
	cin >> numCellNodes;
	cin.get(c);
	while (c != '\n'){
		cin.get(c);
	}
	MasterCell<vector<char>, vector<char>> masterCell;
	//Read what to add to the master cell
	while ((!cin.eof()) && (linecount < numCellNodes)) {
		Cell<vector<char>>* previousCell = new Cell<vector<char>>();
		vector<char>* info = new vector<char>;
		count = 0;
		//Read in the first values
		cin.get(c);
		while (c != ',' && !cin.eof()) {
			(*info).add(c);
			cin.get(c);
		}
		cin.get(blank);
		cin >> noItems; 
		cin.get(blank);
		//Read in the values
		do {
			vector<char>* value = new vector<char>();
			cin.get(c);
			//While there is a valid character read it in
			while ((c != ' ') && (c != '\n') && (!cin.eof())) {
				(*value).add(c);
				cin.get(c);
			}
			//If there is a space and a value has been read
			if ((*value).getSize() >= 1) {
				//Create a new cell with the value
				Cell<vector<char>>* cell = new Cell<vector<char>>(value);
				//Only run for the first cell information in a line
				if (count == 0) {
					//Add the cell and the info to the master cell, which will create a cell node
					masterCell.addCellNode(info, cell);
					previousCell = cell;
					count++;
				}
				else {
					//Give the previous cell a pointer to the new cell
					(*previousCell).setRight(cell);
					previousCell = cell;
				}
			}
			else {
				break;
			}
		} while ((c != '\n') && (!cin.eof()));
		//End of line
		linecount++;
		if (cin.eof()) break;
	}
	//Print master cell and explanation
	cout << "Single master cell object created from input" << endl << "Each line is a cell node, followed by all of its contained cells" << endl << endl;
	cout << masterCell << endl;
	//Read the boolean entries for the project 4 bonus
	while (!cin.eof()) {
		vector<char>* boolQuery = new vector<char>();
		vector<vector<char>>* boolQueryList = new vector<vector<char>>();
		vector<char>* operators = new vector<char>();
		vector<int>* singleResult = new vector<int>;
		vector<int>* result = new vector<int>;
		//For each line 
		do {
			cin.get(c);
			//While there is a valid character read it in
			if (c == '\n') {
				break;
			}
			else if ((c == '|') || (c == '%') || (c == '&')) {
				(*operators).add(c);
				//Trim the extra spaces
				while( (*boolQuery)[(boolQuery->getSize() - 1)] == ' ') {
					boolQuery->removeAt(boolQuery->getSize() - 1);
				}
				boolQueryList->add(*boolQuery);
				boolQuery = new vector<char>();
				cin.get(c);
			}
			else {
				boolQuery->add(c);
			}
		} while ((c != '\n') && (!cin.eof()));
		//Add the last boolean query in the line
		while ((*boolQuery)[(boolQuery->getSize() - 1)] == ' ') {
			boolQuery->removeAt(boolQuery->getSize() - 1);
		}
		boolQueryList->add(*boolQuery);
		//End of line, do operations
		//First operation
		if ((*operators)[0] == '&') {
			*singleResult = masterCell.And((*boolQueryList)[0], (*boolQueryList)[1]);
			for (int i = 0; i < singleResult->getSize(); i++) {
				(*result).add((*singleResult)[i]);
			}
		}
		else if ((*operators)[0] == '|') {
			*singleResult = masterCell.OR((*boolQueryList)[0], (*boolQueryList)[1]);
			for (int i = 0; i < singleResult->getSize(); i++) {
				(*result).add((*singleResult)[i]);
			}
		}
		else if ((*operators)[0] == '%') {
			*singleResult = masterCell.ExclusiveOR((*boolQueryList)[0], (*boolQueryList)[1]);
			for (int i = 0; i < singleResult->getSize(); i++) {
				(*result).add((*singleResult)[i]);
			}
		}
		//For each of the rest of the operations
		for (int i = 1; i < operators->getSize(); i++) {
			if ((*operators)[i] == '&') {
				*result = masterCell.And( (*result) , (*boolQueryList)[i+1]);
			}
			else if ((*operators)[i] == '|') {
				*result = masterCell.OR((*result), (*boolQueryList)[i+1]);
			}
			else if ((*operators)[i] == '%') {
				*result = masterCell.ExclusiveOR((*result) , (*boolQueryList)[i+1]);
			}
		}
		//Print results of boolean operations
	//	cout << *result << endl;
		displayIntList(*result);
	}
	//End of file
/*	 Testing Project 4 methods with example file
	cout << masterCell.findKeywords(3) << endl;
	cout << masterCell.And("Compiler Construction", "Theory of Computation") << endl;
	cout << masterCell.OR("Compiler Construction", "Theory of Computation") << endl;
	cout << masterCell.ExclusiveOR("Compiler Construction", "Theory of Computation") << endl;
	*/
	return 0;
}