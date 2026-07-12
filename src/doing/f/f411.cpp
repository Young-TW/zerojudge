#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int solve() {
    int n;
    if (!(cin >> n)) return -1; // 表示輸入結束

    vector<int> a(n);
    map<int, int> countMap;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        countMap[a[i]]++;
    }

    // 檢查是否可能形成對稱
    int oddCount = 0;
    for (auto const& [val, count] : countMap) {
        if (count % 2 != 0) {
            oddCount++;
        }
    }

    if ((n % 2 == 0 && oddCount > 0) || (n % 2 == 1 && oddCount > 1)) {
        cout << "Impossible" << endl;
        return 0;
    }

    // 構建目標對稱陣列
    vector<int> target(n);
    vector<int> leftPart;
    int middleVal = -1;

    for (auto const& [val, count] : countMap) {
        if (count % 2 != 0) {
            middleVal = val;
            for (int k = 0; k < count / 2; ++k) {
                leftPart.push_back(val);
            }
        } else {
            for (int k = 0; k < count / 2; ++k) {
                leftPart.push_back(val);
            }
        }
    }

    sort(leftPart.begin(), leftPart.end());

    int idx = 0;
    for (int i = 0; i < n / 2; ++i) {
        target[i] = leftPart[i];
        target[n - 1 - i] = leftPart[i];
    }
    if (n % 2 == 1) {
        target[n / 2] = middleVal;
    }

    // 計算最少交換次數
    // 將問題轉化為：將當前陣列 a 透過相鄰交換變成 target 陣列
    // 這等於計算將 a 中的元素重新排列成 target 所需的逆序對數（考慮相同值的處理）
    
    // 為了處理重複元素，我們需要記錄每個值在 target 中出現的位置順序
    // 然後將 a 中的每個元素映射到它在 target 中對應的索引
    
    vector<int> p(n); // p[i] 表示 a[i] 應該移動到 target 中的哪個位置
    map<int, vector<int>> valPositions;
    
    // 記錄 target 中每個值出現的所有位置
    for (int i = 0; i < n; ++i) {
        valPositions[target[i]].push_back(i);
    }
    
    // 為 a 中的每個元素分配目標位置
    map<int, int> valIndex; // 追蹤每個值已經使用了幾個
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        int posIdx = valIndex[val];
        p[i] = valPositions[val][posIdx];
        valIndex[val]++;
    }
    
    // 計算 p 陣列的逆序對數
    long long inversions = 0;
    vector<int> temp(n);
    
    // 使用歸併排序計算逆序對
    auto mergeSort = [&](auto&& self, int l, int r) -> void {
        if (l >= r) return;
        int mid = l + (r - l) / 2;
        self(self, l, mid);
        self(self, mid + 1, r);
        
        int i = l, j = mid + 1, k = l;
        while (i <= mid && j <= r) {
            if (p[i] <= p[j]) {
                temp[k++] = p[i++];
            } else {
                inversions += (mid - i + 1);
                temp[k++] = p[j++];
            }
        }
        while (i <= mid) temp[k++] = p[i++];
        while (j <= r) temp[k++] = p[j++];
        
        for (int x = l; x <= r; ++x) {
            p[x] = temp[x];
        }
    };
    
    mergeSort(mergeSort, 0, n - 1);
    
    cout << inversions << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (true) {
        int result = solve();
        if (result == -1) break;
    }
    
    return 0;
}
