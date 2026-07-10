#include <iostream>
using namespace std;

// a081: NOI2000 Day2.2 青蛙过河 (Frog crossing river)
//
// Model recap (faithful to the problem statement):
//   - A pier (stone block, A / S1..Sn / D) holds a stack: the bottom frog sits
//     directly on the pier and every frog above sits on the back of the frog
//     exactly one size larger. So a pier always holds a contiguous block of
//     consecutive sizes, bottom = largest, top = smallest (Tower-of-Hanoi-like).
//   - A lotus leaf holds at most one frog.
//   - Only the top frog of a pier, or the lone frog on a leaf, may jump.
//   - A frog may land on an empty pier, on the back of a frog one size larger
//     (i.e. on top of a pier whose top is exactly f+1), or on an empty leaf.
//   - Left bank A: out-edges only (no frog returns to A).
//   - Right bank D: in-edges only (no frog leaves D).
//   - River center (S1..Sn, Y1..Ym): fully connected among themselves and to D.
//
// Derivation of F(n, m) = 2^n * (m + 1):
//
// Let F(n, m) = max number of frogs that can cross given n river-center stone
// piers and m lotus leaves (A and D are always present).
//
// Base case n = 0 (no river-center pier, only leaves):
//   Only one pier in the river system (D) may hold a stack. Leaves hold one frog
//   each and can serve as a "holding buffer" only for the single smallest frog:
//   to move the stack off A onto D the stack must be reversed, and with m leaves
//   you can temporarily park m frogs, allowing m+1 frogs total to land on D
//   (the (m+1)-th frog goes straight A->D). Hence F(0, m) = m + 1.
//
// Inductive step: F(n, m) = 2 * F(n-1, m).
//   To move a maximal stack from A across, you must reverse it onto D. With one
//   extra river-center pier S available as a *second stack*, you split the work:
//   move the top half of A onto S (reversed), then the bottom frog of A onto D,
//   then move the stack on S onto D (reversed again -> back to original order).
//   Each "move a stack of size k between two piers using n-1 auxiliary piers and
//   m leaves" is exactly the same subproblem; to reverse the order twice
//   (A->S, S->D) you can double the load: the maximal reversible stack size
//   doubles with each additional pier. Formally the Hanoi-style recurrence is
//     F(n, m) = 2 * F(n-1, m),   F(0, m) = m + 1
//   which solves to  F(n, m) = 2^n * (m + 1).
//
// Bounds: n, m <= 25  =>  answer <= 2^25 * 26 = 872'415'232 < 2^31. Fits in
// 32-bit, but we use long long for safety.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    while (cin >> n >> m) {
        long long ans = (1LL << n) * (m + 1);
        cout << ans << "\n";
    }
    return 0;
}
