#include <random>
#include <vector>
#include <stack>

#include "sand_solver.hpp"

int randomDirection() 
{
    // Create a random number generator
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister 19937 generator
    std::uniform_int_distribution<> dis(0, 1); // Distribution that generates integers 0 or 1

    // Generate a random number and map it to -1 or 1
    return dis(gen) == 0 ? -1 : 1;
}

SandBox::SandBox(int width, int height) 
{
    box.resize(height, std::vector<char>(width, ' '));
}

void SandBox::PlaceSand(int x, int y) 
{
    if (y >= 0 && y < box.size() && x >= 0 && x < box[0].size()) {
        box[y][x] = sand_char;
    }
}

void SandBox::UpdateSandBox()
{
    for (int i = box.size() - 1; i >= 0; --i) {
        for (int j = 0; j < box[0].size(); ++j) {
            if (box[i][j] == sand_char) {
                int rand_dir = randomDirection();
                if (i < box.size() - 1 && box[i + 1][j] == ' ') {
                    box[i + 1][j] = sand_char;
                    box[i][j] = ' ';
                } else if (i < box.size() - 1 && j > 0 && box[i + 1][j - rand_dir] == ' ') {
                    box[i + 1][j - rand_dir] = sand_char;
                    box[i][j] = ' ';
                } else if (i < box.size() - 1 && j < box[0].size() - 1 && box[i + 1][j + rand_dir] == ' ') {
                    box[i + 1][j + rand_dir] = sand_char;
                    box[i][j] = ' ';
                }
            }
        }
    }
}


std::vector<std::pair<int, int>> dfs(const std::vector<std::vector<int>>& grid, int startX, int startY) {
    using namespace std;
    vector<pair<int, int>> blob; // To store the coordinates of the blob elements
    vector<vector<int>> gridCopy = grid; // Create a copy of the grid

    // Define the possible movements (right, down, left, up)
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Create a stack for DFS
    stack<pair<int, int>> s;

    // Push the starting position onto the stack
    s.push({startX, startY});

    // Perform DFS
    while (!s.empty()) {
        // Get the current position
        pair<int, int> current = s.top();
        s.pop();

        int x = current.first;
        int y = current.second;

        // Add the current cell to the blob
        blob.push_back({x, y});

        // Mark the current cell as visited by setting it to 0 (or any other non-1 value)
        gridCopy[y][x] = 0;

        // Explore all possible directions
        for (auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Check if the new position is within bounds and is part of the blob (value is 1)
            if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size() && gridCopy[newY][newX] == 1) {
                // Push the new position onto the stack
                s.push({newX, newY});
            }
        }
    }

    return blob;
}




void SandBox::DFSCheck()
{   

    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::vector<std::vector<char>> box_copy = GetBox();
    std::stack<std::pair<int, int>> s;

    for (int i = 0; i < box.size(); i++)
    {
        bool spanned = false;
        std::vector<std::pair<int, int>> blob;
        std::vector<std::array<int,2>> cells;
        
        //dfs
        if (box[i][0] != ' ' && box_copy[i][0] != 'X')
        {
            // DFS
            char target_char = box[i][0];
            s.push({0, i});
            while (!s.empty()) 
            {
                std::pair<int, int> current = s.top();
                s.pop();    
                int x = current.first;
                int y = current.second;

                blob.push_back({x, y});
                box_copy[y][x] = 'X';

                if (x == box[0].size() - 1)
                {
                    spanned = true;
                }

                for (auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;

                    // Check if the new position is within bounds and is part of the blob (value is 1)
                    if (newX >= 0 && newX < box[0].size() && newY >= 0 && newY < box.size() && box_copy[newY][newX] == target_char) {
                        // Push the new position onto the stack
                        s.push({newX, newY});
                    }
                }
            }
            if (spanned)
            {
                for (auto& coord : blob)
                {
                    box[coord.second][coord.first] = ' ';
                }
            }
        }
    }
}

const std::vector<std::vector<char>>& SandBox::GetBox() const {
    return box;
}
