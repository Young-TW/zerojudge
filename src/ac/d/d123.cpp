#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    int case_num = 1;
    while (cin >> N) {
        int arr[105];
        bool is_b2 = true;
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        
        if (arr[0] < 1) {
            is_b2 = false;
        }
        for (int i = 1; i < N && is_b2; ++i) {
            if (arr[i] <= arr[i-1]) {
                is_b2 = false;
            }
        }
        
        if (is_b2) {
            bool seen[20005] = {false};
            for (int i = 0; i < N && is_b2; ++i) {
                for (int j = i; j < N && is_b2; ++j) {
                    int sum = arr[i] + arr[j];
                    if (seen[sum]) {
                        is_b2 = false;
                    } else {
                        seen[sum] = true;
                    }
                }
            }
        }
        
        cout << "Case #" << case_num << ": ";
        if (is_b2) {
            cout << "It is a B2-Sequence.\n";
        } else {
            cout << "It is not a B2-Sequence.\n";
        }
        cout << "\n";
        case_num++;
    }
    
    return 0;
}
