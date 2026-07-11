#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <cstdio>

using namespace std;

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int n = readInt();
    
    map<tuple<int, int, int>, int> cnt;
    int m = 0;
    
    for (int i = 0; i < n; ++i) {
        int a = readInt();
        int b = readInt();
        int c = readInt();
        int arr[3] = {a, b, c};
        sort(arr, arr + 3);
        if (arr[0] + arr[1] > arr[2]) {
            int g = gcd(arr[0], gcd(arr[1], arr[2]));
            arr[0] /= g;
            arr[1] /= g;
            arr[2] /= g;
            cnt[make_tuple(arr[0], arr[1], arr[2])]++;
            m++;
        }
    }
    
    int max_x = 0;
    for (map<tuple<int, int, int>, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second > max_x) {
            max_x = it->second;
        }
    }
    
    if (max_x > 0) max_x--;
    
    cout << m << " " << max_x << "\n";
    
    return 0;
}
