#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while(cin >> N){
        vector<pair<long long,long long>> beads(N);
        for(int i = 0; i < N; i++){
            cin >> beads[i].first >> beads[i].second; // C, W
        }
        // sort by (C + W) ascending: bottom-to-top build, top has largest C+W
        sort(beads.begin(), beads.end(),
             [](const pair<long long,long long>& a, const pair<long long,long long>& b){
                 return a.first + a.second < b.first + b.second;
             });
        priority_queue<long long> pq; // max-heap of weights in current sequence
        long long W = 0;
        for(int i = 0; i < N; i++){
            long long c = beads[i].first, w = beads[i].second;
            pq.push(w);
            W += w;
            long long limit = c + w; // top bead i: weight-below <= c  <=>  W <= c + w
            while(W > limit){
                W -= pq.top();
                pq.pop();
            }
        }
        cout << pq.size() << "\n" << W << "\n";
    }
    return 0;
}
