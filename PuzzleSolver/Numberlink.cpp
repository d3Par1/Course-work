#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <utility>
using namespace std;

// Cell structure - simplified
struct Cell
{
    char symbol;  // Letter symbol (or space for empty)
    int value;    // Numeric value (for processing)
    bool visited; // For path tracking
};

class NumberlinkSolver
{
public:
    NumberlinkSolver(int size)
    {
        // Initialize grid
        rows = size;
        cols = size;
        grid.resize(size, vector<Cell>(size));

        // Set all cells to empty
        for (int r = 0; r < size; r++)
        {
            for (int c = 0; c < size; c++)
            {
                grid[r][c].symbol = ' ';
                grid[r][c].value = 0;
                grid[r][c].visited = false;
            }
        }
    }

    // Set symbol at position (1-indexed)
    void setSymbol(int row, int col, char sym)
    {
        // Convert to 0-indexed
        row--;
        col--;

        // Check bounds
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            grid[row][col].symbol = sym;
            symbolPositions[sym].push_back({row, col});
        }
    }

    // Print the current grid state
    void printGrid()
    {
        // Print title
        cout << "\n╔═══════════════════════════╗" << endl;
        cout << "║     NUMBERLINK PUZZLE     ║" << endl;
        cout << "╚═══════════════════════════╝" << endl
             << endl;

        // Top border (removed column numbers)
        cout << "   ┌";
        for (int c = 0; c < cols; c++)
        {
            cout << "───";
            cout << (c < cols - 1 ? "┬" : "┐");
        }
        cout << "\n";

        for (int r = 0; r < rows; r++)
        {
            // Removed row numbers, just show border
            cout << "   │";

            for (int c = 0; c < cols; c++)
            {
                if (grid[r][c].symbol != ' ')
                {
                    // Check if part of COLOGNE diagonal
                    bool isCologneWord =
                        (r == 3 && c == 3 && grid[r][c].symbol == 'C') ||
                        (r == 4 && c == 4 && grid[r][c].symbol == 'O') ||
                        (r == 5 && c == 5 && grid[r][c].symbol == 'L') ||
                        (r == 6 && c == 6 && grid[r][c].symbol == 'O') ||
                        (r == 7 && c == 7 && grid[r][c].symbol == 'G') ||
                        (r == 8 && c == 8 && grid[r][c].symbol == 'N') ||
                        (r == 9 && c == 9 && grid[r][c].symbol == 'E');

                    if (isCologneWord)
                    {
                        // Bold and highlight COLOGNE letters
                        cout << " \033[1;33m" << grid[r][c].symbol << "\033[0m ";
                    }
                    else
                    {
                        cout << " \033[1m" << grid[r][c].symbol << "\033[0m ";
                    }
                }
                else if (grid[r][c].value > 0)
                {
                    cout << " · ";
                }
                else
                {
                    cout << "   ";
                }
                cout << "│";
            }
            cout << "\n";

            // Row separator
            if (r < rows - 1)
            {
                cout << "   ├";
                for (int c = 0; c < cols; c++)
                {
                    cout << "───";
                    cout << (c < cols - 1 ? "┼" : "┤");
                }
                cout << "\n";
            }
        }

        // Bottom border
        cout << "   └";
        for (int c = 0; c < cols; c++)
        {
            cout << "───";
            cout << (c < cols - 1 ? "┴" : "┘");
        }
        cout << "\n\n";

        // Add instructions
        cout << "Goal: Connect matching letters with non-intersecting paths" << endl;
        cout << "The word \"COLOGNE\" is highlighted on the diagonal" << endl
             << endl;
    }

    // Solve the puzzle
    void solve()
    {
        // Assign values to symbols
        assignValues();

        // For each symbol pair
        for (const auto &pair : symbolPositions)
        {
            char symbol = pair.first;
            const auto &positions = pair.second;

            if (positions.size() != 2)
            {
                cout << "Warning: Symbol " << symbol << " has " << positions.size() << " endpoints (should be 2)" << endl;
                continue;
            }
            // Find path for this symbol
            findPath(positions[0], positions[1], symbolValues[symbol]);
        }

        // The cell checking code has been removed
    }

    // Draw the solution with line characters
    void drawSolution()
    {
        // Use ANSI color codes for different paths
        vector<string> colors = {
            "\033[38;5;196m", // Red
            "\033[38;5;46m",  // Green
            "\033[38;5;21m",  // Blue
            "\033[38;5;208m", // Orange
            "\033[38;5;129m", // Purple
            "\033[38;5;214m", // Yellow
            "\033[38;5;51m",  // Cyan
            "\033[38;5;201m", // Magenta
            "\033[38;5;226m", // Bright Yellow
            "\033[38;5;82m",  // Bright Green
            "\033[38;5;197m", // Pink
            "\033[38;5;33m",  // Light Blue
            "\033[38;5;202m"  // Deep Orange
        };
        string resetColor = "\033[0m";

        // Print title
        cout << "\n╔════════════════════════════╗" << endl;
        cout << "║     NUMBERLINK SOLUTION    ║" << endl;
        cout << "╚════════════════════════════╝" << endl
             << endl;

        // Top border (removed column numbers)
        cout << "   ┌";
        for (int c = 0; c < cols; c++)
        {
            cout << "───";
            cout << (c < cols - 1 ? "┬" : "┐");
        }
        cout << "\n";

        // Grid cells
        for (int r = 0; r < rows; r++)
        {
            // Removed row number, just show border
            cout << "   │";

            for (int c = 0; c < cols; c++)
            {
                // Get color for this cell's value
                string cellColor = "";
                if (grid[r][c].value > 0)
                {
                    int colorIdx = (grid[r][c].value - 1) % colors.size();
                    cellColor = colors[colorIdx];
                }

                // Cell content
                if (grid[r][c].symbol != ' ')
                {
                    // For symbol cells, check if it's part of the COLOGNE word
                    bool isCologneWord =
                        (r == 3 && c == 3 && grid[r][c].symbol == 'C') ||
                        (r == 4 && c == 4 && grid[r][c].symbol == 'O') ||
                        (r == 5 && c == 5 && grid[r][c].symbol == 'L') ||
                        (r == 6 && c == 6 && grid[r][c].symbol == 'O') ||
                        (r == 7 && c == 7 && grid[r][c].symbol == 'G') ||
                        (r == 8 && c == 8 && grid[r][c].symbol == 'N') ||
                        (r == 9 && c == 9 && grid[r][c].symbol == 'E');

                    // Print symbol with color and bold if needed
                    cout << cellColor << " ";
                    if (isCologneWord)
                    {
                        cout << "\033[1m" << grid[r][c].symbol << "\033[0m";
                    }
                    else
                    {
                        cout << grid[r][c].symbol;
                    }
                    cout << " " << resetColor;
                }
                else
                {
                    // Show path characters based on connections with color
                    cout << cellColor;
                    drawEnhancedPathChar(r, c);
                    cout << resetColor;
                }
                cout << "│";
            }
            cout << "\n";

            // Row separator (if not the last row)
            if (r < rows - 1)
            {
                cout << "   ├";
                for (int c = 0; c < cols; c++)
                {
                    // Colorize vertical connections
                    if (isConnected(r, c, r + 1, c))
                    {
                        int colorIdx = (grid[r][c].value - 1) % colors.size();
                        string cellColor = colors[colorIdx];
                        cout << cellColor << "─║─" << resetColor;
                    }
                    else
                    {
                        cout << "───";
                    }
                    cout << (c < cols - 1 ? "┼" : "┤");
                }
                cout << "\n";
            }
        }

        // Bottom border
        cout << "   └";
        for (int c = 0; c < cols; c++)
        {
            cout << "───";
            cout << (c < cols - 1 ? "┴" : "┘");
        }
        cout << "\n\n";

        // Add a legend for the symbols used
        cout << "LEGEND:" << endl;
        for (const auto &pair : symbolValues)
        {
            int colorIdx = (pair.second - 1) % colors.size();
            cout << colors[colorIdx] << " " << pair.first << " " << resetColor << "- Path " << pair.second << endl;
        }
        cout << endl;
    }

