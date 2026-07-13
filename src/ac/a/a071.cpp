#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

struct Process {
    long long T, M, P;
    long long start, end;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    while (cin >> N) {
        vector<Process> procs;
        while (true) {
            long long T, M, P;
            cin >> T >> M >> P;
            if (T == 0 && M == 0 && P == 0) break;
            procs.push_back({T, M, P, -1, -1});
        }

        vector<pair<long long, long long>> free_blocks;
        free_blocks.reserve(procs.size() + 1);
        free_blocks.emplace_back(0, N - 1);

        auto try_allocate = [&](long long M) -> long long {
            for (size_t i = 0; i < free_blocks.size(); ++i) {
                long long s = free_blocks[i].first;
                long long e = free_blocks[i].second;
                if (e - s + 1 >= M) {
                    long long allocated_start = s;
                    if (e - s + 1 == M) {
                        free_blocks.erase(free_blocks.begin() + i);
                    } else {
                        free_blocks[i].first = s + M;
                    }
                    return allocated_start;
                }
            }
            return -1;
        };

        auto release = [&](long long start, long long end) {
            auto it = lower_bound(free_blocks.begin(), free_blocks.end(), start,
                [](const pair<long long, long long>& block, long long value) {
                    return block.first < value;
                });
            size_t idx = it - free_blocks.begin();
            bool merged = false;
            if (idx > 0 && free_blocks[idx - 1].second + 1 == start) {
                free_blocks[idx - 1].second = end;
                merged = true;
                if (idx < free_blocks.size() && end + 1 == free_blocks[idx].first) {
                    free_blocks[idx - 1].second = free_blocks[idx].second;
                    free_blocks.erase(free_blocks.begin() + idx);
                }
            } else if (idx < free_blocks.size() && end + 1 == free_blocks[idx].first) {
                free_blocks[idx].first = start;
                merged = true;
            }
            if (!merged) {
                free_blocks.insert(free_blocks.begin() + idx, {start, end});
            }
        };

        long long max_completion = 0;
        int wait_count = 0;
        queue<int> waiting_queue;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> completions;
        size_t next_arrival = 0;
        long long cur_time = 0;

        while (next_arrival < procs.size() || !waiting_queue.empty() || !completions.empty()) {
            long long next_time = LLONG_MAX;
            if (next_arrival < procs.size()) next_time = min(next_time, procs[next_arrival].T);
            if (!completions.empty()) next_time = min(next_time, completions.top().first);
            cur_time = next_time;

            while (!completions.empty() && completions.top().first == cur_time) {
                int pid = completions.top().second;
                completions.pop();
                release(procs[pid].start, procs[pid].end);
            }

            bool allocated = true;
            while (allocated && !waiting_queue.empty()) {
                allocated = false;
                int pid = waiting_queue.front();
                long long start = try_allocate(procs[pid].M);
                if (start != -1) {
                    waiting_queue.pop();
                    allocated = true;
                    procs[pid].start = start;
                    procs[pid].end = start + procs[pid].M - 1;
                    long long comp_time = cur_time + procs[pid].P;
                    completions.push({comp_time, pid});
                    if (comp_time > max_completion) max_completion = comp_time;
                }
            }

            while (next_arrival < procs.size() && procs[next_arrival].T == cur_time) {
                int pid = next_arrival;
                long long start = try_allocate(procs[pid].M);
                if (start != -1) {
                    procs[pid].start = start;
                    procs[pid].end = start + procs[pid].M - 1;
                    long long comp_time = cur_time + procs[pid].P;
                    completions.push({comp_time, pid});
                    if (comp_time > max_completion) max_completion = comp_time;
                } else {
                    waiting_queue.push(pid);
                    wait_count++;
                }
                next_arrival++;
            }
        }

        cout << max_completion << "\n" << wait_count << "\n";
    }
    return 0;
}
