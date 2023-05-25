#include "recipe.h"

Recipe::Recipe() {
  category = "";
  recipeName = "";
  preparationTime = 0;
  unitMeasurement = "";
  process = "";
}

Recipe::Recipe(Recipe& recipeToCopy) {
  this->author = recipeToCopy.getAuthor();
  this->ingredients = recipeToCopy.getIngredientList();
  this->category = recipeToCopy.getCategory();
  this->recipeName = recipeToCopy.getRecipeName();
  this->preparationTime = recipeToCopy.getPreparationTime();
  this->unitMeasurement = recipeToCopy.getMeasurementUnit();
  this->process = recipeToCopy.getProcess();
}

void Recipe::setIngredientList(IngredientsList<Ingredient> ingredients) {
  this->ingredients = ingredients;
}

IngredientsList<Ingredient>& Recipe::getIngredientList() { return ingredients; }

void Recipe::setIngredientAux(Ingredient ingredientAux) {
  this->ingredientAux = ingredientAux;
}

Ingredient Recipe::getIngredientAux() { return ingredientAux; }

void Recipe::setAuthor(Name& name) { this->author = name; }

Name& Recipe::getAuthor() { return author; }

void Recipe::setCategory(string category) { this->category = category; }

string Recipe::getCategory() { return category; }

void Recipe::setMeasurementUnit(string unitMeasurementCopy) {
  this->unitMeasurement = unitMeasurementCopy;
}

string Recipe::getMeasurementUnit() { return unitMeasurement; }

void Recipe::setRecipeName(string recipeName) { this->recipeName = recipeName; }

string Recipe::getRecipeName() { return recipeName; }

void Recipe::setPreparationTime(int preparationTime) {
  this->preparationTime = preparationTime;
}

int Recipe::getPreparationTime() { return preparationTime; }

void Recipe::setProcess(string process) { this->process = process; }

string Recipe::getProcess() { return process; }

string Recipe::toString() {
  string result;
  string recipeNameAux, prepTimeAux, categoryAux;

  recipeNameAux = recipeName;
  recipeNameAux.resize(30, ' ');
  prepTimeAux = std::to_string(getPreparationTime());
  prepTimeAux += " ";
  prepTimeAux += unitMeasurement;
  prepTimeAux.resize(20, ' ');

  result += recipeNameAux;
  result += prepTimeAux;
  result += "\t";
  result += category;
  result += "\t";
  result += author.toString();
  result += "\n\nIngredients: \n";
  result += ingredients.toString();
  result += "\n";
  result += "\nDescription: ";
  result += process;
  result += "\n";

  return result;
}

Recipe& Recipe::operator=(Recipe& recipeToCopy) {
  author = recipeToCopy.getAuthor();
  ingredients = recipeToCopy.getIngredientList();
  category = recipeToCopy.getCategory();
  recipeName = recipeToCopy.getRecipeName();
  preparationTime = recipeToCopy.getPreparationTime();
  unitMeasurement = recipeToCopy.getMeasurementUnit();
  process = recipeToCopy.getProcess();
  return *this;
}

int Recipe::compareByRecipeName(Recipe& recipe1, Recipe& recipe2) {
  if (recipe1.getRecipeName() > recipe2.getRecipeName())
    return 1;
  else if (recipe1.getRecipeName() < recipe2.getRecipeName())
    return -1;
  else
    return 0;
}

int Recipe::compareByPreparationTime(Recipe& recipe1, Recipe& recipe2) {
  string measureValue1_string = recipe1.getMeasurementUnit();
  string measureValue2_string = recipe2.getMeasurementUnit();

  int measureValue1_int = 0;
  int measureValue2_int = 0;

  if (measureValue1_string == "sec")
    measureValue1_int = 1;
  else if (measureValue1_string == "min")
    measureValue1_int = 2;
  else if (measureValue1_string == "hr")
    measureValue1_int = 3;

  if (measureValue2_string == "sec")
    measureValue2_int = 1;
  else if (measureValue2_string == "min")
    measureValue2_int = 2;
  else if (measureValue2_string == "hr")
    measureValue2_int = 3;

  if (measureValue1_int > measureValue2_int)
    return 1;
  else if (measureValue1_int < measureValue2_int)
    return -1;
  else if (measureValue1_int == measureValue2_int) {
    if (recipe1.getPreparationTime() > recipe2.getPreparationTime())
      return 1;
    else if (recipe1.getPreparationTime() < recipe2.getPreparationTime())
      return -1;
    else
      return 0;
  }
  return -1;
}

int Recipe::compareByCategory(Recipe& recipe1, Recipe& recipe2) {
  if (recipe1.getCategory() > recipe2.getCategory())
    return 1;
  else if (recipe1.getCategory() < recipe2.getCategory())
    return -1;
  else
    return 0;
}

