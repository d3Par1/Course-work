// ConsoleUI.cpp
#include "ConsoleUI.h"
#include <iostream>
#include <limits>

using namespace std;

ConsoleUI::ConsoleUI() : solver(nullptr) {}

ConsoleUI::~ConsoleUI()
{
  if (solver != nullptr)
  {
    delete solver;
  }
}

void ConsoleUI::displayMenu()
{
  cout << "=======================================\n";
  cout << "  ГОЛОВОЛОМКА З'ЄДНАННЯ ПАР СИМВОЛІВ  \n";
  cout << "=======================================\n";
  cout << "1 - Ввести дані вручну\n";
  cout << "2 - Використати приклад головоломки (8×8)\n";
  cout << "3 - Використати основне завдання (12×12)\n";
  cout << "4 - Вийти з програми\n";
  cout << "=======================================\n";
  cout << "Виберіть опцію: ";
}

void ConsoleUI::handleInput()
{
  int choice;
  cin >> choice;

  // Очищаємо буфер введення
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  switch (choice)
  {
  case 1:
    manualInput();
    break;
  case 2:
    loadSimpleExample();
    break;
  case 3:
    loadExample();
    break;
  case 4:
    cout << "До побачення!\n";
    exit(0);
    break;
  default:
    cout << "Невірний вибір. Спробуйте ще раз.\n";
    break;
  }
}

void ConsoleUI::manualInput()
{
  int rows, cols;

  cout << "Введіть кількість рядків: ";
  cin >> rows;

  cout << "Введіть кількість стовпців: ";
  cin >> cols;

  // Створюємо новий об'єкт PuzzleSolver
  if (solver != nullptr)
  {
    delete solver;
  }
  solver = new PuzzleSolver(rows, cols);

  cout << "Введіть символи (пробіл для порожньої клітини):\n";

  // Очищаємо буфер введення
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      char symbol;
      symbol = cin.get();

      if (symbol == '\n')
      {
        j--;
        continue;
      }

      solver->setSymbol(i, j, symbol);
    }
  }

  displayResult();
}

void ConsoleUI::loadSimpleExample()
{
  const int ROWS = 10;
  const int COLS = 10;
  char example[ROWS][COLS] = {
      {'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '2', '3'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', '4', ' ', ' '},
      {' ', '2', ' ', '5', ' ', '3', ' ', ' ', ' ', '1'},
      {' ', '6', ' ', '4', ' ', ' ', ' ', ' ', '6', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', '7', ' ', ' ', ' ', '7', ' ', '5', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', ' ', ' '},
      {' ', ' ', '8', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
  };
  // Створюємо новий об'єкт PuzzleSolver
  if (solver != nullptr)
  {
    delete solver;
  }
  solver = new PuzzleSolver(ROWS, COLS);

  // Заповнюємо сітку
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      solver->setSymbol(i, j, example[i][j]);
    }
  }

  displayResult();
}

void ConsoleUI::loadExample()
{
  const int ROWS = 13;
  const int COLS = 13;
  char example[ROWS][COLS] = {
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'R', ' '},
      {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', 'L', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'N'},
      {' ', ' ', ' ', ' ', ' ', 'L', ' ', ' ', ' ', ' ', 'C', ' ', ' '},
      {' ', 'G', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', ' '},
      {'Z', ' ', ' ', 'E', ' ', ' ', ' ', ' ', 'N', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', 'T', ' '},
      {' ', ' ', ' ', 'T', ' ', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', 'Z', ' ', ' ', ' ', ' ', ' ', 'M'},
      {' ', ' ', ' ', ' ', ' ', ' ', 'M', ' ', ' ', ' ', ' ', ' ', ' '}
  };

  // Створюємо новий об'єкт PuzzleSolver
  if (solver != nullptr)
  {
    delete solver;
  }
  solver = new PuzzleSolver(ROWS, COLS);

  // Заповнюємо сітку
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      solver->setSymbol(i, j, example[i][j]);
    }
  }

  displayResult();
}

void ConsoleUI::displayResult()
{
  cout << "\nРозв'язуємо головоломку...\n";

  bool result = solver->solve();

  if (result)
  {
    cout << "Розв'язок знайдено:\n\n";
    solver->displayResult();
  }
  else
  {
    cout << "Розв'язок не знайдено!\n";
  }

  // Повернення до меню
  cout << "\nБажаєте повернутися до головного меню? (1 - Так, 2 - Ні): ";
  int choice;
  cin >> choice;

  if (choice == 1)
  {
    displayMenu();
    handleInput();
  }
  else
  {
    cout << "До побачення!\n";
    exit(0);
  }
}