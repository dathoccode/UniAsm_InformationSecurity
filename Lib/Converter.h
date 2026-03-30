#pragma once
#include <iostream>
#include <string>

using namespace std;

int CharToInt(char c){
    if('0' > c || c > '9') return -1;
    return c - '0';
}

string IntToString(int n) {
    if (n == 0) return "0";

    bool isNegative = false;
    if (n < 0) {
        isNegative = true;
        n = -n;
    }

    string s = "";

    while (n > 0) {
        int digit = n % 10;
        s = char(digit + '0') + s;
        n /= 10;
    }

    if (isNegative) {
        s = "-" + s;
    }

    return s;
}

int StringToInt(string s) {
    int result = 0;
    int i = 0;
    bool isNegative = false;

    if (s[0] == '-') {
        isNegative = true;
        i++;
    } else if (s[0] == '+') {
        i++;
    }

    for (; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            break;
        }
        result = result * 10 + (s[i] - '0');
    }

    return isNegative ? -result : result;
}

int HexCharToDec(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

string DecToBin4Bit(int n) {
    string res = "";
    for (int i = 3; i >= 0; i--) {
        res += ((n >> i) & 1) + '0';
    }
    return res;
}

string DecToBin(int dec){
    if (dec == 0) return "0";

    string res = "";
    while(dec > 0){
        res = IntToString(dec % 2) + res;
        dec /= 2;
    }
    return res;
}

string HexCharToBin(char hexChar){
    return DecToBin4Bit(HexCharToDec(hexChar));
}

string HexToBin(string hex){
    string s = "";
    for(int i = 0; i < hex.length(); i++){
        s += HexCharToBin(hex[i]);
    }
    return s;
}

int BinToDec(string bin)
{
    int res = 0;
    for(int i = 0; i < bin.length(); i++)
    {
        res += CharToInt(bin[i]) << (bin.length() - i - 1);
    }
    return res;
}

void ShowBinBlock(string s, int cols){
    for(int i = 0; i < s.length(); i++){
        cout << s[i] << " ";
        if ((i + 1) % cols == 0) cout << endl;
    }
}