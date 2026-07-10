#!/usr/bin/env python3
import sys
from random import Random

# a311 generator.
#
# The input is the "skeleton": operators and parentheses only. Variables
# (blanks) are implicit; the judge inserts one wherever an operand is
# expected. Grammar (left-assoc, '*' tighter than '+'):
#   expr -> term ('+' term)*
#   term -> fact ('*' fact)*
#   fact -> var | '(' expr ')'
# A var contributes 0 chars; '+'/'*' contribute 1; a paren pair contributes 2.
# So reachable skeleton lengths are exactly all non-negative integers.
#
# We build a random expression tree whose skeleton has exactly L chars, then
# emit the skeleton. L is kept small and covers edge cases (0, pure '+',
# pure '*', nested parens, mixed).

def main():
    if len(sys.argv) < 2:
        sys.stderr.write("usage: a311_gen.py <seed>\n")
        sys.exit(1)
    rng = Random(int(sys.argv[1]))

    r = rng.random()
    if r < 0.12:
        L = 0                       # bare variable
    elif r < 0.24:
        L = 1                       # single operator
    elif r < 0.40:
        L = rng.randint(0, 4)
    elif r < 0.70:
        L = rng.randint(0, 9)
    else:
        L = rng.randint(0, 16)
    L = min(L, 30)

    # node = {'t': 'var'|'op'|'paren', 'l', 'r', 'op'}
    nodes = [{'t': 'var', 'l': -1, 'r': -1, 'op': None}]
    slots = [0]  # indices of 'var' nodes that may be expanded

    def size_of(idx):
        nd = nodes[idx]
        if nd['t'] == 'var':
            return 0
        if nd['t'] == 'op':
            return 1 + size_of(nd['l']) + size_of(nd['r'])
        return 2 + size_of(nd['l'])

    def leaf_count(idx):
        nd = nodes[idx]
        if nd['t'] == 'var':
            return 1
        if nd['t'] == 'op':
            return leaf_count(nd['l']) + leaf_count(nd['r'])
        return leaf_count(nd['l'])

    def emit(idx):
        nd = nodes[idx]
        if nd['t'] == 'var':
            return ''
        if nd['t'] == 'op':
            return emit(nd['l']) + nd['op'] + emit(nd['r'])
        return '(' + emit(nd['l']) + ')'

    guard = 0
    while True:
        cur = size_of(0)
        if cur >= L or not slots:
            break
        remaining = L - cur
        leaves = leaf_count(0)
        choices = []
        if remaining >= 1:
            choices.append('op')
        if remaining >= 2:
            choices.append('paren')
        if not choices:
            break
        # Keep variable count bounded so brute (2^vars) stays fast.
        if leaves >= 14:
            pick = 'paren' if ('paren' in choices and rng.random() < 0.85) else 'op'
        else:
            pick = rng.choice(choices)

        si = rng.randrange(len(slots))
        slot_idx = slots[si]
        slots[si] = slots[-1]
        slots.pop()

        if pick == 'op':
            op_ch = rng.choice(['+', '*'])
            li = len(nodes); nodes.append({'t': 'var', 'l': -1, 'r': -1, 'op': None})
            ri = len(nodes); nodes.append({'t': 'var', 'l': -1, 'r': -1, 'op': None})
            nodes[slot_idx] = {'t': 'op', 'l': li, 'r': ri, 'op': op_ch}
            slots.append(li); slots.append(ri)
        else:
            ci = len(nodes); nodes.append({'t': 'var', 'l': -1, 'r': -1, 'op': None})
            nodes[slot_idx] = {'t': 'paren', 'l': ci, 'r': -1, 'op': None}
            slots.append(ci)

        guard += 1
        if guard > 100000:
            break

    skeleton = emit(0)
    L_out = len(skeleton)
    sys.stdout.write(f"{L_out}\n{skeleton}\n")

if __name__ == '__main__':
    main()
