#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long val;
    long long L_greater;
    long long R_smaller;
    Node(long long v = 0) : val(v), L_greater(0), R_smaller(0) {}
};

void mergeSort(vector<Node>& arr, vector<Node>& temp, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(arr, temp, l, mid);
    mergeSort(arr, temp, mid + 1, r);
    
    int i = l, j = mid + 1, k = l;
    int left_size = mid + 1;
    int right_size = r + 1;
    
    while (i < left_size && j < right_size) {
        if (arr[i].val <= arr[j].val) {
            arr[i].R_smaller += (j - (mid + 1));
            temp[k++] = arr[i++];
        } else {
            arr[j].L_greater += (left_size - i);
            temp[k++] = arr[j++];
        }
    }
    while (i < left_size) {
        arr[i].R_smaller += (right_size - (mid + 1));
        temp[k++] = arr[i++];
    }
    while (j < right_size) {
        temp[k++] = arr[j++];
    }
    for (int x = l; x <= r; ++x) {
        arr[x] = temp[x];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<Node> arr(n);
        for (int i = 0; i < n; ++i) {
            long long v;
            cin >> v;
            arr[i].val = v;
            arr[i].L_greater = 0;
            arr[i].R_smaller = 0;
        }
        if (n > 0) {
            vector<Node> temp(n);
            mergeSort(arr, temp, 0, n - 1);
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += arr[i].val * (arr[i].L_greater + arr[i].R_smaller);
        }
        cout << ans << "\n";
    }
    return 0;
}
