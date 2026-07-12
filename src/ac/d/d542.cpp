#include <iostream>
#include <vector>

using namespace std;

long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    long long inv_count = mergeSort(arr, temp, left, mid) + mergeSort(arr, temp, mid + 1, right);
    
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int idx = left; idx <= right; ++idx) {
        arr[idx] = temp[idx];
    }
    return inv_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n && n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        vector<int> temp(n);
        cout << mergeSort(arr, temp, 0, n - 1) << "\n";
    }
    return 0;
}