private:
    int rows, cols;
    vector<vector<Cell>> grid;
    map<char, vector<pair<int, int>>> symbolPositions;
    map<char, int> symbolValues;

    // Direction vectors
    const int dr[4] = {-1, 0, 1, 0}; // up, right, down, left
    const int dc[4] = {0, 1, 0, -1};

    bool isValid(int r, int c)
    {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }

    bool isConnected(int r1, int c1, int r2, int c2)
    {
        return isValid(r1, c1) && isValid(r2, c2) &&
               grid[r1][c1].value > 0 &&
               grid[r1][c1].value == grid[r2][c2].value;
    }

    void assignValues()
    {
        int nextValue = 1;
        for (const auto &pair : symbolPositions)
        {
            char symbol = pair.first;
            symbolValues[symbol] = nextValue++;

            // Assign values to cells with this symbol
            for (const auto &pos : pair.second)
            {
                grid[pos.first][pos.second].value = symbolValues[symbol];
            }
        }
    }

    void findPath(pair<int, int> start, pair<int, int> end, int value)
    {
        // Simple BFS path finding that avoids 2x2 squares
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
        queue<pair<int, int>> q;

        // Start BFS
        visited[start.first][start.second] = true;
        q.push(start);

        bool foundPath = false;
        while (!q.empty() && !foundPath)
        {
            pair<int, int> curr = q.front();
            q.pop();

            int r = curr.first;
            int c = curr.second;

            // Check if reached the end
            if (r == end.first && c == end.second)
            {
                foundPath = true;
                break;
            }

            // Try all four directions
            for (int d = 0; d < 4; d++)
            {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (isValid(nr, nc) && !visited[nr][nc] &&
                    (grid[nr][nc].value == 0 || (nr == end.first && nc == end.second)))
                {

                    // Check if adding this cell would create a 2x2 block
                    if (!wouldCreate2x2(r, c, nr, nc, value))
                    {
                        visited[nr][nc] = true;
                        parent[nr][nc] = {r, c};
                        q.push({nr, nc});
                    }
                }
            }
        }

        // Reconstruct path if found
        if (foundPath)
        {
            pair<int, int> curr = end;
            while (!(curr.first == start.first && curr.second == start.second))
            {
                grid[curr.first][curr.second].value = value;
                curr = parent[curr.first][curr.second];
            }
        }
    }

    bool wouldCreate2x2(int r1, int c1, int r2, int c2, int value)
    {
        // Check if adding a path segment would create a 2x2 block
        // We need to check all possible 2x2 blocks that could include both cells

        // Temporary mark both cells with the value
        int origValue1 = grid[r1][c1].value;
        int origValue2 = grid[r2][c2].value;
        grid[r1][c1].value = value;
        grid[r2][c2].value = value;

        bool creates2x2 = false;

        // Check different possible 2x2 blocks
        for (int dr = -1; dr <= 0 && !creates2x2; dr++)
        {
            for (int dc = -1; dc <= 0 && !creates2x2; dc++)
            {
                int count = 0;
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        int r = r1 + dr + i;
                        int c = c1 + dc + j;
                        if (isValid(r, c) && grid[r][c].value == value)
                        {
                            count++;
                        }
                    }
                }
                if (count == 4)
                {
                    creates2x2 = true;
                }
            }
        }

        // Restore original values
        grid[r1][c1].value = origValue1;
        grid[r2][c2].value = origValue2;

        return creates2x2;
    }

    void drawPathChar(int r, int c)
    {
        // Skip if not part of a path
        if (grid[r][c].value == 0)
        {
            cout << "   ";
            return;
        }

        // Check which directions are connected
        bool conn[4] = {false, false, false, false}; // up, right, down, left
        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            conn[d] = isConnected(r, c, nr, nc);
        }

        // Count connections
        int connCount = 0;
        for (int d = 0; d < 4; d++)
        {
            if (conn[d])
                connCount++;
        }

        // Draw appropriate character
        if (connCount == 2)
        {
            if (conn[0] && conn[2])
            {
                cout << " ║ "; // Vertical line (changed from │)
            }
            else if (conn[1] && conn[3])
            {
                cout << "═══"; // Horizontal line (changed from ───)
            }
            else if ((conn[0] && conn[1]))
            {
                cout << " ╚ "; // Bottom-right corner (changed from └)
            }
            else if ((conn[0] && conn[3]))
            {
                cout << " ╝ "; // Bottom-left corner (changed from ┘)
            }
            else if ((conn[2] && conn[1]))
            {
                cout << " ╔ "; // Top-right corner (changed from ┌)
            }
            else if ((conn[2] && conn[3]))
            {
                cout << " ╗ "; // Top-left corner (changed from ┐)
            }
        }
        else
        {
            // For other cases, use a different character
            cout << " ● "; // Changed from · to ●
        }
    }

    // Add this new helper method for enhanced path visualization
    void drawEnhancedPathChar(int r, int c)
    {
        // Skip if not part of a path
        if (grid[r][c].value == 0)
        {
            cout << "   ";
            return;
        }

        // Check which directions are connected
        bool conn[4] = {false, false, false, false}; // up, right, down, left
        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            conn[d] = isConnected(r, c, nr, nc);
        }

        // Draw appropriate character based on connections
        if (conn[0] && conn[2] && !conn[1] && !conn[3])
        {
            cout << " ║ "; // Vertical line
        }
        else if (!conn[0] && !conn[2] && conn[1] && conn[3])
        {
            cout << "═══"; // Horizontal line
        }
        else if (conn[0] && !conn[2] && conn[1] && !conn[3])
        {
            cout << " ╚═"; // Bottom-right corner
        }
        else if (conn[0] && !conn[2] && !conn[1] && conn[3])
        {
            cout << "═╝ "; // Bottom-left corner
        }
        else if (!conn[0] && conn[2] && conn[1] && !conn[3])
        {
            cout << " ╔═"; // Top-right corner
        }
        else if (!conn[0] && conn[2] && !conn[1] && conn[3])
        {
            cout << "═╗ "; // Top-left corner
        }
        // Handle crossings and T-junctions
        else if (conn[0] && conn[1] && conn[2] && conn[3])
        {
            cout << "═╬═"; // 4-way crossing
        }
        else if (!conn[0] && conn[1] && conn[2] && conn[3])
        {
            cout << "═╦═"; // T-junction (missing up)
        }
        else if (conn[0] && !conn[1] && conn[2] && conn[3])
        {
            cout << "═╣ "; // T-junction (missing right)
        }
        else if (conn[0] && conn[1] && !conn[2] && conn[3])
        {
            cout << "═╩═"; // T-junction (missing down)
        }
        else if (conn[0] && conn[1] && conn[2] && !conn[3])
        {
            cout << " ╠═"; // T-junction (missing left)
        }
        else
        {
            // For other cases or endpoints
            cout << " ● ";
        }
    }
};

