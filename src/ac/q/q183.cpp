#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n;
int total_pairs;
map<int, int> diff_count;

bool solve(vector<int>& result, map<int, int>& counts, int idx) {
    if (idx == n) {
        return true;
    }

    if (counts.empty()) {
        return idx == n;
    }

    int max_diff = counts.rbegin()->first;
    
    // 嘗試將 max_diff 作為新點與 0 的距離 (即新點為 max_diff)
    int candidate1 = max_diff;
    bool possible1 = true;
    vector<int> new_diffs1;
    
    for (int i = 0; i < idx; ++i) {
        int d = abs(candidate1 - result[i]);
        if (counts.find(d) == counts.end() || counts[d] == 0) {
            possible1 = false;
            break;
        }
        new_diffs1.push_back(d);
    }
    
    if (possible1) {
        for (int d : new_diffs1) {
            counts[d]--;
            if (counts[d] == 0) counts.erase(d);
        }
        result[idx] = candidate1;
        if (solve(result, counts, idx + 1)) return true;
        
        // Backtrack
        for (int d : new_diffs1) {
            counts[d]++;
        }
    }

    // 嘗試將 max_diff 作為新點與最大值 (result[idx-1] 假設已排序? 不，最大值是 result 中目前的最大值)
    // 實際上，因為我們是從小到大構建，且 a[0]=0，最大值一定是 diff 中的最大值。
    // 但在遞迴過程中，我們需要知道當前已選集合的最大值。
    // 由於題目要求字典序最小/最大，我們應該固定順序。
    // 對於最小字典序：我們希望前面的數字越小越好。
    // 對於最大字典序：我們希望前面的數字越大越好。
    
    // 重新思考策略：
    // 已知 a[0] = 0。最大的差值 D_max 一定是 max(a) - min(a) = max(a) - 0 = max(a)。
    // 所以陣列中一定包含 0 和 D_max。
    // 接下來，剩下的最大差值 d，必然是某個未決定的點 x 與目前已確定集合中的某個點 y 的距離。
    // 特別是，d 通常是 x 與 0 或 x 與 D_max 的距離（因為這兩個是極端值，最容易產生大距離）。
    // 更精確地說，在每一步，剩下的最大差值 d 必須由新加入的點 x 與目前已選集合中的某個點產生。
    // 為了簡化，我們可以假設新點 x 要嘛是 d (與 0 的距離)，要嘛是 current_max - d (與 current_max 的距離)。
    // 這裡 current_max 是目前已選集合中的最大值。初始時 current_max = D_max。
    
    // 讓我們修正邏輯：
    // 我們維護一個已選點的集合 S。初始 S = {0, max_val}。
    // 每次從剩下的差值中取最大的 d。
    // 這個 d 必須是 |x - s|，其中 x 是新點，s 是 S 中的某點。
    // 關鍵觀察：d 一定是 x 與 S 中最小值 (0) 或最大值 (current_max) 的距離嗎？
    // 不一定，但通常演算法會嘗試這兩種可能性：x = d 或 x = current_max - d。
    // 為什麼？因為如果 d 是最大剩餘差值，它很可能涉及極端點。
    
    // 讓我們用標準的回溯法：
    // 狀態：已選點的列表 sorted_result (包含 0 和 max_val)，以及剩餘的差值計數。
    // 下一步：取剩餘差值中最大的 d。
    // 候選人 x1 = d (假設 d 是 x 與 0 的距離)
    // 候選人 x2 = current_max - d (假設 d 是 x 與 current_max 的距離)
    // 檢查 x1 或 x2 是否能與所有已選點產生存在的差值。
    
    // 注意：我們需要分別求最小字典序和最大字典序。
    // 對於最小字典序：在每個分支點，優先嘗試較小的 x。
    // 對於最大字典序：在每個分支點，優先嘗試較大的 x。
    
    return false;
}

// 重寫一個更清晰的回溯函數
bool backtrack(vector<int>& path, map<int, int>& counts, int n, int current_max, bool find_min) {
    if (path.size() == n) {
        return counts.empty();
    }

    if (counts.empty()) return false;

    int d = counts.rbegin()->first; // 當前最大差值

    // 兩個可能的候選人
    int cand1 = d;             // 假設 d = x - 0
    int cand2 = current_max - d; // 假設 d = current_max - x

    vector<int> candidates;
    if (find_min) {
        if (cand1 >= 0 && cand1 <= current_max) candidates.push_back(cand1);
        if (cand2 >= 0 && cand2 <= current_max && cand2 != cand1) candidates.push_back(cand2);
        sort(candidates.begin(), candidates.end());
    } else {
        if (cand2 >= 0 && cand2 <= current_max) candidates.push_back(cand2);
        if (cand1 >= 0 && cand1 <= current_max && cand1 != cand2) candidates.push_back(cand1);
        sort(candidates.begin(), candidates.end(), greater<int>());
    }

    for (int x : candidates) {
        // 檢查 x 是否有效
        vector<int> needed_diffs;
        bool ok = true;
        for (int val : path) {
            int diff = abs(x - val);
            if (counts.find(diff) == counts.end() || counts[diff] == 0) {
                ok = false;
                break;
            }
            needed_diffs.push_back(diff);
        }

        if (!ok) continue;

        // 使用這個 x
        for (int diff : needed_diffs) {
            counts[diff]--;
            if (counts[diff] == 0) counts.erase(diff);
        }
        path.push_back(x);

        if (backtrack(path, counts, n, current_max, find_min)) return true;

        // 回溯
        path.pop_back();
        for (int diff : needed_diffs) {
            counts[diff]++;
        }
    }

    return false;
}

int main() {
    while (cin >> n) {
        total_pairs = n * (n - 1) / 2;
        diff_count.clear();
        vector<int> diffs(total_pairs);
        int max_val = 0;
        for (int i = 0; i < total_pairs; ++i) {
            cin >> diffs[i];
            diff_count[diffs[i]]++;
            if (diffs[i] > max_val) max_val = diffs[i];
        }

        if (n == 1) {
            cout << "0" << endl;
            cout << "0" << endl;
            continue;
        }

        // 求最小字典序
        map<int, int> counts_min = diff_count;
        vector<int> path_min;
        path_min.push_back(0);
        path_min.push_back(max_val);
        
        // 移除 max_val 對應的差值 (即 max_val - 0)
        counts_min[max_val]--;
        if (counts_min[max_val] == 0) counts_min.erase(max_val);

        backtrack(path_min, counts_min, n, max_val, true);
        sort(path_min.begin(), path_min.end()); // 確保輸出是排序好的？題目範例輸出是排序好的。
        // 題目說 "輸出可以生成該 Δ 的最小與最大字典序陣列"
        // 範例輸出: 0 3 7 -> 這是排序後的結果。
        // 所以我們最後要排序。
        sort(path_min.begin(), path_min.end());
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";
            cout << path_min[i];
        }
        cout << endl;

        // 求最大字典序
        map<int, int> counts_max = diff_count;
        vector<int> path_max;
        path_max.push_back(0);
        path_max.push_back(max_val);
        
        counts_max[max_val]--;
        if (counts_max[max_val] == 0) counts_max.erase(max_val);

        backtrack(path_max, counts_max, n, max_val, false);
        sort(path_max.begin(), path_max.end());
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";
            cout << path_max[i];
        }
        cout << endl;
    }
    return 0;
}
