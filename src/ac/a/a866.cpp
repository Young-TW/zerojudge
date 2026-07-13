#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int count[6] = {0};
    int x;
    while (cin >> x) {
        if (x == 0) {
            int sum = 0;
            int total = 0;
            for (int i = 1; i <= 5; ++i) {
                sum += i * count[i];
                total += count[i];
            }
            
            for (int i = 5; i >= 1; --i) {
                printf("%d (%2d) |", i, count[i]);
                for (int j = 0; j < count[i]; ++j) {
                    printf("=");
                }
                printf("\n");
            }
            
            if (total > 0) {
                printf("Average rating: %.4f\n", (double)sum / total);
            } else {
                printf("Average rating: 0.0000\n");
            }
            
            for (int i = 0; i < 6; ++i) {
                count[i] = 0;
            }
        } else if (x >= 1 && x <= 5) {
            count[x]++;
        }
    }
    return 0;
}
