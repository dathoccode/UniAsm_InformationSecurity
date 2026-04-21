#include <iostream> 
#include "Lib/modulo.h"

using namespace std;


int main()
{
    int a, n, m, b, x, y;

    a = 293, n = 6653, m = 6653;
    cout << " - Tinh luy thua bang cach ha bac: " << endl;
    cout << a << "^" << m << " mod " << n << " = " << PowerByDownGrading(a, m, n) << endl;

    
    a = 1974;
    m = 7841;
    cout << " - Tinh nghich dao bang Euclid mo rong: " << endl;
    cout << "Nghich dao cua " << a << " theo modulo " << m << " : " << InverseModuloByExtendedEuclid(a, m) << endl;
    
    cout << " - Tinh luy thua bang dinh ly fermat: " << endl;
    cout << a << "^" << m << " mod " << n << " = " << PowerByFermat(a, m, n) << endl;

    a = 3312;
    cout << " - Tinh gia tri ham Euler: " << endl; 
    cout << "phi(" << a << ") = " << Phi(a) << endl;

    a = 38;
    m = 2934;
    n = 220;
    cout << " - Tinh luy thua bang dinh ly Euler: " << endl;
    cout << a << "^" << m << " mod " << n << " = " << PowerByEuler(a, m, n) << endl;

    a = 241;
    m = 59;
    n = 63307;
    cout << " - Tinh luy thua bang dinh ly phan du trung hoa: " << endl;
    cout << a << "^" << m << " mod " << n << " = " << PowerByChinesRemainderTheorem(a, m, n) << endl;

    int p[3] = {19,11,13};
    int q[3] = {5,5,6};
    cout << " - Giai phuong trinh bang dinh ly phan du trung hoa: " << endl;
    for(int i = 0; i < 3; i++){
        cout << "x mod " << p[i] << " = " << q[i] << endl;
    }
    cout << "x = " << SolveEquationSysByCRT(p, q) << endl;

    a = 5;
    n = 263;
    cout << " - Kiem tra can nguyen thuy: " << endl;
    bool res = IsPrimitiveRoot(a, n);
    if(res) cout << a << " la can nguyen thuy cua " << n << endl;
    else cout << a << " khong la can nguyen thuy cua " << n << endl; 

    a = 2;
    b = 7;
    n = 11;
    cout << " - Tim logarith roi rac: " << endl;
    cout << "dlog cua " << b << " theo co so " << a << " la: " << DiscreteLogarithm(a, b, n);

    a = 31;
    b = 67;
    x = 375;
    y = 539;
    n = 211;
    cout << " - Tinh cac bieu thuc: " << endl;
    
    int ax = PowerByEuler(a, x, n);
    int by = PowerByEuler(b, y, n);
    
    int A1 = (ax + by) % n;
    int A2 = (ax - by + n) % n;
    int A3 = (1LL * ax * by) % n;
    int A4 = InverseModuloByExtendedEuclid(by, n);
    int A5 = (1LL * ax * A4) % n;
    
    cout << "A1 = (" << a <<  "^" << x << " + " << b << "^" << y << ") mod " << n << " = " << A1 << endl;
    cout << "A2 = (" << a <<  "^" << x << " - " << b << "^" << y << ") mod " << n << " = " << A2 << endl;
    cout << "A3 = (" << a <<  "^" << x << " * " << b << "^" << y << ") mod " << n << " = " << A3 << endl;
    cout << "A4 = (" << b << "^" << y << ")^-1 mod " << n << " = " << A4 << endl;
    cout << "A5 = (" << a <<  "^" << x << "/" << b << "^" << y << ") mod " << n << " = " << A5 << endl;
    
    return 0;
}