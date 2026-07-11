#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 100005;
const int MAXM = 1000005;

int n, m;
int s[MAXN];
int block_size;
int block_id[MAXN];
int freq[MAXN];
int max_freq;
int count_max;

struct Query {
    int l, r, id;
    int block_l;
};

bool compareQueries(const Query& a, const Query& b) {
    if (a.block_l != b.block_l) {
        return a.block_l < b.block_l;
    }
    return (a.block_l & 1) ? (a.r < b.r) : (a.r > b.r);
}

struct Result {
    int max_freq;
    int count_max;
};

Result results[MAXM];

void add(int pos) {
    int val = s[pos];
    freq[val]++;
    if (freq[val] > max_freq) {
        max_freq = freq[val];
        count_max = 1;
    } else if (freq[val] == max_freq) {
        count_max++;
    }
}

void remove(int pos) {
    int val = s[pos];
    if (freq[val] == max_freq) {
        count_max--;
    }
    freq[val]--;
    if (count_max == 0 && max_freq > 0) {
        max_freq--;
        count_max = 0;
        // 這種情況下需要重新計算 count_max，因為可能有其他數字也達到了新的 max_freq
        // 但在 Mo's algorithm 中，我們通常避免這種情況，或者使用更複雜的數據結構
        // 對於這題，我們可以簡化處理：當 count_max 變為 0 時，max_freq 減 1
        // 然後我們需要檢查是否有其他數字的頻率等於新的 max_freq
        // 由於我們不能遍歷所有數字，這裡採用一個技巧：
        // 實際上在標準 Mo's algorithm 中，如果只維護 max_freq 和 count_max，
        // 當 remove 操作導致 count_max 變為 0 時，我們無法高效地更新 max_freq。
        // 因此，我們需要改變策略。
        
        // 重新思考：我們不能在 remove 時高效更新 max_freq 和 count_max。
        // 這意味著標準的 Mo's algorithm 不直接適用於這個問題。
        // 我們需要一個不同的方法。
        
        // 讓我們回到問題本身。我們需要找到區間眾數的出現次數和有多少種數字出現最多次。
        // 這是一個經典問題，可以使用 Mo's algorithm 配合一些技巧來解決。
        // 但是，由於 remove 操作的困難，我們需要一個更高效的方法。
        
        // 另一種方法是使用線段樹或平方分解，但這些方法可能過於複雜。
        // 讓我們嘗試使用 Mo's algorithm，但改進 remove 操作。
        
        // 實際上，我們可以發現，當我們 remove 一個元素時，如果它的頻率等於 max_freq，
        // 那麼 max_freq 可能會減少，也可能不會。如果有多個數字的頻率等於 max_freq，
        // 那麼 max_freq 不會減少。只有當該數字是唯一一個頻率等於 max_freq 的數字時，
        // max_freq 才會減少。
        
        // 但是，即使 max_freq 減少，我們也不知道新的 max_freq 是多少，除非我們遍歷所有數字。
        // 這使得標準的 Mo's algorithm 不適用。
        
        // 讓我們考慮一個不同的方法：使用平方分解，但對每個塊預處理一些信息。
        // 或者，我們可以嘗試使用一個更簡單的觀察：對於每個查詢，我們可以暴力計算眾數，
        // 但這會太慢。
        
        // 實際上，這個問題可以使用 Mo's algorithm 解決，但需要一個巧妙的技巧。
        // 我們可以在 add 操作時正常更新 max_freq 和 count_max。
        // 在 remove 操作時，如果 freq[val] == max_freq - 1 且 count_max == 0，
        // 那麼我們將 max_freq 減 1，並將 count_max 設為 1（因為 val 現在是唯一的候選者）。
        // 但這仍然不正確，因為可能有其他數字也具有 freq == max_freq - 1。
        
        // 讓我們放棄這個想法，並尋找一個已知的解決方案。
        // 經過研究，這個問題可以使用 Mo's algorithm 解決，但需要一個額外的數組來記錄每個頻率的數字數量。
        // 讓我們定義 cnt_freq[f] 為頻率為 f 的數字數量。
        // 當我們 add 一個數字時，我們更新 freq[val]，cnt_freq[freq[val]-1]--，cnt_freq[freq[val]]++。
        // 然後，我們從當前 max_freq 開始向下檢查，直到找到第一個 cnt_freq[f] > 0 的 f。
        // 但這仍然可能很慢。
        
        // 實際上，有一個更簡單的方法：我們不需要在 remove 時立即更新 max_freq。
        // 我們可以在每次查詢結束時，從當前 max_freq 開始向下檢查，直到找到正確的 max_freq。
        // 但這也會很慢。
        
        // 讓我們嘗試另一個方法：使用一個棧來記錄 max_freq 的變化。
        // 但這也很複雜。
        
        // 經過進一步思考，我意識到這個問題確實可以使用 Mo's algorithm 解決，
        // 但需要一個巧妙的觀察：我們不需要在 remove 時精確更新 max_freq 和 count_max。
        // 相反，我們可以在每次查詢時，從當前 max_freq 開始向下檢查，直到找到正確的 max_freq。
        // 但這仍然可能很慢。
        
        // 實際上，有一個已知的解決方案：使用 Mo's algorithm 配合一個額外的數組來記錄每個頻率的數字數量。
        // 讓我們定義 cnt_freq[f] 為頻率為 f 的數字數量。
        // 當我們 add 一個數字時：
        //   old_freq = freq[val]
        //   new_freq = old_freq + 1
        //   freq[val] = new_freq
        //   if (old_freq > 0) cnt_freq[old_freq]--
        //   cnt_freq[new_freq]++
        //   if (new_freq > max_freq) max_freq = new_freq
        // 當我們 remove 一個數字時：
        //   old_freq = freq[val]
        //   new_freq = old_freq - 1
        //   freq[val] = new_freq
        //   cnt_freq[old_freq]--
        //   if (new_freq > 0) cnt_freq[new_freq]++
        //   if (cnt_freq[max_freq] == 0) max_freq--
        // 然後，count_max = cnt_freq[max_freq]
        
        // 這個方法是正確的，並且可以在 O(1) 時間內完成 add 和 remove 操作。
        // 讓我們實現這個方法。
    }
}

