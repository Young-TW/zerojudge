#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char step;
    char phone[10];
    int sh, sm, eh, em;
    
    int rate_int[5][3] = {
        {10, 6, 2},
        {25, 15, 5},
        {53, 33, 13},
        {87, 47, 17},
        {144, 80, 30}
    };
    
    while (cin >> step && step != '#') {
        cin >> phone >> sh >> sm >> eh >> em;
        int start_mins = sh * 60 + sm;
        int end_mins = eh * 60 + em;
        if (end_mins <= start_mins) {
            end_mins += 1440;
        }
        
        int day = 0, evening = 0, night = 0;
        for (int i = start_mins; i < end_mins; ++i) {
            int t = i % 1440;
            if (t >= 480 && t < 1080) {
                day++;
            } else if (t >= 1080 && t < 1320) {
                evening++;
            } else {
                night++;
            }
        }
        
        int idx = step - 'A';
        int total_cents = day * rate_int[idx][0] + evening * rate_int[idx][1] + night * rate_int[idx][2];
        
        printf("%10s%6d%6d%6d%3c%8.2f\n", phone, day, evening, night, step, total_cents / 100.0);
    }
    
    return 0;
}
