//
// Created by leeyu on 2021/12/19.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

#define DEBUG_MODE 0
#if DEBUG_MODE
#define DEBUG(msg, x) cout << endl << "LINE:" << __LINE__ << ", " << (msg) << ", " << (x) << endl;
#else
#define DEBUG(msg, x)
#endif


class dataSet {
public:
    int num_vertices;
    int entry_point;
    vector<vector<int>> matrix;  // adjacency matrix
    vector<bool> visited;
};


void reshape_matrix(int m, vector<int> &matrix_1d, vector<vector<int>> &matrix_2d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix_2d.at(i).at(j) = matrix_1d.at(i * m + j);
        }
    }
}

string open_file(int &m, vector<dataSet> &dataSets, int test_mode) {

    string file_name = "../HW3/testcases/3-2/input_01.txt";
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
    txtFile >> m;  // first number
    DEBUG("m", m);

    int num;
    vector<int> num_list;
    while (txtFile >> num) {
        num_list.push_back(num);
    }
    txtFile.close();

    // trans to dataSets
    dataSet one;
    dataSets = vector<dataSet>(m, one);

    int i = 0;
    int index = 0;  // dataset index
    while (i < num_list.size()) {
        int n = num_list[i];
        int entry = num_list[i+1];
        dataSets.at(index).num_vertices = n;
        dataSets.at(index).entry_point = entry;

        // store matrix
        vector<int> temp_1d_adj(num_list.begin()+i+2, num_list.begin()+i+2+n*n);
        dataSets.at(index).matrix = vector<vector<int>>(n, vector<int>(n, 0));
        reshape_matrix(n, temp_1d_adj, dataSets.at(index).matrix);

        // init visited
        dataSets.at(index).visited = vector<bool>(n, false);

        ++index;  // dataset index
        i += n * n + 2;  // jump to next test dataset
    }

    return file_name;
}

void dfs(int start, vector<bool> &visited, vector<vector<int>> &adj, queue<int> &q) {
    q.push(start);

    visited[start] = true;

    for (int i = 0; i < adj[start].size(); i++) {
        // some node is adjacent to the current node and not visited
        if (adj[start][i] == 1 && (!visited[i])) {
            dfs(i, visited, adj, q);
        }
    }
}

void run_dfs(int start, vector<bool> &visited, vector<vector<int>> &adj, string &output_fileName) {
    queue<int> q;
    dfs(start, visited, adj, q);

    // output txt
    ofstream txt;
    txt.open(output_fileName, ofstream::app);
    while (!q.empty())
    {
        cout << q.front() << " ";
        txt << q.front() << " ";
        q.pop();
    }
    cout << endl;
    txt << endl;
    txt.close();
}

int m;  // nums of test datasets
vector<dataSet> dataSets;  // store m test dataset

int main() {
    string output_fileName = open_file(m, dataSets, 0);
    DEBUG("output_fileName", output_fileName);
    for (int i = 0; i < m; ++i) {
        run_dfs(dataSets.at(i).entry_point, dataSets.at(i).visited, dataSets.at(i).matrix, output_fileName);
    }


    // check
//    for (int i = 0; i < m; ++i) {
//        cout << dataSets[i].matrix.size() << endl;
//        for (int j = 0; j < dataSets[i].matrix.size(); ++j) {
//            for (int k = 0; k < dataSets[i].matrix.size(); ++k) {
//                cout << dataSets.at(i).matrix[j][k] << " ";
//            }
//            cout << endl;
//        }
//    }

}

