import sys
import random


def encode_binary(binary):
    """Convert a binary string (of '0'/'1') into base-1 blocks.

    Encoding per run of k identical bits with value v:
      - a flag-setting block: "0"  if v == '1'  (sets flag=1)
                              "00" if v == '0'  (sets flag=0)
      - an append block: "0" repeated (k + 2) times  (appends k copies of flag)
    The first block is always 1 or 2 zeros, satisfying the rule.
    """
    if not binary:
        binary = "0"
    blocks = []
    i = 0
    n = len(binary)
    while i < n:
        v = binary[i]
        j = i
        while j < n and binary[j] == v:
            j += 1
        k = j - i
        if v == '1':
            blocks.append("0")
        else:
            blocks.append("00")
        blocks.append("0" * (k + 2))
        i = j
    return blocks


def gen_binary(rnd):
    choice = rnd.randint(0, 11)
    if choice == 0:
        # value 0
        return "0"
    elif choice == 1:
        # leading zeros (still valid: first block "00" has 2 zeros)
        lead = rnd.randint(1, 3)
        rest_len = rnd.randint(0, 29 - lead)
        return "0" * lead + "1" + "".join(rnd.choice("01") for _ in range(rest_len))
    elif choice == 2:
        # single bit, value 1
        return "1"
    elif choice == 3:
        # 30 bits all ones (max value)
        return "1" * 30
    elif choice == 4:
        # exactly 30 bits, random
        return "1" + "".join(rnd.choice("01") for _ in range(29))
    elif choice == 5:
        # alternating bits (many short runs)
        nbits = rnd.randint(2, 30)
        return "".join("1" if i % 2 == 0 else "0" for i in range(nbits))
    else:
        nbits = rnd.randint(1, 30)
        return "1" + "".join(rnd.choice("01") for _ in range(nbits - 1))


def main():
    rnd = random.Random(int(sys.argv[1]))
    out = []
    ncases = rnd.randint(1, 8)
    for _ in range(ncases):
        binary = gen_binary(rnd)
        blocks = encode_binary(binary)
        for idx, b in enumerate(blocks):
            out.append(b)
            if idx < len(blocks) - 1:
                # occasionally split a number across lines (never inside a block)
                if rnd.randint(0, 4) == 0:
                    out.append("\n")
                else:
                    out.append(" ")
        out.append(" #\n")
    out.append("~\n")
    sys.stdout.write("".join(out))


if __name__ == "__main__":
    main()
