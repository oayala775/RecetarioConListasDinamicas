#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <stdlib.h>

#include <iostream>

using std::istream;
using std::ostream;
using std::string;

class Ingredient {
 private:
  int amount;
  string measurementUnit;
  string ingredientName;

 public:
  Ingredient();
  Ingredient(Ingredient& copyIngredient);

  int getAmount();
  void setAmount(int amount);

  string getIngredientName();
  void setIngredientName(string ingredientName);

  string getMeasurementUnit();
  void setMeasurementUnit(string measurementUnit);

  string toString();

  Ingredient& operator=(Ingredient& ingredientToCopy);

  static int compareByIngredientName(Ingredient& ingredient1,
                                     Ingredient& ingredient2);
  static int compareByAmount(Ingredient& ingredient1, Ingredient& ingredient2);
  static int compareByMeasurementUnit(Ingredient& ingredient1,
                                      Ingredient& ingredient2);

  bool operator==(Ingredient& ingredientToCompare);
  bool operator!=(Ingredient& ingredientToCompare);
  bool operator>(Ingredient& ingredientToCompare);
  bool operator>=(Ingredient& ingredientToCompare);
  bool operator<(Ingredient& ingredientToCompare);
  bool operator<=(Ingredient& ingredientToCompare);

  void deserialize(istream& input);

  friend istream& operator>>(istream& input, Ingredient& ingredient);
  friend ostream& operator<<(ostream& output, Ingredient& ingredient);
};

#endif  // INGREDIENT_H
