#include "name.h"

Name::Name() {
  name = "";
  lastName = "";
}

Name::Name(Name& nameCopy) {
  this->name = nameCopy.name;
  this->lastName = nameCopy.lastName;
}

string Name::getName() { return name; }

string Name::getLastName() { return lastName; }

void Name::setName(string name) { this->name = name; }

void Name::setLastName(string lastName) { this->lastName = lastName; }

Name& Name::operator=(const Name& nameCopy) {
  name = nameCopy.name;
  lastName = nameCopy.lastName;
  return *this;
}

istream& operator>>(istream& input, Name& name) {
  string nameAux, lastNameAux;
  std::cout << "\n\tEnter the name: ";
  getline(input, nameAux);
  nameAux[0] = toupper(nameAux.front());
  std::cout << "\n\tEnter the last name: ";
  getline(input, lastNameAux);
  lastNameAux[0] = toupper(lastNameAux[0]);
  name.setName(nameAux);
  name.setLastName(lastNameAux);
  return input;
}

ostream& operator<<(ostream& output, Name& name) {
  output << name.getName() << " " << name.getLastName();
  return output;
}

string Name::toString() {
  string result;
  result += name;
  result += " ";
  result += lastName;
  return result;
}
