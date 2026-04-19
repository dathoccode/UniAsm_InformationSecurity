#include <iostream> 
#include "Lib/Converter.h"
#include "Lib/Const.h"
#include "Lib/Arithmetic.h"
#include "Lib/BlockEncryption.h"
#include "Lib/Modulo.h"

using namespace std;


int main()
{
    // int a = 283;
    // int m = 1821;
    // int n = 241;
    //  cout << PowerByDownGrading(a, m, n) << endl;

    // int a = 550;
    // int m = 1759;
    // cout << "Nghich dao cua " << a << " theo modulo " << m << " : " << ReverseModuloByExtendedEuclid(a, m) << endl;
    
    // Giai phuong trinh bang dinh ly phan du trung hoa
    int m[3] = {19,11,13};
    int a[3] = {5,5,6};
    cout << SolveEquationSysByCRT(m, a) << endl;
    
    long long n = m[0] * m[1] * m[2];
    cout << n << endl;
    for(int i = 0; i < 3; i++)
    {
        cout << "nghich dao cua " << m[i] << " theo modulo " << n / m[i] << " la: " << ReverseModuloByExtendedEuclid(m[i], n/m[i]) << endl;
    }
    return 0;
}
