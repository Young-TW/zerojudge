#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    string s;
    while(cin >> s){
        int last[256];
        bool seen[256];
        for(int i = 0; i < 256; i++){
            last[i] = -1;
            seen[i] = false;
        }
        int n = (int)s.size();
        for(int i = 0; i < n; i++){
            unsigned char c = (unsigned char)s[i];
            last[c] = i;
            seen[c] = true;
        }
        vector<int> chars;          // already in ascending ASCII order
        for(int i = 0; i < 256; i++){
            if(seen[i]) chars.push_back(i);
        }
        vector<int> order = chars;  // sort by last occurrence
        sort(order.begin(), order.end(), [&](int a, int b){
            return last[a] < last[b];
        });
        int rnk[256];
        for(int i = 0; i < (int)order.size(); i++){
            rnk[order[i]] = i + 1;
        }
        string out;
        for(size_t i = 0; i < chars.size(); i++){
            out += to_string(rnk[chars[i]]);
        }
        cout << out << "\n";
    }
    return 0;
}
