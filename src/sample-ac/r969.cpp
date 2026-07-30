#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long modpow(long long a,long long e){
    long long r=1;
    while(e){
        if(e&1) r=r*a%MOD;
        a=a*a%MOD;
        e>>=1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    if(!(cin>>N>>M)) return 0;
    string A,B;
    cin>>A>>B;
    vector<int> cntA(26),cntB(26);
    for(char c:A) cntA[c-'A']++;
    for(char c:B) cntB[c-'A']++;

    int MAXN = N;
    vector<long long> fac(MAXN+1),ifac(MAXN+1);
    fac[0]=1;
    for(int i=1;i<=MAXN;i++) fac[i]=fac[i-1]*i%MOD;
    ifac[MAXN]=modpow(fac[MAXN],MOD-2);
    for(int i=MAXN;i>0;i--) ifac[i-1]=ifac[i]*i%MOD;
    auto C = [&](int n,int k)->long long{
        if(k<0||k>n) return 0;
        return fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
    };

    vector<long long> dp(1,1);          // dp[t] for previous letter
    for(int x=0;x<26;x++){
        int a = cntA[x];
        int b = cntB[x];
        vector<long long> pref(dp.size());
        pref[0]=dp[0];
        for(size_t i=1;i<dp.size();i++){
            pref[i]=pref[i-1]+dp[i];
            if(pref[i]>=MOD) pref[i]-=MOD;
        }
        vector<long long> ndp(a+1,0);
        for(int k=0;k<=a;k++){
            long long limit = (long long)b + k - a;
            if(limit<0) continue;
            int idx = (int)min<long long>(limit, (long long)dp.size()-1);
            long long ways = pref[idx];
            ndp[k]=ways*C(a,k)%MOD;
        }
        dp.swap(ndp);
    }
    long long S=0;
    for(long long v:dp){ S+=v; if(S>=MOD) S-=MOD; }

    long long den=1;
    for(int c:cntA) den=den*fac[c]%MOD;
    long long ans = fac[N]*S%MOD*modpow(den,MOD-2)%MOD;
    cout<<ans<<"\n";
    return 0;
}
