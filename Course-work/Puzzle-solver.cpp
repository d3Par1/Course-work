#ifndef POINT_H
#define POINT_H

struct Point {
    int x, y;
    
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

#endif

#ifndef PATH_H
#define PATH_H

#include <vector>
#include "Point.h"

struct Path {
    std::vector<Point> points;
    char symbol;
    
    Path(char _symbol = ' ') : symbol(_symbol) {}
};

#endif

#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <vector>
#include <map>
#include <string>
#include "Point.h"
#include "Path.h"

class PuzzleSolver {
private:
    int rows, cols;                      
    std::vector<std::vector<char>> grid; 
    std::vector<std::vector<bool>> used; 
    std::map<char, std::vector<Point>> symbolPositions; 
    std::vector<Path> paths;
    
    bool isValidPoint(int x, int y);    
    bool violates2x2Rule(const std::vector<Point>& path);
    std::vector<Point> findPath(Point start, Point end);

public:
    PuzzleSolver(int _rows, int _cols);
    
    void setSymbol(int x, int y, char symbol); 
    bool solve();                     
    void displayResult();         
    
    std::vector<Path> getPaths() const { return paths; }
    std::vector<std::vector<char>> getGrid() const { return grid; }
};

#endif 

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

// ConsoleUI.h
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "PuzzleSolver.h"

class ConsoleUI {
private:
    PuzzleSolver* solver; 
    
    void loadExample();  
    void manualInput();
    
public:
    ConsoleUI();
    ~ConsoleUI();
    
    void displayMenu();    
    void handleInput();   
    void displayResult(); 
};

#endif 

#include "ConsoleUI.h"
#include <iostream>
#include <limits>

using namespace std;

ConsoleUI::ConsoleUI() : solver(nullptr) {}

ConsoleUI::~ConsoleUI() {
    if (solver != nullptr) {
        delete solver;
    }
}

void ConsoleUI::displayMenu() {
    cout << "=======================================\n";
    cout << "  ГОЛОВОЛОМКА З'ЄДНАННЯ ПАР СИМВОЛІВ  \n";
    cout << "=======================================\n";
    cout << "1 - Ввести дані вручну\n";
    cout << "2 - Використати приклад із завдання\n";
    cout << "3 - Вийти з програми\n";
    cout << "=======================================\n";
    cout << "Виберіть опцію: ";
}

void ConsoleUI::handleInput() {
    int choice;
    cin >> choice;
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            manualInput();
            break;
        case 2:
            loadExample();
            break;
        case 3:
            cout << "До побачення!\n";
            exit(0);
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
            break;
    }
}

void ConsoleUI::manualInput() {
    int rows, cols;
    
    cout << "Введіть кількість рядків: ";
    cin >> rows;
    
    cout << "Введіть кількість стовпців: ";
    cin >> cols;
    
    if (solver != nullptr) {
        delete solver;
    }
    solver = new PuzzleSolver(rows, cols);
    
    cout << "Введіть символи (пробіл для порожньої клітини):\n";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char symbol;
            symbol = cin.get();
            
            if (symbol == '\n') {
                j--;
                continue;
            }
            
            solver->setSymbol(i, j, symbol);
        }
    }
    
    displayResult();
}

void ConsoleUI::loadExample() {
    const int ROWS = 13;
    const int COLS = 13;
    char example[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'R', ' '},
        {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', 'L', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'N'},
        {' ', ' ', ' ', ' ', ' ', 'L', ' ', ' ', ' ', ' ', 'C', ' ', ' '},
        {' ', 'G', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', ' '},
        {'Z', ' ', ' ', 'E', ' ', ' ', ' ', ' ', 'N', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', 'T', ' '},
        {' ', ' ', ' ', 'T', ' ', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', 'Z', ' ', ' ', ' ', ' ', ' ', 'M'},
        {' ', ' ', ' ', ' ', ' ', ' ', 'M', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    
    if (solver != nullptr) {
        delete solver;
    }
    solver = new PuzzleSolver(ROWS, COLS);
    
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            solver->setSymbol(i, j, example[i][j]);
        }
    }
    
    displayResult();
}

void ConsoleUI::displayResult() {
    cout << "\nРозв'язуємо головоломку...\n";
    
    bool result = solver->solve();
    
    if (result) {
        cout << "Розв'язок знайдено:\n\n";
        solver->displayResult();
    } else {
        cout << "Розв'язок не знайдено!\n";
    }
    
    cout << "\nБажаєте повернутися до головного меню? (1 - Так, 2 - Ні): ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        displayMenu();
        handleInput();
    } else {
        cout << "До побачення!\n";
        exit(0);
    }
}

#include "ConsoleUI.h"

int main() {
    ConsoleUI ui;
    
    ui.displayMenu();
    ui.handleInput();
    
    return 0;
}