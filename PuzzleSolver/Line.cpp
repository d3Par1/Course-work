/**
 * @file Line.cpp
 * @brief Реалізація класу Line
 */

 #include "Line.h"
 #include <algorithm>
 
 Line::Line() : isValid(false) {
     // Конструктор за замовчуванням створює недійсну лінію
 }
 
 Line::Line(const Symbol& start, const Symbol& end) : start(start), end(end), isValid(false) {
     // Перевіряємо, чи символи однакові
     if (!start.isSameValue(end)) {
         isValid = false;
         return;
     }
     
     // Ініціалізуємо шлях початковою точкою
     path.push_back(std::make_pair(start.getRow(), start.getCol()));
     
     // Лінія поки що не завершена, тому не є дійсною
     isValid = false;
 }
 
 Symbol Line::getStart() const {
     return start;
 }
 
 Symbol Line::getEnd() const {
     return end;
 }
 
 std::vector<std::pair<int, int>> Line::getPath() const {
     return path;
 }
 
 bool Line::getIsValid() const {
     return isValid;
 }
 
 void Line::setPath(const std::vector<std::pair<int, int>>& path) {
     this->path = path;
 }
 
 void Line::setIsValid(bool valid) {
     isValid = valid;
 }
 
 void Line::addPoint(int row, int col) {
     // Додаємо точку до шляху
     path.push_back(std::make_pair(row, col));
     
     // Перевіряємо, чи досягли кінцевої точки
     if (row == end.getRow() && col == end.getCol()) {
         isValid = true;
     }
 }
 
 void Line::removeLastPoint() {
     // Перевіряємо, чи шлях не порожній
     if (!path.empty()) {
         // Якщо остання точка була кінцевою, лінія стає недійсною
         if (path.back().first == end.getRow() && path.back().second == end.getCol()) {
             isValid = false;
         }
         
         // Видаляємо останню точку
         path.pop_back();
     }
 }
 
 void Line::clearPath() {
     // Очищаємо шлях, залишаючи лише початкову точку
     path.clear();
     path.push_back(std::make_pair(start.getRow(), start.getCol()));
     isValid = false;
 }
 
 bool Line::containsPoint(int row, int col) const {
     // Перевіряємо, чи шлях містить точку
     return std::find(path.begin(), path.end(), std::make_pair(row, col)) != path.end();
 }
 
 bool Line::crosses2x2Area() const {
     // Перевіряємо, чи шлях перетинає всі 4 клітини будь-якої області 2x2
     
     // Якщо шляху немає або він містить менше 4 точок, то не може перетинати 2x2
     if (path.size() < 4) {
         return false;
     }
     
     // Проходимо по всіх можливих початкових точках 2x2 областей у шляху
     for (size_t i = 0; i < path.size() - 1; ++i) {
         int row = path[i].first;
         int col = path[i].second;
         
         // Перевіряємо, чи всі 4 клітини області 2x2 містяться у шляху
         bool topLeft = containsPoint(row, col);
         bool topRight = containsPoint(row, col + 1);
         bool bottomLeft = containsPoint(row + 1, col);
         bool bottomRight = containsPoint(row + 1, col + 1);
         
         if (topLeft && topRight && bottomLeft && bottomRight) {
             return true;
         }
     }
     
     return false;
 }