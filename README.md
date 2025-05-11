🎓 Course Work (C++)
<img alt="C++" src="https://img.shields.io/badge/C++-17-blue.svg">
<img alt="License" src="https://img.shields.io/badge/license-Unlicense-green.svg">
<img alt="Status" src="https://img.shields.io/badge/status-active-brightgreen.svg">
📋 Overview
Welcome to the Course Work repository! This collection showcases various C++ programming projects developed during coursework. The repository demonstrates a progression in learning C++ concepts through practical implementations.

🧩 Featured Projects
Numberlink Puzzle Solver
A sophisticated implementation of a Numberlink puzzle solver that:

Creates and visualizes a grid-based puzzle board
Connects matching symbols with paths using BFS algorithm
Prevents 2x2 block formations (puzzle constraint)
Renders beautiful console-based UI with Unicode box-drawing characters
<img alt="Numberlink Example" src="https://via.placeholder.com/600x300?text=Numberlink+Puzzle+Solver">
🚀 Getting Started
Prerequisites
C++ compiler (C++11 or newer)
Basic command line knowledge
Installation
Clone the repository:

Navigate to the project directory:

Compile the code:

Run the application:

💻 Code Structure
The codebase follows object-oriented design principles:

Class/Component	Description
Cell	Basic unit of the puzzle grid with symbol, value, and visited state
NumberlinkSolver	Main solver class with grid management and path-finding algorithms
findPath()	BFS implementation for creating symbol-connecting paths
drawSolution()	Renders the completed puzzle with proper connections
🔍 Implementation Details
The Numberlink solver employs these key algorithms and data structures:

Breadth-First Search (BFS) for pathfinding between matching symbols
2x2 Pattern Detection to satisfy puzzle constraints
Unicode Box-Drawing for aesthetically pleasing visualization
STL Containers like vectors, maps and queues for efficient data management
🛠️ Future Improvements
<input disabled="" type="checkbox"> Add ability to load puzzles from files
<input disabled="" type="checkbox"> Implement backtracking for puzzles with multiple solutions
<input disabled="" type="checkbox"> Create a graphical user interface
<input disabled="" type="checkbox"> Add more puzzle types beyond Numberlink
📄 License
This project is licensed under the Unlicense - see the LICENSE file for details.

📊 Technologies Used
C++ Standard Library
Object-Oriented Programming
BFS Path-finding Algorithm
Console-based UI Rendering
<p align="center"> Made with ❤️ by a passionate C++ programmer </p>