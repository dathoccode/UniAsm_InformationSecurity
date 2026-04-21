#include <iostream> 
#include "Lib/Converter.h"
#include "Lib/Const.h"
#include "Lib/Arithmetic.h"
#include "Lib/BlockEncryption.h"
#include "Lib/Modulo.h"

using namespace std;


int main()
{
    cout << PowerByEuler(53, 1027, 1457) << endl;
    cout << Phi(1457);
    return 0;
}
