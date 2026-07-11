#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Peanut {
    int count;
    int row;
    int col;
};

int main() {
    int M, N, K;
    bool first = true;
    while (cin >> M >> N >> K) {
        vector<Peanut> peanuts;
        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                int p;
                cin >> p;
                if (p > 0) {
                    Peanut pt;
                    pt.count = p;
                    pt.row = i;
                    pt.col = j;
                    peanuts.push_back(pt);
                }
            }
        }
        sort(peanuts.begin(), peanuts.end(), [](const Peanut& a, const Peanut& b) {
            return a.count > b.count;
        });
        
        int time_spent = 0;
        int total = 0;
        int cr = 0, cc = 0;
        
        for (size_t i = 0; i < peanuts.size(); i++) {
            int p = peanuts[i].count;
            int r = peanuts[i].row;
            int c = peanuts[i].col;
            
            int time_to_reach;
            if (cr == 0) {
                time_to_reach = r;
            } else {
                time_to_reach = abs(r - cr) + abs(c - cc);
            }
            
            int time_to_return = r;
            
            if (time_spent + time_to_reach + 1 + time_to_return <= K) {
                time_spent += time_to_reach + 1;
                total += p;
                cr = r;
                cc = c;
            } else {
                break;
            }
        }
        
        if (!first) cout << "\n";
        cout << total << "\n";
        first = false;
    }
    
    return 0;
}
