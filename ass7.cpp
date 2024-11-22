#include <iostream>
#include <vector>
using namespace std;

// Key matrix for encryption (3x3)
vector<vector<int>> keyMatrix = {
    {6, 24, 1},
    {13, 16, 10},
    {20, 17, 15}
};

// Function to calculate modular inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

// Function to multiply the key matrix with the vector
vector<int> multiplyMatrix(vector<int> vec) {
    vector<int> result(3);
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += keyMatrix[i][j] * vec[j];
        }
        result[i] = result[i] % 26;  // Modulo operation to wrap around the alphabet
    }
    return result;
}

// Function to perform Hill Cipher encryption
string hillCipher(string text) {
    int n = text.length();
    
    // Padding with 'X' if text length is not a multiple of 3
    while (text.length() % 3 != 0) {
        text += 'X';
    }

    string cipherText = "";

    // Process each 3-letter block
    for (int i = 0; i < text.length(); i += 3) {
        vector<int> vec(3);

        // Convert characters to integers (A=0, B=1, ..., Z=25)
        for (int j = 0; j < 3; j++) {
            vec[j] = text[i + j] - 'A';
        }

        // Multiply the key matrix with the vector
        vector<int> result = multiplyMatrix(vec);

        // Convert back to characters and add to the cipher text
        for (int j = 0; j < 3; j++) {
            cipherText += (result[j] + 'A');
        }
    }

    return cipherText;
}

// Function to find the determinant of a 3x3 matrix
int determinant(vector<vector<int>> matrix) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

// Function to calculate the cofactor matrix
vector<vector<int>> cofactorMatrix(vector<vector<int>> matrix) {
    vector<vector<int>> cofactor(3, vector<int>(3));

    cofactor[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
    cofactor[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    cofactor[0][2] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    cofactor[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    cofactor[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
    cofactor[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);

    cofactor[2][0] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
    cofactor[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    cofactor[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

    return cofactor;
}

// Function to calculate the adjugate matrix (transpose of cofactor matrix)
vector<vector<int>> adjugateMatrix(vector<vector<int>> cofactor) {
    vector<vector<int>> adjugate(3, vector<int>(3));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adjugate[i][j] = cofactor[j][i];
        }
    }

    return adjugate;
}

// Function to calculate the inverse key matrix
vector<vector<int>> inverseMatrix(vector<vector<int>> matrix) {
    int det = determinant(matrix);
    int detInv = modInverse(det % 26, 26);

    vector<vector<int>> cofactor = cofactorMatrix(matrix);
    vector<vector<int>> adjugate = adjugateMatrix(cofactor);

    vector<vector<int>> inverse(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = (adjugate[i][j] * detInv) % 26;
            if (inverse[i][j] < 0) inverse[i][j] += 26;
        }
    }

    return inverse;
}

// Function to decrypt the Hill Cipher
string hillCipherDecrypt(string cipherText) {
    vector<vector<int>> invKeyMatrix = inverseMatrix(keyMatrix);
    string plainText = "";

    for (int i = 0; i < cipherText.length(); i += 3) {
        vector<int> vec(3);

        // Convert characters to integers (A=0, B=1, ..., Z=25)
        for (int j = 0; j < 3; j++) {
            vec[j] = cipherText[i + j] - 'A';
        }

        // Multiply the inverse key matrix with the vector
        vector<int> result(3);
        for (int i = 0; i < 3; i++) {
            result[i] = 0;
            for (int j = 0; j < 3; j++) {
                result[i] += invKeyMatrix[i][j] * vec[j];
            }
            result[i] = result[i] % 26;  // Modulo operation to wrap around the alphabet
        }

        // Convert back to characters and add to the plain text
        for (int j = 0; j < 3; j++) {
            plainText += (result[j] + 'A');
        }
    }

    return plainText;
}

int main() {
    string text = "HELLO";
    string encryptedText = hillCipher(text);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = hillCipherDecrypt(encryptedText);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}