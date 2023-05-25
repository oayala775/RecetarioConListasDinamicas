#ifndef IngredientsList_H
#define IngredientsList_H
#include <fstream>
#include <iostream>
#include <string>
#pragma once

using std::cin;
using std::cout;
using std::string;

template <typename T>
class IngredientsList {
 private:
  class Node {
   private:
    T data;
    Node* next;

   public:
    Node();
    Node(T& data);

    T& getData();
    Node* getNext();

    void setData(T& data);
    void setNext(Node* next);
  };

 private:
  Node* anchor;
  bool isValidPos(Node* node);

 public:
  typedef Node* Position;

  IngredientsList();
  IngredientsList(IngredientsList& copyList);
  bool isEmpty();
  // bool isFull();
  void insertData(T element, Node* node);
  void insertSortedData(T element);
  void eraseData(Node* node);
  T& retrieve(Node* node);
  Node* firstPosition();
  Node* lastPosition();
  Node* previousPosition(Node* node);
  Node* nextPosition(Node* node);
  void eraseList();
  Node* findData(T element, int cmp(T&, T&));
  string toString();

  IngredientsList& operator=(IngredientsList& listCopy);

  void writeToDisk(const string& fileName);
  void readFromDisk(const string& fileName);

  ~IngredientsList();
  // INNER CLASSES
 public:
  class Exception : public std::exception {
   private:
    std::string msg;

   public:
    explicit Exception(const char* message) : msg(message) {}
    explicit Exception(const std::string& message) : msg(message) {}

    virtual ~Exception() throw() {}

    virtual const char* what() const throw() { return msg.c_str(); }
  };
};

#endif  // IngredientsList_H

// CLASS Implementation
template <typename T>
IngredientsList<T>::Node::Node() : next(nullptr) {}

template <typename T>
IngredientsList<T>::Node::Node(T& data) {
  next = nullptr;
  this->data = data;
}

