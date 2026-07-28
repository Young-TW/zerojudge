#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string addBig(string a, string b) {
    string res = "";
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }
        carry = sum / 10;
        res += (sum % 10) + '0';
    }
    
    reverse(res.begin(), res.end());
    return res;
}

string mulBig(string a, long long b) {
    if (b == 0 || a == "0") return "0";
    
    long long carry = 0;
    string res = "";
    
    for (int i = a.length() - 1; i >= 0; i--) {
        long long prod = (a[i] - '0') * b + carry;
        carry = prod / 10;
        res += (prod % 10) + '0';
    }
    
    while (carry > 0) {
        res += (carry % 10) + '0';
        carry /= 10;
    }
    
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string seqLine, targetLine;
    
    while (getline(cin, seqLine)) {
        if (!getline(cin, targetLine)) break;
        
        string targetStr = "";
        bool started = false;
        for (size_t i = 0; i < targetLine.length(); ++i) {
            if (targetLine[i] != ' ' && targetLine[i] != '\r' && targetLine[i] != '\t') {
                targetStr += targetLine[i];
                started = true;
            } else {
                if (started) break;
            }
        }
        
        long long count = 0;
        string currentNum = "";
        bool inNum = false;
        
        for (size_t i = 0; i < seqLine.length(); ++i) {
            if (seqLine[i] != ' ' && seqLine[i] != '\r' && seqLine[i] != '\t') {
                currentNum += seqLine[i];
                inNum = true;
            } else {
                if (inNum) {
                    if (currentNum == targetStr) {
                        count++;
                    }
                    currentNum = "";
                    inNum = false;
                }
            }
        }
        
        if (inNum) {
            if (currentNum == targetStr) {
                count++;
            }
        }
        
        string sumStr = mulBig(targetStr, count);
        
        cout << count << "\n" << sumStr << "\n";
    }
    
    return 0;
}
