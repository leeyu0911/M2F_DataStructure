//
// Created by leeyu on 2021/12/19.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

#define DEBUG_MODE 0
#if DEBUG_MODE
#define DEBUG(msg, x) cout << endl << "LINE:" << __LINE__ << ", " << (msg) << ", " << (x) << endl;
#else
#define DEBUG(msg, x)
#endif

class dataSet {  // test dataste
public:
    string str_order;
    int nodes;
    vector<int> preOrPost_order;
    vector<int> inorder;
};

string open_file(int &m, vector<dataSet> &dataSets, int test_mode) {

    string file_name = "../HW3/testcases/3-1/input_01.txt";
    cout << "Please input file name:";
    if (!test_mode) cin >> file_name;

    ifstream txtFile;

    txtFile.open(file_name);
    while (!txtFile) {  // if file not found, get file_name again
        cout << "file not found!" << endl;
        cout << "enter file_name :";
        cin >> file_name;  //commend for auto load maze.txt
        txtFile.open(file_name);
    }

    // output filename
    file_name.replace(file_name.find("input"), 5, "output");
    ofstream txt;
    txt.open(file_name);
    txt << "";  // clean the file

    // load file
    string s;

    getline(txtFile, s);   // first number m
    m = stoi(s);
    DEBUG("m", m);

    // creat dataSets
    dataSet one;
    dataSets = vector<dataSet>(m, one);

    int i_getline = 2;
    while (getline(txtFile, s))  // start from 2nd line
    {
        int index = (i_getline-2) / 4;  // dataSets index
        istringstream stream(s);
        int a;
        switch (i_getline % 4) {
            case 2:  // preorder-inorder
                stream >> dataSets.at(index).str_order;
                break;
            case 3:  // 7
                stream >> dataSets.at(index).nodes;
                break;
            case 0:  // 1 2 3 4 5 6 7
                while (stream >> a) {
                    dataSets.at(index).preOrPost_order.push_back(a);
                }
                break;
            case 1:  // 3 2 4 1 6 5 7
                while (stream >> a) {
                    dataSets.at(index).inorder.push_back(a);
                }
                break;
        }
        ++i_getline;
    }
    txtFile.close();
    return file_name;
}

/* pre-in order */
int search(vector<int> arr, int x, int n) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}

void pre_in_order(vector<int> in, vector<int> pre, int n, queue<int> &s) {
    // first element is always root
    int root = search(in, pre[0], n);

    // if left subtree is not empty, go left subtree
    if (root != 0) {
        vector<int> n_pre = {pre.begin() + 1, pre.end()};
        pre_in_order(in, n_pre, root, s);
    }

    // if right subtree is not empty, go right subtree
    if (root != n - 1) {
        vector<int> n_in = {in.begin() + root + 1, in.end()};
        vector<int> n_pre = {pre.begin() + root + 1, pre.end()};
        pre_in_order(n_in, n_pre, n - root - 1, s);
    }

//    cout << pre[0] << " ";
    s.push(pre[0]);
}


void find_postorder(vector<int> const &inorder, vector<int> const &preorder, string output_fileName) {
    int n = preorder.size();
//    cout << "postorder: " << endl;
    queue<int> s;
    pre_in_order(inorder, preorder, n, s);
    ofstream txt;
    txt.open(output_fileName, ofstream::app);
    while (!s.empty())
    {
//        cout << s.front() << ' ';
        txt << s.front() << " ";
        s.pop();
    }
    txt << endl;
    txt.close();
}

/* post in order */
void post_in_order(int start, int end, vector<int> const &postorder, int &pIndex,
                   unordered_map<int, int> &map, stack<int> &stack) {
    // base case
    if (start > end) {
        return;
    }

    // the next element in the postorder sequence from the end will be the root node of subtree
    int value = postorder[pIndex--];

    // get the current node index in inorder sequence to determine its left and right subtree boundary
    int index = map[value];

    post_in_order(index + 1, end, postorder, pIndex, map, stack);
    post_in_order(start, index - 1, postorder, pIndex, map, stack);

    stack.push(value);
}

void find_preorder(vector<int> const &inorder, vector<int> const &postorder, string output_fileName)
{
    unordered_map<int, int> map;

    // fill the map
    for (int i = 0; i < inorder.size(); i++) {
        map[inorder[i]] = i;
    }

    // `lastIndex` stores the index of the next unprocessed node from the end
    // of the postorder sequence
    int lastIndex = inorder.size() - 1;

    stack<int> stack;

    // fill the stack
    post_in_order(0, lastIndex, postorder, lastIndex, map, stack);

    ofstream txt;
    txt.open(output_fileName, ofstream::app);
    while (!stack.empty())
    {
//        cout << stack.top() << ' ';
        txt << stack.top() << " ";
        stack.pop();
    }
    txt << endl;
    txt.close();
}

/* chose function */
void order_algo(dataSet &data, vector<int> &answer, string output_fileName) {
    if (data.str_order == "preorder-inorder")
        find_postorder(data.inorder, data.preOrPost_order, output_fileName);
    else if (data.str_order == "postorder-inorder")
        find_preorder(data.inorder, data.preOrPost_order, output_fileName);
    else
        DEBUG("data.str_order not find", data.str_order);
}

int m;  // nums of test datasets
vector<dataSet> dataSets;  // store m test dataset
vector<vector<int>> answers;  // store m answers

int main()
{
    string output_fileName = open_file(m, dataSets, 0);  // TODO: test_mode
    DEBUG("output file name", output_fileName);

    answers = vector<vector<int>>(m, vector<int>(m, 0));
    for (int i = 0; i < m; ++i) {
        order_algo(dataSets.at(i), answers.at(i), output_fileName);
    }


    // check
//    cout << m << endl;
//    for (int i = 0; i < m; ++i) {
//        cout << dataSets[i].nodes << endl;
//        cout << dataSets[i].str_order << endl;
//        for (int j = 0; j < dataSets[i].nodes; ++j) {
//            cout << dataSets[i].preOrPost_order[j] << " ";
//        }
//        cout << endl;
//        for (int j = 0; j < dataSets[i].nodes; ++j) {
//            cout << dataSets[i].inorder[j] << " ";
//        }
//        cout << endl;
//    }
}
