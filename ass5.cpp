//5. Playfair Cipher with Key 'LDRP'
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void createPlayfairTable(char table[5][5], string key) {
    bool exists[26] = {false};
    exists['J' - 'A'] = true; // Usually I/J are combined in Playfair

    int idx = 0;
    for (char c : key) {
        if (!exists[c - 'A']) {
            table[idx / 5][idx % 5] = c;
            exists[c - 'A'] = true;
            idx++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (!exists[c - 'A']) {
            table[idx / 5][idx % 5] = c;
            idx++;
        }
    }
}

string playfairEncrypt(string text, char table[5][5]) {
    string result = "";

    // Pad 'X' if needed and split into digraphs
    if (text.length() % 2 != 0)
        text += 'X';

    for (int i = 0; i < text.length(); i += 2) {
        char a = text[i];
        char b = text[i + 1];
        if (a == b) b = 'X'; // Handling repeating characters in a digraph

        int r1, c1, r2, c2;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (table[r][c] == a) {
                    r1 = r;
                    c1 = c;
                }
                if (table[r][c] == b) {
                    r2 = r;
                    c2 = c;
                }
            }
        }

        if (r1 == r2) {
            result += table[r1][(c1 + 1) % 5];
            result += table[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            result += table[(r1 + 1) % 5][c1];
            result += table[(r2 + 1) % 5][c2];
        } else {
            result += table[r1][c2];
            result += table[r2][c1];
        }
    }

    return result;
}

int main() {
    string key = "LDRP";
    char table[5][5];
    createPlayfairTable(table, key);

    string text = "HELLO";
    cout << "Ciphertext: " << playfairEncrypt(text, table);
    return 0;
}