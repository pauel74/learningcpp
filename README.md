# learningcpp
testing things out with c++
## Maze
### Generation
In the following experiment, I wanted to generate a random maze that the computer would navigate using the _A* search algorithm_.

To do this, however, I first had to write a function that visualizes the maze.

This program iterates through the attached two-dimensional vector and writes a blue ASCII square for each “1” and a white ASCII square for each “0.” When the current row of the vector is complete, a new line is started.
```cpp
// simplified code
    for(int i = 0; i<grid.size(); i++) {
        for(int j = 0; j<grid[0].size(); j++) {
            int currentField = grid[i][j];
            if(currentField == 0) {cout << "\033[37m";}
            else if(currentField == 1) {cout << "\033[34m";}
            cout << "██";
        }
        cout << endl;
    }
```
Then I had to generate the maze, which turned out to be more difficult than I initially thought.

<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/56a3f4c3-2145-40d1-a397-a58945819e3f" />
<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/b41024a3-c37c-4583-8bed-b73a23873e1d" />
<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/79ac4782-1c11-487c-9d72-151d78643b12" />
<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/c1a34602-190a-4ac3-af33-e1ed5d402ca3" />

1. To test the `drawMaze()` function, I temporarily used a random number between 0 and 1 for each individual cell, however this usually makes the maze impossible to solve and would be dependent on chance.
2. So I generated a random path that always contains empty cells and goes from the top left to the bottom right, but it usually takes too long and sometimes leaves not a single cell behind before it reaches its destination.
3. To limit the movement distance of the paths, I therefore used a while loop that generates random paths until they no longer exceed a certain length.
4. After that, I used a random number between 0 and 1 again for the empty cells to obscure the result.

This can be used as a template, but many of these paths are inaccessible and consist only of isolated cells, so I need to find a way to connect multiple paths together.

<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/fda49d77-d82b-400b-a93e-a979b2639109" />
<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/8c391f16-baf6-48b6-b012-070a08d1e764" />
