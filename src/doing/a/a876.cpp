#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Cage {
    int target;
    char op;
    vector<int> cells;
    int filled_count;
    int current_sum;
    int current_prod;
};

int grid[81];
bool row_used[9][10];
bool col_used[9][10];

bool dfs(int idx, int N, vector<Cage>& cages, vector<int>& cage_id) {
    if (idx == N * N) {
        return true;
    }
    int r = idx / N;
    int c = idx % N;
    int cid = cage_id[idx];
    for (int v = 1; v <= N; ++v) {
        if (row_used[r][v] || col_used[c][v]) continue;
        
        grid[idx] = v;
        row_used[r][v] = true;
        col_used[c][v] = true;
        
        Cage& cg = cages[cid];
        cg.filled_count++;
        int prev_sum = cg.current_sum;
        int prev_prod = cg.current_prod;
        cg.current_sum += v;
        cg.current_prod *= v;
        
        bool valid = true;
        if (cg.op == '+') {
            int remaining = (int)cg.cells.size() - cg.filled_count;
            if (cg.current_sum + remaining > cg.target) valid = false;
            else if (cg.current_sum + remaining * N < cg.target) valid = false;
            else if (cg.filled_count == (int)cg.cells.size() && cg.current_sum != cg.target) valid = false;
        } else if (cg.op == '*') {
            int remaining = (int)cg.cells.size() - cg.filled_count;
            if (cg.current_prod > cg.target) valid = false;
            else if (cg.target % cg.current_prod != 0) valid = false;
            else {
                long long max_p = cg.current_prod;
                for (int i = 0; i < remaining; ++i) max_p *= N;
                if (max_p < cg.target) valid = false;
                else if (cg.filled_count == (int)cg.cells.size() && cg.current_prod != cg.target) valid = false;
            }
        } else if (cg.op == '-') {
            if (cg.filled_count == 1) {
                bool ok = false;
                if (v + cg.target <= N) ok = true;
                if (v - cg.target >= 1) ok = true;
                if (!ok) valid = false;
            } else if (cg.filled_count == 2) {
                int a = grid[cg.cells[0]];
                int b = grid[cg.cells[1]];
                int diff = a - b;
                if (diff < 0) diff = -diff;
                if (diff != cg.target) valid = false;
            }
        } else if (cg.op == '/') {
            if (cg.filled_count == 1) {
                bool ok = false;
                if (v * cg.target <= N) ok = true;
                if (v % cg.target == 0 && v / cg.target >= 1) ok = true;
                if (!ok) valid = false;
            } else if (cg.filled_count == 2) {
                int a = grid[cg.cells[0]];
                int b = grid[cg.cells[1]];
                int mx = a > b ? a : b;
                int mn = a < b ? a : b;
                if (mn == 0 || mx % mn != 0 || mx / mn != cg.target) valid = false;
            }
        }
        
        if (valid) {
            if (dfs(idx + 1, N, cages, cage_id)) return true;
        }
        
        cg.current_sum = prev_sum;
        cg.current_prod = prev_prod;
        cg.filled_count--;
        row_used[r][v] = false;
        col_used[c][v] = false;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<Cage> cages(M);
        vector<int> cage_id(N * N, -1);
        for (int i = 0; i < M; ++i) {
            int a;
            cin >> cages[i].target >> cages[i].op >> a;
            cages[i].cells.resize(a);
            for (int j = 0; j < a; ++j) {
                int pos;
                cin >> pos;
                cages[i].cells[j] = pos - 1;
                cage_id[pos - 1] = i;
            }
            cages[i].filled_count = 0;
            cages[i].current_sum = 0;
            cages[i].current_prod = 1;
        }
        
        for(int i=0; i<9; ++i) {
            for(int j=0; j<10; ++j) {
                row_used[i][j] = false;
                col_used[i][j] = false;
            }
        }
        
        dfs(0, N, cages, cage_id);
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << grid[i * N + j];
                if (j == N - 1) cout << "\n";
                else cout << " ";
            }
        }
    }
    return 0;
}
