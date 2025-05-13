# 🎓 Course Work (C++)

```
╔═══════════════════════════════════════════════════════════════╗
║                                                               ║
║   ██████╗ ██████╗ ██╗   ██╗██████╗ ███████╗███████╗          ║
║  ██╔════╝██╔═══██╗██║   ██║██╔══██╗██╔════╝██╔════╝          ║
║  ██║     ██║   ██║██║   ██║██████╔╝███████╗█████╗            ║
║  ██║     ██║   ██║██║   ██║██╔══██╗╚════██║██╔══╝            ║
║  ╚██████╗╚██████╔╝╚██████╔╝██║  ██║███████║███████╗          ║
║   ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝          ║
║                                                               ║
║   ██╗    ██╗ ██████╗ ██████╗ ██╗  ██╗                        ║
║   ██║    ██║██╔═══██╗██╔══██╗██║ ██╔╝                        ║
║   ██║ █╗ ██║██║   ██║██████╔╝█████╔╝                         ║
║   ██║███╗██║██║   ██║██╔══██╗██╔═██╗                         ║
║   ╚███╔███╔╝╚██████╔╝██║  ██║██║  ██╗                        ║
║    ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝                        ║
║                                                               ║
║   ╔═════╗   ╔═════╗ ╔═════╗                                  ║
║   ║  C  ╟───╢  +  ║ ║  +  ║                                  ║
║   ╚═════╝   ╚═════╝ ╚═════╝                                  ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
```


![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License](https://img.shields.io/badge/license-Unlicense-green.svg)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg)

## 📋 Overview

Welcome to the **Course Work** repository! This collection showcases various C++ programming projects developed during coursework. The repository demonstrates a progression in learning C++ concepts through practical implementations.

## 🧩 Featured Projects

### Numberlink Puzzle Solver

A sophisticated implementation of a [Numberlink](https://en.wikipedia.org/wiki/Numberlink) puzzle solver that:

- Creates and visualizes a grid-based puzzle board
- Connects matching symbols with paths using BFS algorithm
- Prevents 2x2 block formations (puzzle constraint)
- Renders beautiful console-based UI with Unicode box-drawing characters

```
┌───┬───┬───┬───┬───┐
│ 1 │   │   │ 1 │ 2 │
├───┼───┼───┼───┼───┤
│ ━ │ ━ │ ━ │ ┘ │ ┃ │
├───┼───┼───┼───┼───┤
│ 3 │   │   │ 3 │ ┃ │
├───┼───┼───┼───┼───┤
│ ┃ │ ━ │ ━ │ ┘ │ ┃ │
├───┼───┼───┼───┼───┤
│   │ 4 │ ━ │ 4 │ 2 │
└───┴───┴───┴───┴───┘
```

## 🚀 Getting Started

### Prerequisites

- C++ compiler (C++11 or newer)
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

| Class/Component    | Description                                                                      |
| ------------------ | -------------------------------------------------------------------------------- |
| `Cell`             | Basic unit of the puzzle grid with symbol, value, and visited state              |
| `Grid`             | Container for cells with operations for accessing and modifying the puzzle board |
| `NumberlinkSolver` | Main solver class with grid management and path-finding algorithms               |
| `PuzzleValidator`  | Ensures puzzle has a valid configuration before solving                          |
| `SolutionRenderer` | Handles UI rendering with different output modes (text, Unicode)                 |

### Key Algorithms

```cpp
// Breadth-First Search implementation for path finding
std::vector<std::pair<int, int>> NumberlinkSolver::findPath(
    std::pair<int, int> start,
    std::pair<int, int> end,
    int value)
{
    std::queue<std::pair<int, int>> bfsQueue;
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // BFS algorithm implementation
    // ...

    // Path reconstruction from parent map
    // ...

    return path;
}
```

```cpp
// Checks if placing a value would create an invalid 2x2 pattern
bool NumberlinkSolver::creates2x2Pattern(int row, int col, int value) {
    // Check neighboring cells in 2x2 formations
    // ...
    return false;
}
```

### Data Structures

- **Grid Representation**: 2D vector of `Cell` objects
- **Path Storage**: Vectors of coordinate pairs
- **State Management**: Maps for tracking symbol locations and completed paths
- **BFS Implementation**: Queue for frontier cells with map for parent tracking

### Class Relationships

```
┌───────────────┐     ┌───────────┐     ┌─────────────────┐
│ NumberlinkGame│───▶│   Grid     │───▶│      Cell       │
└───────┬───────┘     └───────────┘     └─────────────────┘
        │                    ▲
        │                    │
        ▼                    │
┌───────────────┐     ┌─────────────┐    ┌─────────────────┐
│NumberlinkSolver│──▶│PuzzleValidator│   │SolutionRenderer │
└───────┬───────┘     └─────────────┘    └─────────────────┘
        │                                          ▲
        └──────────────────────────────────────────┘
```

## 📄 License

This project is licensed under the Unlicense - see the `LICENSE` file for details.

## 📊 Technologies Used

- C++ Standard Library
- Object-Oriented Programming
- BFS Path-finding Algorithm
- Console-based UI Rendering

---

<p align="center">
  Made with ❤️ by a Nazar Stepanenko
</p>
