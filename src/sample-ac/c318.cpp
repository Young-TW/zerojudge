#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, T;
    while(cin >> N >> T){
        priority_queue<pair<int,int> > pq;
        vector<int> S(N), D(N), cur(N);
        for(int i=0;i<N;i++){
            cin >> S[i] >> D[i];
            cur[i] = S[i];
            if(cur[i] > 0) pq.push(make_pair(cur[i], i));
        }
        long long ans = 0;
        while(T > 0 && !pq.empty()){
            pair<int,int> top = pq.top(); pq.pop();
            int sc = top.first, idx = top.second;
            ans += sc;
            T--;
            cur[idx] -= D[idx];
            if(cur[idx] > 0) pq.push(make_pair(cur[idx], idx));
        }
        cout << ans << "\n";
    }
    return 0;
}
