#include <iostream> 
#include "Lib/Converter.h"
#include "Lib/Const.h"
#include "Lib/Arithmetic.h"
#include "Lib/BlockEncryption.h"

using namespace std;

void SubByte(string (&hex)[4]) 
{
    string res[4];
    for(int i = 0; i < 4; i++)
    {
        res[i] = "";
        for(int j = 0; j < hex[i].length(); j += 2)
        {
            res[i] += AES_S_box[HexCharToDec(hex[i][j])][HexCharToDec(hex[i][j + 1])];
        }
        hex[i] = res[i];
    }
}

void LeftShiftRows(string (&hex)[4])
{
    for(int i = 0; i < 4; i++){
        CircularLeftShift(hex[i], i * 2);
    }
}

void MixColumn(string (&hex)[4])
{
    string s[4];
    for(int i = 0; i < 4; i++){
        s[i] = "";
        for(int j = 0; j < 4; j++){
            string temp = "00";
            for(int k = 0; k < 4; k++){
                string t2 = hex[k].substr(j * 2, 2);
                HexMul(t2, MixColumnMatrix[i][k]);
                HexXor(temp, t2);
            }
            s[i] += temp;
        }
    }

    for(int i = 0; i < 4; i++){
        hex[i] = s[i];
    }
}

void AddRoundKey(string (&hex)[4], string key)
{
    for(int col = 0; col < 4; col++)
    {
        for(int row = 0; row < 4; row++)
        {
            string k = key.substr(row * 8 + col * 2, 2);
            string s = hex[row].substr(col*2, 2);

            HexXor(s, k);

            hex[row].replace(col*2, 2, s);
        }
    }
}

void SubWord(string &word){
    string subTemp = "";
    for (int i = 0; i < 8; i += 2) {
        subTemp += AES_S_box[HexCharToDec(word[i])][HexCharToDec(word[i + 1])];
    }
    word = subTemp;
}

void RotWord(string &word){
    CircularLeftShift(word, 2);
}

void KeyExpansion(string key, string word[44]){

    for (int i = 0; i < 4; i++) {
        word[i] = key.substr(i * 8, 8);
    }

    for (int i = 4; i < 44; i++) {
        string temp = word[i - 1];
        if (i % 4 == 0) {
            RotWord(temp);
            SubWord(temp);
            HexXor(temp, Rcon[i / 4 - 1]);
        }
        string w_i_4 = word[i - 4];
        HexXor(w_i_4, temp);
        word[i] = w_i_4;
    }
}

int main(){

    // aes sắp xếp các byte theo quy tắc lấp cột 
    // ma trận có dạng 
    // b0 b4 b8 b12
    // b1 b5 b9 b13
    // b2 b6 b10 b14
    // b3 b7 b11 b15
    string m = "AB5BFF34115C963B835CAF027EBE0B53";
    string k = "CDAB0FC51CACBCF9A8A348C3D2D0247A";
    string word[44];
    string s[4];

    cout << "Bản rõ: " << m << endl;

    // sắp xếp các byte trong m thành ma trận 4x4 lấp cột
    for(int i = 0; i < 4; i++){
        s[i] = "";
        for(int j = 0; j < 4; j++){
            s[i] += m.substr((j * 8) + i * 2, 2);
        }
    }

    KeyExpansion(k, word);

    // lấy ra 4 word đầu của key sau khi đã mở rộng để xor với state
    string tempWord = "";
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            tempWord += word[col].substr(row*2,2);
        }
    }

    AddRoundKey(s, tempWord);

    for(int round = 1; round <= 10; round++){

        SubByte(s);

        LeftShiftRows(s);

        if(round != 10){
            MixColumn(s);
        }

        // lấy ra các word tương ứng trong bộ khóa để addroundkey
        tempWord = "";
        for(int row = 0; row < 4; row++){
            for(int col = 0; col < 4; col++){
                tempWord += word[round*4 + col].substr(row*2,2);
            }
        }

        AddRoundKey(s, tempWord);
    }

    //in ra theo cột
    cout << "Cipher text: ";

    for(int col = 0; col < 4; col++){
        for(int row = 0; row < 4; row++){
            cout << s[row].substr(col*2,2);
        }
    }

    cout << endl;
    return 0;
}