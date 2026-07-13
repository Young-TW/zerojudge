#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        long long count = 0;
        
        // 使用 map 來記錄每個數字出現的次數
        // 對於每個起始點 i，我們向右擴展到 j
        // 並維護一個計數器，記錄當前子陣列中出現奇數次的數字個數
        // 以及一個 flag 表示是否所有出現的數字都是奇數次
        
        for (int i = 0; i < N; ++i) {
            map<int, int> freq;
            int odd_count = 0; // 記錄出現奇數次的數字種類數
            int total_types = 0; // 記錄總共出現過的數字種類數
            
            for (int j = i; j < N; ++j) {
                int num = A[j];
                
                if (freq.find(num) == freq.end()) {
                    freq[num] = 1;
                    odd_count++;
                    total_types++;
                } else {
                    if (freq[num] % 2 == 1) {
                        // 原本是奇數，現在變成偶數
                        odd_count--;
                    } else {
                        // 原本是偶數，現在變成奇數
                        odd_count++;
                    }
                    freq[num]++;
                }
                
                // 如果所有出現過的數字都是奇數次，則這個子陣列符合条件
                if (odd_count == total_types) {
                    count++;
                }
            }
        }
        
        cout << count << "\n";
    }

    return 0;
}
