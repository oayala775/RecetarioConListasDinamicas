#include "recipesmenu.h"

RecipesMenu::RecipesMenu() {}

void RecipesMenu::display() {
  char option;
  do {
    system("cls");
    cout << "*********************** RECIPES MENU ****************" << endl;
    cout << "\n\tChoose the option to execute: "
            "\n\t\tD -> Show on display all recipes"
            "\n\t\tA -> Add a recipe"
            "\n\t\tF -> Find a recipe"
            "\n\t\tE -> Erase a recipe"
            "\n\t\tT -> Erase all recipes"
            "\n\t\tS -> Sort recipes"
            "\n\t\tG -> Go to ingredients menu of a recipe"
            "\n\t\tM -> Modify the process of a recipe"
            "\n\t\tW -> Write recipe book to disk"
            "\n\t\tL -> Load recipe book from disk"
            "\n\t\tQ -> Quit program"
            "\n\t\t\t-> ";
    cin >> option;
    cin.ignore();
    option = toupper(option);
    system("cls");
    if (option == 'A')
      addRecipe();
    else if (option == 'G')
      displayIngredientMenu();
    else if (option == 'S')
      sortRecipes();
    else if (option == 'F')
      findRecipe();
    else if (option == 'E')
      eraseRecipe();
    else if (option == 'T')
      eraseAllRecipes();
    else if (option == 'D')
      showRecipes();
    else if (option == 'M')
      modifyProcess();
    else if (option == 'W')
      saveToDisk();
    else if (option == 'L')
      readFromDisk();
  } while (option != 'Q');
}

void RecipesMenu::displayIngredientMenu() {
  cout << "\n\tEnter the name of the recipe which menu will be displayed: ";
  getline(cin, recipeNameAux);
  // capitalizes the auxiliar recipe name in order to match the recipe name of
  // the recipe to be found
  recipeNameAux[0] = toupper(recipeNameAux[0]);
  recipeAux.setRecipeName(recipeNameAux);

  // Obtains the position of the searched recipe
  pos = recipeList.findData(recipeAux, Recipe::compareByRecipeName);

  // Gets the ingredient list of the desired recipe
  IngredientMenu ingredientsMenu(recipeList.retrieve(pos).getIngredientList());

  // Shows on display the ingredients menu of the desired recipe
  ingredientsMenu.display();
}

void RecipesMenu::addRecipe() {
  system("cls");
  cout << "\n\tCAPTURE MENU" << endl;
  cin >> recipeAux;

  // Inserts the fresh captured recipe at the end of the list
  recipeList.insertData(recipeAux, recipeList.lastPosition());
  //    counter++;

  // Obtains the list of ingredients of the new recipe and throws it to the
  // ingredients menu allowing the user to insert as many ingredients as the
  // user wants.
  IngredientMenu ingredientsMenu(
      recipeList.retrieve(recipeList.lastPosition()).getIngredientList());
  ingredientsMenu.addIngredient();
  //    currentElement++;
  cout << "\n\tRecipe successfully added" << endl;
}

void RecipesMenu::sortRecipes() {
  char option;
  cout << "\n\tChoose if you want to sort by recipe name of by preparation "
          "time: "
          "\n\t\tN -> Sort by name"
          "\n\t\tP -> Sort by preparation time"
          "\n\t\t\t-> ";
  cin >> option;
  cin.ignore();
  option = toupper(option);
  if (option == 'N')
    recipeList.quickSort(Recipe::compareByRecipeName);
  else if (option == 'P')
    recipeList.quickSort(Recipe::compareByPreparationTime);
}

void RecipesMenu::findRecipe() {
  char option;
  string recipeNameAux;
  string categoryNameAux;

  cout << "\n\tChoose the method you want to search for:"
          "\n\t\tC -> By category name"
          "\n\t\tN -> By recipe name"
          "\n\t\t\t-> ";
  cin >> option;
  cin.ignore();
  option = toupper(option);

  if (option == 'C') {
    cout << "\n\tEnter the category name: ";
    getline(cin, categoryNameAux);

    // Capitalizes the category name aux in order to match the format of the
    // original category name allowing it to be found
    categoryNameAux[0] = toupper(categoryNameAux[0]);

    recipeAux.setCategory(categoryNameAux);

    pos = recipeList.findData(recipeAux, Recipe::compareByCategory);
  }

  else if (option == 'N') {
    cout << "\n\tEnter the recipe name: ";
    getline(cin, recipeNameAux);
    // Capitalizes the category name aux in order to match the format of the
    // original category name allowing it to be found
    recipeNameAux[0] = toupper(recipeNameAux[0]);
    recipeAux.setRecipeName(recipeNameAux);

    pos = recipeList.findData(recipeAux, Recipe::compareByRecipeName);
  }

  system("cls");

  // It checks if the position is valid in order to retrieve it
  if (pos != nullptr) {
    header();
    cout << recipeList.retrieve(pos).toString() << endl;
    system("pause");
  } else {
    cout << "\n\tItem not found, try again" << endl;
    sleep_for(seconds(2));
  }
}

