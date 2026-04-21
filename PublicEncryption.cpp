#include <iostream> 
#include "Lib/Modulo.h"
#include "Lib/PublicEncryption.h"

using namespace std;


int main()
{
    int p, q, e, pu[2], pr[2], m, c, a, xa, xb, ya, yb;

    cout << " - Diffie-Hellman: " << endl;
    q = 7207;
    a = 3;
    xa = 422;
    xb = 286;
    ya = PublicKeyDH(a, q, xa);
    yb = PublicKeyDH(a, q, xb);
    cout << "Khoa cong khai cua A: " << ya << endl;
    cout << "Khoa cong khai cua B: " << yb << endl;
    cout << "Khoa phien K: " << SessionKeyDH(ya, xb, q) << endl;

    cout << " - RSA - Bai 1: " << endl; 
    p = 31;
    q = 47;
    e = 43;
    PublicKeyRSA(p, q, e, pu);
    cout << "Khoa cong khai: {" << pu[0] << ", " << pu[1] << "}" << endl;

    PrivateKeyRSA(p, q, e, pr);
    cout << "Khoa rieng: {" << pr[0] << ", " << pr[1] << "}" << endl;

    m = 53;
    c = EncryptRSA(m, pr);
    cout << "An ma khoa: " << m << " -> " << c << endl;

    m = DecryptRSA(c, pu);
    cout << "Ba cua An giai ma: " << c << " -> " << m << endl;

    cout << " - RSA - Bai 2:" << endl;
    cout << "Khoa cong khai: {" << pu[0] << ", " << pu[1] << "}" << endl;
    cout << "Khoa rieng: {" << pr[0] << ", " << pr[1] << "}" << endl;
    m = 53;
    c = EncryptRSA(m, pu);
    cout << "Ba ma hoa thong diep gui cho An: " << m << " -> " << c << endl;

    m = DecryptRSA(c, pr);
    cout << "An giai ma thong diep: " << c << " -> " << m << endl;

    cout << " - Elgaman: " << endl;
    int puElGamal[3], prElGamal[3];
    q = 7349;
    a = 3;
    xa = 366;
    
    int mElgamal[2], cElgamal[2];
    PublicKeyElgamal(a, q,xa, puElGamal);
    ya = puElGamal[2];
    cout << "Khoa cong khai cua An: {" << q << ", " << a << ", " << ya << "}" << endl;
    m = 333;
    int smallk = 32;
    EncryptElgamal(smallk, ya, a, m, q, cElgamal);
    cout << "Ba ma hoa: " << m << " -> " << "{" << cElgamal[0] << ", " << cElgamal[1] << "}" << endl;

    m = DecryptElgamal(cElgamal, xa, q);
    cout << "An giai ma: " << "{" << cElgamal[0] << ", " << cElgamal[1] << "}" << " -> " << m << endl;
    
    cout << " - Chu ky dien tu(DSA): " << endl;
    int hm = 7;
    p = 59;
    q = 29;
    int h = 10;
    xa = 2;
    int k = 3;
    int g = PowerByEuler(h, (p - 1) / q, p);
    ya = PublicKeyDSA(g, xa, p);
    cout << "Khoa cong khai cua An: " << ya << endl;
    int sign[2];
    SignDSA(g, k, p, q, hm, xa, sign);
    cout << "Chu ky so cua An cho ban tin M:" << "{" << sign[0] << ", " << sign[1] << "}" << endl;
    bool isAuthed = false;
    isAuthed = AuthorizationDSA(sign, p, q, hm, g, ya);
    cout << "Ket qua xac minh chu ky so: " << (isAuthed? "Dung" : "Sai") << endl;
    return 0;
}