#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int pow_mod(int a, int b, int p);

void encryption(int m, int pub, int p, int g, int* c1, int* c2) {
    int k = 5;
    *c1 = pow_mod(g, k, p);
    *c2 = m * pow_mod(pub, k, p) % p;
}

int decryption(int c1, int c2, int pri, int p, int g) {
    int m;
    int c1_ = pow_mod(c1, p - 2, p);
    m = c2 * pow_mod(c1_, pri, p);
    m = c2 * pow_mod(c1_, pri, p) % p;
    return m;
}

int is_prime(int p) {
    int i;
    for(int i = 2; i <= sqrt(p); i++) {
        if(p % i == 0) {
            return 0;
        }
    }
    return 1;
}

// public key
int pow_mod(int a, int b, int p) {
    int ans = 1;int tmp = a % p;
    while(b) {
        if (b & 1) {
            ans = ans * tmp % p;
        }
        b >>= 1;
        tmp = tmp * tmp % p;
    }
    return ans % p;
}

int main() {
    int p = 7919; // some random prime
    int g = 9768657;

    srand (time(NULL));
    int pri = rand() % 1000;
    // cout << "pri1 = " << pri << endl;
    int pub = pow_mod(g, pri, p);


    int m = 899675; // plaintext
    // cin >> m;
    int c1, c2;
    encryption(m, pub, p, g, &c1, &c2);
    cout << "Alice encrypted and generates 2 keys: " << c1  << ", " << c2 << endl;

    int pri2 = rand() % 1000;
    int pub2 = pow_mod(g, pri2, p);
    int c3, c4;
    encryption(c2, pub2, p, g, &c3, &c4);
    cout << "Bob encrypted and generates 2 keys: " << c3  << ", " << c4 << endl;

    int c2_ = decryption(c3, c4, pri2, p, g);
    int m_n = decryption(c1, c2, pri, p, g);
    cout << "decrypted: " << c2_ << endl << m_n;
}