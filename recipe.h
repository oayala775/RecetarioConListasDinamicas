#ifndef RECIPE_H
#define RECIPE_H

#include <algorithm>

#include "ingredient.h"
#include "ingredientslist.h"
#include "name.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Recipe {
 private:
  Name author;
  IngredientsList<Ingredient> ingredients;
  Ingredient ingredientAux;
  string category;
  string recipeName;
  int preparationTime;
  string unitMeasurement;
  string process;

 public:
  Recipe();
  Recipe(Recipe& recipeToCopy);

  void setIngredientList(IngredientsList<Ingredient> ingredients);
  IngredientsList<Ingredient>& getIngredientList();

  void setIngredientAux(Ingredient ingredientAux);
  Ingredient getIngredientAux();

  void setAuthor(Name& name);
  Name& getAuthor();

  void setCategory(string category);
  string getCategory();

  void setMeasurementUnit(string unitMeasurement);
  string getMeasurementUnit();

  void setRecipeName(string recipeName);
  string getRecipeName();

  void setPreparationTime(int preparationTime);
  int getPreparationTime();

  void setProcess(string process);
  string getProcess();

  string toString();

  Recipe& operator=(Recipe& recipeToCopy);

  static int compareByRecipeName(Recipe& recipe1, Recipe& recipe2);
  static int compareByPreparationTime(Recipe& recipe1, Recipe& recipe2);
  static int compareByCategory(Recipe& recipe1, Recipe& recipe2);

  bool operator==(Recipe& recipe);
  bool operator<=(Recipe& recipe);
  bool operator>=(Recipe& recipe);
  bool operator!=(Recipe& recipe);
  bool operator<(Recipe& recipe);
  bool operator>(Recipe& recipe);

  void deserialize(istream& input);

  friend istream& operator>>(istream& input, Recipe& recipe);
  friend ostream& operator<<(ostream& output, Recipe& recipe);
};

#endif  // RECIPE_H
