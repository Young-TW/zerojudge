#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool comp(char a, char b) {
    char la = (a >= 'a' && a <= 'z') ? a - ('a' - 'A') : a;
    char lb = (b >= 'a' && b <= 'z') ? b - ('a' - 'A') : b;
    if (la != lb) return la < lb;
    return a < b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        while (n--) {
            string s;
            cin >> s;
            sort(s.begin(), s.end(), comp);
            do {
                cout << s << "\n";
            } while (next_permutation(s.begin(), s.end(), comp));
        }
    }
    return 0;
}
