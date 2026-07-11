#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            vector<int> cards(5);
            for (int j = 0; j < 5; j++) cin >> cards[j];
            
            vector<int> ranks(5), suits(5);
            for (int j = 0; j < 5; j++) {
                ranks[j] = (cards[j] - 1) % 13 + 1;
                suits[j] = (cards[j] - 1) / 13;
            }
            
            bool flush = true;
            for (int j = 1; j < 5; j++) {
                if (suits[j] != suits[0]) { flush = false; break; }
            }
            
            vector<int> sr = ranks;
            sort(sr.begin(), sr.end());
            
            bool straight = false;
            bool normal = true;
            for (int j = 1; j < 5; j++) {
                if (sr[j] != sr[j-1] + 1) { normal = false; break; }
            }
            if (normal) straight = true;
            if (!straight) {
                if (sr[0]==1 && sr[1]==10 && sr[2]==11 && sr[3]==12 && sr[4]==13) {
                    straight = true;
                }
            }
            
            map<int,int> freq;
            for (int r : ranks) freq[r]++;
            vector<int> counts;
            for (auto& p : freq) counts.push_back(p.second);
            sort(counts.rbegin(), counts.rend());
            
            int score = 0;
            if (flush && straight) score = 7;
            else if (counts[0] == 4) score = 6;
            else if (counts[0] == 3 && counts.size() >= 2 && counts[1] == 2) score = 5;
            else if (straight) score = 4;
            else if (counts[0] == 3) score = 3;
            else if (counts[0] == 2 && counts.size() >= 2 && counts[1] == 2) score = 2;
            else if (counts[0] == 2) score = 1;
            else score = 0;
            
            cout << score << "\n";
        }
    }
    return 0;
}
