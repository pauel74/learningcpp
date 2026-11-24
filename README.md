# learningcpp
testing things out with c++
## Maze
### Generation
I wanted to generate a random maze that the computer would solve using the _A* search algorithm_.

First, I wrote a function that draws the maze. It goes through a two-dimensional vector and writes a blue square for each “1” and a white square for each “0.”
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
Then I had to generate the maze, which was harder than I thought.

<img width="200" height="220" alt="image" src="https://github.com/user-attachments/assets/56a3f4c3-2145-40d1-a397-a58945819e3f" />
<img width="200" height="220" alt="image" src="https://github.com/user-attachments/assets/b41024a3-c37c-4583-8bed-b73a23873e1d" />
<img width="200" height="220" alt="image" src="https://github.com/user-attachments/assets/79ac4782-1c11-487c-9d72-151d78643b12" />
<img width="200" height="220" alt="image" src="https://github.com/user-attachments/assets/c1a34602-190a-4ac3-af33-e1ed5d402ca3" />

First I used random 0s and 1s, but this is usually impossible to solve. So I made a random path from the top left to the bottom right and filled the rest randomly. The paths worked, but many areas were isolated, so I had to find a way to connect them.

<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/fda49d77-d82b-400b-a93e-a979b2639109" />
<img width="245" height="270" alt="image" src="https://github.com/user-attachments/assets/8c391f16-baf6-48b6-b012-070a08d1e764" />

To make the paths clearer, I added invisible cells at regular intervals, and the path can't go to visited cells or to those. When it got stuck, I started a new path. But with big fields it took tens of thousands of attempts, so I **rewrote the maze generation**.

<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/bb82e0e4-84c5-4788-a909-78d6d56e8b7c" />
<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/55a014aa-8da3-4bce-8d7c-45b6e7422452" />
<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/9f6a5fa9-27f0-4f7a-8554-7c88de2ac930" />

#### How the new algorithm works

The path moves randomly and stores every step in an array. When it gets stuck, it turns the dead end into a wall and walks back along its steps until it finds a free cell. This repeats until it reaches the bottom right.
| | Old | New |
|---|---|---|
| When stuck | Restart with a new grid | Walk back along the steps |
| Dead ends | Stay as path | Become walls |
| Attempts | Tens of thousands | One run |

#### Filling the empty areas

The path works now, but it leaves big empty areas next to it. To fill them, I open the walls between the rooms, but only if one room is already a path and the other one has not been visited yet. The wall and the new room are opened together.
```cpp
// simplified code

// wall with a room on the left and on the right
if((left == 0 && right == 1) || (left == 1 && right == 0)) {
    grid[i][j-1] = 0;
    grid[i][j] = 0;
    grid[i][j+1] = 0;
}

// wall with a room above and below
if((up == 0 && down == 1) || (up == 1 && down == 0)) {
    grid[i-1][j] = 0;
    grid[i][j] = 0;
    grid[i+1][j] = 0;
}
```
This repeats in a while loop until no wall can be opened anymore. Every new room is connected exactly once, so there are **no loops and no single open cells**.

<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/1e37fe0f-42fb-41da-a094-823482cbe228" />
<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/cb3b3499-7a8f-4437-9ab5-70eed8a99599" />
<img width="260" height="277" alt="image" src="https://github.com/user-attachments/assets/96757a42-ca67-49c7-90c7-17943c706b00" />
