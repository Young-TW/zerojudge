#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> nums;
    int n, k, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> k;
        switch (k) {
            case 1:
                cin >> x;
                nums.push(x);
                break;
            case 2:
                if (nums.empty())
                    cout << "-1" << endl;
                else
                    cout << nums.front() << endl;
                break;
            case 3:
                if (nums.empty())
                    break;
                else
                    nums.pop();
                break;
        }
    }
    return 0;
}