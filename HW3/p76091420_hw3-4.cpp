//
// Created by leeyu on 2021/12/19.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


#define DEBUG_MODE 0
#if DEBUG_MODE
#define DEBUG(msg, x) cout << endl << "LINE:" << __LINE__ << ", " << (msg) << ", " << (x) << endl;
#else
#define DEBUG(msg, x)
#endif

typedef pair<int, int> iPair;

struct DisjointSets {
    int *parent, *rnk;
    int n;

    // Constructor.
    explicit DisjointSets(int n) {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // init
        for (int i = 0; i <= n; i++) {
            rnk[i] = 0;
            parent[i] = i;  //every element is parent of itself
        }
    }

    // find the parent, path Compression
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // if rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

struct Graph {
    int V{}, E{};
    vector<pair<int, iPair>> edges;

    Graph() = default;

    // constructor
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    // Kruskal's MST algorithm
    int kruskalMST() {
        int mst_wt = 0; // weight of MST

        // sort edges in increasing order on basis of cost
        sort(edges.begin(), edges.end());

        DisjointSets ds(V);

        // Iterate through all sorted edges
        vector<pair<int, iPair>>::iterator it;
        for (it=edges.begin(); it!=edges.end(); it++) {
            int u = it->second.first;
            int v = it->second.second;

            int set_u = ds.find(u);
            int set_v = ds.find(v);

            // check selected edge be cycled (u and v belong to same set)
            if (set_u != set_v) {
//                cout << u << " - " << v << endl;
                mst_wt += it->first;
                ds.merge(set_u, set_v);
            }
        }
        return mst_wt;
    }
};

string open_file(int &V, int &E, vector<int> &num_list, int test_mode) {

    string file_name = "input.txt";
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
    txtFile >> V;  // first number
    DEBUG("V", V);
    txtFile >> E;  // second number
    DEBUG("E", E);

    // store number
    int num;
    while (txtFile >> num) {
        num_list.push_back(num);
    }
    txtFile.close();

    return file_name;
}

Graph build_graph(int V, int E, vector<int> &num_list) {
    // trans to edges
    DEBUG("V", V);
    DEBUG("E", E);
    Graph g(V, E);
    int i = 0;
    while (i < 3*E) {
        DEBUG("i", i);
        g.addEdge(num_list[i], num_list[i+1], num_list[i+2]);
//        cout << num_list[i] << " ";
//        cout << num_list[i+1] << " ";
//        cout << num_list[i+2] << endl;
        i = i + 3;
    }
    return g;
}

int output_answer(Graph &g, string &output_fileName) {
    int mst_wt = g.kruskalMST();

    // output txt
    ofstream txt;
    txt.open(output_fileName, ofstream::app);
    txt << mst_wt << endl;
    txt.close();

    return mst_wt;
}


int main() {
    int V, E;
    vector<int> num_list;
    string output_fileName = open_file(V, E, num_list, DEBUG_MODE);

    Graph g = build_graph(V, E, num_list);
    cout << g.kruskalMST() << endl;
    output_answer(g, output_fileName);
}
