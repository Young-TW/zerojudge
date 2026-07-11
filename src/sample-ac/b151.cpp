#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while(cin >> n){
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for(int i=0;i<n;i++){
            long long x;
            cin >> x;
            pq.push(x);
        }
        long long total = 0;
        while(pq.size() > 1){
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            total += a + b;
            pq.push(a + b);
        }
        cout << total << "\n";
    }
    return 0;
}
