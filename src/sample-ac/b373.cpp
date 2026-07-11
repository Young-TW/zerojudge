#include <iostream>
#include <vector>

using namespace std;

long long mergeSort(vector<int>& arr, vector<int>& temp, int l, int r) {
    if (l >= r) return 0;
    int mid = l + (r - l) / 2;
    long long cnt = mergeSort(arr, temp, l, mid) + mergeSort(arr, temp, mid + 1, r);
    
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            cnt += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int m = l; m <= r; ++m) {
        arr[m] = temp[m];
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        vector<int> temp(N);
        cout << mergeSort(arr, temp, 0, N - 1) << "\n";
    }
    return 0;
}
