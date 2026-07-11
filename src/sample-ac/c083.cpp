#include <iostream>
#include <vector>
using namespace std;

bool simulate(int n, int k, int start) {
    vector<int> person_at(n + 1);
    vector<int> next_alive(n + 1), prev_alive(n + 1);
    for (int i = 1; i <= n; i++) {
        person_at[i] = i;
        next_alive[i] = (i % n) + 1;
        prev_alive[i] = (i - 2 + n) % n + 1;
    }
    int remaining = n;
    int current = start;
    int last_kill = -1;
    int phase = 0; // 0 = kill, 1 = move
    while (remaining > 1) {
        if (phase == 0) { // Kill phase
            int steps = (k - 1) % remaining;
            int target = current;
            for (int s = 0; s < steps; s++) target = next_alive[target];
            int kill_pos = target;
            int next_current = next_alive[kill_pos];
            // Remove kill_pos from the circle
            next_alive[prev_alive[kill_pos]] = next_alive[kill_pos];
            prev_alive[next_alive[kill_pos]] = prev_alive[kill_pos];
            person_at[kill_pos] = 0;
            remaining--;
            last_kill = kill_pos;
            current = next_current;
            phase = 1;
        } else { // Move phase
            int steps = (k - 1) % remaining;
            int target = current;
            for (int s = 0; s < steps; s++) target = next_alive[target];
            int mover_pos = target;
            int mover_person = person_at[mover_pos];
            // Remove mover_pos from the circle
            next_alive[prev_alive[mover_pos]] = next_alive[mover_pos];
            prev_alive[next_alive[mover_pos]] = prev_alive[mover_pos];
            person_at[mover_pos] = 0;
            // Insert last_kill back into the circle at its original position
            int next_ins = last_kill % n + 1;
            while (person_at[next_ins] == 0) next_ins = next_ins % n + 1;
            int prev_ins = (last_kill - 2 + n) % n + 1;
            while (person_at[prev_ins] == 0) prev_ins = (prev_ins - 2 + n) % n + 1;
            next_alive[prev_ins] = last_kill;
            prev_alive[last_kill] = prev_ins;
            next_alive[last_kill] = next_ins;
            prev_alive[next_ins] = last_kill;
            person_at[last_kill] = mover_person;
            current = next_ins;
            phase = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (person_at[i] != 0) return person_at[i] == 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            if (simulate(n, k, i)) {
                ans = i;
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
