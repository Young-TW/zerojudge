#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <iterator>

using namespace std;

constexpr uint64_t BASE1 = 1315423911ULL;
constexpr uint64_t BASE2 = 2654435761ULL;

struct Hash128 {
    uint64_t h1, h2;
};

Hash128 compute_hash(const char* s, size_t len) {
    uint64_t h1 = 0, h2 = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = s[i];
        h1 = h1 * BASE1 + c;
        h2 = h2 * BASE2 + c;
    }
    return {h1, h2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read all input
    string data((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    const size_t data_size = data.size();
    size_t pos = 0;
    
    while (true) {
        // Skip whitespace
        while (pos < data_size && isspace(static_cast<unsigned char>(data[pos]))) pos++;
        if (pos >= data_size) break;
        
        // Read n
        long long n = 0;
        while (pos < data_size && isdigit(static_cast<unsigned char>(data[pos]))) {
            n = n * 10 + (data[pos] - '0');
            pos++;
        }
        // Skip whitespace
        while (pos < data_size && isspace(static_cast<unsigned char>(data[pos]))) pos++;
        // Read m
        long long m = 0;
        while (pos < data_size && isdigit(static_cast<unsigned char>(data[pos]))) {
            m = m * 10 + (data[pos] - '0');
            pos++;
        }
        if (n == 0 && m == 0) break;
        
        // Skip to end of line (after newline)
        while (pos < data_size && data[pos] != '\n') pos++;
        if (pos < data_size && data[pos] == '\n') pos++;
        
        long long total_strings = n * m - 1;
        size_t start = pos;
        size_t cur = start;
        
        // First pass: count bits
        int counters[128] = {0};
        for (long long cnt = 0; cnt < total_strings; ++cnt) {
            size_t line_end = cur;
            while (line_end < data_size && data[line_end] != '\n') line_end++;
            size_t line_len = line_end - cur;
            if (line_len > 0 && data[line_end - 1] == '\r') line_len--;
            Hash128 h = compute_hash(data.data() + cur, line_len);
            for (int b = 0; b < 64; ++b) {
                counters[b] += (h.h1 >> b) & 1;
                counters[64 + b] += (h.h2 >> b) & 1;
            }
            if (line_end < data_size && data[line_end] == '\n') line_end++;
            cur = line_end;
        }
        size_t end = cur;
        
        // Compute missing hash
        uint64_t missing_h1 = 0, missing_h2 = 0;
        for (int b = 0; b < 64; ++b) {
            if (counters[b] % m == m - 1) missing_h1 |= (1ULL << b);
        }
        for (int b = 0; b < 64; ++b) {
            if (counters[64 + b] % m == m - 1) missing_h2 |= (1ULL << b);
        }
        
        // Second pass: find missing string
        string missing_str;
        cur = start;
        for (long long cnt = 0; cnt < total_strings; ++cnt) {
            size_t line_end = cur;
            while (line_end < data_size && data[line_end] != '\n') line_end++;
            size_t line_len = line_end - cur;
            if (line_len > 0 && data[line_end - 1] == '\r') line_len--;
            Hash128 h = compute_hash(data.data() + cur, line_len);
            if (h.h1 == missing_h1 && h.h2 == missing_h2) {
                missing_str.assign(data.data() + cur, line_len);
                break;
            }
            if (line_end < data_size && data[line_end] == '\n') line_end++;
            cur = line_end;
        }
        
        cout << missing_str << '\n';
        
        pos = end;
    }
    
    return 0;
}
