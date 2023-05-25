#ifndef RECIPELIST_
#define RECIPELIST_

#pragma once

#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

template <typename T>
class RecipeList {
 private:
  class Node {
   private:
    T* data;
    Node* next;
    Node* prev;

   public:
    Node();
    Node(T element);

    T& getData();
    T* getDataPtr();
    Node* getNext();
    Node* getPrev();

    void setData(T value);
    void setDataPtr(T* data);
    void setNext(Node* next);
    void setPrev(Node* prev);

    ~Node();

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

 private:
  Node* header;
  bool isValidPos(Node* node);
  void quickSort(Node* leftEdge, Node* rightEdge,
                 int cmp(T& element1, T& element2));
  void swapData(T* element1, T* element2);

 public:
  typedef Node* Position;

  RecipeList();
  RecipeList(RecipeList& copyList);
  bool isEmpty();
  void quickSort(int cmp(T&, T&));
  bool isSorted();
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

  void writeToDisk(const string& fileName);
  void readFromDisk(const string& fileName);

  RecipeList& operator=(const RecipeList& listCopy);

  ~RecipeList();
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

#endif  // RECIPELIST_

// CLASS Implementation
template <typename T>
RecipeList<T>::Node::Node() : next(nullptr), prev(nullptr), data(nullptr) {}

template <typename T>
RecipeList<T>::Node::Node(T element) {
  next = nullptr;
  prev = nullptr;
  data = new T(element);
  if (data == nullptr) throw Exception("Not enought memory");
}

template <typename T>
T& RecipeList<T>::Node::getData() {
  if (data == nullptr) throw Exception("Non existent data, getData");
  return *data;
}

template <typename T>
T* RecipeList<T>::Node::getDataPtr() {
  return data;
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::Node::getNext() {
  return next;
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::Node::getPrev() {
  return prev;
}

template <typename T>
void RecipeList<T>::Node::setData(T value) {
  if (data == nullptr) {
    // Tries to create a new data, if it isn't capable of creating it
    // then rises an exception
    if ((data = new T(value)) == nullptr)
      throw Exception("Non available memory, setData");
  } else
    *data = value;
}

template <typename T>
void RecipeList<T>::Node::setDataPtr(T* data) {
  this->data = data;
}

template <typename T>
void RecipeList<T>::Node::setNext(Node* next) {
  this->next = next;
}

template <typename T>
void RecipeList<T>::Node::setPrev(Node* prev) {
  this->prev = prev;
}

template <typename T>
RecipeList<T>::Node::~Node() {
  delete data;
}

template <typename T>
bool RecipeList<T>::isValidPos(Node* node) {
  Node* aux(header->getNext());

  while (aux != header) {
    if (aux == node) return true;

    aux = aux->getNext();
  }

  return false;
}

template <typename T>
void RecipeList<T>::swapData(T* element1, T* element2) {
  T aux(*element1);
  *element1 = *element2;
  *element2 = aux;
}

template <typename T>
void RecipeList<T>::quickSort(int cmp(T&, T&)) {
  quickSort(header->getNext(), header->getPrev(), cmp);
}

template <typename T>
void RecipeList<T>::quickSort(Node* leftEdge, Node* rightEdge,
                              int cmp(T& element1, T& element2)) {
  Node* j = leftEdge;
  Node* i = leftEdge->getPrev();

  if (rightEdge != header && leftEdge != rightEdge &&
      leftEdge != rightEdge->getNext()) {
    while (j != rightEdge) {
      if (cmp(j->getData(), rightEdge->getData()) <= 0) {
        if (i == header)
          i = leftEdge;
        else
          i = i->getNext();

        swapData(&i->getData(), &j->getData());
      }
      j = j->getNext();
    }

    if (i == header)
      i = leftEdge;
    else
      i = i->getNext();

    swapData(&i->getData(), &rightEdge->getData());

    quickSort(leftEdge, i->getPrev(), cmp);
    quickSort(i->getNext(), rightEdge, cmp);
  }
}

template <typename T>
RecipeList<T>::RecipeList() {
  header = new Node;

  if (header == nullptr)
    throw Exception("Non available memory, ListConstructor");

  // Initializes the circularity of the list
  header->setNext(header);
  header->setPrev(header);
}

template <typename T>
RecipeList<T>::RecipeList(RecipeList& copyList) {
  // header = nullptr;
  Node* aux(copyList.header->getNext());
  Node* newNode;

  while (aux != copyList.header) {
    try {
      if ((newNode = new Node(aux->getData())) == nullptr) {
        throw Exception("Non available memory, operator = ");
      }
    } catch (typename Node::Exception ex) {
      throw Exception(ex.what());
    }

    newNode->setPrev(header->getPrev());
    newNode->setNext(header);

    header->getPrev()->setNext(newNode);
    header->setPrev(newNode);

    aux = aux->getNext();
  }
}

template <typename T>
bool RecipeList<T>::isEmpty() {
  return header->getNext() == header;
}

template <typename T>
bool RecipeList<T>::isSorted() {
  Node* i(header->getNext());
  Node* j(i->getNext());

  while (j != header) {
    if (i->getData() > j->getData()) return false;
    i = i->getNext();
    j = j->getNext();
  }
  return true;
}

template <typename T>
void RecipeList<T>::insertData(T element, Node* node) {
  if (node != nullptr && !isValidPos(node))
    throw Exception("\n\tInvalid position, insertData");

  Node* aux;
  try {
    aux = new Node(element);
  } catch (typename Node::Exception ex) {
    throw Exception(ex.what());
  }

  if (aux == nullptr) throw Exception("\n\tInsuficient memory, insertData");

  if (node == nullptr) {
    node = header;
  }
  aux->setPrev(node);
  aux->setNext(node->getNext());
  node->getNext()->setPrev(aux);
  node->setNext(aux);
}

template <typename T>
void RecipeList<T>::insertSortedData(T element) {
  /*
  int i = -1;
  bool flag = false;

  while (i < last && flag == false) {
      if (element < data[i + 1]) {
          insertData(element, i);
          flag = true;
          }
      i++;
      }
  if (last == -1 || flag == false) insertData(element, last);
  */

  bool flag = false;
  Node* i(header->getNext());

  while (i != header && flag == false) {
    if (element < i->getData()) {
      if (i->getPrev() == header) {
        //                    i = nullptr;
        Node* j(nullptr);
        insertData(element, j);
      } else {
        insertData(element, i->getPrev());
      }
      //            insertData(element,i);
      flag = true;
    }
    i = i->getNext();
  }

  if (isEmpty() || flag == false) insertData(element, lastPosition());
}

//
template <typename T>
void RecipeList<T>::eraseData(Node* node) {
  if (isEmpty() || node == nullptr)
    throw Exception("\n\tInvalid position, eraseData");

  node->getPrev()->setNext(node->getNext());
  node->getNext()->setPrev(node->getPrev());

  delete node;
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::firstPosition() {
  if (isEmpty()) return nullptr;
  return header->getNext();
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::lastPosition() {
  if (isEmpty()) return nullptr;

  return header->getPrev();
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::previousPosition(Node* node) {
  if (isEmpty() || node == header->getNext()) return nullptr;
  // if(node == header) return nullptr;

  return node->getPrev();
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::nextPosition(Node* node) {
  if (isEmpty() || node == header->getPrev()) return nullptr;

  return node->getNext();
}

template <typename T>
typename RecipeList<T>::Node* RecipeList<T>::findData(T element,
                                                      int cmp(T& element1,
                                                              T& element2)) {
  T dataAux;
  Node* aux(header->getNext());

  while (aux != header) {
    dataAux = aux->getData();
    if (cmp(dataAux, element) == 0) return aux;
    aux = aux->getNext();
  }
  return nullptr;
}

template <typename T>
T& RecipeList<T>::retrieve(Node* node) {
  if (isEmpty() || node == nullptr)
    throw Exception("\n\tInvalid position, Retrieve");

  return node->getData();
}

template <typename T>
void RecipeList<T>::eraseList() {
  Node* aux;
  while (!isEmpty()) {
    aux = header->getNext();
    header->setNext(aux->getNext());
    delete aux;
  }
  header->setPrev(header);
}

template <typename T>
string RecipeList<T>::toString() {
  string result;

  Node* aux(header->getNext());

  while (aux != header) {
    result += aux->getData().toString() + "\n";

    aux = aux->getNext();
  }

  return result;
}

template <typename T>
RecipeList<T>& RecipeList<T>::operator=(const RecipeList& copyList) {
  eraseList();
  Node* aux(copyList.header->getNext());
  Node* newNode;

  while (aux != copyList.header) {
    try {
      if ((newNode = new Node(aux->getData())) == nullptr) {
        throw Exception("Non available memory, operator = ");
      }
    } catch (typename Node::Exception ex) {
      throw Exception(ex.what());
    }

    newNode->setPrev(header->getPrev());
    newNode->setNext(header);

    header->getPrev()->setNext(newNode);
    header->setPrev(newNode);
    aux = aux->getNext();
  }

  return *this;
}

template <typename T>
void RecipeList<T>::writeToDisk(const string& fileName) {
  std::ofstream myFile;
  myFile.open(fileName, myFile.trunc);

  if (!myFile.is_open()) throw Exception("Couldn't open file");

  //    int i = 0;

  Node* i(header->getNext());
  while (i != header) {
    //        myFile << data[i++] << std::endl;
    myFile << i->getData() << std::endl;
    i = i->getNext();
  }

  myFile.close();
}

template <typename T>
void RecipeList<T>::readFromDisk(const string& fileName) {
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
RecipeList<T>::~RecipeList() {
  eraseList();
}
