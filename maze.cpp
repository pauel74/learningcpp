#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

struct Pos {
    int x = 0, y = 0;
};

void drawMaze(vector<vector<int>> grid) {
    cout << "\033[H"; // only moves the cursor back to the top-left corner
    // cout << "width: "<< grid[0].size() << "\nheight: " << grid.size() << endl;
    for(int i = 0; i<grid.size(); i++) {
        for(int j = 0; j<grid[0].size(); j++) {
            int currentField = grid[i][j];
            if(i == 0 && j == 0) {
                cout << "\033[31m";
            }
            else if(i == grid.size()-1 && j == grid[0].size()-1) {
                cout << "\033[32m";
            }
            else if(currentField == 0) { // already stepped on cells
                cout << "\033[37m";
            }
            else if(currentField == 1) { // empty cells
                cout << "\033[34m";
            }
            else if(currentField == 2) { // blocking cells
                cout << "\033[36m";
            }
            cout << "██";
        }
        cout << "\n"; // endl also forces the text to be sent right to the terminal
    }
    cout << "\033[37m";
}

bool isStuck(vector<vector<int>> grid, int x, int y) {
    if(y > 0 &&grid[y-1][x] == 1) return false;                      // up
    if(x < int(grid[0].size())-1 && grid[y][x+1] == 1) return false; // right
    if(y < int(grid.size())-1 && grid[y+1][x] == 1) return false;    // down
    if(x > 0 && grid[y][x-1] == 1) return false;                     // left
    return true;
}

vector<vector<int>> generateMaze(int width, int height) {

    srand(time(0));
    vector<vector<int>> grid;
    
    // if width or heigth is even add 1 to make it uneven
    // otherwise the type 2 cells would block the start or finish
    cout << "\033[31m";
    if(width % 2 == 0) {
        width++;
        cout << "changed width to " << width << endl;
    }
    if(height % 2 == 0) {
        height++;
        cout << "changed height to " << height << endl;
    }
    cout << "\033[37m";

    // fill with type 1 and 2 cells
    for(int i = 0; i<height; i++) {
        grid.push_back(vector<int>()); // () creates a new empty vector object
        for(int j = 0; j<width; j++) {
            grid[i].push_back(1);
            if(i % 2 != 0 && j % 2 != 0) {
                grid[i][j] = 2;
            }
        }
        grid[0][0] = 0;
    }

    // actual maze gen

    int x = 0, y = 0;
    Pos pos;
    vector<Pos> steps;
    steps.push_back(pos);

    while(true) {

        int dir = rand() % 4;
        
        switch(dir) {
            case 0: y--; break; // up
            case 1: x++; break; // right
            case 2: y++; break; // down
            case 3: x--; break; // left
        }

        pos.x = x; pos.y = y;
        steps.push_back(pos);

        // check for invalid inputs
        if( x < 0 ||
            y < 0 ||
            x >= int(grid[0].size()) ||
            y >= int(grid.size()) ||
            grid[y][x] != 1
        ) {
            steps.pop_back();
        }
        
        y = steps[steps.size()-1].y;
        x = steps[steps.size()-1].x;
        
        while(isStuck(grid, x, y) == true) {
            steps.pop_back();
            grid[y][x] = 2;
            y = steps[steps.size()-1].y;
            x = steps[steps.size()-1].x;
        }

        grid[y][x] = 0; // sets type 0 on grid
        
        if(x == grid[0].size()-1 && y == grid.size()-1) {
            break;
        }
        
        this_thread::sleep_for(chrono::milliseconds(4));
        drawMaze(grid);
    }
    return grid;
}

int main() {
    cout << "generating..." << endl;
    drawMaze(generateMaze(40,40));
}