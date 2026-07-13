#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int numerator, denominator;
    while (cin >> numerator >> denominator) {
        if (numerator == 0 && denominator == 0) break;
        
        string decimal = ".";
        vector<int> remainders(denominator, -1);
        int remainder = numerator % denominator;
        
        int repeat_start = -1;
        int pos = 0;
        
        if (remainder == 0) {
            decimal += "0";
        } else {
            remainders[remainder] = 0;
            pos = 1;
            
            while (true) {
                remainder *= 10;
                int digit = remainder / denominator;
                decimal += to_string(digit);
                remainder %= denominator;
                
                if (remainder == 0) {
                    break;
                }
                
                if (remainders[remainder] != -1) {
                    repeat_start = remainders[remainder];
                    break;
                }
                
                remainders[remainder] = pos;
                pos++;
            }
        }
        
        for (size_t i = 0; i < decimal.length(); i += 50) {
            cout << decimal.substr(i, 50) << endl;
        }
        
        if (remainder == 0) {
            cout << "This expansion terminates." << endl;
        } else {
            int repeat_len = pos - repeat_start;
            cout << "The last " << repeat_len << " digits repeat forever." << endl;
        }
    }
    
    return 0;
}
