#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* maze config */
const int mazeWidth = 17;
const int maxSize = mazeWidth * mazeWidth;  //max size if stack

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
    if (top == maxSize) {
        cout << "Stack Overflow!" << endl;
        return false;
    } else {
        array[++top] = data;
        return true;
    }
}

int Stack::pop() {
    if (top < 0) {
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
Stack positionStack;
Stack xStack;
Stack yStack;
int mazeSize = 17;


/* my func */
void pushStack(int position, int x, int y) {
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
void popStack(int *temp) {
    int p = positionStack.pop();
    int x = xStack.pop();
    int y = yStack.pop();
    temp[0] = p;
    temp[1] = x;
    temp[2] = y;
}


int main() {
    //get filename
    string filename = "maze.txt";
    cout << "enter filename :";
    cin >> filename;  //commend for auto load maze.txt

    //open file
    string s;
    ifstream txtFile;
    txtFile.open(filename);

    // init maze matrix
    int maze[mazeWidth][mazeWidth];

    // build maze matrix
    int i_getline = 0;
    while (getline(txtFile, s))
    {
        cout << s << endl;
        for (int j = 0; j < mazeWidth; ++j) {
            if (s[j] == '1') maze[i_getline][j] = 1;
            else if (s[j] == '0') maze[i_getline][j] = 0;
        }
        ++i_getline;
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
        // deal start and exit position
        int start[2];
        int exit[2];
        cout << "enter start position :";
        cin >> start[0] >> start[1];
        //end code
        if (start[0] == -1 && start[1] == -1) {
            cout << "end the code.";
            return 0;
        }
        cout << "enter exit position :";
        cin >> exit[0] >> exit[1];

        // input maze index start from 1
        --start[0];
        --start[1];
        --exit[0];
        --exit[1];
//        cout << start[0] << start[1] << exit[0] << exit[0] << endl;

        //right -> down -> up -> left
        int curX = start[0];
        int curY = start[1];
        maze[curY][curX] = 2;  //record path
        pushStack(0, curX, curY);
        int step = 1;
        while (true) {
            cout << step << ":" << curX+1 << "," << curY+1 << endl;  //maze output index from 1
            if (maze[curY][curX+1] == 0) {  //right
                maze[curY][curX+1] = 2;
                pushStack(0, ++curX, curY);
            } else if (maze[curY+1][curX] == 0) {  //down
                maze[curY+1][curX] = 2;
                pushStack(0, curX, ++curY);
            } else if (maze[curY-1][curX] == 0) {  //up
                maze[curY-1][curX] = 2;
                pushStack(0, curX, --curY);
            } else if (maze[curY][curX-1] == 0) {  //left
                maze[curY][curX-1] = 2;
                pushStack(0, --curX, curY);
            } else {
//                int *last = popStack();
                int last[3];
                popStack(last);
                if (last[0] == -1) {  //stack empty
                    cout << "Failed to escape." << endl;
                    break;
                } else {
                    curX = last[1];
                    curY = last[2];
                }
            }
            if (curX == exit[0] && curY == exit[1]) {  //success escaped
                cout << "successfully escaped!!" << endl;
                break;
            }
            ++step;
        }  //end maze loop

        //print maze
        for (int i = 0; i < mazeWidth; ++i) {
            for (int j = 0; j < mazeWidth; ++j) {
                cout << maze[i][j] << ",";
            }
            cout << endl;
        }

        //check position
//        cout << maze[start[0]][start[1]] << endl;
//        cout << maze[exit[0]][exit[1]] << endl;

    }  //end code loop
    return 0;
}


