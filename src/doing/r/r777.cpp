#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int get_score(const string& rank) {
    if (rank == "J" || rank == "Q" || rank == "K" || rank == "A") return 10;
    return stoi(rank);
}

int get_rank_value(const string& rank) {
    if (rank == "2") return 2;
    if (rank == "3") return 3;
    if (rank == "4") return 4;
    if (rank == "5") return 5;
    if (rank == "6") return 6;
    if (rank == "7") return 7;
    if (rank == "8") return 8;
    if (rank == "9") return 9;
    if (rank == "10") return 10;
    if (rank == "J") return 11;
    if (rank == "Q") return 12;
    if (rank == "K") return 13;
    if (rank == "A") return 14;
    return 0;
}

bool is_straight(const vector<string>& ranks) {
    if (ranks.size() != 5) return false;
    vector<int> values;
    for (const auto& r : ranks) {
        values.push_back(get_rank_value(r));
    }
    sort(values.begin(), values.end());
    
    // Check for normal straight
    bool consecutive = true;
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[i] != values[i-1] + 1) {
            consecutive = false;
            break;
        }
    }
    if (consecutive) return true;
    
    return false;
}

long long get_divisors_sum(long long n) {
    if (n <= 0) return 0;
    long long sum = 0;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int count_set_bits(long long n) {
    if (n < 0) n = -n; 
    int count = 0;
    unsigned long long un = static_cast<unsigned long long>(n);
    while (un > 0) {
        if (un & 1) count++;
        un >>= 1;
    }
    return count;
}

long long get_superfactor_product(long long n) {
    if (n == 0) return 0;
    if (n < 0) n = -n;
    
    long long result = 1;
    long long temp = n;
    
    for (long long i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            long long power = 1;
            while (temp % i == 0) {
                power *= i;
                temp /= i;
            }
            result *= power;
        }
    }
    if (temp > 1) {
        result *= temp;
    }
    return result;
}

