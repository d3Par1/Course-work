#ifndef POINT_H
#define POINT_H

struct Point {
    int x, y;
    
    // Конструктор за замовчуванням
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    // Оператор порівняння для перевірки рівності двох точок
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    // Оператор порівняння для використання Point як ключа у map
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};
#endif