/**
 * @file Symbol.cpp
 * @brief Реалізація класу Symbol
 */

 #include "Symbol.h"
 #include <cmath>
 
 Symbol::Symbol() : value(' '), row(0), col(0), isConnected(false) {
     // Конструктор за замовчуванням створює порожній символ
 }
 
 Symbol::Symbol(char value, int row, int col) : 
     value(value), row(row), col(col), isConnected(false) {
     // Конструктор з параметрами створює символ із заданими значеннями
 }
 
 char Symbol::getValue() const {
     return value;
 }
 
 int Symbol::getRow() const {
     return row;
 }
 
 int Symbol::getCol() const {
     return col;
 }
 
 bool Symbol::getIsConnected() const {
     return isConnected;
 }
 
 void Symbol::setIsConnected(bool connected) {
     isConnected = connected;
 }
 
 bool Symbol::isSameValue(const Symbol& other) const {
     // Перевіряє, чи символи мають однакове значення
     return (value == other.value);
 }
 
 int Symbol::manhattanDistance(const Symbol& other) const {
     // Обчислює манхеттенську відстань між символами
     // Манхеттенська відстань - це сума абсолютних різниць координат
     return std::abs(row - other.row) + std::abs(col - other.col);
 }
 
 bool Symbol::isInLine(const Symbol& other) const {
     // Перевіряє, чи символи знаходяться на одній лінії (рядку або стовпці)
     return (row == other.row || col == other.col);
 }