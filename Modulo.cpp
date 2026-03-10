#include <iostream> 
#include <vector>
#include <math.h>

using namespace std;

int EulerFunction(int n){
    int res = n;
    for(int i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            while(n % i == 0){
                n /= i;
            }
            res -= res/i;
        }
    }
    if (n > 1){
        res -= res/n;
    }
    return res;
}

int main()
{
    for(int i = 0; i < 20; i++){
        cout << "Phi(" << i << ") = " << EulerFunction(i) << endl;
    }
    return 0;
}