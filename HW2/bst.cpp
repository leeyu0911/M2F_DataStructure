#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;
#define MAX_ARRAY_SIZE 1024

/* Data structure */
class BST_Node {
    friend class BST;
public:
    int data;
    BST_Node *left;
    BST_Node *right;

    BST_Node(int x):  // init BST_Node
    data(x), left(NULL), right(NULL) {}
};

class BST {

public:
    int minimum() {  //get minimum num
        BST_Node *temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp->data;
    }
    int maximum() {  //get maximum num
        BST_Node *temp = root;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        return temp->data;
    }
    BST_Node *_search(int num) {  // return the node pointer
        BST_Node *temp = root;
        while (temp != NULL && temp->data != num) {
            if (temp->data > num) temp = temp->left;
            else temp = temp->right;
        }
        return temp;
    }
    BST_Node *getParent(int num) {  // return parent pointer
        if (_search(num)) {
            BST_Node *temp = root;
            BST_Node *parent;
            while (temp->data != num) {
                parent = temp;
                if (temp->data > num) temp = temp->left;
                else temp = temp->right;
            }
            if (temp == root) return NULL;
            else return parent;
        } else {
            return NULL;
        }
    }
    BST_Node *predecessor(int num) {  // get pointer of predecessor
        BST_Node *the_node = _search(num);
        BST_Node *parent = getParent(num);
        if (!the_node || minimum() == num) return NULL;
        else {
            if (the_node->left != NULL) {  // left subtree
                BST_Node *temp = the_node->left;
                while (temp->right != NULL)
                    temp = temp->right;
                return temp;
            } else {  // no left subtree
                if (parent->right == the_node) return parent;
                else {
                    while (parent->data > num)
                        parent = getParent(parent->data);
                    return parent;
                }
            }
        }
    }
    BST_Node *successor(int num) {  // get pointer of successor
        BST_Node *the_node = _search(num);
        BST_Node *parent = getParent(num);
        if (!the_node || maximum() == num) {  // not found or self
            return NULL;
        } else {
            if (the_node->right != NULL) {  // right subtree
                BST_Node *temp = the_node->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                return temp;
            } else {  // no right subtree
                if (parent->left == the_node)
                    return parent;
                else {
                    while (parent->data < num)
                        parent = getParent(parent->data);
                    return parent;
                }
            }
        }
    }
//    BST_Node *getNode(int num) {  // get the node pointer
//        if (_search(num)) {
//            BST_Node *temp = root;
//            while (temp->data != num) {
//                if (temp->data > num) temp = temp->left;
//                else temp = temp->right;
//            }
//            return temp;
//        } else {
//            return NULL;
//        }
//    }
    void prefix(BST_Node *node) {
        if (node) {
            cout << node->data << " ";
            prefix(node->left);
            prefix(node->right);
        }
    }
    void infix(BST_Node *node) {
        if (node) {
            infix(node->left);
            cout << node->data << " ";
            infix(node->right);
        }
    }
    void postfix(BST_Node *node) {
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
    BST():  // init binary _search tree
    root(NULL) {}

    BST_Node *root;

    void insert(int num, bool isPrint) {
        if (_search(num)) {  // num exists
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
            if (isPrint)  // ctrl print
                cout << "Number " << num << " is inserted." << endl;
        }
    }
    void delete_node(int num) {
//        (a) If the deleted node is a leaf, then delete directly.
//        (b) If the deleted node has a child, then replace the deleted node with its child.
//        (c) If the deleted node has left and right sub-tree, then replace the deleted node with the smallest node of the right subtree.
        BST_Node *the_node = _search(num);
        BST_Node *parent = getParent(num);
        if (the_node) {  // the node is in the tree

            // case (a) node is a leaf
            if (the_node->left == NULL && the_node->right == NULL) {
                if (parent->data > the_node->data) {
                    parent->left = NULL;
//                    free(the_node);
                } else {
                    parent->right = NULL;
//                    free(the_node);
                }
            }

            // case (b) node has a child
            else if (the_node->left != NULL && the_node->right == NULL) {  // the node has left subtree
                if (parent->data > the_node->data) {
                    parent->left = the_node->left;
//                    free(the_node);
                } else {
                    parent->right = the_node->left;
//                    free(the_node);
                }
            }
            else if (the_node->left == NULL && the_node->right != NULL) {  // the node has right subtree
                if (parent->data > the_node->data) {
                    parent->left = the_node->right;
//                    free(the_node);
                } else {
                    parent->right = the_node->right;
//                    free(the_node);
                }
            }

            // case (c) node has left and right sub-tree
            else {
                BST_Node *suc = successor(num);
                BST_Node *suc_parent = getParent(suc->data);

                the_node->data = suc->data;

//                cout << "suc:" << suc->data << endl;
//                cout << "suc parent:" << suc_parent->data << endl;

                // case c(a) node is a leaf
                if (suc->left == NULL && suc->right == NULL) {
                    if (suc_parent->data > suc->data) {
                        suc_parent->left = NULL;
//                        free(suc);
                    } else {
                        suc_parent->right = NULL;
//                        free(suc);
                    }
                }

                // case c(b) node has a child
                else if (suc->left != NULL && suc->right == NULL) {  // the node has left subtree
                    if (suc_parent->data > suc->data) {
                        suc_parent->left = suc->left;
//                        free(suc);
                    } else {
                        suc_parent->right = suc->left;
//                        free(suc);
                    }
                } else if (suc->left == NULL && suc->right != NULL) {  // the node has right subtree
                    if (suc_parent->data > suc->data) {
                        suc_parent->left = suc->right;
//                        free(suc);
                    } else {
                        suc_parent->right = suc->right;
//                        free(suc);
                    }
                }
            }
            cout << "Number " << num << " is deleted." << endl;
        } else { // num not exist
            cout << "Number " << num << " is not exist." << endl;
        }
    }
    void search(int num) {
        BST_Node *temp = root;
        while (temp != NULL && temp->data != num) {
            if (temp->data > num) temp = temp->left;
            else temp = temp->right;
        }
        if (temp)
            cout << "Bingo! " << temp->data << " is found." << endl;
        else
            cout << "SORRY. " << num << " is not found." << endl;
//        cout << "suc: " << successor(num)->data << endl;
//        cout << "parent: " << getParent(num)->data << endl;
    }

    void print() {
        cout << "The tree in prefix order : ";
        prefix(root);
        cout << endl;
        cout << "The tree in infix order : ";
        infix(root);
        cout << endl;
        cout << "The tree in postfix order : ";
        postfix(root);
        cout << endl;
        cout << "The tree in level order : ";
        level_order(root);
        cout << endl;
    }
//    ~BST() {
//        cout << "delete tree!!!" << endl;
//    }
};

/* Level function */
class Binary_searching_Tree {
private:
    static void input_handler(int num[]) {
        int i = 0;
        int input;

        cin >> input;
        while(input!=-1)
        {
            num[i] = input;
            cin >> input;
            ++i;
        }
    }
public:
    static void insert_number(BST *tree) {
        /* Enter “i”, then enter a sequence of numbers and ended
           with “-1” to build a BST. Noticed that the number “-1” is
           not a node for insertion. */
        cout << "Enter numbers: ";
        int num[MAX_ARRAY_SIZE] = {0};
        input_handler(num);

        for (int i = 0; num[i] != 0; ++i) {
            tree->insert(num[i], true);
        }
    }

