#include <iostream> 
#include "Lib/Converter.h"
#include "Lib/Const.h"
#include "Lib/Arithmetic.h"
#include "Lib/BlockEncryption.h"

using namespace std;

void InitialPermutation(string &s)
{
    string res = "";
    for (int i = 0; i < 64; i++){
        res += s[IP_table[i] - 1];
    }
    s = res;
}

void Split(string s, string &left, string &right)
{
    left = s.substr(0, 32);
    right = s.substr(32, 32);
}

void ExpansionPermutation(string &r){
    string res = "";
    for (int i = 0; i < 48; i++){
        res += r[EP_table[i] - 1];
    }
    r = res;
}

void SubstitionChoice(string &s)
{
    string res = "";
    for(int i = 0; i < 8; i++){
        string bits = s.substr(i * 6, 6);
        int row = (CharToInt(bits[0]) << 1) | CharToInt(bits[5]);
        int col =  BinToDec(bits.substr(1, 4));

        res += DecToBin4Bit(DES_S_box[i][row][col]);
    }
    s = res;
}

void Permutation(string &s)
{
    string res = "";
    for (int i = 0; i < 32; i++)
    {
        res += s[P_table[i] - 1];
    }
    s = res;
}

void ReverseInitialPermutation(string &s){
    string res = "";
    for (int i = 0; i < 64; i++){
        res += s[IP_1_table[i] - 1];
    }
    s = res;
}

void PermutedChoice1(string &key){
    string res = "";
    for(int i = 0; i < 56; i++){
        res += key[PC1_table[i] - 1];
    }
    key = res;
}

void SplitKey(string s, string &top, string &bot)
{
    top = "";
    bot = "";
    for(int i = 0; i < 56; i++){
        if (i < 28) top += s[i];
        else bot += s[i]; 
    }
}

void PermutedChoice2(string &s, string top, string bot)
{
    string temp = top + bot;
    s = "";
    for(int i = 0; i < 48; i++){
        s += temp[PC2_table[i] - 1];
    }
}

void GetSubKey(string &subkey, string& c, string& d, int round)
{
    CircularLeftShift(c, LeftShiftSchedule[round]);
    CircularLeftShift(d, LeftShiftSchedule[round]);
    PermutedChoice2(subkey, c, d);
}

int main()
{
    string s = "1EDE3CBCAF288822";
    string k = "F35D514714F45A8A";
    
    string l, r, c, d;
    s = HexToBin(s);
    InitialPermutation(s);

    k = HexToBin(k);
    PermutedChoice1(k);
    SplitKey(k, c, d);

    for(int round = 0; round < 16; round++){
        Split(s, l, r);
        string rBackup = r;

        ExpansionPermutation(r);
        
        string subkey;
        GetSubKey(subkey, c, d, round);

        XOR(r, subkey);

        SubstitionChoice(r);

        Permutation(r);

        XOR(r, l);

        s = rBackup + r;
    }
    
    Split(s, l, r);
    s = r + l;

    ReverseInitialPermutation(s);

    cout << "res: " << endl;
    ShowBinBlock(s, 8);

    cout << "hex res: " << endl;
    cout << BinToHex(s);
    return 0;
}