#include "Modulo.h"

int PublicKeyDH(int a, int q, int xa){
    return PowerByDownGrading(a, xa, q);
}


int SessionKeyDH(int ya, int xb, int q){
    return PowerByDownGrading(ya, xb, q);
}

void PublicKeyRSA(int p, int q, int e, int (&key)[2])
{
    key[0] = e;
    key[1] = p * q;
}

void PrivateKeyRSA(int p, int q, int e, int (&key)[2]){
    int n = p * q;
    int phiN = Phi(n);
    if(!IsPrime(p) || !IsPrime(q) || p == q || GCD(e, phiN) != 1)
    {
        return;
    }
    
    key[0] = InverseModuloByExtendedEuclid(e, phiN);
    key[1] = n;
}

int EncryptRSA(int m, int key[2]){
    return PowerByDownGrading(m, key[0], key[1]);
}

int DecryptRSA(int c, int key[2]){
    return PowerByDownGrading(c, key[0], key[1]);
}

void PublicKeyElgamal(int a, int q, int xa, int pu[3]){
    pu[0] = q;
    pu[1] = a;
    pu[2] = PowerByDownGrading(a, xa, q);
}

void EncryptElgamal(int smallK, int ya, int a, int m, int q, int (&c)[2]){
    int bigK = PowerByDownGrading(ya, smallK, q);
    c[0] = PowerByDownGrading(a, smallK , q);
    c[1] = (bigK * m) % q;
}

int DecryptElgamal(int c[2], int xa, int q){
    int bigK = PowerByDownGrading(c[0], xa, q);
    int res = c[1] * InverseModuloByExtendedEuclid(bigK, q) % q;
    if (res < 0) res += q;
    return res;
}

int PublicKeyDSA(int g, int x, int p)
{
    g %= p;
    if (g < 0) g += p;
    return PowerByDownGrading(g, x, p);
}

void SignDSA(int g, int k, int p, int q, int hm, int x, int (&sign)[2]){
    int r = PowerByDownGrading(g, k, p) % q;
    if (r < 0) r += q;
    int s = InverseModuloByExtendedEuclid(k, q) * (hm + x * r) % q;
    sign[0] = r;
    sign[1] = s;
}

bool AuthorizationDSA(int sign[2], int p, int q, int hm, int g, int y){
    int w = InverseModuloByExtendedEuclid(sign[1], q);
    int u1 = InverseModuloByExtendedEuclid(hm, q) * w % q;
    if(u1 < 0) u1 += q;
    int u2 = sign[0] * w % q;
    if (u2 < 0) u2 += q;
    int v = (PowerByDownGrading(g, u1, p) * PowerByDownGrading(y, u2, p)) % q;
    if (v < 0) v += q;
    return v = sign[0];
}