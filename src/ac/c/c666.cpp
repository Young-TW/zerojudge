#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>

const int BASE = 100000000;

struct BigInt {
    std::vector<int> d;
    BigInt() {}
    BigInt(int x) {
        if (x == 0) {
            d.push_back(0);
        } else {
            while (x > 0) {
                d.push_back(x % BASE);
                x /= BASE;
            }
        }
    }
    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }
    BigInt operator*(int x) const {
        BigInt res;
        res.d.reserve(d.size() + 1);
        long long carry = 0;
        for (size_t i = 0; i < d.size(); i++) {
            carry += (long long)d[i] * x;
            res.d.push_back((int)(carry % BASE));
            carry /= BASE;
        }
        while (carry > 0) {
            res.d.push_back((int)(carry % BASE));
            carry /= BASE;
        }
        res.trim();
        return res;
    }
    void print() const {
        std::string out;
        out.reserve(d.size() * 8 + 2);
        char buf[10];
        std::sprintf(buf, "%d", d.back());
        out += buf;
        for (int i = (int)d.size() - 2; i >= 0; i--) {
            std::sprintf(buf, "%08d", d[i]);
            out += buf;
        }
        out += '\n';
        fputs(out.c_str(), stdout);
    }
};

std::vector<int> primes;
bool is_prime[100000];

void get_primes(int count) {
    std::memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; primes.size() < count; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            if ((long long)p * p < 100000) {
                for (long long i = (long long)p * p; i < 100000; i += p) {
                    is_prime[i] = false;
                }
            }
        }
    }
}

std::vector<BigInt> res;

void precompute() {
    get_primes(5000);
    res.resize(5005);
    res[0] = BigInt(1);
    for (int i = 1; i <= 5000; i++) {
        res[i] = res[i - 1] * primes[i - 1];
    }
}

int main() {
    precompute();
    int n;
    while (std::cin >> n) {
        res[n].print();
    }
    return 0;
}
