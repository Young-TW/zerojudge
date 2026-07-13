#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int MOD = 11;

int mod_inv(int a) {
    a = (a % MOD + MOD) % MOD;
    for (int x = 1; x < MOD; ++x) {
        if ((a * x) % MOD == 1) return x;
    }
    return -1; // Should not happen for valid input
}

vector<vector<int>> inverse_matrix(const vector<vector<int>>& H) {
    int d = H.size();
    vector<vector<int>> inv(d, vector<int>(d, 0));
    if (d == 2) {
        int a = H[0][0], b = H[0][1], c = H[1][0], d_val = H[1][1];
        int det = (a * d_val - b * c) % MOD;
        if (det < 0) det += MOD;
        int det_inv = mod_inv(det);
        inv[0][0] = (d_val * det_inv) % MOD;
        inv[0][1] = ((-b) * det_inv) % MOD;
        inv[1][0] = ((-c) * det_inv) % MOD;
        inv[1][1] = (a * det_inv) % MOD;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                if (inv[i][j] < 0) inv[i][j] += MOD;
    } else if (d == 3) {
        // Compute determinant
        int det = (H[0][0] * (H[1][1]*H[2][2] - H[1][2]*H[2][1])
                 - H[0][1] * (H[1][0]*H[2][2] - H[1][2]*H[2][0])
                 + H[0][2] * (H[1][0]*H[2][1] - H[1][1]*H[2][0])) % MOD;
        if (det < 0) det += MOD;
        int det_inv = mod_inv(det);

        // Compute cofactor matrix
        vector<vector<int>> cofactor(3, vector<int>(3, 0));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int rows[2], cols[2], r = 0, c = 0;
                for (int ii = 0; ii < 3; ++ii) if (ii != i) rows[r++] = ii;
                for (int jj = 0; jj < 3; ++jj) if (jj != j) cols[c++] = jj;
                int minor_det = (H[rows[0]][cols[0]] * H[rows[1]][cols[1]]
                               - H[rows[0]][cols[1]] * H[rows[1]][cols[0]]) % MOD;
                if (minor_det < 0) minor_det += MOD;
                int sign = ((i + j) % 2 == 0) ? 1 : -1;
                cofactor[i][j] = (sign * minor_det) % MOD;
                if (cofactor[i][j] < 0) cofactor[i][j] += MOD;
            }
        }
        // Adjugate is transpose of cofactor
        vector<vector<int>> adj(3, vector<int>(3, 0));
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                adj[i][j] = cofactor[j][i];
        // Multiply by det_inv
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                inv[i][j] = (adj[i][j] * det_inv) % MOD;
    }
    return inv;
}

string decrypt(const string& enc, const vector<vector<int>>& inv, int d) {
    string dec;
    for (int i = 0; i < 12; i += d) {
        vector<int> vec(d);
        for (int j = 0; j < d; ++j) {
            char c = enc[i + j];
            vec[j] = (c == ':') ? 10 : (c - '0');
        }
        vector<int> res(d, 0);
        for (int r = 0; r < d; ++r) {
            int sum = 0;
            for (int c = 0; c < d; ++c) {
                sum += inv[r][c] * vec[c];
            }
            res[r] = sum % MOD;
            if (res[r] < 0) res[r] += MOD;
        }
        for (int r = 0; r < d; ++r) {
            dec += (res[r] == 10) ? ':' : char('0' + res[r]);
        }
    }
    return dec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    cout << setw(4) << T << '\n';

    for (int tc = 0; tc < T; ++tc) {
        int d;
        cin >> d;
        vector<vector<int>> H(d, vector<int>(d));
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < d; ++j)
                cin >> H[i][j];

        string enc;
        cin >> enc;

        vector<vector<int>> inv = inverse_matrix(H);

        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < d; ++j) {
                cout << setw(4) << inv[i][j];
            }
            cout << '\n';
        }

        string dec = decrypt(enc, inv, d);
        cout << dec << '\n';
    }

    return 0;
}
