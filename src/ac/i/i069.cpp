#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        long long sum = 0;
        int mx = 0, mn = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
            if (a[i] > a[mx]) mx = i;
            if (a[i] < a[mn]) mn = i;
        }
        long long avg = sum / n;
        long long d = a[mx] - avg;
        a[mx] -= d;
        a[mn] += d;
        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
