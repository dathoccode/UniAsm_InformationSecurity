#include <iostream> 
#include "Lib/modulo.h"

using namespace std;


int main()
{
    for(int i = 0; i < 20; i++){
        cout << "Phi(" << i << ") = " << Phi(i) << endl;
    }
    return 0;
}