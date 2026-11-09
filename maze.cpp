#include <iostream>
#include <random>
#include <ctime>
#include <vector>
using namespace std;

void drawMaze(vector<vector<int>> grid) {
    int lengthWidth = grid[0].size();
    for(int i = 0; i<lengthWidth; i++) {
        for(int j = 0; j<lengthWidth; j++) {
            int currentField = grid[i][j];
            if(currentField == 0) {
                cout << "\033[37m";
            }
            else if(currentField == 1) {
                cout << "\033[34m";
            }
            cout << "██";
        }
        cout << endl;
    }
    cout << "\033[40m";
}

vector<vector<int>> generateMaze() {
    srand(time(0));
    vector<vector<int>> grid;
    for(int i = 0; i<20; i++) {
        grid.push_back(vector<int>()); // () creates a new empty vector object
        for(int j = 0; j<20; j++) {
            grid[i].push_back(rand() % 2);
        }
    }
    return grid;
}

int main() {
    drawMaze(generateMaze());
}