int main() {
    string card;
    vector<string> hand_ranks;
    vector<string> hand_suits;
    
    while (cin >> card) {
        hand_ranks.clear();
        hand_suits.clear();
        
        // Parse first card
        string rank, suit;
        if (card.size() == 2) {
            rank = card.substr(0, 1);
            suit = card.substr(1, 1);
        } else if (card.size() == 3) {
            rank = card.substr(0, 2);
            suit = card.substr(2, 1);
        } else {
            continue;
        }
        hand_ranks.push_back(rank);
        hand_suits.push_back(suit);
        
        // Read remaining 4 cards
        for (int i = 0; i < 4; ++i) {
            cin >> card;
            if (card.size() == 2) {
                rank = card.substr(0, 1);
                suit = card.substr(1, 1);
            } else if (card.size() == 3) {
                rank = card.substr(0, 2);
                suit = card.substr(2, 1);
            }
            hand_ranks.push_back(rank);
            hand_suits.push_back(suit);
        }
        
        // Calculate initial value
        long long value = 0;
        for (const auto& r : hand_ranks) {
            value += get_score(r);
        }
        
        vector<bool> rule_modified(14, false);
        int modified_count = 0;
        int last_modified_rule = -1;
        
        // Rule 1
        if (hand_ranks.size() >= 4) {
            value += 1;
            int j_count = 0;
            for (const auto& r : hand_ranks) {
                if (r == "J") j_count++;
            }
            value += j_count * get_score(hand_ranks[0]);
            rule_modified[0] = true;
            modified_count++;
            last_modified_rule = 0;
        }
        
        // Rule 2
        map<string, int> suit_count;
        for (const auto& s : hand_suits) {
            suit_count[s]++;
        }
        bool has_two_same_suit = false;
        for (const auto& p : suit_count) {
            if (p.second >= 2) {
                has_two_same_suit = true;
                break;
            }
        }
        if (has_two_same_suit) {
            value *= 2;
            rule_modified[1] = true;
            modified_count++;
            last_modified_rule = 1;
        }
        
        // Rule 3
        if (suit_count.size() == 4) {
            value *= 2;
            rule_modified[2] = true;
            modified_count++;
            last_modified_rule = 2;
        }
        
        // Rule 4
        int black_count = 0;
        int red_count = 0;
        for (const auto& s : hand_suits) {
            if (s == "C" || s == "S") black_count++;
            else if (s == "H" || s == "D") red_count++;
        }
        if (black_count != red_count) {
            value += abs(black_count - red_count);
            rule_modified[3] = true;
            modified_count++;
            last_modified_rule = 3;
        }
        
        // Rule 5
        if (value % 2 == 0) {
            value += get_divisors_sum(value);
            rule_modified[4] = true;
            modified_count++;
            last_modified_rule = 4;
        }
        
        // Rule 6
        int seven_count = 0;
        for (const auto& r : hand_ranks) {
            if (r == "7") seven_count++;
        }
        if (seven_count == 4) {
            value -= 112;
            rule_modified[5] = true;
            modified_count++;
            last_modified_rule = 5;
        }
        
        // Rule 7
        if (value >= 0) {
            int min_score = 100;
            for (const auto& r : hand_ranks) {
                min_score = min(min_score, get_score(r));
            }
            value += min_score;
            rule_modified[6] = true;
            modified_count++;
            last_modified_rule = 6;
        }
        
        // Rule 8
        if (value < 0) {
            value *= -1;
            rule_modified[7] = true;
            modified_count++;
            last_modified_rule = 7;
        }
        
        // Rule 9
        int diamond_count = 0;
        for (const auto& s : hand_suits) {
            if (s == "D") diamond_count++;
        }
        if (diamond_count >= 3) {
            value += 1;
            rule_modified[8] = true;
            modified_count++;
            last_modified_rule = 8;
            
            for (size_t i = 0; i < hand_ranks.size(); ++i) {
                if (hand_ranks[i] == "6") hand_ranks[i] = "9";
                else if (hand_ranks[i] == "9") hand_ranks[i] = "6";
                else if (hand_ranks[i] == "2") hand_ranks[i] = "5";
                else if (hand_ranks[i] == "5") hand_ranks[i] = "2";
            }
        }
        
        // Rule 10
        if (is_straight(hand_ranks)) {
            int a_count = 0;
            for (const auto& r : hand_ranks) {
                if (r == "A") a_count++;
            }
            value += 5LL * a_count;
            rule_modified[9] = true;
            modified_count++;
            last_modified_rule = 9;
        }
        
        // Rule 11
        if (modified_count > 8) {
            value += count_set_bits(value);
            rule_modified[10] = true;
            modified_count++;
            last_modified_rule = 10;
        }
        
        // Rule 12
        bool has_two = false;
        for (const auto& r : hand_ranks) {
            if (r == "2") {
                has_two = true;
                break;
            }
        }
        if (has_two && last_modified_rule != -1) {
            int rule_to_apply = last_modified_rule;
            
            if (rule_to_apply == 0) {
                if (hand_ranks.size() >= 4) {
                    value += 1;
                    int j_count = 0;
                    for (const auto& r : hand_ranks) {
                        if (r == "J") j_count++;
                    }
                    value += j_count * get_score(hand_ranks[0]);
                }
            } else if (rule_to_apply == 1) {
                map<string, int> sc;
                for (const auto& s : hand_suits) sc[s]++;
                bool hts = false;
                for (const auto& p : sc) {
                    if (p.second >= 2) { hts = true; break; }
                }
                if (hts) value *= 2;
            } else if (rule_to_apply == 2) {
                map<string, int> sc;
                for (const auto& s : hand_suits) sc[s]++;
                if (sc.size() == 4) value *= 2;
            } else if (rule_to_apply == 3) {
                int bc = 0, rc = 0;
                for (const auto& s : hand_suits) {
                    if (s == "C" || s == "S") bc++;
                    else if (s == "H" || s == "D") rc++;
                }
                if (bc != rc) value += abs(bc - rc);
            } else if (rule_to_apply == 4) {
                if (value % 2 == 0) value += get_divisors_sum(value);
            } else if (rule_to_apply == 5) {
                int sc = 0;
                for (const auto& r : hand_ranks) if (r == "7") sc++;
                if (sc == 4) value -= 112;
            } else if (rule_to_apply == 6) {
                if (value >= 0) {
                    int ms = 100;
                    for (const auto& r : hand_ranks) ms = min(ms, get_score(r));
                    value += ms;
                }
            } else if (rule_to_apply == 7) {
                if (value < 0) value *= -1;
            } else if (rule_to_apply == 8) {
                int dc = 0;
                for (const auto& s : hand_suits) if (s == "D") dc++;
                if (dc >= 3) {
                    value += 1;
                    for (size_t i = 0; i < hand_ranks.size(); ++i) {
                        if (hand_ranks[i] == "6") hand_ranks[i] = "9";
                        else if (hand_ranks[i] == "9") hand_ranks[i] = "6";
                        else if (hand_ranks[i] == "2") hand_ranks[i] = "5";
                        else if (hand_ranks[i] == "5") hand_ranks[i] = "2";
                    }
                }
            } else if (rule_to_apply == 9) {
                if (is_straight(hand_ranks)) {
                    int ac = 0;
                    for (const auto& r : hand_ranks) if (r == "A") ac++;
                    value += 5LL * ac;
                }
            } else if (rule_to_apply == 10) {
                if (modified_count > 8) value += count_set_bits(value);
            }
            
            rule_modified[11] = true;
            modified_count++;
            last_modified_rule = 11;
        }
        
        // Rule 13
        has_two = false;
        for (const auto& r : hand_ranks) {
            if (r == "2") {
                has_two = true;
                break;
            }
        }
        if (has_two) {
            value += get_superfactor_product(value);
            rule_modified[12] = true;
            modified_count++;
            last_modified_rule = 12;
        }
        
        // Rule 14 is just a check, no modification
        
        cout << value << endl;
    }
    
    return 0;
}
