/**
 * @file Line.h
 * @brief Клас для представлення лінії між символами
 */

 #ifndef LINE_H
 #define LINE_H
 
 #include <vector>
 #include <utility>
 #include "Symbol.h"
 
 /**
  * @class Line
  * @brief Клас для представлення лінії, що з'єднує два символи
  * 
  * Клас Line представляє лінію, яка з'єднує два однакові символи
  * на ігровій дошці. Лінія складається з послідовності точок (клітин).
  */
 class Line {
 private:
     Symbol start;                            // Початковий символ
     Symbol end;                              // Кінцевий символ
     std::vector<std::pair<int, int>> path;   // Шлях лінії (послідовність координат)
     bool isValid;                            // Чи є лінія дійсною
 
 public:
     /**
      * @brief Конструктор за замовчуванням
      */
     Line();
     
     /**
      * @brief Конструктор з параметрами
      * @param start Початковий символ
      * @param end Кінцевий символ
      */
     Line(const Symbol& start, const Symbol& end);
     
     /**
      * @brief Отримати початковий символ
      * @return Початковий символ
      */
     Symbol getStart() const;
     
     /**
      * @brief Отримати кінцевий символ
      * @return Кінцевий символ
      */
     Symbol getEnd() const;
     
     /**
      * @brief Отримати шлях лінії
      * @return Шлях лінії
      */
     std::vector<std::pair<int, int>> getPath() const;
     
     /**
      * @brief Перевірити, чи лінія дійсна
      * @return true, якщо лінія дійсна
      */
     bool getIsValid() const;
     
     /**
      * @brief Встановити шлях лінії
      * @param path Новий шлях
      */
     void setPath(const std::vector<std::pair<int, int>>& path);
     
     /**
      * @brief Встановити валідність лінії
      * @param valid Нове значення валідності
      */
     void setIsValid(bool valid);
     
     /**
      * @brief Додати точку до шляху
      * @param row Рядок
      * @param col Стовпець
      */
     void addPoint(int row, int col);
     
     /**
      * @brief Видалити останню точку з шляху
      */
     void removeLastPoint();
     
     /**
      * @brief Очистити шлях
      */
     void clearPath();
     
     /**
      * @brief Перевірити, чи шлях містить точку
      * @param row Рядок
      * @param col Стовпець
      * @return true, якщо шлях містить точку
      */
     bool containsPoint(int row, int col) const;
     
     /**
      * @brief Перевірити, чи шлях перетинає область 2x2
      * @param board Посилання на дошку
      * @return true, якщо шлях перетинає область 2x2
      */
     bool crosses2x2Area() const;
 };
 
 #endif // LINE_H