void RecipesMenu::eraseRecipe() {
  string recipeNameAux;

  cout << "\n\tEnter the name of the recipe to remove: ";
  getline(cin, recipeNameAux);
  // Capitalizes the recipe name aux in order to match the format of the
  // original recipe name allowing it to be found
  recipeNameAux[0] = toupper(recipeNameAux[0]);
  recipeAux.setRecipeName(recipeNameAux);

  pos = recipeList.findData(recipeAux, Recipe::compareByRecipeName);

  recipeList.eraseData(pos);
}

void RecipesMenu::eraseAllRecipes() {
  cout << "\n\tErasing all recipes..." << endl;
  sleep_for(seconds(2));
  recipeList.eraseList();
  cout << "\n\tRecipe list erased successfully" << endl;
  sleep_for(seconds(2));

  // Resets the auxiliary counters
  //    currentElement = 0;
  //    counter = -1;
}

void RecipesMenu::showRecipes() {
  char option;
  char innerOption;
  RecipeList<Recipe>::Position i(recipeList.firstPosition());
  cout << "\n\tDo you want to see all recipes or filtered by category? "
          "\n\t\tA -> Show all recipes"
          "\n\t\tC -> Show recipes by category"
          "\n\t\t\t-> ";
  cin >> option;
  cin.ignore();
  option = toupper(option);
  if (option == 'A') {
    system("cls");
    while (i != recipeList.lastPosition()->getNext()) {
      header();
      cout << recipeList.retrieve(i).toString();
      cout << "****------------------------------------------------------------"
              "-----------------------------------****\n\n\n";
      i = i->getNext();
    }
    system("pause");
  } else if (option == 'C') {
    cout << "\n\tEnter the category which recipes will be displayed"
            "\n\t\tB -> Breakfast"
            "\n\t\tD -> Dinner"
            "\n\t\tL -> Lunch"
            "\n\t\tC -> Christmas"
            "\n\t\t\t-> ";
    cin >> innerOption;
    cin.ignore();
    innerOption = toupper(innerOption);
    if (innerOption == 'B')
      showRecipesByCategory("Breakfast");
    else if (innerOption == 'D')
      showRecipesByCategory("Dinner");
    else if (innerOption == 'L')
      showRecipesByCategory("Lunch");
    else if (innerOption == 'C')
      showRecipesByCategory("Christmas");
    else
      cout << "\n\tEnter a valid category" << endl;
  }
}

void RecipesMenu::showRecipesByCategory(string categoryToSearch) {
  RecipeList<Recipe>::Position i(recipeList.firstPosition());

  system("cls");
  string categoryHelper;
  bool flag = false;

  while (i != recipeList.lastPosition()) {
    categoryHelper = recipeList.retrieve(i).getCategory();
    if (categoryHelper == categoryToSearch) {
      header();
      cout << recipeList.retrieve(i).toString() << endl;
      cout << "****************************************************************"
              "*******"
           << endl
           << endl;
      flag = true;
    }
    i = i->getNext();
  }
  if (!flag)
    cout << "\n\tNo item with this category: " << categoryToSearch
         << " was found." << endl;
  system("pause");
}

void RecipesMenu::modifyProcess() {
  string recipeNameAux;
  string processAux, processSafer;

  cout << "\n\tEnter the name of the recipe to modify: ";
  getline(cin, recipeNameAux);
  recipeNameAux[0] = toupper(recipeNameAux[0]);
  recipeAux.setRecipeName(recipeNameAux);

  // As the process of finding must be automatic, the method checks if the
  // recipe lsit is already sorted, and if it is, it binary searches for the
  // desired recipe fastening the finding process
  pos = recipeList.findData(recipeAux, Recipe::compareByRecipeName);

  cout << "\n\tEnter the full process of the recipe, (once you finish enter a "
          "line with just a ;): "
       << endl;

  while (getline(cin, processAux)) {
    // The end of string character is ;, so it checks whether the character is
    // found or not
    if (processAux == ";") break;
    processSafer += "\n";
    processSafer += processAux;
  }

  recipeList.retrieve(pos).setProcess(processSafer);
  cout << "\n\tProcess successfully changed" << endl;
}

void RecipesMenu::saveToDisk() {
  recipeList.writeToDisk("read.txt");
  cout << "\n\tList succesfully wrote";
  sleep_for(seconds(2));
}

void RecipesMenu::readFromDisk() {
  string auxFileName;

  recipeList.readFromDisk("read.txt");

  RecipeList<Recipe>::Position i(recipeList.firstPosition());

  while (i != recipeList.lastPosition()->getNext()) {
    // Generates the file name of every ingredient list of the recipe list
    auxFileName = "readIngredients";
    auxFileName += recipeList.retrieve(i).getRecipeName();
    auxFileName += ".txt";

    // Calls the method of the ingredientsList that reads from disk
    recipeList.retrieve(i).getIngredientList().readFromDisk(auxFileName);
    i = i->getNext();
  }

  system("cls");
  cout << "\n\tList succesfully read";
  sleep_for(seconds(2));
}

void RecipesMenu::header() {
  cout << "Recipe Name\t\tPreparation Time\t\tCategory\tAuthor" << endl;
  cout << "--------------------------------------------------------------------"
          "-----------------------------------"
       << endl;
}
