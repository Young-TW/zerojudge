#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 10000000;
char mu[MAXN + 1];
long long sum_mu[MAXN + 1];
int primes[700000];
char is_composite[MAXN + 1];
int prime_count = 0;

void sieve() {
    mu[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (!is_composite[i]) {
            primes[prime_count++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < prime_count && (long long)i * primes[j] <= MAXN; ++j) {
            is_composite[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            } else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= MAXN; ++i) {
        sum_mu[i] = sum_mu[i - 1] + mu[i];
    }
}

char input_buf[1 << 22];
int input_pos = 0, input_len = 0;

inline int readInt() {
    int x = 0;
    while (input_pos < input_len && (input_buf[input_pos] < '0' || input_buf[input_pos] > '9')) {
        input_pos++;
    }
    while (input_pos < input_len && input_buf[input_pos] >= '0' && input_buf[input_pos] <= '9') {
        x = (x << 3) + (x << 1) + (input_buf[input_pos] - '0');
        input_pos++;
    }
    return x;
}

char output_buf[1 << 22];
int output_pos = 0;

inline void writeLongLong(long long x) {
    if (x == 0) {
        output_buf[output_pos++] = '0';
    } else {
        char temp[20];
        int ptr = 0;
        while (x > 0) {
            temp[ptr++] = (x % 10) + '0';
            x /= 10;
        }
        while (ptr > 0) {
            output_buf[output_pos++] = temp[--ptr];
        }
    }
    output_buf[output_pos++] = '\n';
}

int main() {
    input_len = fread(input_buf, 1, sizeof(input_buf), stdin);
    sieve();
    int T = readInt();
    while (T--) {
        int n = readInt();
        int m = readInt();
        long long ans = 0;
        int min_nm = n < m ? n : m;
        for (int l = 1, r; l <= min_nm; l = r + 1) {
            r = n / (n / l);
            int r_m = m / (m / l);
            if (r_m < r) r = r_m;
            ans += (sum_mu[r] - sum_mu[l - 1]) * (long long)(n / l) * (m / l);
        }
        writeLongLong(ans);
    }
    fwrite(output_buf, 1, output_pos, stdout);
    return 0;
}
