#ifndef INGREDIENTMENU_H
#define INGREDIENTMENU_H

#include <chrono>
#include <thread>

#include "ingredient.h"
#include "ingredientslist.h"
using std::cin;
using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

class IngredientMenu {
 private:
  IngredientsList<Ingredient>* ingredients;
  Ingredient ingredientAux;
  IngredientsList<Ingredient>::Position positionSelected;

 public:
  IngredientMenu();
  IngredientMenu(IngredientsList<Ingredient>& ingredientsParam);
  void display();
  void addIngredient();
  void editIngredient();
  void eraseIngredient();
  void eraseFullList();
};

#endif  // INGREDIENTMENU_H
