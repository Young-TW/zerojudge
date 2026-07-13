#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> elements;
    // Reserve approximate memory if needed, but not strictly necessary
    // elements.reserve(200000); 

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int val;
            cin >> val;
            elements.push_back({val, i});
        }
    }

    sort(elements.begin(), elements.end());

    vector<int> count(n, 0);
    int covered_count = 0;
    int min_diff = INT_MAX;

    int left = 0;
    int total_elements = elements.size();

    for (int right = 0; right < total_elements; ++right) {
        int group_r = elements[right].second;
        if (count[group_r] == 0) {
            covered_count++;
        }
        count[group_r]++;

        while (covered_count == n) {
            int current_diff = elements[right].first - elements[left].first;
            if (current_diff < min_diff) {
                min_diff = current_diff;
            }

            int group_l = elements[left].second;
            count[group_l]--;
            if (count[group_l] == 0) {
                covered_count--;
            }
            left++;
        }
    }

    cout << min_diff << endl;

    return 0;
}
