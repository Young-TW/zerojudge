#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while(cin >> n){
        vector<int> A(n), B(n);
        for(int i=0;i<n;i++) cin >> A[i];
        for(int i=0;i<n;i++) cin >> B[i];
        unordered_map<int, vector<int>> pos;
        pos.reserve(n*2+1);
        for(int i=0;i<n;i++) pos[B[i]].push_back(i);
        string out;
        out.reserve(n*4);
        for(int i=0;i<n;i++){
            auto it = pos.find(A[i]);
            int ans;
            if(it==pos.end()){
                ans = -1;
            } else {
                auto &v = it->second;
                int idx = lower_bound(v.begin(), v.end(), i) - v.begin();
                int best = INT_MAX;
                if(idx < (int)v.size()) best = v[idx]-i;
                if(idx > 0) best = min(best, i-v[idx-1]);
                ans = best;
            }
            if(i) out += ' ';
            out += to_string(ans);
        }
        cout << out << '\n';
    }
    return 0;
}
