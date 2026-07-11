#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int popcount(int x) {
    int c = 0;
    while (x) {
        c += x & 1;
        x >>= 1;
    }
    return c;
}

int getRank(const vector<string>& cards) {
    vector<int> nums;
    vector<char> suits;
    for (const auto& c : cards) {
        char r = c[0];
        char s = c[1];
        int n;
        if (r == 'A') n = 14;
        else if (r == 'T') n = 10;
        else if (r == 'J') n = 11;
        else if (r == 'Q') n = 12;
        else if (r == 'K') n = 13;
        else n = r - '0';
        nums.push_back(n);
        suits.push_back(s);
    }
    sort(nums.begin(), nums.end());
    
    bool flush = true;
    for (int i = 1; i < 5; i++) {
        if (suits[i] != suits[0]) flush = false;
    }
    
    bool straight = false;
    if (nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2] && nums[2] + 1 == nums[3] && nums[3] + 1 == nums[4]) {
        straight = true;
    }
    if (nums[0] == 2 && nums[1] == 3 && nums[2] == 4 && nums[3] == 5 && nums[4] == 14) {
        straight = true;
    }
    
    if (straight && flush) return 9;
    
    int cnt[15] = {0};
    for (int n : nums) cnt[n]++;
    vector<int> freqs;
    for (int i = 2; i <= 14; i++) {
        if (cnt[i] > 0) freqs.push_back(cnt[i]);
    }
    sort(freqs.rbegin(), freqs.rend());
    
    if (freqs[0] == 4) return 8;
    if (freqs[0] == 3 && freqs[1] == 2) return 7;
    if (flush) return 6;
    if (straight) return 5;
    if (freqs[0] == 3) return 4;
    if (freqs[0] == 2 && freqs[1] == 2) return 3;
    if (freqs[0] == 2) return 2;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string names[] = {"", "highest-card", "one-pair", "two-pairs", "three-of-a-kind", "straight", "flush", "full-house", "four-of-a-kind", "straight-flush"};
    
    string card;
    while (cin >> card) {
        vector<string> hand(5), deck(5);
        hand[0] = card;
        for (int i = 1; i < 5; i++) cin >> hand[i];
        for (int i = 0; i < 5; i++) cin >> deck[i];
        
        int best = 0;
        for (int k = 0; k <= 5; k++) {
            for (int mask = 0; mask < (1 << 5); mask++) {
                if (popcount(mask) != 5 - k) continue;
                vector<string> cur;
                for (int i = 0; i < 5; i++) {
                    if (mask & (1 << i)) {
                        cur.push_back(hand[i]);
                    }
                }
                for (int i = 0; i < k; i++) {
                    cur.push_back(deck[i]);
                }
                int rank = getRank(cur);
                if (rank > best) {
                    best = rank;
                }
            }
        }
        
        cout << "Hand: ";
        for (int i = 0; i < 5; i++) {
            if (i > 0) cout << " ";
            cout << hand[i];
        }
        cout << " Deck: ";
        for (int i = 0; i < 5; i++) {
            if (i > 0) cout << " ";
            cout << deck[i];
        }
        cout << " Best hand: " << names[best] << "\n";
    }
    
    return 0;
}
