//6. Advanced Columnar Transposition Technique
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string columnarTransposition(string text, string key) {
    int col = key.length();
    int row = (text.length() + col - 1) / col;

    vector<vector<char>> grid(row, vector<char>(col, 'X')); // 'X' used for padding

    int k = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (k < text.length())
                grid[i][j] = text[k++];
        }
    }

    vector<pair<char, int>> order;
    for (int i = 0; i < col; i++)
        order.push_back(make_pair(key[i], i));

    sort(order.begin(), order.end());

    string result = "";
    for (auto p : order) {
        for (int i = 0; i < row; i++) {
            result += grid[i][p.second];
        }
    }

    return result;
}

string advancedColumnarTransposition(string text, string key) {
    string result = columnarTransposition(text, key);
    return columnarTransposition(result, key); // Multiple passes
}

int main() {
    string text = "HELLO";
    string key = "3142";
    cout << "Ciphertext: " << advancedColumnarTransposition(text, key);
    return 0;
}