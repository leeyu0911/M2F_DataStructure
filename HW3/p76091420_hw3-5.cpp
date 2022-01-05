//
// Created by leeyu on 2021/12/19.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

#define DEBUG_MODE 0
#if DEBUG_MODE
#define DEBUG(msg, x) cout << endl << "LINE:" << __LINE__ << ", " << (msg) << ", " << (x) << endl;
#else
#define DEBUG(msg, x)
#endif


class Data {
public:
    int nodes;
    int root;
    vector<vector<int>> matrix;
    vector<bool> visited;

    map<pair<int, int>, int> table;  // key: <node1, node2> value: weight
    map<int ,int> answer;
};


string open_file(int &nodes, int &root, vector<int> &num_list, int test_mode) {

    string file_name = "input_02.txt";
    cout << "Please input file name:";
    if (!test_mode) cin >> file_name;

    ifstream txtFile;

    txtFile.open(file_name);
    while (!txtFile) {  // if file not found, get file_name again
        cout << "file not found!" << endl;
        cout << "enter file_name :";
        cin >> file_name;
        txtFile.open(file_name);
    }

    // output filename
    file_name.replace(file_name.find("input"), 5, "output");
    ofstream txt;
    txt.open(file_name);
    txt << "";  // clean the file
    txt.close();

    // load file
    txtFile >> nodes;  // first number
    DEBUG("nodes", nodes);

    // store number
    int num;
    for (int i = 0; i < 3 * (nodes-1); ++i) {
        txtFile >> num;
        num_list.push_back(num);
    }
    txtFile >> root;
    DEBUG("root", root);
    txtFile.close();

    return file_name;
}

void build_table(map<pair<int, int>, int> &m, vector<int> &num_list) {
    for (int i = 0; i < num_list.size(); i=i+3) {
        // key: <node1, node2> value: weight
        // key: <node2, node1> value: weight
        pair<int, int> temp_1 = {num_list[i], num_list[i+1]};
        pair<int, int> temp_2 = {num_list[i+1], num_list[i]};
        m[temp_1] = num_list[i+2];
        m[temp_2] = num_list[i+2];
    }
}

void build_matrix(Data &data) {
    // init matrix
    data.matrix = vector<vector<int>>(data.nodes, vector<int>(data.nodes, 0));

    for (auto &i: data.table) {  // i.first: dict key, i.first.first: key of pair first
        data.matrix.at(i.first.first-1).at(i.first.second-1) = 1;  // index - 1
        DEBUG("first", i.first.first);
        DEBUG("second", i.first.second);
    }

}

void dfs(int start, Data &data, map<int ,int> &answer, int &weight) {

    // record result
    answer[start] = weight;

    data.visited[start] = true;

    for (int i = 0; i < data.matrix[start].size(); i++) {

        // some node is adjacent to the current node and not visited
        if (data.matrix[start][i] == 1 && (!data.visited[i])) {
            // add when recursion
            weight = weight + data.table[{start+1, i+1}];
            DEBUG("weight", weight);
            dfs(i, data, answer, weight);
            // deduction on return
            weight = weight - data.table[{start+1, i+1}];
        }
    }
}

void run_dfs(int start, Data &data, string &output_fileName) {
//    queue<pair<int, int>> q;
    map<int ,int> answer;
    int weight = 0;
    dfs(start, data, answer, weight);

    // output txt
    ofstream txt;
    txt.open(output_fileName, ofstream::app);

    // ouput index+1
    for (auto &i: answer) {
        cout << i.first + 1 << " " << i.second << endl;
        txt << i.first + 1 << " " << i.second << endl;
    }
    txt.close();
}


int main() {
    Data data;
    vector<int> num_list;
    string output_fileName = open_file(data.nodes, data.root, num_list, DEBUG_MODE);

    build_table(data.table, num_list);
    build_matrix(data);

    // init visited
    data.visited = vector<bool>(data.nodes, false);
    run_dfs(data.root-1, data, output_fileName);


    // check matrix
//    for (auto &i:data.matrix) {
//        for (auto &j: i){
//            cout << j << " ";
//        }
//        cout << endl;
//    }

    // check num_list
//    for (int i = 0; i < num_list.size(); ++i) {
//        if (i % 3 == 0) cout << endl;
//        cout << num_list[i] << " ";
//    }

}