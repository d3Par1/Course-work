/**
 * @file Cell.h
 * @brief Клас для представлення клітини на дошці
 */

 #ifndef CELL_H
 #define CELL_H
 
 #include <string>
 #include "Constants.h"
 
 /**
  * @class Cell
  * @brief Клас для представлення однієї клітини на ігровій дошці
  * 
  * Клас Cell представляє окрему клітину на ігровій дошці головоломки.
  * Клітина може містити символ або бути порожньою, а також може бути
  * частиною лінії, яка з'єднує два однакові символи.
  */
 class Cell {
 private:
     char content;       // Символ у клітині (букви, цифри або пусто)
     int state;          // Стан клітини (пуста, зайнята лінією, містить символ)
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     Cell();
     
     /**
      * @brief Конструктор з параметрами
      * @param content Символ у клітині
      * @param state Стан клітини
      */
     Cell(char content, int state);
     
     /**
      * @brief Отримати символ у клітині
      * @return Символ у клітині
      */
     char getContent() const;
     
     /**
      * @brief Встановити символ у клітині
      * @param content Новий символ
      */
     void setContent(char content);
     
     /**
      * @brief Отримати стан клітини
      * @return Стан клітини
      */
     int getState() const;
     
     /**
      * @brief Встановити стан клітини
      * @param state Новий стан
      */
     void setState(int state);
     
     /**
      * @brief Перевірити, чи клітина пуста
      * @return true, якщо клітина пуста
      */
     bool isEmpty() const;
     
     /**
      * @brief Перевірити, чи клітина містить символ
      * @return true, якщо клітина містить символ
      */
     bool hasSymbol() const;
     
     /**
      * @brief Перевірити, чи клітина є частиною лінії
      * @return true, якщо клітина є частиною лінії
      */
     bool isPartOfLine() const;
     
     /**
      * @brief Отримати символ для відображення в консолі
      * @return Символ для відображення
      */
     char getDisplayChar() const;
     
     /**
      * @brief Очистити клітину
      */
     void clear();
 };
 
 #endif // CELL_H