void LeftShift(string &s, int n){
    for(int i = 0; i < n; i++)
    {
        s.erase(0, 1);
        s += '0';
    }
}

void CircularLeftShift(string &s, int n){
    for(int i = 0; i < n; i++)
    {
        char temp = s[0];
        s.erase(0, 1);
        s += temp;
    }
}

void XOR(string &r, string k)
{
    for(int i = 0; i < r.length(); i++){
        r[i] = IntToChar(CharToInt(r[i]) ^ CharToInt(k[i]));
    }
}

void HexXor(string &hex, string k)
{
    hex = HexToBin(hex);
    k = HexToBin(k);
    XOR(hex, k);
    hex = BinToHex(hex);
}

void HexMulBy2(string &s){
    s = HexToBin(s);
    char firstChar = s[0];
    LeftShift(s, 1);
    if(firstChar == '1')
    {
        XOR(s, "00011011");
    }
    s = BinToHex(s);
}

void HexMulBy3(string &s)
{
    string temp = HexToBin(s);
    HexMulBy2(s);
    s = HexToBin(s);
    XOR(s, temp);
    s = BinToHex(s);
}

void HexMul(string &s, int mul)
{
    if(mul == 1) return;
    else if(mul == 2) HexMulBy2(s);
    else if(mul == 3) HexMulBy3(s);
}