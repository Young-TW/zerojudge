#include <iostream>
#include <vector>

using namespace std;

long long MOD = 1000000007LL;

long long mod_mul(long long a, long long b) {
    return (a * b) % MOD;
}

long long mod_add(long long a, long long b) {
    long long res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = mod_mul(res, base);
        base = mod_mul(base, base);
        exp /= 2;
    }
    return res;
}

long long mod_inverse(long long n) {
    return power(n, MOD - 2);
}

// Calculate sum_{k=0}^{n-1} r^k
long long geometric_sum(long long r, long long n) {
    if (n == 0) return 0;
    if (r == 0) return 1; // 1 + 0 + ... = 1 for n>=1, but loop is k=0 to 0 -> r^0=1.
    // Wait, if r=0: sum is 1 (k=0) + 0 + ... = 1.
    // My formula (r^n - 1)/(r-1) fails for r=1.
    if (r == 1) {
        return n % MOD;
    }
    long long num = power(r, n);
    num = (num - 1 + MOD) % MOD;
    long long den = mod_inverse((r - 1 + MOD) % MOD);
    return mod_mul(num, den);
}

// Calculate value at index k (0-based) for sequence defined by s, a, c
// val(0) = s
// val(k) = a * val(k-1) + c
// val(k) = s * a^k + c * (a^{k-1} + ... + 1) if k>=1
// val(k) = s * a^k + c * geometric_sum(a, k)
long long get_val(long long k, long long s, long long a, long long c) {
    if (k == 0) return s;
    long long term1 = mod_mul(s, power(a, k));
    long long term2 = mod_mul(c, geometric_sum(a, k));
    return mod_add(term1, term2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    int q;
    
    if (!(cin >> n >> q)) return 0;

    long long sA, aA, cA;
    long long sB, aB, cB;
    
    cin >> sA >> aA >> cA >> sB >> aB >> cB;

    // Precompute powers and geometric sums coefficients if possible?
    // No, n is up to 1e9, but queries are 5e5.
    // We need O(1) or O(log MOD) per query.
    // The formula derived:
    // C_ij = sum_{k=0}^{n-1} A(i, k) * B(k, j)
    // A(i, k) corresponds to index idxA = i*n + k
    // B(k, j) corresponds to index idxB = k*n + j
    
    // Let's re-evaluate the sum structure.
    // A_{ik} = ValA(i*n + k)
    // B_{kj} = ValB(k*n + j)
    // ValA(x) = sA * aA^x + cA * S_aA(x) where S_a(x) = sum_{t=0}^{x-1} a^t
    // ValB(y) = sB * aB^y + cB * S_aB(y)
    
    // This looks like it might be too complex to simplify into a closed form without iterating if aA, aB are arbitrary.
    // However, notice the constraints: n up to 1e9. We cannot iterate k from 0 to n-1.
    // We must find a closed form for sum_{k=0}^{n-1} [ (sA * aA^(i*n+k) + ...) * (sB * aB^(k*n+j) + ...) ]
    
    // Let's expand the product. There are 4 terms.
    // Term 1: (sA * aA^(i*n+k)) * (sB * aB^(k*n+j))
    //       = sA * sB * aA^(i*n) * aB^j * (aA * aB^n)^k
    // This is a geometric series in k! Sum_{k=0}^{n-1} R^k where R = aA * aB^n.
    
    // Term 2: (sA * aA^(i*n+k)) * (cB * S_aB(k*n+j))
    // S_aB(x) = (aB^x - 1)/(aB-1) if aB != 1.
    // So this involves sum of aA^k * (aB^(k*n+j) - 1).
    // = sum aA^k * aB^(k*n) * aB^j - sum aA^k
    // = aB^j * sum (aA * aB^n)^k - sum aA^k.
    // Both are geometric series.
    
    // Term 3: (cA * S_aA(i*n+k)) * (sB * aB^(k*n+j))
    // S_aA(x) = (aA^x - 1)/(aA-1).
    // Involves sum (aA^(i*n+k) - 1) * aB^(k*n+j)
    // = sum aA^(i*n) * aA^k * aB^(k*n) * aB^j - sum aB^(k*n+j)
    // = aA^(i*n)*aB^j * sum (aA*aB^n)^k - aB^j * sum (aB^n)^k.
    // Geometric series.
    
    // Term 4: (cA * S_aA(i*n+k)) * (cB * S_aB(k*n+j))
    // Product of two sums.
    // S_aA(...) * S_aB(...) = [(aA^(i*n+k)-1)/(aA-1)] * [(aB^(k*n+j)-1)/(aB-1)]
    // Numerator: (aA^(i*n) * aA^k - 1) * (aB^j * aB^(n*k) - 1)
    // = aA^(i*n)*aB^j * (aA*aB^n)^k - aA^(i*n)*aA^k - aB^j*aB^(n*k) + 1
    // All terms are geometric series in k.
    
    // Conclusion: The entire sum can be computed as a linear combination of geometric series sums.
    // We need to handle cases where ratio R == 1 separately (sum is n).
    // Ratios involved:
    // R1 = aA * aB^n
    // R2 = aA
    // R3 = aB^n
    // R4 = 1 (constant term)
    
    // Constants needed:
    // pow_aB_n = aB^n
    // pow_aA_in = aA^(i*n) -- depends on i
    // pow_aB_j = aB^j -- depends on j
    
    // Let's define a function to compute Sum_{k=0}^{n-1} r^k
    // Already have geometric_sum(r, n).
    
    // Coefficients calculation:
    // Let invA = (aA == 1) ? 0 : mod_inverse(aA - 1); // Careful with division by zero logic later
    // Let invB = (aB == 1) ? 0 : mod_inverse(aB - 1);
    
    // Actually, better to handle aA==1 and aB==1 inside the term expansion logically or use the generic geometric_sum which handles r=1.
    // geometric_sum(r, n) returns sum_{k=0}^{n-1} r^k.
    
    // Precompute common values:
    long long pow_aB_n = power(aB, n);
    
    // Denominators for the S_a expansions
    long long denA = 1;
    bool aA_is_1 = (aA == 1);
    if (!aA_is_1) denA = mod_inverse((aA - 1 + MOD) % MOD);
    
    long long denB = 1;
    bool aB_is_1 = (aB == 1);
    if (!aB_is_1) denB = mod_inverse((aB - 1 + MOD) % MOD);

    for (int k_query = 0; k_query < q; ++k_query) {
        long long i, j;
        cin >> i >> j;
        
        // Dependencies on i, j
        long long pow_aA_in = power(aA, (i % MOD) * (n % MOD) % (MOD-1)); 
        // Wait, exponent modulo MOD-1 only works if base is not 0? 
        // Fermat's Little Theorem: a^(p-1) = 1 mod p. So exponents are mod p-1.
        // But n can be large, so we must take n % (MOD-1).
        // However, i*n can be huge. i < n <= 1e9. i*n <= 1e18.
        // We need (i*n) % (MOD-1).
        // MOD = 1e9+7 is prime. MOD-1 = 1e9+6.
        long long exp_A_in = ( (i % (MOD-1)) * (n % (MOD-1)) ) % (MOD-1);
        long long val_aA_in = power(aA, exp_A_in);
        
        long long exp_B_j = j % (MOD-1);
        long long val_aB_j = power(aB, exp_B_j);
        
        long long ans = 0;
        
        // We need sums for specific ratios:
        // R1 = aA * aB^n
        long long R1 = mod_mul(aA, pow_aB_n);
        long long S1 = geometric_sum(R1, n);
        
        // R2 = aA
        long long S2 = geometric_sum(aA, n);
        
        // R3 = aB^n
        long long S3 = geometric_sum(pow_aB_n, n);
        
        // R4 = 1
        long long S4 = n % MOD; // geometric_sum(1, n)
        
        // Now assemble the 4 terms.
        // Recall:
        // A_ik = sA * aA^(in+k) + cA * (aA^(in+k) - 1) * invA   [if aA!=1]
        //      = sA * aA^in * aA^k + cA * invA * (aA^in * aA^k - 1)
        //      = (sA + cA*invA) * aA^in * aA^k - cA*invA
        // Let K_A = (sA + cA*invA) % MOD. If aA==1, A_ik = sA + cA*(in+k). This breaks the geometric form slightly?
        // Wait, if aA=1:
        // val(k) = s + c*k.
        // Then A_ik = sA + cA*(i*n+k).
        // B_kj = sB + cB*(k*n+j) if aB=1.
        // Product is quadratic in k. Sum of k, k^2.
        // My previous derivation assumed aA != 1 and aB != 1 to use the geometric series form for the "c" part.
        // I need to handle cases where aA=1 or aB=1 separately or unify them.
        
        // Unified approach:
        // Val(x) = s * a^x + c * (a^x - 1) * inv(a-1)  IF a != 1
        // Val(x) = s + c*x                            IF a == 1
        // Since there are only 4 combinations of (aA==1, aB==1), maybe just branch?
        // Or stick to the algebraic expansion which naturally handles limits?
        // No, division by zero is real.
        // Let's branch based on aA==1 and aB==1.
        
        long long term_total = 0;
        
        if (aA_is_1 && aB_is_1) {
            // A_ik = sA + cA*(i*n + k)
            // B_kj = sB + cB*(k*n + j)
            // Prod = (sA + cA*i*n + cA*k) * (sB + cB*j + cB*n*k)
            // Let U = sA + cA*i*n
            // Let V = cA
            // Let X = sB + cB*j
            // Let Y = cB*n
            // Prod = (U + V*k) * (X + Y*k) = U*X + (U*Y + V*X)*k + V*Y*k^2
            // Sum = n*(U*X) + (U*Y + V*X)*sum(k) + V*Y*sum(k^2)
            
            long long U = (sA + mod_mul(cA, (i % MOD) * (n % MOD) % MOD)) % MOD;
            long long V = cA;
            long long X = (sB + mod_mul(cB, j)) % MOD;
            long long Y = mod_mul(cB, n % MOD);
            
            long long sum_k = (n % MOD) * ((n - 1) % MOD) % MOD * mod_inverse(2) % MOD;
            // sum k^2 = n(n+1)(2n+1)/6
            long long n_mod = n % MOD;
            long long sum_k2 = n_mod * ((n_mod + 1) % MOD) % MOD;
            sum_k2 = sum_k2 * ((2 * n_mod + 1) % MOD) % MOD;
            sum_k2 = sum_k2 * mod_inverse(6) % MOD;
            
            long long t1 = mod_mul(U % MOD, X % MOD);
            t1 = mod_mul(t1, n_mod);
            
            long long coeff_k = (mod_mul(U % MOD, Y) + mod_mul(V, X % MOD)) % MOD;
            long long t2 = mod_mul(coeff_k, sum_k);
            
            long long coeff_k2 = mod_mul(V, Y);
            long long t3 = mod_mul(coeff_k2, sum_k2);
            
            term_total = (t1 + t2) % MOD;
            term_total = (term_total + t3) % MOD;
        } else if (aA_is_1 && !aB_is_1) {
            // A_ik = sA + cA*(i*n + k) = U + V*k
            // B_kj = sB * aB^(kn+j) + cB * (aB^(kn+j) - 1) * invB
            //      = sB * aB^j * (aB^n)^k + cB * invB * (aB^j * (aB^n)^k - 1)
            //      = (sB + cB*invB) * aB^j * (aB^n)^k - cB*invB
            // Let W = (sB + cB*invB) % MOD * aB^j % MOD
            // Let Z = cB*invB % MOD
            // B_kj = W * (aB^n)^k - Z
            
            // Prod = (U + V*k) * (W * R3^k - Z) where R3 = aB^n
            //      = U*W*R3^k - U*Z + V*W*k*R3^k - V*Z*k
            // Sum = U*W*S3 - U*Z*n + V*W*Sum(k*R3^k) - V*Z*Sum(k)
            
            long long U = (sA + mod_mul(cA, (i % MOD) * (n % MOD) % MOD)) % MOD;
            long long V = cA;
            
            long long invB_val = denB;
            long long coeffB = (sB + mod_mul(cB, invB_val)) % MOD;
            long long W = mod_mul(coeffB, val_aB_j);
            long long Z = mod_mul(cB, invB_val);
            
            long long R3 = pow_aB_n;
            
            // Need Sum_{k=0}^{n-1} k * r^k
            // Formula: r * (1 - (n+1)r^n + n*r^(n+1)) / (1-r)^2
            auto arith_geo_sum = [&](long long r, long long count) -> long long {
                if (count == 0) return 0;
                if (r == 0) return 0; // 0*1 + 1*0... = 0? No. k=0 term is 0. k=1 term 1*0=0. All 0.
                if (r == 1) {
                    // Sum k = n(n-1)/2
                    long long nm = count % MOD;
                    return nm * ((nm - 1 + MOD) % MOD) % MOD * mod_inverse(2) % MOD;
                }
                long long rn = power(r, count); // r^n
                long long rn1 = mod_mul(rn, r); // r^(n+1)
                
                long long num = (1 - mod_mul(count + 1, rn) + MOD) % MOD;
                num = (num + mod_mul(count % MOD, rn1)) % MOD;
                
                long long den = (1 - r + MOD) % MOD;
                den = mod_mul(den, den);
                den = mod_inverse(den);
                
                return mod_mul(mod_mul(r, num), den);
            };
            
            long long sum_kR3 = arith_geo_sum(R3, n);
            long long sum_k = (n % MOD) * ((n - 1) % MOD) % MOD * mod_inverse(2) % MOD;
            long long S3_val = S3; // precomputed
            
            long long t1 = mod_mul(mod_mul(U, W), S3_val);
            long long t2 = mod_mul(mod_mul(U, Z), n % MOD);
            long long t3 = mod_mul(mod_mul(V, W), sum_kR3);
            long long t4 = mod_mul(mod_mul(V, Z), sum_k);
            
            term_total = (t1 - t2 + MOD) % MOD;
            term_total = (term_total + t3) % MOD;
            term_total = (term_total - t4 + MOD) % MOD;
            
        } else if (!aA_is_1 && aB_is_1) {
            // Symmetric to above
            // A_ik = (sA + cA*invA) * aA^(in) * aA^k - cA*invA
            //      = K * aA^in * aA^k - L
            // Let M = (sA + cA*invA) * aA^in
            // Let L = cA*invA
            // A_ik = M * aA^k - L
            
            // B_kj = sB + cB*(kn+j) = X + Y*k
            // X = sB + cB*j
            // Y = cB*n
            
            // Prod = (M * aA^k - L) * (X + Y*k)
            //      = M*X*aA^k + M*Y*k*aA^k - L*X - L*Y*k
            
            long long invA_val = denA;
            long long coeffA = (sA + mod_mul(cA, invA_val)) % MOD;
            long long M = mod_mul(coeffA, val_aA_in);
            long long L = mod_mul(cA, invA_val);
            
            long long X = (sB + mod_mul(cB, j)) % MOD;
            long long Y = mod_mul(cB, n % MOD);
            
            long long R2 = aA;
            
            auto arith_geo_sum = [&](long long r, long long count) -> long long {
                if (count == 0) return 0;
                if (r == 0) return 0;
                if (r == 1) {
                    long long nm = count % MOD;
                    return nm * ((nm - 1 + MOD) % MOD) % MOD * mod_inverse(2) % MOD;
                }
                long long rn = power(r, count);
                long long rn1 = mod_mul(rn, r);
                long long num = (1 - mod_mul(count + 1, rn) + MOD) % MOD;
                num = (num + mod_mul(count % MOD, rn1)) % MOD;
                long long den = (1 - r + MOD) % MOD;
                den = mod_mul(den, den);
                den = mod_inverse(den);
                return mod_mul(mod_mul(r, num), den);
            };
            
            long long sum_aAk = S2; // precomputed
            long long sum_k_aAk = arith_geo_sum(R2, n);
            long long sum_k = (n % MOD) * ((n - 1) % MOD) % MOD * mod_inverse(2) % MOD;
            
            long long t1 = mod_mul(mod_mul(M, X), sum_aAk);
            long long t2 = mod_mul(mod_mul(M, Y), sum_k_aAk);
            long long t3 = mod_mul(mod_mul(L, X), n % MOD);
            long long t4 = mod_mul(mod_mul(L, Y), sum_k);
            
            term_total = (t1 + t2) % MOD;
            term_total = (term_total - t3 + MOD) % MOD;
            term_total = (term_total - t4 + MOD) % MOD;
            
        } else {
            // Neither is 1
            // A_ik = M * aA^k - L
            // M = (sA + cA*invA) * aA^(in)
            // L = cA*invA
            
            // B_kj = W * (aB^n)^k - Z
            // W = (sB + cB*invB) * aB^j
            // Z = cB*invB
            
            // Prod = (M * aA^k - L) * (W * R3^k - Z) where R3 = aB^n
            //      = M*W * (aA * R3)^k - M*Z * aA^k - L*W * R3^k + L*Z
            
            long long invA_val = denA;
            long long coeffA = (sA + mod_mul(cA, invA_val)) % MOD;
            long long M = mod_mul(coeffA, val_aA_in);
            long long L = mod_mul(cA, invA_val);
            
            long long invB_val = denB;
            long long coeffB = (sB + mod_mul(cB, invB_val)) % MOD;
            long long W = mod_mul(coeffB, val_aB_j);
            long long Z = mod_mul(cB, invB_val);
            
            long long R3 = pow_aB_n;
            long long R1 = mod_mul(aA, R3);
            
            long long S_R1 = S1; // sum (aA * aB^n)^k
            long long S_R2 = S2; // sum aA^k
            long long S_R3 = S3; // sum (aB^n)^k
            long long S_const = n % MOD;
            
            long long t1 = mod_mul(mod_mul(M, W), S_R1);
            long long t2 = mod_mul(mod_mul(M, Z), S_R2);
            long long t3 = mod_mul(mod_mul(L, W), S_R3);
            long long t4 = mod_mul(mod_mul(L, Z), S_const);
            
            term_total = (t1 - t2 + MOD) % MOD;
            term_total = (term_total - t3 + MOD) % MOD;
            term_total = (term_total + t4) % MOD;
        }
        
        cout << term_total << "\n";
    }

    return 0;
}