bool Recipe::operator==(Recipe& recipe) {
  return (recipeName == recipe.getRecipeName());
}

bool Recipe::operator<=(Recipe& recipe) {
  return (recipeName <= recipe.getRecipeName());
}

bool Recipe::operator>=(Recipe& recipe) {
  return (recipeName >= recipe.getRecipeName());
}

bool Recipe::operator!=(Recipe& recipe) {
  return (recipeName != recipe.getRecipeName());
}

bool Recipe::operator<(Recipe& recipe) {
  return (recipeName < recipe.getRecipeName());
}

bool Recipe::operator>(Recipe& recipe) {
  return (recipeName > recipe.getRecipeName());
}

ostream& operator<<(ostream& output, Recipe& recipe) {
  string fileName, recipeNameAux;
  IngredientsList<Ingredient> ingredientsAux;

  recipeNameAux = recipe.getRecipeName();

  // Generates the fileName for its ingredient list
  fileName = "readIngredients";
  fileName += recipeNameAux;
  fileName += ".txt";

  output << recipe.getPreparationTime() << endl;
  output << recipe.getMeasurementUnit() << endl;
  output << recipe.getCategory() << endl;
  output << recipe.getAuthor().getName() << endl;
  output << recipe.getAuthor().getLastName() << endl;
  output << recipe.getRecipeName() << endl;
  output << recipe.getProcess() << endl;
  output << ";" << endl;

  // Obtains the correspondent ingredient list for the recipe
  // and writes the file to disk with the customized file name
  ingredientsAux = recipe.getIngredientList();
  ingredientsAux.writeToDisk(fileName);

  return output;
}

istream& operator>>(istream& input, Recipe& recipe) {
  int auxPreparationTime;
  string recipeNameAux, categoryAux, processAux, processSafer;
  string unitMeasurementAux, nameAux, lastNameAux;
  string preparationTimeStr;
  Name authorAux;
  Ingredient ingredientAux;

  cout << "\n\tEnter the preparation time: ";
  input >> auxPreparationTime;
  input.ignore();
  recipe.setPreparationTime(auxPreparationTime);

  cout << "\n\tEnter the preparation time unit of measurement: ";
  getline(input, unitMeasurementAux);
  recipe.setMeasurementUnit(unitMeasurementAux);

  cout << "\n\tEnter the category: ";
  getline(input, categoryAux);
  categoryAux[0] = toupper(categoryAux[0]);
  recipe.setCategory(categoryAux);

  cout << "\n\tEnter the author of the recipe: ";
  getline(input, nameAux);
  getline(input, lastNameAux);
  nameAux[0] = toupper(nameAux[0]);
  lastNameAux[0] = toupper(lastNameAux[0]);
  authorAux.setName(nameAux);
  authorAux.setLastName(lastNameAux);
  recipe.setAuthor(authorAux);

  cout << "\n\tEnter the name of the recipe: ";
  getline(input, recipeNameAux);
  recipeNameAux[0] = toupper(recipeNameAux[0]);
  recipe.setRecipeName(recipeNameAux);

  cout << "\n\tEnter the full process of the recipe, (once you finish enter a "
          "line with just a ;): ";
  while (getline(input, processAux)) {
    if (processAux == ";") break;
    processSafer += "\n";
    processSafer += processAux;
  }
  recipe.setProcess(processSafer);
  return input;
}

void Recipe::deserialize(istream& input) {
  int auxPreparationTime;
  string recipeNameAux, categoryAux, processAux, processSafer;
  string unitMeasurementAux, nameAux, lastNameAux;
  string preparationTimeStr;
  Name authorAux;
  Ingredient ingredientAux;

  input >> auxPreparationTime;
  input.ignore();
  setPreparationTime(auxPreparationTime);

  getline(input, unitMeasurementAux);
  setMeasurementUnit(unitMeasurementAux);

  getline(input, categoryAux);
  categoryAux[0] = toupper(categoryAux[0]);
  setCategory(categoryAux);

  getline(input, nameAux);
  getline(input, lastNameAux);
  nameAux[0] = toupper(nameAux[0]);
  lastNameAux[0] = toupper(lastNameAux[0]);
  authorAux.setName(nameAux);
  authorAux.setLastName(lastNameAux);
  setAuthor(authorAux);

  getline(input, recipeNameAux);
  recipeNameAux[0] = toupper(recipeNameAux[0]);
  setRecipeName(recipeNameAux);

  while (getline(input, processAux)) {
    if (processAux == ";") break;
    processSafer += "\n";
    processSafer += processAux;
  }
  setProcess(processSafer);
}
