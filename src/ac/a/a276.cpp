#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while(cin >> n){
        vector<long long> m(n);
        long long total = 0;
        for(int i=0;i<n;i++){ cin>>m[i]; total+=m[i]; }
        int na = n/2;
        int nb = n - na;
        vector<long long> A, B;
        A.reserve(1<<na);
        B.reserve(1<<nb);
        for(int mask=0; mask<(1<<na); mask++){
            long long s=0;
            for(int i=0;i<na;i++) if(mask&(1<<i)) s+=m[i];
            A.push_back(s);
        }
        for(int mask=0; mask<(1<<nb); mask++){
            long long s=0;
            for(int i=0;i<nb;i++) if(mask&(1<<i)) s+=m[na+i];
            B.push_back(s);
        }
        sort(B.begin(), B.end());
        long long best = LLONG_MAX;
        for(long long a : A){
            long long target = total/2 - a;
            auto it = lower_bound(B.begin(), B.end(), target);
            if(it!=B.end()){
                long long sum = a + *it;
                best = min(best, llabs(total - 2*sum));
            }
            if(it!=B.begin()){
                --it;
                long long sum = a + *it;
                best = min(best, llabs(total - 2*sum));
            }
            if(best==0) break;
        }
        cout << best << "\n";
    }
    return 0;
}
