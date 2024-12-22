# AI Pathfinding Algorithms Assignment

This repository contains the implementation of various pathfinding algorithms, developed as part of an Artificial Intelligence course assignment. The program demonstrates the application of Greedy Best-First Search, A* Search, and Iterative Deepening A* Search on a grid-based map.

## Features

- **Grid Representation:** The program reads a grid from a file (`grid.txt`), where each cell can represent an open space or an obstacle.
- **Pathfinding Algorithms:**
  - **Greedy Best-First Search**: Uses heuristic to expand nodes.
  - **A* Search**: Combines heuristic and path cost for efficient traversal.
  - **Iterative Deepening A***: Adds depth limits to the A* approach.
- **Visualization:** Displays the grid with the path found by the algorithm.
- **Customizable Input:** Modify `grid.txt` to test different scenarios.

## Files in the Repository

### Source Code
- **`Source.cpp`**: Contains the main implementation of the pathfinding algorithms.
- **`grid.txt`**: Input file defining the grid, start point, goal point, and obstacles.
- **`Assignment 02 Final.vcxproj` and related files**: Visual Studio project files for building and running the program.
- **`Source.exe`**: Precompiled executable for running the program (Windows only).

### Folders
- **`Debug`**: Contains build artifacts and debugging information.

## Grid Input Format (`grid.txt`)

The input grid format is as follows:
```
<Number of Columns> <Number of Rows>
<Start Column> <Start Row>
<Goal Column> <Goal Row>
<Row-wise representation of the grid>
```
- **0**: Open cell.
- **1**: Obstacle.

Example:
```
5 5
0 0
4 4
0 0 0 0 0
0 1 1 1 0
0 1 0 1 0
0 1 0 0 0
0 0 0 0 0
```

## How to Run

### Prerequisites
- **Windows OS** (for compatibility with `Windows.h` header).
- Visual Studio (or any compatible C++ compiler).

### Steps
1. Clone the repository:
   ```
   git clone <repository_url>
   cd <repository_directory>
   ```
2. Open the Visual Studio project (`Assignment 02 Final.vcxproj`).
3. Build the project to generate the executable.
4. Place the input grid in the `grid.txt` file.
5. Run the program:
   - Use the terminal or double-click `Source.exe`.
   - Follow the on-screen menu to select a pathfinding algorithm.

### Menu Options
Upon running the program, the following options are presented:
```
Press:
0: Exit
1: Greedy Best First Search
2: A* Search
3: Iterative Deepening A* Search
```

## Example Execution
Input Grid:
```
5 5
0 0
4 4
0 0 0 0 0
0 1 1 1 0
0 1 0 1 0
0 1 0 0 0
0 0 0 0 0
```

Output (Path Visualization):
```
S  *  *  *  *
0  1  1  1  *
0  1  0  1  *
0  1  0  0  *
0  0  0  0  G

Path Cost = 8
```

## Notes
- The program uses heuristic calculations based on Manhattan distance.
- Modify the `grid.txt` file to test different scenarios or adjust the program logic.

## Contribution
Feel free to create issues or submit pull requests for improvements or bug fixes.

---

Enjoy exploring AI pathfinding algorithms!
