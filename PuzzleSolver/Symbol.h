/**
 * @file Symbol.h
 * @brief Клас для представлення символів на дошці
 */

 #ifndef SYMBOL_H
 #define SYMBOL_H
 
 #include <string>
 
 /**
  * @class Symbol
  * @brief Клас для представлення символу на ігровій дошці
  * 
  * Клас Symbol представляє символ на ігровій дошці, який є частиною пари,
  * що потрібно з'єднати. Клас містить інформацію про символ та його координати.
  */
 class Symbol {
 private:
     char value;         // Значення символу (буква або цифра)
     int row;            // Рядок на дошці
     int col;            // Стовпець на дошці
     bool isConnected;   // Чи з'єднаний з іншим таким самим символом
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     Symbol();
     
     /**
      * @brief Конструктор з параметрами
      * @param value Значення символу
      * @param row Рядок
      * @param col Стовпець
      */
     Symbol(char value, int row, int col);
     
     /**
      * @brief Отримати значення символу
      * @return Значення символу
      */
     char getValue() const;
     
     /**
      * @brief Отримати рядок символу
      * @return Рядок символу
      */
     int getRow() const;
     
     /**
      * @brief Отримати стовпець символу
      * @return Стовпець символу
      */
     int getCol() const;
     
     /**
      * @brief Перевірити, чи символ з'єднаний
      * @return true, якщо символ з'єднаний
      */
     bool getIsConnected() const;
     
     /**
      * @brief Встановити стан з'єднання символу
      * @param connected Новий стан з'єднання
      */
     void setIsConnected(bool connected);
     
     /**
      * @brief Перевірити, чи символи мають однакове значення
      * @param other Інший символ для порівняння
      * @return true, якщо символи однакові
      */
     bool isSameValue(const Symbol& other) const;
     
     /**
      * @brief Обчислити манхеттенську відстань між символами
      * @param other Інший символ
      * @return Манхеттенська відстань
      */
     int manhattanDistance(const Symbol& other) const;
     
     /**
      * @brief Перевірити, чи символи знаходяться на одній лінії (рядку або стовпці)
      * @param other Інший символ
      * @return true, якщо символи на одній лінії
      */
     bool isInLine(const Symbol& other) const;
 };
 
 #endif // SYMBOL_H