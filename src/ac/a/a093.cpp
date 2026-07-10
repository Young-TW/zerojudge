#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 10000;
const long long M2 = 20000; // 2*MOD for the /2 trick

long long pw(long long b, long long e, long long m){
    long long r=1%m; b%=m;
    while(e){ if(e&1) r=r*b%m; b=b*b%m; e>>=1; }
    return r;
}

int main(){
    int k;
    while(cin>>k){
        vector<long long> p(k), e(k);
        long long mmod=1; // m mod 10000
        long long A=1%M2, B=1%M2; // A=prod q_i mod 20000, B=prod(2-q_i) mod 20000
        for(int i=0;i<k;i++){
            cin>>p[i]>>e[i];
            mmod = mmod * pw(p[i], e[i], MOD) % MOD;
            if(p[i]!=2){
                // odd prime
                A = A * (p[i] % M2) % M2;
                long long t = ((2 - p[i]) % M2 + M2) % M2;
                B = B * t % M2;
            }
        }
        long long m_minus_1 = (mmod - 1 + MOD) % MOD;
        // politician = (A+B)/2 - 1 ; military = (A-B)/2  (both mod 20000 then /2)
        long long sum = (A + B) % M2;      // even*2 region
        long long dif = (A - B % M2 + M2) % M2;
        long long pol = (sum / 2 - 1 + MOD) % MOD;
        long long mil = (dif / 2) % MOD;
        long long sch = (m_minus_1 - pol - mil % MOD + 2*MOD) % MOD;
        cout << pol << "\n" << mil << "\n" << sch << "\n";
    }
    return 0;
}
