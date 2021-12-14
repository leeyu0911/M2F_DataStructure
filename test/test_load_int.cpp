//
// Created by leeyu on 2021/12/6.
//

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string filename_input = "bstmap.txt";
//    cin >> filename_input;
    string filename(filename_input);
    int num[100] = {0x0};

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return 13;
    }

    int i = 0;
    while (input_file >> num[i++]) {
    }
    for (int j = 0; j < 20; ++j) {
        cout << num[j] << endl;
    }
    if (num[20] == 0) cout << "!!!" << endl;
    input_file.close();

    return EXIT_SUCCESS;
}