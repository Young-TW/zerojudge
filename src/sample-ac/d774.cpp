#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Candidate {
    int id;
    int score;
};

bool cmp(const Candidate& a, const Candidate& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<Candidate> cands(n);
        for (int i = 0; i < n; ++i) {
            cin >> cands[i].id >> cands[i].score;
        }
        
        sort(cands.begin(), cands.end(), cmp);
        
        int line_idx = m * 3 / 2;
        int line_score = cands[line_idx - 1].score;
        
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (cands[i].score >= line_score) {
                count++;
            } else {
                break;
            }
        }
        
        cout << line_score << " " << count << "\n";
        for (int i = 0; i < count; ++i) {
            cout << cands[i].id << " " << cands[i].score << "\n";
        }
    }
    
    return 0;
}
