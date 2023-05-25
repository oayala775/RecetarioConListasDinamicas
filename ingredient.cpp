#include "ingredient.h"

Ingredient::Ingredient() {}

Ingredient::Ingredient(Ingredient& copyIngredient) {
  amount = copyIngredient.getAmount();
  ingredientName = copyIngredient.getIngredientName();
  measurementUnit = copyIngredient.getMeasurementUnit();
}

int Ingredient::getAmount() { return amount; }

void Ingredient::setAmount(int amount) { this->amount = amount; }

string Ingredient::getIngredientName() { return ingredientName; }
void Ingredient::setIngredientName(string ingredientName) {
  this->ingredientName = ingredientName;
}

string Ingredient::getMeasurementUnit() { return measurementUnit; }

void Ingredient::setMeasurementUnit(string measurementUnit) {
  this->measurementUnit = measurementUnit;
}

string Ingredient::toString() {
  string result, auxIngredientName, auxMeasurementUnit;

  result += std::to_string(amount);
  result += " ";

  auxMeasurementUnit = measurementUnit;
  auxMeasurementUnit.resize(10, ' ');

  result += auxMeasurementUnit;
  result += " \t\t";

  auxIngredientName = ingredientName;
  auxIngredientName.resize(20, ' ');
  result += auxIngredientName;
  return result;
}

Ingredient& Ingredient::operator=(Ingredient& ingredientToCopy) {
  amount = ingredientToCopy.getAmount();
  ingredientName = ingredientToCopy.getIngredientName();
  measurementUnit = ingredientToCopy.getMeasurementUnit();
  return *this;
}

int Ingredient::compareByIngredientName(Ingredient& ingredient1,
                                        Ingredient& ingredient2) {
  if (ingredient1.getIngredientName() > ingredient2.getIngredientName())
    return 1;
  else if (ingredient1.getIngredientName() < ingredient2.getIngredientName())
    return -1;
  else
    return 0;
}

int Ingredient::compareByAmount(Ingredient& ingredient1,
                                Ingredient& ingredient2) {
  if (ingredient1.getAmount() > ingredient2.getAmount())
    return 1;
  else if (ingredient1.getAmount() < ingredient2.getAmount())
    return -1;
  else
    return 0;
}

int Ingredient::compareByMeasurementUnit(Ingredient& ingredient1,
                                         Ingredient& ingredient2) {
  if (ingredient1.getMeasurementUnit() > ingredient2.getMeasurementUnit())
    return 1;
  else if (ingredient1.getMeasurementUnit() < ingredient2.getMeasurementUnit())
    return -1;
  else
    return 0;
}

bool Ingredient::operator==(Ingredient& ingredientToCompare) {
  return (ingredientName == ingredientToCompare.getIngredientName());
}

bool Ingredient::operator!=(Ingredient& ingredientToCompare) {
  return (ingredientName != ingredientToCompare.getIngredientName());
}

bool Ingredient::operator>(Ingredient& ingredientToCompare) {
  return (ingredientName > ingredientToCompare.getIngredientName());
}

bool Ingredient::operator>=(Ingredient& ingredientToCompare) {
  return (ingredientName >= ingredientToCompare.getIngredientName());
}

bool Ingredient::operator<(Ingredient& ingredientToCompare) {
  return (ingredientName < ingredientToCompare.getIngredientName());
}

bool Ingredient::operator<=(Ingredient& ingredientToCompare) {
  return (ingredientName <= ingredientToCompare.getIngredientName());
}

istream& operator>>(istream& input, Ingredient& ingredient) {
  string ingredientNameAux, measurementUnitAux;
  int amountAux;

  std::cout << "\n\tEnter the ingredient name: ";
  getline(input, ingredientNameAux);
  ingredientNameAux[0] = toupper(ingredientNameAux[0]);
  ingredient.setIngredientName(ingredientNameAux);

  std::cout << "\n\tEnter the amount: ";
  input >> amountAux;
  input.ignore();
  ingredient.setAmount(amountAux);

  std::cout << "\n\tEnter the measurement unit: ";
  getline(input, measurementUnitAux);
  ingredient.setMeasurementUnit(measurementUnitAux);

  return input;
}

ostream& operator<<(ostream& output, Ingredient& ingredient) {
  output << ingredient.getIngredientName() << std::endl;
  output << ingredient.getAmount() << std::endl;
  output << ingredient.getMeasurementUnit();
  return output;
}

void Ingredient::deserialize(istream& input) {
  string ingredientNameAux, measurementUnitAux;
  int amountAux;

  getline(input, ingredientNameAux);
  ingredientNameAux[0] = toupper(ingredientNameAux[0]);
  setIngredientName(ingredientNameAux);

  input >> amountAux;
  input.ignore();
  setAmount(amountAux);

  getline(input, measurementUnitAux);
  setMeasurementUnit(measurementUnitAux);
}
