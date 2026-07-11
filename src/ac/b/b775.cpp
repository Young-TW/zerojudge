#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<string> mat(N);
        vector<int> outdeg(N, 0);
        for (int i = 0; i < N; ++i) {
            cin >> mat[i];
            for (char c : mat[i]) {
                if (c == '1') outdeg[i]++;
            }
        }
        
        int total_edges = 0;
        for (int i = 0; i < N; ++i) total_edges += outdeg[i];
        vector<int> edges;
        edges.reserve(total_edges);
        vector<int> head(N + 1, 0);
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                if (mat[j][i] == '1') {
                    edges.push_back(i);
                }
            }
            head[j + 1] = edges.size();
        }
        mat.clear();
        mat.shrink_to_fit();
        
        vector<double> q_cur(N, 1.0);
        vector<double> q_next(N);
        
        const double alpha = 0.85;
        const double beta = 0.15;
        
        while (true) {
            double dangling_sum = 0;
            for (int j = 0; j < N; ++j) {
                if (outdeg[j] == 0) {
                    dangling_sum += q_cur[j];
                }
            }
            
            double base = beta + alpha * (dangling_sum / N);
            
            for (int i = 0; i < N; ++i) {
                q_next[i] = base;
            }
            
            for (int j = 0; j < N; ++j) {
                if (outdeg[j] > 0) {
                    double val = alpha * q_cur[j] / outdeg[j];
                    for (int k = head[j]; k < head[j + 1]; ++k) {
                        q_next[edges[k]] += val;
                    }
                }
            }
            
            double diff = 0;
            for (int i = 0; i < N; ++i) {
                double d = q_next[i] - q_cur[i];
                diff += d * d;
            }
            
            q_cur.swap(q_next);
            
            if (sqrt(diff) < 1e-10) {
                break;
            }
        }
        
        for (int i = 0; i < N; ++i) {
            cout << fixed << setprecision(2) << q_cur[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
