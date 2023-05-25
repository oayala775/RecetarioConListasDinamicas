#ifndef RECIPESMENU_H
#define RECIPESMENU_H

#include <chrono>
#include <iostream>
#include <thread>

#include "ingredientmenu.h"
#include "ingredientslist.h"
#include "recipe.h"
#include "recipelist.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class RecipesMenu {
 private:
  RecipeList<Recipe> recipeList;
  Recipe recipeAux;
  string recipeNameAux;
  RecipeList<Recipe>::Position pos;

 public:
  RecipesMenu();
  void display();
  void displayIngredientMenu();
  void addRecipe();
  void sortRecipes();
  void findRecipe();
  void eraseRecipe();
  void eraseAllRecipes();
  void showRecipes();
  void showRecipesByCategory(string categoryToSearch);
  void modifyProcess();
  void saveToDisk();
  void readFromDisk();
  void header();
};

#endif  // RECIPESMENU_H
