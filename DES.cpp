#include <iostream> 
#include "Lib/Converter.h"
#include "Lib/Const.h"
#include "Lib/Arithmetic.h"

using namespace std;


void IP(string &s)
{
    string res = "";
    for (int i = 0; i < 64; i++){
        res += s[IP_table[i] - 1];
    }
    s = res;
}

void Split(string s, string &left, string &right)
{
    left = "";
    right = "";
    for(int i = 0; i < 64; i++){
        if (i % 8 < 4) left += s[i];
        else right += s[i]; 
    }
}

void R1(string &r){
    string res = "";
    for (int i = 0; i < 48; i++){
        res += r[EP_table[i] - 1];
    }
    r = res;
}

void XOR(string &r, string k)
{
    for(int i = 0; i < 48; i++){
        r[i] = CharToInt(r[i]) ^ CharToInt(k[i]);
    }
}

void SUB(string &s)
{
    string res = "";
    for(int i = 0; i < 8; i++){
        string bits = "";
        for (int j = i; j < i + 6; j++){
            bits += s[j];
        }
        int row = (CharToInt(bits[0]) << 1) | CharToInt(bits[5]);
        int col =  BinToDec(bits.substr(1, bits.length() - 2));

        res += S_box[i][row - 1][col - 1];
    }
    s = res;
}

void P(string &s)
{
    string res = "";
    for (int i = 0; i < 32; i++)
    {
        res += s[P_table[i] - 1];
    }
    s = res;
}

int main()
{
    string s = "F35D514714F45A8A";

    s = HexToBin(s);

    ShowBinBlock(s, 8);

    IP(s);
    cout << "After IP:" << endl;
    ShowBinBlock(s, 8);

    return 0;
}