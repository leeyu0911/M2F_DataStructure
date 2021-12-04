//
// Created by leeyu on 2021/12/4.
//
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *link;
    void set(int num) {
        data = num;
    }

    Node(int num):
    data(num), link(NULL) {}
};

class Tree_Node {
public:
    Node *root;
    void test_address(Node *&node) {
        if (node->link) {
            cout << node->data << endl;
            test_address(node->link);
        }
    }
    void test_address2(Node *node) {
        if (node->link) {
            cout << node->data << endl;
            test_address2(node->link);
        }
    }
};

void call_by_value(Node node) {  // call by value
    node.data = 777;
    cout << node.data << endl;
}
void call_by_pointer(Node *node) {
    node->data = 888;
    cout << node->data << endl;
}
void call_by_address(Node &node) {
    node.data = 999;
    cout << node.data << endl;
}
void call_by_pointer_address(Node *&node) {
    node->data = 1000;
    cout << node->data << endl;
}

void test_class_link(Node *node) {
    if (node->link) {
        cout << node->data << endl;
        test_class_link(node->link);
    }
}
void test_class_link2(Node &node) {
    if (node.link) {
        cout << node.data << endl;
        test_class_link(node.link);
    }
}
void test_class_link3(Node node) {
    if (node.link) {
        cout << node.data << endl;
        test_class_link(node.link);
    }
}



int main() {

    Node node1(11);
    Node node2(22);
    Node node3(33);
    Node node4(44);
    node1.link = &node2;
    node2.link = &node3;
    node3.link = &node4;

    Tree_Node tree;
    tree.root = &node1;
    cout << "Test Tree *&\n";
    tree.test_address(tree.root);  //因為class兩層？
    cout << "Test Tree *\n";
    tree.test_address2(tree.root);

    cout << "Call by pointer\n";
    test_class_link(&node1);
    cout << "Call by address\n";
    test_class_link2(node1);
    cout << "Call by value\n";
    test_class_link3(node1);

    cout << node4.link << endl;

    cout << "Test modify\n";
    Node node0(0);
    call_by_value(node0);
    cout << node0.data << endl;
    call_by_pointer(&node0);
    cout << node0.data << endl;
    call_by_address(node0);
    cout << node0.data << endl;

    Node *nodee = &node0;
    cout << nodee->data << endl;
    call_by_pointer(nodee);
    call_by_pointer_address(nodee);
    cout << node0.data << endl;


}
