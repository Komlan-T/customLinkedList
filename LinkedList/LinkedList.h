#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
struct LinkedList {
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node() {
			data = {};
			next = nullptr;
			prev = nullptr;
		}
	};
	Node* headPtr;
	Node* tailPtr;
	size_t counter;

	/*==== Behaviors ====*/
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	/*==== Accessors ====*/
	size_t NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(size_t index) const;
	Node* GetNode(size_t index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	/*==== Insertion ====*/
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, size_t count);
	void AddNodesTail(const T* data, size_t count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, size_t index);

	/*==== Removal ====*/
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(size_t index);
	void Clear();

	/*==== Operators ====*/
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T> rhs);
	
	/*==== Construction / Destruction ====*/
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();
};
/*Default constructor*/
template <typename T>
LinkedList<T>::LinkedList() {
	headPtr = nullptr;
	tailPtr = nullptr;
	counter = 0;
}
/*Copy constructor*/
template <typename T>
/*Sets "this" to a copy of the passed in LinkedList. For example, if the other list has
10 nodes, with values of 1-10? "this" should have a copy of that same data. */
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	headPtr = nullptr;
	tailPtr = nullptr;
	counter = 0;
	Node* oldList = list.headPtr;
	while (oldList != nullptr) {
		AddTail(oldList->data);
		oldList = oldList->next;
	}
}
template <typename T>
/*Assignment operator. After listA = listB, listA == listB is true. Can you utilize any
of your existing functions to make write this one? (Hint: Yes you can.)*/
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> rhs) {
	LinkedList<T> temp(rhs);
	swap(temp.headPtr, headPtr);
	swap(temp.tailPtr, tailPtr);
	return *this;
}
/*Destructor*/
template <typename T>
LinkedList<T>::~LinkedList() {
	Node* deletePtr = headPtr;
	while (deletePtr != nullptr) {
		headPtr = headPtr->next;
		delete deletePtr;
		deletePtr = headPtr;
	}
	headPtr = nullptr;
	tailPtr = nullptr;
	counter = 0;
}
template <typename T>
/*Overloaded subscript operator. Takes an index, and returns data from the index-
th node. Throws an out_of_range exception for an invalid index. Const and non-
const versions. */
const T& LinkedList<T>::operator[](size_t index) const {
	if (index > counter) {
		throw out_of_range("Invalid index");
	}
	//Iterate through nodes "index" amound of times
	Node* find = headPtr;
	int _counter = 0;
	while (_counter != index) {
		_counter++;
		find = find->next;
	}
	return find->data;
}
template <typename T>
/*Overloaded subscript operator. Takes an index, and returns data from the index-
th node. Throws an out_of_range exception for an invalid index. Const and non-
const versions. */
T& LinkedList<T>::operator[](size_t index) {
	if (index > counter) {
		throw out_of_range("Invalid index");
	}
	Node* find = headPtr;
	int _counter = 0;
	while (_counter != index) {
		_counter++;
		find = find->next;
	}
	return find->data;
}
/*How many things are stored in this list?*/
template <typename T>
size_t LinkedList<T>::NodeCount() const {
	return counter;
}
/*Create a new Node at the front of the list to store the passed in parameter.*/
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* newNode = new Node();
	counter++;
	if (headPtr == nullptr) {
		newNode->data = data;
		newNode->next = headPtr;
		newNode->prev = nullptr;
		headPtr = newNode;
		tailPtr = newNode;
	}
	else {
		newNode->data = data;
		newNode->next = headPtr;
		newNode->prev = nullptr;
		headPtr->prev = newNode;
		headPtr = newNode;
	}
}
/*Create a new Node at the end of the list to store the passed in parameter.*/
template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* newNode = new Node();
	counter++;
	newNode->data = data;
	if (headPtr == nullptr) {
		newNode->next = headPtr;
		headPtr = newNode;
		tailPtr = newNode;
	}
	else {
		Node* findLast = headPtr;
		while (findLast->next != nullptr) {
			findLast = findLast->next;
		}
		findLast->next = newNode;
		newNode->prev = tailPtr;
		tailPtr = newNode;
	}
}
/*Given an array of values, insert a node for each of those at the beginning of the
list, maintaining the original order.
*/
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, size_t count) {
	for (int i = count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}
/*Ditto, except adding to the end of the list.*/
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, size_t count) {
	for (size_t i = 0; i < count; i++) {
		AddTail(data[i]);
	}
}
/*Iterator through all of the nodes and print out their values, one a time.*/
template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* nodes = headPtr;
	while (nodes->next != nullptr) {
		cout << nodes->data << endl;
		nodes = nodes->next;
	}
	cout << tailPtr->data << endl;
}
/*Exactly the same as PrintForward, except completely the opposite.*/
template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* nodes = tailPtr;
	while (nodes->prev != nullptr) {
		cout << nodes->data << endl;
		nodes = nodes->prev;
	}
	cout << headPtr->data << endl;
}
/*Returns the head pointer. Const and non-const versions*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return headPtr;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return headPtr;
}
/*Returns the tail pointer. Const and non-const versions*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tailPtr;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tailPtr;
}
template <typename T>
/*Find the first node with a data value matching the passed in parameter,
returning a pointer to that node. Returns nullptr if no matching node found.*/
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	if (headPtr == nullptr) {
		return nullptr;
	}
	else {
		Node* find = headPtr;
		while (find->next != nullptr) {
			find = find->next;
			if (find->data == data) {
				return find;
			}
		}
		return nullptr;
	}
}
template <typename T>
/*Find the first node with a data value matching the passed in parameter,
returning a pointer to that node. Returns nullptr if no matching node found.*/
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	if (headPtr == nullptr) {
		return nullptr;
	}
	else {
		Node* find = headPtr;
		while (find->next != nullptr) {
			find = find->next;
			if (find->data == data) {
				return find;
			}
		}
		return nullptr;
	}
}
template <typename T>
/*Find all nodes which match the passed in parameter value, and store a pointer to
that node in the passed in vector. Use of a parameter like this (passing a
something in by reference, and storing data for later use) is called an output
parameter. */
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* find = headPtr;
	while (find != nullptr) {
		if (find->data == value) {
			outData.push_back(find);
		}
		find = find->next;
	}
}
template <typename T>
/*Given an index, return a pointer to the node at that index. Throws an exception
of type out_of_range if the index is out of range. Const and non-const versions.*/
typename LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index) {
	if (index >= counter) {
		throw out_of_range("Invalid index.");
	}
	Node* find = headPtr;
	size_t _counter = 0;
	while (find->next != nullptr) {
		if (_counter == index) {
			return find;
		}
		_counter++;
		find = find->next;
	}
	return nullptr;
}
template <typename T>
/*Given an index, return a pointer to the node at that index. Throws an exception
of type out_of_range if the index is out of range. Const and non-const versions.*/
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index) const {
	if (index >= counter) {
		throw out_of_range("Invalid index.");
	}
	Node* find = headPtr;
	int _counter = 0;
	while (find->next != nullptr) {
		if (_counter == index) {
			return find;
		}
		_counter++;
		find = find->next;
	}
	return nullptr;
}
template <typename T>
/*Given a pointer to a node, create a new node to store the passed in value, after
the indicated node.*/
void LinkedList<T>::InsertAfter(LinkedList<T>::Node* node, const T& data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = node->next;
	newNode->prev = node;
	node->next = newNode;
	newNode->next->prev = newNode;
	counter++;
}
template <typename T>
/*Ditto, except insert the new node before the indicated node.
*/
void LinkedList<T>::InsertBefore(LinkedList<T>::Node* node, const T& data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->prev = node->prev;
	newNode->next = node;
	node->prev = newNode;
	newNode->prev->next = newNode;
	counter++;
}
template <typename T>
/*Inserts a new Node to store the first parameter, at the index-th location. So if
you specified 3 as the index, the new Node should have 3 Nodes before it.
Throws an out_of_range exception if given an invalid index.*/
void LinkedList<T>::InsertAt(const T& data, size_t index) {
	if (index > counter) {
		throw out_of_range("Invalid index.");
	}
	else if (index == counter) {
		AddTail(data);
	}
	else if (index == 0) {
		AddHead(data);
	}
	else {
		size_t _counter = 0;
		Node* iterate = headPtr;
		Node* newNode = new Node();
		Node* prevNode = GetNode(index - 1);
		newNode->data = data;
		while (iterate != nullptr) {
			if (_counter == index) {
				newNode->next = prevNode->next;
				newNode->prev = prevNode;
				prevNode->next = newNode;
				newNode->next->prev = newNode;
			}
			_counter++;
			iterate = iterate->next;
		}
		counter++;
	}
}
template <typename T>
/*Overloaded equality operator. Given listA and listB, is listA equal to listB? What
would make one Linked List equal to another? If each of its nodes were equal to
the corresponding node of the other. (Similar to comparing two arrays, just with
non-contiguous data).*/
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	Node* oldList = rhs.headPtr;
	Node* currList = headPtr;
	if (counter != rhs.counter) {
		return false;
	}
	while ((oldList != nullptr) && (currList != nullptr)) {
		if (oldList->data == currList->data) {
			return true;
		}
		else {
			return false;
		}
		oldList = oldList->next;
		currList = currList->next;
	}
	return 0;
}
template <typename T>
/*Deletes the first Node in the list. Returns whether or not the Node was removed.*/
bool LinkedList<T>::RemoveHead(){
	if (headPtr == nullptr) {
		return false;
	}
	Node* firstNode = headPtr;
	headPtr = headPtr->next;
	if(headPtr != nullptr){
		headPtr->prev = nullptr;
	}
	delete firstNode;
	counter--;
	if (counter == 0) {
		headPtr = nullptr;
		tailPtr = nullptr;
	}
	return true;
}
template <typename T>
/*Deletes the last Node, returning whether or not the operation was successful.*/
bool LinkedList<T>::RemoveTail(){
	if (tailPtr == nullptr) {
		return false;
	}
	Node* lastNode = tailPtr;
	tailPtr = tailPtr->prev;
	if (tailPtr != nullptr) {
		tailPtr->next = nullptr;
	}
	delete lastNode;
	counter--;
	if (counter == 0) {
		headPtr = nullptr;
		tailPtr = nullptr;
	}
	return true;
}
template <typename T>
/*Remove ALL Nodes containing values matching that of the passed-in parameter. 
Returns how many instances were removed.*/
unsigned int LinkedList<T>::Remove(const T& data){
	unsigned int instances = 0;
	Node* iterate = headPtr;
	size_t index = 0;
	while (iterate != nullptr) {
	if (iterate->data == data) {
		RemoveAt(index);
		instances++;
	}
	index++;
	iterate = iterate->next;
}
	return instances;

	/*unsigned int instances = 0;
	Node* iterate = headPtr;
	size_t index = 0;
	vector<Node*> nodesFound;
	FindAll(nodesFound, data);
	for (size_t i = 0; i < nodesFound.size(); i++) {
		if (nodesFound[i] == headPtr) {
			RemoveHead();
			instances++;
			continue;
		}
		else if (nodesFound[i] == tailPtr) {
			RemoveTail();
			instances++;
			continue;
		}
		else {
			while (iterate != nullptr) {
				if (iterate == nodesFound[i]) {
					RemoveAt(index);
					instances++;
				}
				index++;
				iterate = iterate->next;
			}
		}
	}
	counter = counter - instances;
	return instances;*/
}
template <typename T>
/*Deletes the index-th Node from the list, returning whether or not the operation 
was successful.*/
bool LinkedList<T>::RemoveAt(size_t index) {
	if (index > counter) {
		return false;
	}
	else if (index == counter) {
		RemoveTail();
	}
	else if (index == 0) {
		RemoveHead();
	}
	else {
		Node* prevNode = GetNode(index - 1);
		Node* currNode = GetNode(index);
		prevNode->next = currNode->next;
		currNode->next->prev = currNode->prev;
		delete currNode;	
		counter--;
		return true;
	}
	return 0;
}
template <typename T>
/*Deletes all Nodes. Don’t forget the node count—how many nodes do you have 
after you deleted all of them?*/
void LinkedList<T>::Clear(){
	Node* clear = headPtr;
	while (clear != nullptr) {
		headPtr = headPtr->next;
		delete clear;
		clear = headPtr;
	}
	headPtr = nullptr;
	tailPtr = nullptr;
	counter = 0;
}
template <typename T>
/* This function takes in a pointer to a Node—a starting node. From that node, 
recursively visit each node that follows, in forward order, and print their values.
This function MUST be implemented using recursion, or tests using it will be 
worth no points. Check your textbook for a reference on recursion.*/
void LinkedList<T>::PrintForwardRecursive(const LinkedList<T>::Node* node) const{
	if (node == nullptr) {
		return;
	}
	cout << node->data << endl;
	PrintForwardRecursive(node->next);
}
template <typename T>
/* Same deal as PrintForwardRecursive, but in reverse*/
void LinkedList<T>::PrintReverseRecursive(const LinkedList<T>::Node* node) const{
	if (node == nullptr) {
		return;
	}
	cout << node->data << endl;
	PrintReverseRecursive(node->prev);
}