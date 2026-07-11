#include <iostream>
#include <string>

using namespace std;

long long P(long long n, long long k) {
    if (k < 0 || k > n) return 0;
    long long res = 1;
    for (long long i = 0; i < k; ++i) {
        res *= (n - i);
    }
    return res;
}

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int M;
        string S;
        cin >> M >> S;
        
        long long tiles[256] = {0};
        long long total = 0;
        for (int i = 0; i < M; ++i) {
            char C;
            long long N;
            cin >> C >> N;
            tiles[(unsigned char)C] += N;
            total += N;
        }
        
        long long need[256] = {0};
        for (char c : S) {
            need[(unsigned char)c]++;
        }
        
        long long L = S.length();
        long long ways = 1;
        bool possible = true;
        for (int i = 0; i < 256; ++i) {
            if (need[i] > 0) {
                if (tiles[i] < need[i]) {
                    possible = false;
                    break;
                }
                ways *= P(tiles[i], need[i]);
            }
        }
        
        if (!possible) ways = 0;
        
        long long total_ways = P(total, L);
        
        if (total_ways == 0) {
            cout << "1\n";
            continue;
        }
        
        long long numerator = total_ways - ways;
        long long denominator = total_ways;
        
        long long g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        
        if (denominator == 1) {
            cout << numerator;
        } else {
            cout << numerator << "/" << denominator;
        }
        
        if (2 * ways >= total_ways) {
            cout << " DD真幸運!!我要下注!";
        }
        cout << "\n";
    }
    
    return 0;
}
