/**
 * @file UserInterface.h
 * @brief Клас для взаємодії з користувачем
 */

 #ifndef USER_INTERFACE_H
 #define USER_INTERFACE_H
 
 #include <string>
 #include "Board.h"
 
 /**
  * @class UserInterface
  * @brief Клас для взаємодії з користувачем через консоль
  * 
  * Клас UserInterface відповідає за взаємодію з користувачем через консольний інтерфейс.
  * Він надає методи для відображення меню, отримання введення користувача та інших
  * взаємодій з програмою.
  */
 class UserInterface {
 private:
     /**
      * @brief Очистити екран консолі
      */
     void clearScreen() const;
     
     /**
      * @brief Відобразити лого програми
      */
     void displayLogo() const;
     
     /**
      * @brief Відобразити інформацію про програму
      */
     void displayInfo() const;
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     UserInterface();
     
     /**
      * @brief Деструктор
      */
     ~UserInterface();
     
     /**
      * @brief Відобразити головне меню
      */
     void displayMainMenu() const;
     
     /**
      * @brief Відобразити меню вирішення головоломки
      */
     void displaySolutionMenu() const;
     
     /**
      * @brief Відобразити меню ручного вирішення
      */
     void displayManualSolutionMenu() const;
     
     /**
      * @brief Отримати вибір користувача з меню
      * @param min Мінімальне значення
      * @param max Максимальне значення
      * @return Вибір користувача
      */
     int getMenuChoice(int min, int max) const;
     
     /**
      * @brief Отримати розмір дошки від користувача
      * @return Розмір дошки
      */
     int getBoardSize() const;
     
     /**
      * @brief Отримати символ від користувача
      * @return Символ
      */
     char getSymbol() const;
     
     /**
      * @brief Отримати координати від користувача
      * @param board Посилання на дошку
      * @param message Повідомлення для користувача
      * @return Пара координат (рядок, стовпець)
      */
     std::pair<int, int> getCoordinates(const Board& board, const std::string& message) const;
     
     /**
      * @brief Ввести дошку вручну
      * @param board Посилання на дошку
      */
     void inputBoard(Board& board) const;
     
     /**
      * @brief Відобразити повідомлення для користувача
      * @param message Повідомлення
      */
     void displayMessage(const std::string& message) const;
     
     /**
      * @brief Відобразити помилку
      * @param message Повідомлення про помилку
      */
     void displayError(const std::string& message) const;
     
     /**
      * @brief Відобразити вітання з вирішенням головоломки
      */
     void displayCongratulations() const;
     
     /**
      * @brief Очікування натискання клавіші для продовження
      */
     void waitForKeyPress() const;
     
     /**
      * @brief Вирішити головоломку вручну
      * @param board Посилання на дошку
      * @return true, якщо головоломка вирішена
      */
     bool solveManually(Board& board) const;
 };
 
 #endif // USER_INTERFACE_H