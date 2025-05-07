#include "PuzzleSolver.h"
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

PuzzleSolver::PuzzleSolver(int _rows, int _cols) : rows(_rows), cols(_cols) {
    grid.resize(rows, vector<char>(cols, ' '));
    used.resize(rows, vector<bool>(cols, false));
}

bool PuzzleSolver::isValidPoint(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

void PuzzleSolver::setSymbol(int x, int y, char symbol) {
    if (isValidPoint(x, y)) {
        grid[x][y] = symbol;
        if (symbol != ' ') {
            symbolPositions[symbol].push_back(Point(x, y));
        }
    }
}

bool PuzzleSolver::violates2x2Rule(const vector<Point>& path) {
    // Перевіряємо, чи порушує шлях правило 2x2
    for (size_t i = 0; i < path.size() - 3; ++i) {
        int minX = min(path[i].x, min(path[i+1].x, min(path[i+2].x, path[i+3].x)));
        int maxX = max(path[i].x, max(path[i+1].x, max(path[i+2].x, path[i+3].x)));
        int minY = min(path[i].y, min(path[i+1].y, min(path[i+2].y, path[i+3].y)));
        int maxY = max(path[i].y, max(path[i+1].y, max(path[i+2].y, path[i+3].y)));
        
        if (maxX - minX <= 1 && maxY - minY <= 1) {
            // Усі 4 точки лежать у квадраті 2x2
            return true;
        }
    }
    return false;
}

vector<Point> PuzzleSolver::findPath(Point start, Point end) {
    // BFS для пошуку найкоротшого шляху
    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(-1, -1)));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Point> q;
    
    q.push(start);
    visited[start.x][start.y] = true;
    
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if (curr == end) {
            // Шлях знайдено, відновлюємо його
            vector<Point> path;
            Point p = end;
            while (!(p == start)) {
                path.push_back(p);
                p = parent[p.x][p.y];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            
            // Перевіряємо правило 2x2
            if (violates2x2Rule(path)) {
                return vector<Point>(); // Порожній шлях
            }
            
            return path;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (isValidPoint(nx, ny) && !visited[nx][ny] && !used[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = curr;
                q.push(Point(nx, ny));
            }
        }
    }
    
    return vector<Point>(); // Шлях не знайдено
}

bool PuzzleSolver::solve() {
    // Очищаємо попередні дані
    paths.clear();
    used.assign(rows, vector<bool>(cols, false));
    
    // Позначаємо клітини з символами як використані
    for (const auto& pair : symbolPositions) {
        for (const Point& p : pair.second) {
            used[p.x][p.y] = true;
        }
    }
    
    // Для кожного символу знаходимо шлях
    for (const auto& pair : symbolPositions) {
        char symbol = pair.first;
        
        // Пропускаємо символи, які з'являються не рівно 2 рази
        if (pair.second.size() != 2) continue;
        
        Point start = pair.second[0];
        Point end = pair.second[1];
        
        // Знаходимо шлях
        vector<Point> path = findPath(start, end);
        
        if (path.empty()) {
            return false; // Шлях не знайдено
        }
        
        // Додаємо шлях до списку
        Path newPath(symbol);
        newPath.points = path;
        paths.push_back(newPath);
        
        // Позначаємо клітини шляху як використані (крім кінцевих точок)
        for (size_t i = 1; i < path.size() - 1; ++i) {
            used[path[i].x][path[i].y] = true;
        }
    }
    
    return true; // Усі шляхи знайдено
}

void PuzzleSolver::displayResult() {
    // Створюємо матрицю для відображення
    vector<vector<string>> display(rows, vector<string>(cols, "   "));
    
    // Вставляємо символи
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != ' ') {
                display[i][j] = " " + string(1, grid[i][j]) + " ";
            }
        }
    }
    
    // Вставляємо шляхи
    for (const Path& path : paths) {
        for (size_t i = 0; i < path.points.size() - 1; ++i) {
            Point curr = path.points[i];
            Point next = path.points[i + 1];
            
            if (curr.x == next.x) { // Горизонтальна лінія
                int minY = min(curr.y, next.y);
                int maxY = max(curr.y, next.y);
                for (int y = minY; y <= maxY; ++y) {
                    if (grid[curr.x][y] == ' ') {
                        display[curr.x][y] = "---";
                    }
                }
            } else if (curr.y == next.y) { // Вертикальна лінія
                int minX = min(curr.x, next.x);
                int maxX = max(curr.x, next.x);
                for (int x = minX; x <= maxX; ++x) {
                    if (grid[x][curr.y] == ' ') {
                        display[x][curr.y] = " | ";
                    }
                }
            }
        }
    }
    
    // Виводимо результат
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << display[i][j];
        }
        cout << endl;
    }
}