template <typename T>
T& IngredientsList<T>::Node::getData() {
  return data;
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::Node::getNext() {
  return next;
}

template <typename T>
void IngredientsList<T>::Node::setData(T& data) {
  this->data = data;
}

template <typename T>
void IngredientsList<T>::Node::setNext(Node* next) {
  this->next = next;
}

template <typename T>
bool IngredientsList<T>::isValidPos(Node* node) {
  Node* aux(anchor);

  while (aux != nullptr) {
    if (aux == node) return true;

    aux = aux->getNext();
  }

  return false;
}

template <typename T>
IngredientsList<T>::IngredientsList() {
  anchor = nullptr;
}

template <typename T>
IngredientsList<T>::IngredientsList(IngredientsList& copyList) {
  anchor = nullptr;
  Node* aux(copyList->anchor);
  Node* last(nullptr);
  Node* newNode;

  if (newNode == nullptr) throw Exception("\n\tOut of memory");

  while (aux != nullptr) {
    newNode = new Node(aux->getData());

    if (last == nullptr)
      anchor = newNode;
    else
      last->setNext(newNode);

    last = newNode;

    aux = aux->getNext();
  }
}

template <typename T>
bool IngredientsList<T>::isEmpty() {
  return anchor == nullptr;
}

template <typename T>
void IngredientsList<T>::insertData(T element, Node* node) {
  if (node != nullptr && !isValidPos(node))
    throw Exception("\n\tInvalid position, insertData");
  Node* aux;
  aux = new Node(element);
  if (aux == nullptr) throw Exception("\n\tInsuficient memory, insertData");

  if (node == nullptr) {
    aux->setNext(anchor);
    anchor = aux;
  } else {
    aux->setNext(node->getNext());
    node->setNext(aux);
  }
}

template <typename T>
void IngredientsList<T>::insertSortedData(T element) {
  bool flag = false;
  Node* aux(anchor);
  if (isEmpty())
    insertData(element, lastPosition());
  else {
    while (aux != nullptr && flag != true) {
      if (element < aux->getData()) {
        insertData(element, previousPosition(aux));
        flag = true;
      }
      aux = nextPosition(aux);
    }
    if (flag == false) insertData(element, lastPosition());
  }
}

//
template <typename T>
void IngredientsList<T>::eraseData(Node* node) {
  if (isEmpty() || node == nullptr)
    throw Exception("\n\tInvalid position, eraseData");

  if (node == anchor) {
    anchor = anchor->getNext();
  } else {
    previousPosition(node)->setNext(node->getNext());
  }

  delete node;
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::firstPosition() {
  return anchor;
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::lastPosition() {
  if (isEmpty()) return nullptr;

  Node* aux(anchor);
  while (aux->getNext() != nullptr) aux = aux->getNext();

  return aux;
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::previousPosition(
    Node* node) {
  if (isEmpty() || node == nullptr) return nullptr;
  // if(node == anchor) return nullptr;
  Node* aux(anchor);
  while (aux != nullptr && aux->getNext() != node) {
    aux = aux->getNext();
  }

  return aux;
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::nextPosition(
    Node* node) {
  if (isEmpty() || node == nullptr) return nullptr;
  return node->getNext();
}

template <typename T>
typename IngredientsList<T>::Node* IngredientsList<T>::findData(
    T element, int cmp(T& element1, T& element2)) {
  Node* aux(anchor);

  // while (aux != nullptr && aux->getData() != element) aux = aux->getNext();
  while (aux != nullptr && cmp(aux->getData(), element) != 0)
    aux = aux->getNext();
  return aux;
}

template <typename T>
T& IngredientsList<T>::retrieve(Node* node) {
  if (isEmpty() || node == nullptr)
    throw Exception("\n\tInvalid position, Retrieve");

  return node->getData();
}

template <typename T>
void IngredientsList<T>::eraseList() {
  Node* aux;
  while (!isEmpty()) {
    aux = anchor;
    anchor = anchor->getNext();
    delete aux;
  }
}

template <typename T>
string IngredientsList<T>::toString() {
  string result;

  Node* aux(anchor);

  while (aux != nullptr) {
    result += aux->getData().toString() + "\n";

    aux = aux->getNext();
  }

  return result;
}

template <typename T>
IngredientsList<T>& IngredientsList<T>::operator=(IngredientsList& copyList) {
  eraseList();
  Node* aux(copyList.anchor);
  Node* last(nullptr);
  Node* newNode;

  while (aux != nullptr) {
    newNode = new Node(aux->getData());
    if (newNode == nullptr) throw Exception("\n\tOut of memory");

    if (last == nullptr)
      anchor = newNode;
    else
      last->setNext(newNode);

    last = newNode;

    aux = aux->getNext();
  }

  return *this;
}

template <typename T>
void IngredientsList<T>::writeToDisk(const string& fileName) {
  std::ofstream myFile;
  myFile.open(fileName, myFile.trunc);

  if (!myFile.is_open()) throw Exception("Couldn't open file");

  //    int i = 0;

  Node* i(anchor->getNext());
  while (i != anchor) {
    //        myFile << data[i++] << std::endl;
    myFile << i->getData() << std::endl;
    i = i->getNext();
  }

  myFile.close();
}

template <typename T>
void IngredientsList<T>::readFromDisk(const string& fileName) {
  std::ifstream myFile;
  myFile.open(fileName);
  string ender;

  if (!myFile.is_open()) throw Exception("Couldn't open file");

  eraseList();

  T myData;

  try {
    while (myFile.peek() != EOF) {
      //                myData.deserialize(myFile);
      myData.deserialize(myFile);
      if (myFile.peek() == EOF) {
        break;
      }
      //            insertSortedData(myData);
      insertData(myData, lastPosition());
    }
  } catch (Exception ex) {
    myFile.close();
    throw Exception(ex.what());
  }

  myFile.close();
}

template <typename T>
IngredientsList<T>::~IngredientsList() {
  eraseList();
}
