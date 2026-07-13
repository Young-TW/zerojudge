#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

bool canCover(const vector<int>& positions, int K, int diameter) {
    int count = 1;
    int lastPos = positions[0] + diameter;
    for (size_t i = 1; i < positions.size(); ++i) {
        if (positions[i] > lastPos) {
            count++;
            lastPos = positions[i] + diameter;
            if (count > K) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i];
    }

    sort(positions.begin(), positions.end());

    int left = 1;
    int right = positions.back() - positions.front();
    int answer = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canCover(positions, K, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << '\n';

    return 0;
}
