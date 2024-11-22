//4. Polyalphabetic Cipher (Vigenère Cipher)
#include <iostream>
using namespace std;

string vigenereCipher(string text, string key) {
    string result = "";
    int j = 0;

    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        char k = key[j % key.length()];
        
        if (isupper(c)) {
            result += char(((c - 'A') + (toupper(k) - 'A')) % 26 + 'A');
        } else {
            result += char(((c - 'a') + (tolower(k) - 'a')) % 26 + 'a');
        }
        j++;
    }
    return result;
}

int main() {
    string text = "HELLO";
    string key = "KEY";
    cout << "Ciphertext: " << vigenereCipher(text, key);
    return 0;
}