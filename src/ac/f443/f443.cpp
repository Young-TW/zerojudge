#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<int> sales(N), id(N);
        for (int i = 0; i < N; i++) cin >> sales[i];
        for (int i = 0; i < N; i++) cin >> id[i];
        int i = 0;
        while (i < N) {
            if (sales[i] == -1) { i++; continue; }
            int j = i;
            while (j < N && sales[j] != -1) j++;
            // 區間 [i, j)，左右都有隔板才調整
            bool leftDiv = (i > 0);
            bool rightDiv = (j < N);
            if (leftDiv && rightDiv) {
                int mn = i, mx = i;
                for (int k = i; k < j; k++) {
                    if (sales[k] < sales[mn]) mn = k;
                    if (sales[k] > sales[mx]) mx = k;
                }
                swap(sales[mn], sales[mx]);
                swap(id[mn], id[mx]);
            }
            i = j;
        }
        for (int k = 0; k < N; k++) cout << id[k] << " ";
        cout << "\n";
    }
    return 0;
}
