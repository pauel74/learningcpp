#include <iostream>
#include <random>
#include <ctime>
#include <vector>
using namespace std;

void drawMaze(vector<vector<int>> grid) {
    cout << "width: "<< grid[0].size() << "\nheight: " << grid.size() << endl;
    for(int i = 0; i<grid.size(); i++) {
        for(int j = 0; j<grid[0].size(); j++) {
            int currentField = grid[i][j];
            if(i == 0 && j == 0) {
                cout << "\033[31m";
            }
            else if(i == grid.size()-1 && j == grid[0].size()-1) {
                cout << "\033[32m";
            }
            else if(currentField == 0) {
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

vector<vector<int>> generateMaze(int width, int height) {

    srand(time(0));
    vector<vector<int>> grid;

    int x = 0;
    int y = 0;
    int step = 1001;
    int generated = 0;

    while(step > (width+height)*5) {

        grid.clear();

        x = 0;
        y = 0;
        step = 0;

        for(int i = 0; i<height; i++) {
            grid.push_back(vector<int>()); // () creates a new empty vector object
            for(int j = 0; j<width; j++) {
                grid[i].push_back(rand() % 2);
            }
        }

        while(x != width-1 || y != height-1) {
            int move = rand() % 4;
            
            if(move == 0) { // up
                if(y != 0) {y--;}
            }
            if(move == 1) { // down
                if(y != height-1) {y++;}
            }
            if(move == 2) { // left
                if(x != 0) {x--;}
            }
            if(move == 3) { // right
                if(x != width-1) {x++;}
            }
            grid[y][x] = 0;

            step++;
        }
        generated++;
    }
    cout << "generated " << generated << " mazes" << endl;
    return grid;
}

int main() {
    drawMaze(generateMaze(25,20));
}