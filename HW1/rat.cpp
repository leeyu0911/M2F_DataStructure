#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* maze config */
const int mazeWidth = 17;  //maze: 17 x 17
const int maxSize = mazeWidth * mazeWidth;  //max size of stack

/* stack class */
class Stack {
    int top = -1;

public:
    int array[maxSize];
    bool push(int data);
    int pop();
    bool isEmpty();
};

bool Stack::push(int data) {
    if (top == maxSize) {  //can not push to stack
        cout << "Stack Overflow!" << endl;
        return false;
    } else {
        array[++top] = data;
        return true;
    }
}

int Stack::pop() {
    if (top < 0) {  //if stack is empty
//        cout << "Stack is empty!" << endl;
        return -1;
    } else {
        return array[top--];
    }
}

bool Stack::isEmpty() {
    return top < 0;
}

/* Stack init */
Stack positionStack;  //store position
Stack xStack;         //store last x
Stack yStack;         //store last y


/* my func */
void pushStack(int position, int x, int y) {  //push data to 3 stack
    positionStack.push(position);
    xStack.push(x);
    yStack.push(y);
}

//int *popStack() {
//    int p = positionStack.pop();
//    int x = xStack.pop();
//    int y = yStack.pop();
//    static int temp[] = {p, x, y};
//    return temp;
//}
void popStack(int *temp) {  //pop data to 3 stack
    int p = positionStack.pop();
    int x = xStack.pop();
    int y = yStack.pop();
    temp[0] = p;
    temp[1] = x;
    temp[2] = y;
}


int main() {
    // get filename
    ifstream txtFile;
    string filename = "maze.txt";
    cout << "enter filename :";
    cin >> filename;  //commend for auto load maze.txt
    txtFile.open(filename);
    // if file not found, get filename again
    while (!txtFile) {
        cout << "file not found!" << endl;
        cout << "enter filename :";
        cin >> filename;  //commend for auto load maze.txt
        txtFile.open(filename);
    }

    // init maze matrix
    int maze[mazeWidth][mazeWidth];

    // open file
    string s;
    int i_getline = 0;
    while (getline(txtFile, s))
    {
        cout << s << endl;  //print maze
        for (int j = 0; j < mazeWidth; ++j) {  //build maze matrix
            if (s[j] == '1') maze[i_getline][j] = 1;
            else if (s[j] == '0') maze[i_getline][j] = 0;
        }
        ++i_getline;
    }
    txtFile.close();

    // copy maze for restart maze
    int maze_copy[mazeWidth][mazeWidth];
    for (int i = 0; i < mazeWidth; ++i) {
        for (int j = 0; j < mazeWidth; ++j) {
            maze_copy[i][j] = maze[i][j];
        }
    }

    //check maze
//    for (int i = 0; i < mazeWidth; ++i) {
//        for (int j = 0; j < mazeWidth; ++j) {
//            cout << maze[i][j] << ",";
//        }
//        cout << endl;
//    }


    //code loop
    while (true){
        // init maze for continuously enter a start and an exit position for a journey
        for (int i = 0; i < mazeWidth; ++i) {
            for (int j = 0; j < mazeWidth; ++j) {
                maze[i][j] = maze_copy[i][j];
            }
        }
        // input start and exit position
        int start[2];
        int exit[2];
        cout << "enter start position :";
        cin >> start[0] >> start[1];
        // input -1 -1 to end the code
        if (start[0] == -1 && start[1] == -1) {
            cout << "end the code.";
            return 0;
        }
        cout << "enter exit position :";
        cin >> exit[0] >> exit[1];

        // ctrl input and maze index gap
//        --start[0];
//        --start[1];
//        --exit[0];
//        --exit[1];
//        cout << start[0] << start[1] << exit[0] << exit[0] << endl;

        //right -> down -> up -> left
        int curX = start[1];  //x in homework is column
        int curY = start[0];  //y in homework is row

        maze[curY][curX] = 2;  //record path
        pushStack(0, curX, curY);
        int step = 1;
        while (true) {
//            cout << step << ":" << curX << "," << curY << endl;  //output journey
            if (maze[curY][curX+1] == 0) {  //right
                maze[curY][curX+1] = 2;  //if rat has visited
                pushStack(1, ++curX, curY);
                cout << step << ":" << curY << "," << curX << endl;
                ++step;  //count the step
            } else if (maze[curY+1][curX] == 0) {  //down
                maze[curY+1][curX] = 2;
                pushStack(2, curX, ++curY);
                cout << step << ":" << curY << "," << curX << endl;
                ++step;  //count the step
            } else if (maze[curY-1][curX] == 0) {  //up
                maze[curY-1][curX] = 2;
                pushStack(3, curX, --curY);
                cout << step << ":" << curY << "," << curX << endl;
                ++step;  //count the step
            } else if (maze[curY][curX-1] == 0) {  //left
                maze[curY][curX-1] = 2;
                pushStack(4, --curX, curY);
                cout << step << ":" << curY << "," << curX << endl;
                ++step;  //count the step
            } else {  //back
//                int *last = popStack();
                int last[3];
                popStack(last);  //get data from stack and store in "last"
                if (maze[curY][curX] != 1) {  //Do not count path is 1
                    cout << step << ":" << curY << "," << curX << endl;
                    ++step;  //count the step
                }
                if (last[0] == -1) {  //stack empty
                    cout << "Failed to escape." << endl;
                    break;
                } else {
                    curX = last[1];
                    curY = last[2];
                }
            }
            if (curX == exit[1] && curY == exit[0]) {  //success escaped (x, y same with start)
                cout << "successfully escaped!!" << endl;
                break;
            }

        }  //end maze loop

        //print visited maze, 2 means the path
//        cout << "Journey: (2 means path)" << endl;
//        for (int i = 0; i < mazeWidth; ++i) {
//            for (int j = 0; j < mazeWidth; ++j) {
//                cout << maze[i][j] << ",";
//            }
//            cout << endl;
//        }

        //check position
//        cout << maze[start[0]][start[1]] << endl;
//        cout << maze[exit[0]][exit[1]] << endl;

    }  //end code loop
    return 0;
}


