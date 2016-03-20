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
	void add(DT& x); //Adds a new datatype
	void insertAt(int i, DT& x); //Insert an element at a given index
	void removeAt(int i); //Remove an element at a given index
	void expand(); //Expand the array capacity
	void empty(); //Empty the array
	int getCapacity(); //Return the array capacity
	int getSize(); //Return the array size
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
	bool CellNode<DT1, DT2>::contains(int key);
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
	vector<vector<char>> findKeywords(int key);
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
void vector<DT>::add(DT & x) {
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

template<class DT>
Cell<DT>::Cell() {
	DT* _value = nullptr;
	Cell<DT>* _right = nullptr;
}

template<class DT>
Cell<DT>::Cell(DT* v) {
	_value = v;
	_right = nullptr;
}

template<class DT>
Cell<DT>::Cell(const Cell<DT>& c) {
	_value = c._value;
	_right = c._right;
}

template<class DT>
Cell<DT>::~Cell() {
}

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
//Project 4 files

//Return a list of info variables corresponding to cell nodes containing the key
template<class DT1, class DT2>
vector<vector<char>> MasterCell<DT1, DT2>::findKeywords(int key) {
	vector<vector<char>> matchingNodes;
	//For each cell node
	for (int i = 0; i < numNodes; i++) {
		//If the cell node contains the key add its info to the list
		if (_myCellNodes[i].contains(key)) {
			matchingNodes.add(*_myCellNodes[i].getInfo());
		}
	}

//	for (Cell<DT2>* c = _myCell; c != nullptr; c = c->getRight()) {
//		if (intMatch(c->getValue(), key)) {
//			return true;
//		}
//	}
	return matchingNodes;
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
int vectorCharToInt(vector<char> charForm) {
	int sum = 0;
	int multiplier = 1;
	int length = charForm.getSize();
	for(int i = (length -1) ; i >= 0; i--) {
		sum += (charForm[i] - ASCIIOFFSET) * multiplier;
		multiplier *= 10;
	}
	return sum;
}
bool intMatch(vector<char> charForm, int i) {
	if (vectorCharToInt(charForm) == i){
	return true;
	}
	return false;
}
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
int main() {
	char blank = ' ';
	int noItems;
	char c;
	int count = 0;
	MasterCell<vector<char>, vector<char>> masterCell;
	while (!cin.eof()) {
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
			bool b = (bool)cin;
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
		if (cin.eof()) break;
	}
	//End of file
	cout << "Single master cell object created from input" << endl << "Each line is a cell node, followed by all of its contained cells" << endl << endl;
	cout << masterCell << endl;
	cout<< masterCell.findKeywords(3);

/*
	///Call the methods for each class to demonstrate that they work
	//	Demonstrate	the	working	of the classes with	two	different data types: int and character strings.

	vector<char>* testInfo = new vector<char>;
	char testChar = 'i';
	(*testInfo).add(testChar);
	vector<char>* testValue = new vector<char>;
	char testChar2 = 'v';
	(*testValue).add(testChar2);
	{
		//Cell
		//Cell(); //Default constructor
		Cell<vector<char>>* emptyCell = new Cell<vector<char>>();
		cout << "Empty cell: " << *emptyCell << endl;
		//Cell(DT* v); //Initializer
		Cell<vector<char>>filledCell = Cell<vector<char>>(testValue);
		//friend ostream& operator<< (ostream& s, Cell<T>& c); //Overloaded ostream operator
		cout << "Filled cell: " << filledCell << endl;
		//Cell(const Cell<DT>& c);//Copy constructor
		Cell<vector<char>> copyOfCell = Cell<vector<char>>(filledCell);
		cout << "Copy of cell: " << copyOfCell << endl;
		//void operator= (const Cell<DT>& c);//Overloaded assignment operator
		Cell<vector<char>> assignedCopyOfCell = copyOfCell;
		cout << "Assigned copy of cell: " << assignedCopyOfCell << endl;
		//void setRight(Cell<DT>* cellPointer);
		copyOfCell.setRight(&assignedCopyOfCell);
		//Cell<DT>* getRight();
		cout << "Right cell: " << *copyOfCell.getRight() << endl;
		cout << endl;

		//CellNode
		//CellNode(); //Default constructor
		CellNode<vector<char>, vector<char>> emptyCellNode = CellNode<vector<char>, vector<char>>();
		cout << "Empty cell node: " << emptyCellNode << endl;
		//CellNode(DT1* i, Cell<DT2>* c);//Initializer
		CellNode<vector<char>, vector<char>> initializedCellNode = CellNode<vector<char>, vector<char>>(testInfo, &filledCell);
		//friend ostream& operator<< (ostream& s, CellNode<DT1, DT2>& cn); //Overloaded ostream operator
		cout << "Initialized cell node: " << initializedCellNode << endl;
		//CellNode(const CellNode<DT1, DT2>& cn);//Copy constructor
		CellNode<vector<char>, vector<char>> copiedCellNode = CellNode<vector<char>, vector<char>>(initializedCellNode);
		cout << "Copied cell node: " << copiedCellNode << endl;
		//void operator= (const CellNode<DT1, DT2>& c);//Overloaded assignment operator
		CellNode<vector<char>, vector<char>> assignedCellNode = initializedCellNode;
		cout << "Assigned cell node: " << assignedCellNode << endl;
		//Cell<DT2>* getFirstCell();
		cout << "First cell: " << *initializedCellNode.getFirstCell() << endl;
		//DT1* getInfo();
		cout << "Cell node info: " << *initializedCellNode.getInfo() << endl;
		cout << endl;

		// MasterCell
		//MasterCell();//Default constructor
		MasterCell<vector<char>, vector<char>> emptyMasterCell = MasterCell<vector<char>, vector<char>>();
		//friend ostream& operator<< (ostream& s, MasterCell<T1, T2>& mc); //Overloaded ostream operator
		cout << "Empty master cell: " << emptyMasterCell << endl;
		//MasterCell();//Initializer
		MasterCell<vector<char>, vector<char>> initializedMasterCell = MasterCell<vector<char>, vector<char>>(initializedCellNode);
		cout << "Initialized master cell: " << initializedMasterCell;
		//MasterCell(const MasterCell<DT1, DT2>& mc);//Copy constructor
		MasterCell<vector<char>, vector<char>> copiedMasterCell(initializedMasterCell);
		cout << "Copied master cell: " << copiedMasterCell;
		//void addCellNode(DT1* info, Cell<DT2>* cell);
		copiedMasterCell.addCellNode(testInfo, &filledCell);
		cout << "Added another cell node: " << copiedMasterCell;
		//void operator= (const MasterCell<DT1, DT2>& mc);//Overloaded assignment operator
		MasterCell<vector<char>, vector<char>> assignedMasterCell = copiedMasterCell;
		cout << "Assigned master cell: " << assignedMasterCell;
		//int getNumNodes();
		cout << "Assigned cell numNodes: " << assignedMasterCell.getNumNodes() << endl;
		//CellNode<DT1, DT2>* getCellNodes();
		for (int i = 0; i < assignedMasterCell.getNumNodes(); i++) {
			cout << "\tAssigned cell cellNode " << i << ' ' << assignedMasterCell.getCellNodes()[i] << endl;
		}
	}
	cout << endl;
	cout << "Repeated with integer values " << endl;
	cout << endl;

	//	Demonstrate	the	working	of the classes with	two	different data types: int and intacter strings.
	vector<int>* testIntInfo = new vector<int>;
	int testint = 1;
	(*testIntInfo).add(testint);
	vector<int>* testIntValue = new vector<int>;
	int testint2 = 2;
	(*testIntValue).add(testint2);

	//Cell
	//Cell(); //Default constructor
	Cell<vector<int>>* emptyCell = new Cell<vector<int>>();
	cout << "Empty cell: " << *emptyCell << endl;
	//Cell(DT* v); //Initializer
	Cell<vector<int>>filledCell = Cell<vector<int>>(testIntValue);
	//friend ostream& operator<< (ostream& s, Cell<T>& c); //Overloaded ostream operator
	cout << "Filled cell: " << filledCell << endl;
	//Cell(const Cell<DT>& c);//Copy constructor
	Cell<vector<int>> copyOfCell = Cell<vector<int>>(filledCell);
	cout << "Copy of cell: " << copyOfCell << endl;
	//void operator= (const Cell<DT>& c);//Overloaded assignment operator
	Cell<vector<int>> newCopyOfCell = copyOfCell;
	cout << "Assigned copy of cell: " << newCopyOfCell << endl;
	//void setRight(Cell<DT>* cellPointer);
	copyOfCell.setRight(&newCopyOfCell);
	//Cell<DT>* getRight();
	cout << "Right cell: " << *copyOfCell.getRight() << endl;
	cout << endl;

	//CellNode
	//CellNode(); //Default constructor
	CellNode<vector<int>, vector<int>> emptyCellNode = CellNode<vector<int>, vector<int>>();
	cout << "Empty cell node: " << emptyCellNode << endl;
	//CellNode(DT1* i, Cell<DT2>* c);//Initializer
	CellNode<vector<int>, vector<int>> intinitedCellNode = CellNode<vector<int>, vector<int>>(testIntInfo, &filledCell);
	//friend ostream& operator<< (ostream& s, CellNode<DT1, DT2>& cn); //Overloaded ostream operator
	cout << "Initialized cell node: " << intinitedCellNode << endl;
	//CellNode(const CellNode<DT1, DT2>& cn);//Copy constructor
	CellNode<vector<int>, vector<int>> copiedCellNode = CellNode<vector<int>, vector<int>>(intinitedCellNode);
	cout << "Copied cell node: " << copiedCellNode;
	//void operator= (const CellNode<DT1, DT2>& c);//Overloaded assignment operator
	CellNode<vector<int>, vector<int>> assignedCellNode = intinitedCellNode;
	cout << "Assigned cell node: " << assignedCellNode << endl;
	//Cell<DT2>* getFirstCell();
	cout << "First cell: " << *intinitedCellNode.getFirstCell() << endl;
	//DT1* getInfo();
	cout << "Cell node info: " << *intinitedCellNode.getInfo() << endl;
	cout << endl;

	// MasterCell
	//MasterCell();//Default constructor
	MasterCell<vector<int>, vector<int>> emptyMasterCell = MasterCell<vector<int>, vector<int>>();
	//friend ostream& operator<< (ostream& s, MasterCell<T1, T2>& mc); //Overloaded ostream operator
	cout << "Empty master cell: " << emptyMasterCell << endl;
	//MasterCell();//Initializer
	MasterCell<vector<int>, vector<int>> initializedMasterCell = MasterCell<vector<int>, vector<int>>(intinitedCellNode);
	cout << "Initialized master cell: " << initializedMasterCell;
	//MasterCell(const MasterCell<DT1, DT2>& mc);//Copy constructor
	MasterCell<vector<int>, vector<int>> copiedMasterCell(initializedMasterCell);
	cout << "Copied master cell: " << copiedMasterCell << endl;
	//void addCellNode(DT1* info, Cell<DT2>* cell);
	initializedMasterCell.addCellNode(testIntInfo, &filledCell);
	cout << "Added another cell node: " << initializedMasterCell;
	//void operator= (const MasterCell<DT1, DT2>& mc);//Overloaded assignment operator
	MasterCell<vector<int>, vector<int>> assignedMasterCell = copiedMasterCell;
	cout << "Assigned master cell: " << assignedMasterCell;
	//int getNumNodes();
	cout << "Initialized cell numNodes: " << assignedMasterCell.getNumNodes() << endl;
	//CellNode<DT1, DT2>* getCellNodes();
	for (int i = 0; i < initializedMasterCell.getNumNodes(); i++) {
		cout << "\tInitialized cell cellNode " << i << ' ' << initializedMasterCell.getCellNodes()[i] << endl;
	}
	cout << "Finished" << endl;
*/
	return 0;
}
