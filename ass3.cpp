#include <iostream>
#include <vector>
using namespace std;
//2. Rail Fence Technique

string railFenceCipher(string text, int key) {
    vector<string> rail(key);
    bool down = false;
    int row = 0;

    for (char c : text) {
        rail[row] += c;

        if (row == 0 || row == key - 1)
            down = !down;

        row += down ? 1 : -1;
    }

    string result;
    for (string r : rail)
        result += r;

    return result;
}

int main() {
    string text = "HELLO";
    int key = 2;
    cout << "Ciphertext: " << railFenceCipher(text, key);
    return 0;
}