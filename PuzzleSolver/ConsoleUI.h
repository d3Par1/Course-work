#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "PuzzleSolver.h"

class ConsoleUI {
private:
    PuzzleSolver* solver;  // Вказівник на об'єкт PuzzleSolver
    
    // Приватні методи
    void loadExample();    // Завантаження прикладу головоломки
    void manualInput();    // Ручне введення даних
    
public:
    // Конструктор і деструктор
    ConsoleUI();
    ~ConsoleUI();
    
    // Публічні методи
    void displayMenu();    // Відображення меню
    void handleInput();    // Обробка введення користувача
    void displayResult();  // Відображення результату
};
#endif