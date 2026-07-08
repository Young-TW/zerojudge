#!/usr/bin/env python3
"""用 curl 並發補齊缺的 .out（繞過 urllib SSL 慢的問題）。"""
import os, sys, glob, subprocess, json
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, ROOT)
import fetch_problems as fp
fp.ROOT = ROOT
fp.OUT = os.path.join(ROOT, "problems")
PROB = fp.OUT

missing = []
for d in sorted(glob.glob(os.path.join(PROB, "[a-z][0-9]*"))):
    if not os.path.isdir(d): continue
    id_ = os.path.basename(d)
    for inp in sorted(glob.glob(os.path.join(d, "*.in"))):
        outp = inp[:-3] + ".out"
        if not os.path.exists(outp):
            missing.append((id_, inp, outp))

pids = sorted(set(m for m,_,_ in missing))
print(f"缺 .out 涉及的題目: {len(pids)}")

def fetch(pid):
    r = subprocess.run(
        ["curl", "-sS", "-A", "Mozilla/5.0",
         f"https://zerojudge.tw/ShowProblem?problemid={pid}"],
        capture_output=True, timeout=15,
    )
    return pid, r.stdout.decode("utf-8", "replace"), None

def fix(pid):
    try:
        _, html, _ = fetch(pid)
        _, _, samples = fp.parse(pid, html)
        wrote = 0
        for k, s in samples.items():
            if 'out' not in s: continue
            in_path = os.path.join(PROB, pid, f"{k}.in")
            if not os.path.exists(in_path): continue
            with open(os.path.join(PROB, pid, f"{k}.out"), "w", encoding="utf-8") as f:
                f.write(s['out'])
            wrote += 1
        return pid, wrote, None
    except Exception as e:
        return pid, 0, e

ok = fail = 0
with ThreadPoolExecutor(max_workers=8) as ex:
    futs = {ex.submit(fix, pid): pid for pid in pids}
    for i, fu in enumerate(as_completed(futs), 1):
        pid, wrote, err = fu.result()
        if err: fail += 1
        else: ok += 1
        if i % 50 == 0 or i == len(pids):
            print(f"progress {i}/{len(pids)}  ok={ok}  fail={fail}  last={pid}+{wrote}")

print(f"\ndone. ok={ok}  fail={fail}")
