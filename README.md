# 🎓 Course Work (C++)

```
╔═══════════════════════════════════════════════════════════════╗
║                                                               ║
║   ██████╗ ██████╗ ██╗   ██╗██████╗ ███████╗███████╗           ║
║  ██╔════╝██╔═══██╗██║   ██║██╔══██╗██╔════╝██╔════╝           ║
║  ██║     ██║   ██║██║   ██║██████╔╝███████╗█████╗             ║
║  ██║     ██║   ██║██║   ██║██╔══██╗╚════██║██╔══╝             ║
║  ╚██████╗╚██████╔╝╚██████╔╝██║  ██║███████║███████╗           ║
║   ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝           ║
║                                                               ║
║   ██╗    ██╗ ██████╗ ██████╗ ██╗  ██╗                         ║
║   ██║    ██║██╔═══██╗██╔══██╗██║ ██╔╝                         ║
║   ██║ █╗ ██║██║   ██║██████╔╝█████╔╝                          ║
║   ██║███╗██║██║   ██║██╔══██╗██╔═██╗                          ║
║   ╚███╔███╔╝╚██████╔╝██║  ██║██║  ██╗                         ║
║    ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝                         ║
║                                                               ║
║   ╔═════╗   ╔═════╗ ╔═════╗                                   ║
║   ║  C  ╟───╢  +  ║ ║  +  ║                                   ║
║   ╚═════╝   ╚═════╝ ╚═════╝                                   ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
```

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License](https://img.shields.io/badge/license-Unlicense-green.svg)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg)

## 📋 Overview

Welcome to the **Course Work** repository! This collection showcases various C++ programming projects developed during coursework. The repository demonstrates a progression in learning C++ concepts through practical implementations.

## 🚀 Getting Started

### Prerequisites

- C++ compiler (C++11 or newer)
- Terminal with ANSI color support for best visual experience
- Basic command line knowledge

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/Course-work.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Course-work/PuzzleSolver
   ```

3. Compile the code with warnings enabled:

   ```bash
   g++ -Wall numberlink.cpp -o numberlink
   ```

4. Run the application:
   ```bash
   ./numberlink
   ```

## 💻 Code Structure

The codebase follows object-oriented design principles with robust error handling and algorithmic optimizations:

### Core Components

| Component          | Description                                                                         |
| ------------------ | ----------------------------------------------------------------------------------- |
| `Cell`             | Basic unit struct of the puzzle grid with symbol, value, and visited state          |
| `NumberlinkSolver` | Main solver class with grid management, path-finding algorithms and rendering logic |

### Key Algorithms

```cpp
// Breadth-First Search implementation for path finding
void NumberlinkSolver::findPath(
    std::pair<int, int> start,
    std::pair<int, int> end,
    int value)
{
    // Simple BFS path finding that avoids 2x2 squares
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    queue<pair<int, int>> q;

    // BFS algorithm implementation
    // ...

    // Path reconstruction
    // ...
}
```

```cpp
// Checks if placing a value would create an invalid 2x2 pattern
bool NumberlinkSolver::wouldCreate2x2(int r1, int c1, int r2, int c2, int value)
{
    // Check if adding a path segment would create a 2x2 block
    // Temporarily mark both cells with the value
    // Check all possible 2x2 blocks that could include both cells
    // ...

    return creates2x2;
}
```

### Special Features

- **COLOGNE Diagonal**: Special highlighting for the letters C, O, L, O, G, N, E arranged diagonally
- **ANSI Color Coding**: Different path colors for easy visual distinction
- **Enhanced Path Characters**: Special Unicode box-drawing characters to show path connections, corners, and junctions

### Data Structures

- **Grid Representation**: 2D vector of `Cell` objects
- **Symbol Positions**: Map of character to vector of coordinate pairs
- **Path Storage**: Parent tracking in 2D vector for path reconstruction
- **BFS Implementation**: Queue for frontier cells with visited tracking

## 📄 License

This project is licensed under the Unlicense - see the [`LICENSE`](LICENSE) file for details.

## 📊 Technologies Used

- C++ Standard Library
- Object-Oriented Programming
- BFS Path-finding Algorithm
- ANSI Color Terminal Output
- Unicode Box-Drawing Characters

---

<p align="center">
  Made with ❤️ by a Nazar Stepanenko
</p>