int main()
{
    try
    {
        cout << "Initializing 13x13 Numberlink puzzle..." << endl;

        // Create a 13x13 grid
        NumberlinkSolver solver(13);

        cout << "Setting up symbols..." << endl;

        // Set up the symbols as specified
        solver.setSymbol(1, 12, 'S');
        solver.setSymbol(2, 9, 'S');
        solver.setSymbol(3, 12, 'R');
        solver.setSymbol(4, 4, 'C');
        solver.setSymbol(4, 10, 'L');
        solver.setSymbol(5, 5, 'O');
        solver.setSymbol(5, 13, 'N');
        solver.setSymbol(6, 6, 'L');
        solver.setSymbol(6, 11, 'C');
        solver.setSymbol(7, 2, 'G');
        solver.setSymbol(7, 7, 'O');
        solver.setSymbol(8, 8, 'G');
        solver.setSymbol(9, 1, 'Z');
        solver.setSymbol(9, 4, 'E');
        solver.setSymbol(9, 9, 'N');
        solver.setSymbol(10, 10, 'E');
        solver.setSymbol(10, 12, 'T');
        solver.setSymbol(11, 4, 'T');
        solver.setSymbol(11, 6, 'R');
        solver.setSymbol(12, 7, 'Z');
        solver.setSymbol(12, 13, 'M');
        solver.setSymbol(13, 7, 'M');

        cout << "Initial grid:" << endl;
        solver.printGrid();

        cout << "Solving puzzle..." << endl;
        solver.solve();

        cout << "Solution:" << endl;
        solver.drawSolution();

        return 0;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cout << "Unknown error occurred" << endl;
        return 1;
    }
}