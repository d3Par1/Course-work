/**
 * @file Cell.cpp
 * @brief Реалізація класу Cell
 */

 #include "Cell.h"

 Cell::Cell() : content(ConsoleSymbols::EMPTY), state(CellState::EMPTY) {
     // Конструктор за замовчуванням створює порожню клітину
 }
 
 Cell::Cell(char content, int state) : content(content), state(state) {
     // Конструктор з параметрами створює клітину з заданими значеннями
 }
 
 char Cell::getContent() const {
     return content;
 }
 
 void Cell::setContent(char content) {
     this->content = content;
 }
 
 int Cell::getState() const {
     return state;
 }
 
 void Cell::setState(int state) {
     this->state = state;
 }
 
 bool Cell::isEmpty() const {
     return (state == CellState::EMPTY);
 }
 
 bool Cell::hasSymbol() const {
     return (state == CellState::ENDPOINT && content != ConsoleSymbols::EMPTY);
 }
 
 bool Cell::isPartOfLine() const {
     return (state == CellState::OCCUPIED);
 }
 
 char Cell::getDisplayChar() const {
     // Повертає символ для відображення в консолі
     if (hasSymbol()) {
         // Якщо клітина містить символ, повертаємо його
         return content;
     } else if (isPartOfLine()) {
         // Якщо клітина є частиною лінії, повертаємо відповідний символ
         return content; // В даному випадку content міститиме символ для відображення лінії
     } else {
         // Порожня клітина
         return ConsoleSymbols::EMPTY;
     }
 }
 
 void Cell::clear() {
     // Очищення клітини
     content = ConsoleSymbols::EMPTY;
     state = CellState::EMPTY;
 }