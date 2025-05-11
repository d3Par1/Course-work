# 🎓 Course Work (C++)

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

![Numberlink Example](https://via.placeholder.com/600x300?text=Numberlink+Puzzle+Solver)

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

3. Compile the code:

   ```bash
   g++ numberlink.cpp -o numberlink
   ```

4. Run the application:
   ```bash
   ./numberlink
   ```

## 💻 Code Structure

The codebase follows object-oriented design principles:

| Class/Component    | Description                                                         |
| ------------------ | ------------------------------------------------------------------- |
| `Cell`             | Basic unit of the puzzle grid with symbol, value, and visited state |
| `NumberlinkSolver` | Main solver class with grid management and path-finding algorithms  |
| `findPath()`       | BFS implementation for creating symbol-connecting paths             |
| `drawSolution()`   | Renders the completed puzzle with proper connections                |

## 🔍 Implementation Details

The Numberlink solver employs these key algorithms and data structures:

- **Breadth-First Search (BFS)** for pathfinding between matching symbols
- **2x2 Pattern Detection** to satisfy puzzle constraints
- **Unicode Box-Drawing** for aesthetically pleasing visualization
- **STL Containers** like vectors, maps and queues for efficient data management

```cpp
void findPath(pair<int, int> start, pair<int, int> end, int value) {
    // BFS implementation with queue
    // Avoids creating 2x2 blocks of the same value
    // ...
}
```

## 🛠️ Future Improvements

- [ ] Add ability to load puzzles from files
- [ ] Implement backtracking for puzzles with multiple solutions
- [ ] Create a graphical user interface
- [ ] Add more puzzle types beyond Numberlink

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
