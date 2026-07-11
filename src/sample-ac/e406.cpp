#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MaxN = 1000000+5;
const int MaxQ = 100000+5;
int A[MaxN];
bool C[MaxQ];
int X[MaxQ] , Y[MaxQ];
int k,m,N,Q;

void gen_dat()
{
   int i,j;
   for( i=k+1; i<=max(Q,N); ++i )
        A[i] = ( A[i-2]*97 + A[i-1]*3 )%m+1;
   for(i=1,j=max(Q,N); i<=Q; ++i,--j)
  {
       C[i] = A[i]&1;
       X[i] = (A[i]+A[j])%N+1;
        if(C[i]) Y[i] = X[i]+ ( (A[i]<<3)+(A[j]<<5)+m )%( N-X[i]+1 );
       else Y[i] = ((A[i]<<3)+(A[j]<<5))%m+1;
  }
}

long long bit[MaxN];

void add(int idx, int val) {
    for (; idx <= N; idx += idx & -idx)
        bit[idx] += val;
}

long long sum(int idx) {
    long long res = 0;
    for (; idx > 0; idx -= idx & -idx)
        res += bit[idx];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    if (!(cin >> k >> m)) return 0;
    for (int i = 1; i <= k; ++i) {
        cin >> A[i];
    }
    cin >> N >> Q;
    gen_dat();
    
    for (int i = 1; i <= N; ++i) {
        add(i, A[i]);
    }
    
    for (int i = 1; i <= Q; ++i) {
        if (C[i] == 0) {
            int x = X[i];
            int y = Y[i];
            int diff = y - A[x];
            if (diff != 0) {
                add(x, diff);
                A[x] = y;
            }
        } else {
            int x = X[i];
            int y = Y[i];
            long long ans = sum(y) - sum(x - 1);
            ans = (ans % m + m) % m;
            cout << ans << "\n";
        }
    }
    
    return 0;
}
