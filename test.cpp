#include <iostream> 
#include "Lib/Const.h"
#include "Lib/Converter.h"

using namespace std;

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


int main()
{
    string s = "1001";
    cout << BinToDec(s);
    return 0;
}