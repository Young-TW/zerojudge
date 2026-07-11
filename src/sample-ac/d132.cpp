#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int N;
    int game = 0;
    while (cin >> N) {
        if (N == 0) break;
        game++;
        int secret[1005];
        for (int i = 0; i < N; i++) cin >> secret[i];
        cout << "Game " << game << ":" << endl;
        while (true) {
            int guess[1005];
            bool allzero = true;
            for (int i = 0; i < N; i++) {
                cin >> guess[i];
                if (guess[i] != 0) allzero = false;
            }
            if (allzero) break;
            int A = 0, B = 0;
            int cs[10] = {0}, cg[10] = {0};
            for (int i = 0; i < N; i++) {
                if (guess[i] == secret[i]) {
                    A++;
                } else {
                    cs[secret[i]]++;
                    cg[guess[i]]++;
                }
            }
            for (int d = 1; d <= 9; d++) {
                B += min(cs[d], cg[d]);
            }
            printf("    (%d,%d)\n", A, B);
        }
    }
    return 0;
}
