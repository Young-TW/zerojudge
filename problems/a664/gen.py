import sys
import random


def rand_num(rng):
    """Random non-negative operand <= 65535 (problem's stated operand max)."""
    return rng.randint(0, 65535)


def gen_expr(rng, depth, budget):
    """Recursively build one fully-parenthesized-safe arithmetic expression.

    Budget caps the total count of tokens (parentheses, operators, operands)
    at <= 100 as required. Depth keeps the recursion shallow so the brute
    parser stays fast. No division by zero is ever generated.
    """
    # Minimum tokens a subtree can contribute: a single number = 1 token.
    # A binary subtree: '(' + L + op + R + ')' = len(L) + len(R) + 3.
    # Decide whether to recurse based on remaining budget and depth.
    can_recurse = depth > 0 and budget >= 2 * 1 + 3 + 2  # need room for two children + wrapper
    # Bias toward leaves when budget is tight or depth is low.
    leaf_prob = 0.30 if can_recurse else 1.0
    if not can_recurse or rng.random() < leaf_prob:
        return str(rand_num(rng))

    # Split budget between the two children, reserving 3 for '(' ')' and op.
    reserve = 3
    child_budget = max(1, (budget - reserve) // 2)
    left = gen_expr(rng, depth - 1, child_budget)
    right = gen_expr(rng, depth - 1, budget - reserve - len_tokens(left))
    op = rng.choice(['+', '-', '*', '/'])
    if op == '/':
        # Avoid division by zero: ensure the right subtree value is nonzero.
        # Easiest robust approach — regenerate right until it is a nonzero
        # bare number, or append "+1". We just pick a nonzero number leaf.
        right = str(rng.randint(1, 65535))
    return '(' + left + op + right + ')'


def len_tokens(expr):
    """Count tokens the way the problem does: each of '(', ')', an operator,
    or a maximal run of digits counts as one token."""
    n = 0
    i = 0
    while i < len(expr):
        c = expr[i]
        if c in '()+-*/':
            n += 1
            i += 1
        elif c.isdigit():
            n += 1
            while i < len(expr) and expr[i].isdigit():
                i += 1
        else:
            i += 1
    return n


def gen_one(rng):
    """Produce one expression covering a variety of boundary cases."""
    mode = rng.randint(0, 9)
    if mode == 0:
        # Single bare number (no parens, no operators) — minimal edge case.
        return str(rand_num(rng))
    elif mode == 1:
        # Single pair of parens around one op.
        a = rand_num(rng)
        b = rand_num(rng) or 1
        op = rng.choice(['+', '-', '*', '/'])
        if op == '/':
            b = rng.randint(1, 65535)
        return '(' + str(a) + op + str(b) + ')'
    elif mode == 2:
        # No parens at all — exercises precedence.
        a = rand_num(rng)
        b = rand_num(rng)
        c = rand_num(rng)
        op1 = rng.choice(['+', '-', '*', '/'])
        op2 = rng.choice(['+', '-', '*', '/'])
        # avoid div by zero
        if op1 == '/':
            b = rng.randint(1, 65535)
        if op2 == '/':
            c = rng.randint(1, 65535)
        return str(a) + op1 + str(b) + op2 + str(c)
    elif mode == 3:
        # Boundary operand: 0 and 65535.
        return '(' + str(rng.choice([0, 65535])) + rng.choice(['+', '-', '*']) + str(rng.choice([0, 65535])) + ')'
    elif mode == 4:
        # Division yielding a truncated (negative) result.
        a = rng.randint(0, 65535)
        b = rng.randint(1, 65535)
        return '(' + str(a) + '-' + str(b) + ')/' + str(rng.randint(1, 65535))
    elif mode == 5:
        # Nested left-deep expression of moderate size.
        return gen_expr(rng, depth=4, budget=40)
    elif mode == 6:
        # Nested balanced expression.
        return gen_expr(rng, depth=5, budget=60)
    elif mode == 7:
        # Near-max token budget (<= 100).
        return gen_expr(rng, depth=6, budget=95)
    elif mode == 8:
        # Mix of precedence levels with parens.
        a = rand_num(rng)
        b = rand_num(rng)
        c = rand_num(rng)
        d = rand_num(rng)
        b2 = b if b else 1
        d2 = d if d else 1
        return '(' + str(a) + '+' + str(b) + ')*(' + str(c) + '-' + str(d2) + ')'
    else:
        # Subtraction producing negative intermediate, then multiplied.
        a = rng.randint(0, 65535)
        b = rng.randint(0, 65535)
        c = rng.randint(1, 100)
        return '(' + str(a) + '-' + str(b) + ')*' + str(c)


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # 1 to 3 test cases (problem allows up to 10; keep small for brute speed).
    cases = rng.randint(1, 3)

    lines = [str(cases)]
    for _ in range(cases):
        lines.append(gen_one(rng))

    sys.stdout.write('\n'.join(lines) + '\n')


if __name__ == '__main__':
    main()
