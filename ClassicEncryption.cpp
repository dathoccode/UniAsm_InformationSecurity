#include <iostream> 
#include <utility>

using namespace std;

#pragma region finished 
string CaesarEncrypt(string plainText, int key){
    string cipherText = "";
    for(int i = 0; i < plainText.length(); i++){
        int index = plainText[i] - 'A'; 
        cipherText += (index + key) % 26 + 'A';
    }
    return cipherText;
}

// mode: 0 = loop key, 1 = autokey
string VigenereEncrypt(string plainText, string key, int mode){
    string cipherText = "", newKey = "";

    //generate new key
    if(mode == 0){
        while(newKey.length() < plainText.length()){
            newKey += key;
        }
    } else{
        newKey = key + plainText;
    }

    cout << "New key: " << newKey << endl;

    for(int i = 0; i < plainText.length(); i++){
        int index = plainText[i] - 'A';
        int keyIndex = newKey[i] - 'A';
        cipherText += (index + keyIndex) % 26 + 'A';
    }
    
    return cipherText;
}

string SingleAlphabetEncrypt(string plainText, string key){
    string cipherText = "";
    for(int i = 0; i < plainText.length(); i++){
        int index = plainText[i] - 'A';
        cipherText += key[index];
    }
    return cipherText;
}
#pragma endregion


void GenerateMatrix(char matrix[5][5], string word){
    bool used[26] = {false};
    int k = 0;
    char c = 'A';
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(k < word.length()){
                matrix[i][j] = word[k];
                used[word[k] - 'A'] = true;
                k++;
                continue;
            }

            while(c <= 'Z'){
                if(c == 'J' || used[c - 'A']){
                    c++;
                    continue;
                }
                
                matrix[i][j] = c;
                used[c - 'A']= true;  
                break;             
            }
            
        }
    }

    // show matrix
    cout << "Ma tran playfair: " << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}

// find the position of a character in a 5x5 matrix
void PositionFinding(char matrix[5][5], char character, int &r, int &c){
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if(matrix[i][j] == character){
                r = i;
                c = j;
            }
        }
    }
}


string PlayFairEncrypt(string plainText, string word){
    string cipherText = "";
    char matrix[5][5];

    // normalize plainText
    for(int i = 0; i < plainText.length() - 1; i += 2)   //remove duplicated character pair by inserting 'X'
    {
        if(plainText[i] == plainText[i+1]){
            plainText.insert(i+1, "X");
        }
    }
    if(plainText.length() % 2 != 0) plainText += 'X';   // add sub character if there's an odd character

    GenerateMatrix(matrix, word);

    for(int i = 0; i < plainText.length() - 1; i += 2){
        char ch1 = plainText[i], ch2 = plainText[i+1];
        int r1, c1, r2, c2;
        PositionFinding(matrix, ch1, r1, c1);
        PositionFinding(matrix, ch2, r2, c2);
        if(r1 == r2){
            cipherText += matrix[r1][(c1 + 1) % 5];
            cipherText += matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            cipherText += matrix[(r1 + 1) % 5][c1];
            cipherText += matrix[(r2 + 1) % 5][c2];
        } else{
            cipherText += matrix[r1][c2];
            cipherText += matrix[r2][c1];
        }
    }
    return cipherText;
}

int main()
{
    string plainText = "ACLEANFASTISB";
    string key = "EASTO";
    cout << "Plain Text: " << plainText << endl;
    string cipherText = PlayFairEncrypt(plainText, key);
    cout << "Cipher Text: " << cipherText << endl;

    return 0;
}