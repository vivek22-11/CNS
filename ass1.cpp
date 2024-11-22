#include <iostream>
using namespace std;
//1. Caesar Cipher

string caesarCipher(string text, int shift) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char(int(text[i] + shift - 65) % 26 + 65);
        } else {
            result += char(int(text[i] + shift - 97) % 26 + 97);
        }
    }
    return result;
}

int main() {
    string text = "HELLO";
    int shift = 3;
    cout << "Ciphertext: " << caesarCipher(text, shift);
    return 0;
}