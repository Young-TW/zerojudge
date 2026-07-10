#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while(cin >> s){
        string t;
        for(char c : s){
            if(isalpha((unsigned char)c)) t += (char)toupper((unsigned char)c);
        }
        if(t.empty()) continue;
        int ans = -1;
        for(int ST = 1; ST <= 10000; ST++){
            vector<int> d;
            d.reserve(60);
            for(char c : t){
                int v = ST + (c - 'A');
                string ds = to_string(v);
                for(char ch : ds) d.push_back(ch - '0');
            }
            int m = (int)d.size();
            int k = m - 3;
            if(k < 0){
                // fewer than 3 digits: cannot be "100"
                continue;
            }
            int r0 = 0, r1 = 0, r2 = 0;
            long long C = 1;
            for(int j = 0; j <= k; j++){
                if(j > 0){
                    C = C * (long long)(k - j + 1) / j;
                }
                int c = (int)(C % 10);
                r0 = (r0 + c * d[j]) % 10;
                r1 = (r1 + c * d[j+1]) % 10;
                r2 = (r2 + c * d[j+2]) % 10;
            }
            if(r0 == 1 && r1 == 0 && r2 == 0){
                ans = ST;
                break;
            }
        }
        if(ans == -1) cout << ":(" << "\n";
        else cout << ans << "\n";
    }
    return 0;
}
