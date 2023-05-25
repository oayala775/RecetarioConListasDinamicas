#ifndef NAME_H
#define NAME_H

#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

class Name {
 private:
  string name;
  string lastName;

 public:
  Name();
  Name(Name& nameCopy);

  string getName();
  string getLastName();

  void setName(string name);
  void setLastName(string lastName);

  Name& operator=(const Name& nameCopy);

  friend std::istream& operator>>(istream& input, Name& name);
  friend std::ostream& operator<<(ostream& output, Name& name);

  string toString();
};

#endif  // NAME_H
