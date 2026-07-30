#include <bits/stdc++.h>
using namespace std;

int f[26];
int ans = 0;
vector<int> buf;

void process_segment(int a, int b, int c) {
    int n = buf.size();
    if (n < 3) return;
    
    int lim[3] = {f[a], f[b], f[c]};
    
    // Case 1: all ≤ limits
    {
        int cnt[3] = {0, 0, 0};
        int left = 0;
        for (int right = 0; right < n; right++) {
            cnt[buf[right]]++;
            while (cnt[0] > lim[0] || cnt[1] > lim[1] || cnt[2] > lim[2]) {
                cnt[buf[left]]--;
                left++;
            }
            if (cnt[0] >= 1 && cnt[1] >= 1 && cnt[2] >= 1) {
                int mx = max({cnt[0], cnt[1], cnt[2]});
                if (mx > ans) ans = mx;
            }
        }
    }
    
    // Case 2: char 0 exceeds
    {
        int cnt[3] = {0, 0, 0};
        int left = 0;
        for (int right = 0; right < n; right++) {
            cnt[buf[right]]++;
            while (cnt[1] > lim[1] || cnt[2] > lim[2]) {
                cnt[buf[left]]--;
                left++;
            }
            if (cnt[1] >= 1 && cnt[2] >= 1 && cnt[0] > lim[0]) {
                if (cnt[0] > ans) ans = cnt[0];
            }
        }
    }
    
    // Case 2: char 1 exceeds
    {
        int cnt[3] = {0, 0, 0};
        int left = 0;
        for (int right = 0; right < n; right++) {
            cnt[buf[right]]++;
            while (cnt[0] > lim[0] || cnt[2] > lim[2]) {
                cnt[buf[left]]--;
                left++;
            }
            if (cnt[0] >= 1 && cnt[2] >= 1 && cnt[1] > lim[1]) {
                if (cnt[1] > ans) ans = cnt[1];
            }
        }
    }
    
    // Case 2: char 2 exceeds
    {
        int cnt[3] = {0, 0, 0};
        int left = 0;
        for (int right = 0; right < n; right++) {
            cnt[buf[right]]++;
            while (cnt[0] > lim[0] || cnt[1] > lim[1]) {
                cnt[buf[left]]--;
                left++;
            }
            if (cnt[0] >= 1 && cnt[1] >= 1 && cnt[2] > lim[2]) {
                if (cnt[2] > ans) ans = cnt[2];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    for (int i = 0; i < 26; i++) cin >> f[i];
    
    string s;
    cin >> s;
    
    vector<int> pos[26];
    for (int i = 0; i < N; i++) {
        pos[s[i] - 'a'].push_back(i);
    }
    
    for (int a = 0; a < 26; a++) {
        if (pos[a].empty()) continue;
        for (int b = a + 1; b < 26; b++) {
            if (pos[b].empty()) continue;
            for (int c = b + 1; c < 26; c++) {
                if (pos[c].empty()) continue;
                
                // 3-way merge of pos[a], pos[b], pos[c]
                int ia = 0, ib = 0, ic = 0;
                int na = pos[a].size(), nb = pos[b].size(), nc = pos[c].size();
                int prev_pos = -2;
                
                while (ia < na || ib < nb || ic < nc) {
                    int p = INT_MAX;
                    int ch = -1;
                    if (ia < na && pos[a][ia] < p) { p = pos[a][ia]; ch = 0; }
                    if (ib < nb && pos[b][ib] < p) { p = pos[b][ib]; ch = 1; }
                    if (ic < nc && pos[c][ic] < p) { p = pos[c][ic]; ch = 2; }
                    
                    if (p > prev_pos + 1) {
                        // segment break
                        if (!buf.empty()) {
                            process_segment(a, b, c);
                            buf.clear();
                        }
                    }
                    
                    buf.push_back(ch);
                    prev_pos = p;
                    
                    if (ch == 0) ia++;
                    else if (ch == 1) ib++;
                    else ic++;
                }
                if (!buf.empty()) {
                    process_segment(a, b, c);
                    buf.clear();
                }
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}
