#pragma once
#include <math.h>

int InverseModuloByExtendedEuclid(int a, int n);

bool IsPrime(int n){
    if(n <= 1) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int GCD(int a, int b){
    if(a < 0) a = -a;
    if(b < 0) b = -b;

    while(b != 0){
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int Phi(int n){
    if(IsPrime(n)) return n - 1;

    int res = n;
    for(int i = 2; i * i <= n; i++){
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

int CountDistinctPrimeFactors(int n, int primeFactors[32]){
    int count = 0;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            primeFactors[count++] = i;
            while(n % i == 0){
                n /= i;
            }
        }
    }

    if(n > 1){
        primeFactors[count++] = n;
    }

    return count;
}

int PowerByDownGrading(int a, int m, int n){
    if(n <= 0 || m < 0){
        return -1;
    }

    a %= n;
    if(a < 0) a += n;

    if(m == 0){
        return 1 % n;
    }

    int t = log2(m);
    long long p[100];
    p[0] = a;
    for(int i = 1; i <= t; i++){
        p[i] = p[i-1] * p[i-1] % n;
    }

    int res = 1; 
    for(int i = t; i >= 0; i--){
        if(pow(2, i) <= m)
        {
            res = res * p[i] % n;
            m -= pow(2, i);
        }
    }
    return res;
}

int PowerByFermat(int a, int m, int n){
    if(!IsPrime(n) || m < 0){
        return -1;
    }

    a %= n;
    if(a < 0) a += n;

    if(m == 0) return 1 % n;

    if(a == 0) return 0;

    m %= (n - 1);
    return PowerByDownGrading(a, m, n);
}

int PowerByEuler(int a, int m, int n){
    if(n <= 0 || m < 0){
        return -1;
    }

    a %= n;
    if(a < 0){
        a += n;
    }

    if(m == 0){
        return 1 % n;
    }

    if(a == 0){
        return 0;
    }

    int phiN = Phi(n);
    m %= phiN;
    return PowerByDownGrading(a, m, n);
}

int PowerByChinesRemainderTheorem(int a, int m, int n){
    if(n <= 0 || m < 0){
        return -1;
    }

    a %= n;
    if(a < 0){
        a += n;
    }

    if(m == 0){
        return 1 % n;
    }

    int modList[32];
    int residueList[32];
    int count = 0;
    int tempN = n;

    for(int i = 2; i * i <= tempN; i++){
        if(tempN % i == 0){
            int primePower = 1;
            while(tempN % i == 0){
                tempN /= i;
                primePower *= i;
            }
            modList[count++] = primePower;
        }
    }

    if(tempN > 1){
        modList[count++] = tempN;
    }

    if(count == 0){
        modList[count++] = n;
    }

    for(int i = 0; i < count; i++){
        int ni = modList[i];
        if(GCD(a, ni) == 1){
            int reducedExponent = m % Phi(ni);
            residueList[i] = PowerByDownGrading(a, reducedExponent, ni);
        }
        else{
            residueList[i] = PowerByDownGrading(a, m, ni);
        }
    }

    long long result = 0;
    for(int i = 0; i < count; i++){
        int ni = modList[i];
        int Mi = n / ni;
        int inverseMi = InverseModuloByExtendedEuclid(Mi, ni);

        if(inverseMi == -1){
            return -1;
        }

        result += 1LL * residueList[i] * Mi * inverseMi;
    }

    result %= n;
    if(result < 0){
        result += n;
    }

    return (int)result;
}

int SolveEquationSysByCRT(int m[3], int a[3]){
    long long n = 1;
    for(int i = 0; i < 3; i++){
        n *= m[i];
    }

    long long res = 0;
    for(int i = 0; i < 3; i++){
        long long Ni = n / m[i];
        int invNi = InverseModuloByExtendedEuclid((int)(Ni % m[i]), m[i]);
        if(invNi == -1){
            return -1;
        }
        res += 1LL * a[i] * Ni * invNi;
    }

    res %= n;
    if(res < 0) res += n;
    return (int)res;
}

bool IsPrimitiveRoot(int a, int n){
    if(n <= 1){
        return false;
    }

    a %= n;
    if(a < 0) a += n;

    if(GCD(a, n) != 1){
        return false;
    }

    int phiN = Phi(n);
    int primeFactors[32];
    int factorCount = CountDistinctPrimeFactors(phiN, primeFactors);

    for(int i = 0; i < factorCount; i++){
        int p = primeFactors[i];
        if(PowerByDownGrading(a, phiN / p, n) == 1){
            return false;
        }
    }

    return PowerByDownGrading(a, phiN, n) == 1;
}

int DiscreteLogarithm(int a, int b, int n){
    if(n <= 1){
        return -1;
    }

    a %= n;
    b %= n;
    if(a < 0) a += n;
    if(b < 0) b += n;

    if(b == 1 % n){
        return 0;
    }

    long long current = 1 % n;
    int limit = Phi(n);

    for(int k = 1; k <= limit; k++){
        current = (current * a) % n;
        if(current == b){
            return k;
        }
    }

    return -1;
}


int InverseModuloByExtendedEuclid(int a, int n){
    if (n <= 0) return -1;

    int originalN = n;
    a %= n;
    if(a < 0){
        a += n;
    }

    int A1 = 0, A2 = n;
    int B1 = 1, B2 = a;

    while(B2 != 0){
        int Q = A2 / B2;

        int T1 = A1 - Q * B1;
        int T2 = A2 - Q * B2;

        A1 = B1;
        A2 = B2;
        B1 = T1;
        B2 = T2;
    }

    if(A2 != 1){
        return -1;
    }

    if(A1 < 0){
        A1 += originalN;
    }

    return A1;
}
