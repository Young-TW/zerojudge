#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> humble(5843);
    humble[1] = 1;
    int p2 = 1, p3 = 1, p5 = 1, p7 = 1;

    for (int i = 2; i <= 5842; ++i) {
        long long next2 = humble[p2] * 2;
        long long next3 = humble[p3] * 3;
        long long next5 = humble[p5] * 5;
        long long next7 = humble[p7] * 7;

        long long next_h = min({next2, next3, next5, next7});
        humble[i] = next_h;

        if (next_h == next2) p2++;
        if (next_h == next3) p3++;
        if (next_h == next5) p5++;
        if (next_h == next7) p7++;
    }

    int n;
    while (cin >> n && n != 0) {
        string suffix;
        if (n % 100 >= 11 && n % 100 <= 13) {
            suffix = "th";
        } else {
            switch (n % 10) {
                case 1: suffix = "st"; break;
                case 2: suffix = "nd"; break;
                case 3: suffix = "rd"; break;
                default: suffix = "th"; break;
            }
        }
        cout << "The " << n << suffix << " humble number is " << humble[n] << ".\n";
    }

    return 0;
}