// 重新定義全局變量以支持新的方法
int cnt_freq[MAXN]; // cnt_freq[f] = 頻率為 f 的數字數量

void add_new(int pos) {
    int val = s[pos];
    int old_freq = freq[val];
    int new_freq = old_freq + 1;
    
    freq[val] = new_freq;
    if (old_freq > 0) {
        cnt_freq[old_freq]--;
    }
    cnt_freq[new_freq]++;
    
    if (new_freq > max_freq) {
        max_freq = new_freq;
    }
}

void remove_new(int pos) {
    int val = s[pos];
    int old_freq = freq[val];
    int new_freq = old_freq - 1;
    
    freq[val] = new_freq;
    cnt_freq[old_freq]--;
    if (new_freq > 0) {
        cnt_freq[new_freq]++;
    }
    
    if (cnt_freq[max_freq] == 0) {
        max_freq--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n >> m)) return 0;
    
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    
    block_size = sqrt(n);
    vector<Query> queries(m);
    
    for (int i = 0; i < m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
        queries[i].block_l = queries[i].l / block_size;
    }
    
    sort(queries.begin(), queries.end(), compareQueries);
    
    memset(freq, 0, sizeof(freq));
    memset(cnt_freq, 0, sizeof(cnt_freq));
    max_freq = 0;
    count_max = 0;
    
    int current_l = 1;
    int current_r = 0;
    
    for (int i = 0; i < m; i++) {
        int L = queries[i].l;
        int R = queries[i].r;
        
        while (current_l > L) {
            current_l--;
            add_new(current_l);
        }
        while (current_r < R) {
            current_r++;
            add_new(current_r);
        }
        while (current_l < L) {
            remove_new(current_l);
            current_l++;
        }
        while (current_r > R) {
            remove_new(current_r);
            current_r--;
        }
        
        results[queries[i].id].max_freq = max_freq;
        results[queries[i].id].count_max = cnt_freq[max_freq];
    }
    
    for (int i = 0; i < m; i++) {
        cout << results[i].max_freq << " " << results[i].count_max << "\n";
    }
    
    return 0;
}
