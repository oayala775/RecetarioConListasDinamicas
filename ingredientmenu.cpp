#include "ingredientmenu.h"

IngredientMenu::IngredientMenu() {}

IngredientMenu::IngredientMenu(IngredientsList<Ingredient>& ingredientsParam) {
  ingredients = &ingredientsParam;
}

void IngredientMenu::display() {
  char option;
  do {
    system("cls");
    cout << "\t\t\t\t\tINGREDIENTS MENU\t\t\t\t\t" << endl;
    cout << "Amount\t\t\tIngredient" << endl;
    cout << "------------------------------------------------------------------"
            "---------------------------------"
         << endl;
    cout << ingredients->toString() << endl << endl;
    cout << "\tEnter the desired option: "
            "\n\tA -> Add new ingredient"
            "\n\tB -> Edit an ingredient"
            "\n\tC -> Erase an ingredient"
            "\n\tD -> Erase the ingredient list"
            "\n\tE -> Exit menu"
            "\n\t\t-> ";
    cin >> option;
    cin.ignore();
    option = std::toupper(option);
    if (option == 'A')
      addIngredient();
    else if (option == 'B')
      editIngredient();
    else if (option == 'C')
      eraseIngredient();
    else if (option == 'D')
      eraseFullList();
  } while (option != 'E');
}

void IngredientMenu::addIngredient() {
  char option;
  do {
    cin >> ingredientAux;
    ingredients->insertSortedData(ingredientAux);
    cout << "\n\n\tDo you want to add a new ingredient? [y/n]: ";
    cin >> option;
    cin.ignore();
    option = toupper(option);
  } while (option != 'N');
}

void IngredientMenu::editIngredient() {
  string auxIngredientName;
  cout << "\n\tIntroduce the name of the desired ingredient"
          "\n\t\t\t-> ";
  getline(cin, auxIngredientName);
  auxIngredientName[0] = std::toupper(auxIngredientName[0]);
  ingredientAux.setIngredientName(auxIngredientName);

  positionSelected =
      ingredients->findData(ingredientAux, Ingredient::compareByIngredientName);

  int amountAux;
  cout << "\n\t\t\t-------------EDITION-------------\t\t\t\n";
  if (positionSelected != nullptr) {
    cout
        << "\n\tIngredient found, introduce the new amount of the ingredient: ";
    cin >> amountAux;
    cin.ignore();
    ingredients->retrieve(positionSelected).setAmount(amountAux);
  } else {
    cout << "\n\tIngredient not found, try again";
  }
}

void IngredientMenu::eraseIngredient() {
  string auxIngredientName;

  cout << "\n\tIntroduce the name of the desired ingredient"
          "\n\t\t\t-> ";
  getline(cin, auxIngredientName);
  auxIngredientName[0] = std::toupper(auxIngredientName[0]);
  ingredientAux.setIngredientName(auxIngredientName);

  positionSelected =
      ingredients->findData(ingredientAux, Ingredient::compareByIngredientName);

  if (positionSelected != nullptr) {
    cout << "\n\tIngredient found, erasing...";
    ingredients->eraseData(positionSelected);
    sleep_for(seconds(2));
    cout << "\n\tIngredient succesfully erased";
    sleep_for(seconds(2));
  } else {
    cout << "\n\tIngredient not found, try again";
  }
}

void IngredientMenu::eraseFullList() {
  cout << "\n\tErasing list...";
  sleep_for(seconds(2));
  ingredients->eraseList();
  system("cls");
  cout << "\n\tList erased succesfully" << endl;
  sleep_for(seconds(2));
}
