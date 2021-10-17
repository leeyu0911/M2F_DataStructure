#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int mazeWidth = 17;
const int maxSize = mazeWidth * mazeWidth;  //max size if stack



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
        cout << "Stack is empty!" << endl;
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



void pushStack(int position, int x, int y) {
    positionStack.push(position);
    xStack.push(x);
    yStack.push(y);
}

void popStack(int *result) {
    int p = positionStack.pop();
    int x = xStack.pop();
    int y = yStack.pop();
    result[0] = p;
    result[1] = x;
    result[2] = y;
}

int *popStack_pointer() {
    int p = positionStack.pop();
    int x = xStack.pop();
    int y = yStack.pop();
    static int result[3];
    result[0] = p;
    result[1] = x;
    result[2] = y;
    return result;
}

int main() {

    pushStack(1,2,3);

    int *a = popStack_pointer();
    for (int i = 0; i < 3; ++i) {
        cout << a[i] << endl;
    }

//    pushStack(1,2,3);
//    int p = positionStack.pop();
//    int x = xStack.pop();
//    int y = yStack.pop();
//    int temp[] = {p, x , y};
//
//    for (int i = 0; i < 3; ++i) {
//        cout << temp[i] << endl;
//    }

//    int a[3];
//    popStack(a);
////    int a1 = a[0];
////    int a2 = a[1];
////    int a3 = a[2];
////    cout<<a<<endl;
////    cout<<a1<<endl;
////    cout<<a2<<endl;
////    cout<<a3<<endl;
//
//    printf("%d\n", a[0]);
//    printf("%d\n", a[1]);
//    printf("%d\n", a[2]);
//    cout<<a[1]<< endl;
//    cout<<a[1]<< endl;
//    cout<<a[1]<< endl;

//    for (int i = 0; i < 3; ++i) {
//        cout << a[i] << endl;
//    }




}


