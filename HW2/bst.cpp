#include <iostream>
#include<queue>

using namespace std;

/* Data structure */
class BST_Node {
    friend class BST;
private:
    int data;
    BST_Node *left;
    BST_Node *right;
public:
    BST_Node(int x):  // init BST_Node
    data(x), left(NULL), right(NULL) {}
};

class BST {
private:
    BST_Node *root;
    void prefix(BST_Node *node) {
        cout << "The tree in prefix order : ";
        if (node) {
            cout << node->data << " ";
            prefix(node->left);
            prefix(node->right);
        }
    }
    void infix(BST_Node *node) {
        cout << "The tree in infix order : ";
        if (node) {
            infix(node->left);
            cout << node->data << " ";
            infix(node->right);
        }
    }
    void postfix(BST_Node *node) {
        cout << "The tree in postfix order : ";
        if (node) {
            postfix(node->left);
            postfix(node->right);
            cout << node->data << " ";
        }
    }
    void level_order(BST_Node *node) {
        queue<BST_Node*> q_node;
        if (node) {  // tree is not empty
            q_node.push(node);
            while (!q_node.empty()) {
                BST_Node *temp = q_node.front();  // get first node
                cout << temp->data << " ";
                q_node.pop();
                if (temp->left) q_node.push(temp->left);
                if (temp->right) q_node.push(temp->right);
            }
        }

    }
public:
    BST():  // init binary search tree
    root(NULL) {}

    void insert(int num) {
        if (search(num)) {  // num exists
            cout << "Error. Number " << num << " exists." << endl;
        } else {
            BST_Node *temp = root;
            if (temp == NULL) {  // empty tree
                root = new BST_Node(num);
            } else {  // none empty tree
                BST_Node *temp1;
                while (temp != NULL) {
                    temp1 = temp;
                    if (temp->data > num) temp = temp->left;
                    else temp = temp->right;
                }
                temp = temp1;
                if (temp->data > num) temp->left = new BST_Node(num);
                else temp->right = new BST_Node(num);
            }
            cout << "Number " << num << " is inserted." << endl;
        }
    }
    void delete_node(int num) {
        if (search(num)) {

        } else { // num not exist
            cout << "Number " << num << " is not exist." << endl;
        }
    }
    bool search(int num) {
        BST_Node *temp = root;
        while (temp != NULL && temp->data != num) {
            if (temp->data > num) temp = temp->left;
            else temp = temp->right;
        }
        if (temp == NULL) return false;
        else return true;
    }
    void print() {
        prefix(root);
        infix(root);
        postfix(root);
        level_order(root);
    }
};

/* Level function */
class Binary_searching_Tree {
private:

public:
    static void insert_number(BST tree) {
        /* Enter “i”, then enter a sequence of numbers and ended
           with “-1” to build a BST. Noticed that the number “-1” is
           not a node for insertion. */
    }
    static void delete_number(BST tree) {
        /* Enter “d”, then enter a sequence of numbers ended with “-1” to
           delete (the same as insert) as Fig. 4.
                (a) If the deleted node is a leaf, then delete directly.
                (b) If the deleted node has a child, then replace the deleted node with its child.
                (c) If the deleted node has left and right sub-tree, then replace
           the deleted node with the smallest node of the right sub-tree.
           Also consider the error deletion case that the deleted
           node(number) is not existed. */


    }
    static void search_number(BST tree) {
        /* Enter “s”, then enter a sequence ended with “-1” to search whether
           the numbers are in the BST.
           If the number is not in the BST then print the number is not found. */
    }
    static void print(BST tree) {
        /* Enter “p” to print prefix -> infix -> postfix and level order of
           the BST after the above executions.
           Enter “r” to return to the main menu.
           You must use queue skills in level order! */
    }

};


/* main function */
void binary_searching_tree() {
    while (true) {
        cout << "(I)nsert a number." << endl;
        cout << "(D)elete a number." << endl;
        cout << "(S)earch a number." << endl;
        cout << "(P)rint 4 kinds of orders." << endl;
        cout << "(R)eturn" << endl;

        char action_input;
        cin >> action_input;
        BST tree;
        switch (action_input) {
            case 'I':
            case 'i':
                Binary_searching_Tree::insert_number(tree);
                break;
            case 'D':
            case 'd':
                Binary_searching_Tree::delete_number(tree);
                break;
            case 'S':
            case 's':
                Binary_searching_Tree::search_number(tree);
                break;
            case 'P':
            case 'p':
                Binary_searching_Tree::print(tree);
                break;
            case 'R':
            case 'r':
                return;
            default:
                break;
        }
    }

}

void finding_meaty() {

}

void escape_and_face_to_music_next_year() {
    // not used
}


int main() {
    while (true) {
        cout << "(1)Binary searching Tree." << endl;
        cout << "(2)Finding Meaty." << endl;
        cout << "(0)Escape and face to music next year." << endl;


        char first_input;
        cin >> first_input;

        switch(first_input) {
            case '1':
                binary_searching_tree();
                break;
            case '2':
                finding_meaty();
                break;
            case '0':
                escape_and_face_to_music_next_year();
                break;
            default:
                cout << "0~2" << endl;
        }
    }
}
