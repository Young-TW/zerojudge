#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    int N;
    int tc = 0;
    while(scanf("%d", &N) == 1){
        tc++;
        vector<pair<int,int>> v;
        v.reserve(N);
        for(int i = 0; i < N; i++){
            int L, R;
            scanf("%d %d", &L, &R);
            if(L < R) v.push_back(make_pair(L, R));
        }
        sort(v.begin(), v.end());
        priority_queue<int, vector<int>, greater<int> > pq;
        long long ans = 0;
        for(size_t i = 0; i < v.size(); i++){
            int L = v[i].first;
            int R = v[i].second;
            while(!pq.empty() && pq.top() <= L) pq.pop();
            ans += (long long)pq.size();
            pq.push(R);
        }
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