    static void delete_number(BST *tree) {
        /* Enter “d”, then enter a sequence of numbers ended with “-1” to
           delete (the same as insert) as Fig. 4.
           Also consider the error deletion case that the deleted
           node(number) is not existed. */
        cout << "Enter number to deleted: ";
        int num[MAX_ARRAY_SIZE] = {0};
        input_handler(num);

        for (int i = 0; num[i] != 0; ++i) {
            tree->delete_node(num[i]);
        }
    }

    static void search_number(BST *tree) {
        /* Enter “s”, then enter a sequence ended with “-1” to _search whether
           the numbers are in the BST.
           If the number is not in the BST then print the number is not found. */
        cout << "Enter elements to searching: ";
        int num[MAX_ARRAY_SIZE] = {0};
        input_handler(num);

        for (int i = 0; num[i] != 0; ++i) {
            tree->search(num[i]);
        }
    }
    static void print(BST *tree) {
        /* Enter “p” to print prefix -> infix -> postfix and level order of
           the BST after the above executions.
           Enter “r” to return to the main menu.
           You must use queue skills in level order! */
        tree->print();
    }

};

class Meaty {
public:
    static void broccoli_traps(int index, int traps[], int num[]) {
        int i = 0;
        int j = 0;
        while (num[i] != 0) {  // do every num

            int test_num = num[i];
            while (test_num / 10 != 0 || test_num % 10 != 0) {  // do if not zero
                if (test_num % 10 == index) {
                    traps[j] = num[i];
                    ++j;
                    break;
                }
                test_num = test_num / 10;
            }
            ++i;
        }
    }
};


/* main function */
void binary_searching_tree() {
    BST *tree = new BST;
    while (true) {
        cout << "(I)nsert a number." << endl;
        cout << "(D)elete a number." << endl;
        cout << "(S)earch a number." << endl;
        cout << "(P)rint 4 kinds of orders." << endl;
        cout << "(R)eturn" << endl;

        char action_input;
        cin >> action_input;

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
    // get filename
    string filename_input = "bstmap.txt";
    cout << "Please input the map file:";
    cin >> filename_input;
    // open file
    string filename(filename_input);
    ifstream input_file(filename);
    // if file not found, return to menu
    if (!input_file.is_open()) {
        cerr << "Could not open the file '" << filename << "'" << endl;
        return;
    }
    // store number
    int num[MAX_ARRAY_SIZE] = {0};
    int i = 0;
    while (input_file >> num[i++]) {
    }
//    for (int j = 0; num[j] != 0; ++j) {  // debug
//        cout << num[j] << endl;
//    }
    input_file.close();
    cout << "Load file success." << endl;

    // build tree
    BST tree;
    for (int j = 0; num[j] != 0; ++j) {
        tree.insert(num[j], false);
    }
    cout << endl;
//    tree.print();

    int sword_location, meaty_location, broccoli_traps_index;
    cout << "Please input the sword location: ";
    cin >> sword_location;
    cout << "Please input the Meaty's location: ";
    cin >> meaty_location;
    cout << "Please input the broccoli trap's index (0~9): ";
    cin >> broccoli_traps_index;

    // delete the broccoli traps and replace with correct nodes
    int traps[MAX_ARRAY_SIZE] = {0};
    Meaty::broccoli_traps(broccoli_traps_index, traps, num);  // TODO: postfix delete
    for (int j = 0; traps[j] != 0; ++j) {
        tree.delete_node(traps[j]);
//        cout << traps[j] << endl;
    }

    cout << endl;
    cout << "Capoo successfully found his favorite meaty<3." << endl;
    cout << endl;
    cout << "Shortest path to find the meaty:" << endl;

    // output the correct path of Finding Meaty
    BST_Node *cur = tree.root;
    BST_Node *parent;
    stack<BST_Node *> s;

//    tree.print();

    /* find sword */
    cout << cur->data;
    while (cur->data != sword_location) {
        if (cur->data > sword_location) {
            s.push(cur);
            cur = cur->left;
            cout << "->" << cur->data;
        } else {
            s.push(cur);
            cur = cur->right;
            cout << "->" << cur->data;
        }
    }


    /* find the shortest path root */
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        cout << "->" << cur->data;

        if (meaty_location > sword_location) {
            if (cur->right != NULL && cur->right->data >= meaty_location) {
                break;
            }
        } else {
            if (cur->left != NULL && cur->left->data <= meaty_location) {
                break;
            }
        }
    }

    /* find meaty */
    while (cur->data != meaty_location) {
        if (cur->data > meaty_location) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        cout << "->" << cur->data;
    }
    cout << endl;

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
