#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }

        for (int k = 1; k <= n; ++k) {
            vector<int> temp;
            int i = 0;
            while (i < n) {
                int j = i;
                vector<int> segment;
                while (j < n && j < i + k) {
                    segment.push_back(a[j]);
                    ++j;
                }
                if (!segment.empty()) {
                    int first = segment[0];
                    for (int idx = 1; idx < segment.size(); ++idx) {
                        temp.push_back(segment[idx]);
                    }
                    if (segment.size() == k) {
                        temp.push_back(first);
                    } else {
                        temp.push_back(first);
                    }
                }
                i = j;
            }
            a = temp;
        }

        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}
