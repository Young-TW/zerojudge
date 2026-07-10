#!/usr/bin/env python3
"""補抓不在 Problems 列表上的隱藏題。

ZeroJudge 的 Problems 列表只是全站子集，很多題（如 a007、d906、e001）
只能用題號直接開。這支腳本暴力枚舉 a001..t999，跳過本地已有的題目，
有效頁面（<title> 以「題號.」開頭）就照 fetch_problems 的格式寫入 problems/。

可中斷重跑：已有 problem.md 的題號會跳過；判定為不存在的題號記在
problems/.absent_ids.txt，重跑時也跳過。跑完重建 problems/README.md 與 .all_ids.txt。
"""
import os, re, sys, glob, subprocess, time, threading
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, ROOT)
import fetch_problems as fp
PROB = fp.OUT

LETTERS = "abcdefghijklmnopqrst"
WORKERS = 6
ABSENT = os.path.join(PROB, ".absent_ids.txt")
_absent_lock = threading.Lock()

def fetch(pid):
    """回傳 (http_code, body)。不存在的題號站方回 500。"""
    r = subprocess.run(
        ["curl", "-sS", "-A", "Mozilla/5.0", "-w", "\n%{http_code}",
         f"https://zerojudge.tw/ShowProblem?problemid={pid}"],
        capture_output=True, timeout=25,
    )
    if r.returncode != 0:
        raise RuntimeError(r.stderr.decode("utf-8", "replace").strip() or f"curl rc={r.returncode}")
    body, _, code = r.stdout.decode("utf-8", "replace").rpartition("\n")
    return int(code), body

def write_problem(pid, title, sections, samples):
    d = os.path.join(PROB, pid)
    os.makedirs(d, exist_ok=True)
    md = ["# %s\n" % title]
    for k in ('內容', '輸入說明', '輸出說明'):
        if sections.get(k):
            md.append("## %s\n\n%s\n" % (k, sections[k]))
    for k in sorted(samples, key=int):
        s = samples[k]
        md.append("## 範例輸入 #%s\n\n```\n%s\n```\n" % (k, s.get('in', '').rstrip('\n')))
        md.append("## 範例輸出 #%s\n\n```\n%s\n```\n" % (k, s.get('out', '').rstrip('\n')))
    open(os.path.join(d, "problem.md"), "w", encoding="utf-8").write("\n".join(md))
    for k in sorted(samples, key=int):
        s = samples[k]
        if 'in' in s:
            open(os.path.join(d, "%s.in" % k), "w", encoding="utf-8").write(s['in'])
        if 'out' in s:
            open(os.path.join(d, "%s.out" % k), "w", encoding="utf-8").write(s['out'])

def mark_absent(pid):
    with _absent_lock:
        with open(ABSENT, "a", encoding="utf-8") as f:
            f.write(pid + "\n")

def probe(pid):
    """回傳 'found' | 'absent' | 'error'"""
    try:
        code, t = fetch(pid)
        if code == 500:  # 站方對不存在的題號回 500
            mark_absent(pid)
            return "absent", None
        if code != 200:
            return "error", RuntimeError(f"HTTP {code}")
        title, sections, samples = fp.parse(pid, t)
        if not title.startswith(pid + "."):  # 保險：頁面存在但不是題目
            mark_absent(pid)
            return "absent", None
        write_problem(pid, title, sections, samples)
        return "found", (title, len(samples))
    except Exception as e:
        return "error", e

def main():
    have = {os.path.basename(d) for d in glob.glob(os.path.join(PROB, "[a-z][0-9]*")) if os.path.isdir(d)}
    absent = set()
    if os.path.exists(ABSENT):
        absent = {x for x in open(ABSENT).read().split() if x}
    todo = [f"{c}{n:03d}" for c in LETTERS for n in range(1, 1000)
            if f"{c}{n:03d}" not in have and f"{c}{n:03d}" not in absent]
    print(f"已有 {len(have)} 題、已知不存在 {len(absent)}，待探測 {len(todo)} 個題號", flush=True)

    found = errs = done = 0
    retry = []
    with ThreadPoolExecutor(max_workers=WORKERS) as ex:
        futs = {ex.submit(probe, pid): pid for pid in todo}
        for fu in as_completed(futs):
            pid = futs[fu]
            status, info = fu.result()
            done += 1
            if status == "found":
                found += 1
                print(f"[OK] {pid}  {info[0]}  ({info[1]} 組範例)", flush=True)
            elif status == "error":
                errs += 1
                retry.append(pid)
            if done % 500 == 0:
                print(f"progress {done}/{len(todo)}  found={found}  err={errs}", flush=True)
            time.sleep(0.02)

    # 網路錯誤重試一輪（序列、慢速）
    if retry:
        print(f"重試 {len(retry)} 個錯誤題號…", flush=True)
        still = []
        for pid in retry:
            status, info = probe(pid)
            if status == "found":
                found += 1
                print(f"[OK] {pid}  {info[0]}  ({info[1]} 組範例)", flush=True)
            elif status == "error":
                still.append((pid, info))
            time.sleep(0.5)
        for pid, e in still:
            print(f"[FAIL] {pid}  {e}", flush=True)

    ids = sorted(os.path.basename(d) for d in glob.glob(os.path.join(PROB, "[a-z][0-9]*")) if os.path.isdir(d))
    open(os.path.join(PROB, ".all_ids.txt"), "w").write("\n".join(ids) + "\n")
    fp.build_index(ids)
    print(f"done. 新增 {found} 題，總計 {len(ids)} 題", flush=True)

if __name__ == "__main__":
    main()
