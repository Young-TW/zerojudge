#!/usr/bin/env python3
import re, os, sys, html, time, urllib.request, glob

ROOT = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(ROOT, "problems")
UA = "Mozilla/5.0 (zerojudge-local-sample-fetcher)"

def fetch_url(url):
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    with urllib.request.urlopen(req, timeout=30) as r:
        return r.read().decode("utf-8", "replace")

def fetch(pid):
    return fetch_url("https://zerojudge.tw/ShowProblem?problemid=%s" % pid)

def balanced_div(t, start):
    """start = index right after the opening tag's '>'. Return inner html up to matching </div>."""
    depth = 1
    i = start
    while i < len(t) and depth > 0:
        nd = t.find("<div", i)
        cd = t.find("</div", i)
        if cd == -1:
            break
        if nd != -1 and nd < cd:
            depth += 1
            i = nd + 4
        else:
            depth -= 1
            i = cd + 5
    return t[start:cd], cd

def panels(t):
    """Yield (heading_text, body_html) for each panel-heading/panel-body pair."""
    out = []
    for m in re.finditer(r'<div class="panel-heading">(.*?)</div>', t, re.S):
        head = re.sub(r'\s+', ' ', html.unescape(re.sub(r'<[^>]+>', '', m.group(1)))).strip()
        # find the next panel-body after this heading
        bm = re.search(r'<div class="panel-body">', t[m.end():])
        if not bm:
            continue
        bstart = m.end() + bm.end()
        body, _ = balanced_div(t, bstart)
        out.append((head, body))
    return out

def html_to_text(h):
    # strip HTML comments
    h = re.sub(r'<!--.*?-->', '', h, flags=re.S)
    # images -> markdown, make src absolute
    def img(m):
        src = m.group(1)
        if src.startswith('/'):
            src = 'https://zerojudge.tw' + src
        return '\n![image](%s)\n' % src
    h = re.sub(r'<img[^>]*\bsrc="([^"]*)"[^>]*>', img, h)
    h = re.sub(r'<br\s*/?>', '\n', h, flags=re.I)
    h = re.sub(r'</p>', '\n\n', h, flags=re.I)
    h = re.sub(r'</div>', '\n', h, flags=re.I)
    h = re.sub(r'</li>', '\n', h, flags=re.I)
    h = re.sub(r'<li[^>]*>', '- ', h, flags=re.I)
    # keep pre content but as code fence
    h = re.sub(r'<pre[^>]*>(.*?)</pre>', lambda m: '\n```\n' + html.unescape(re.sub(r'<[^>]+>','',m.group(1))).strip('\n') + '\n```\n', h, flags=re.S|re.I)
    h = re.sub(r'<[^>]+>', '', h)
    h = html.unescape(h)
    h = re.sub(r'\n[ \t]+\n', '\n\n', h)
    h = re.sub(r'\n{3,}', '\n\n', h)
    return h.strip()

def parse(pid, t):
    m = re.search(r'<title>\s*([^<]*?)\s*</title>', t)
    full = html.unescape(m.group(1)) if m else pid
    title = re.sub(r'\s*-\s*高中生程式解題系統.*$', '', full).strip()

    ps = panels(t)
    sections = {}
    samples = {}  # n -> [in, out]
    n_in = n_out = 0  # 舊題的範例標題可能不帶編號，依出現順序補號
    for head, body in ps:
        hn = re.match(r'範例輸入\s*#?\s*(\d*)', head)
        ho = re.match(r'範例輸出\s*#?\s*(\d*)', head)
        pre = re.search(r'<pre[^>]*>(.*?)</pre>', body, re.S)
        preval = html.unescape(re.sub(r'<[^>]+>', '', pre.group(1))).replace('\r', '') if pre else ''
        if hn:
            n_in += 1
            samples.setdefault(hn.group(1) or str(n_in), {})['in'] = preval
        elif ho:
            n_out += 1
            samples.setdefault(ho.group(1) or str(n_out), {})['out'] = preval
        elif head in ('內容', '輸入說明', '輸出說明'):
            sections[head] = html_to_text(body)
    return title, sections, samples

def enumerate_ids():
    t = fetch_url("https://zerojudge.tw/Problems?&page=1")
    pages = [int(x) for x in re.findall(r'Problems\?&page=(\d+)', t)]
    maxp = max(pages) if pages else 1
    ids = set(re.findall(r'ShowProblem\?problemid=([a-z]\d+)', t))
    for p in range(2, maxp + 1):
        tp = fetch_url("https://zerojudge.tw/Problems?&page=%d" % p)
        ids.update(re.findall(r'ShowProblem\?problemid=([a-z]\d+)', tp))
        time.sleep(0.2)
    return sorted(ids)

def main():
    os.makedirs(OUT, exist_ok=True)
    idfile = os.path.join(OUT, ".all_ids.txt")
    if os.path.exists(idfile):
        ids = [x for x in open(idfile).read().split() if x]
    else:
        ids = enumerate_ids()
        open(idfile, "w").write("\n".join(ids))
    print("total problems:", len(ids))
    for n, pid in enumerate(ids, 1):
        d = os.path.join(OUT, pid)
        os.makedirs(d, exist_ok=True)
        mdpath = os.path.join(d, "problem.md")
        if os.path.exists(mdpath):  # resume: skip already fetched
            print("[skip] %s" % pid)
            continue
        try:
            t = fetch(pid)
            title, sections, samples = parse(pid, t)
        except Exception as e:
            print("[FAIL]", pid, e)
            continue
        # write problem.md
        md = ["# %s\n" % title]
        if sections.get('內容'):
            md.append("## 內容\n\n%s\n" % sections['內容'])
        if sections.get('輸入說明'):
            md.append("## 輸入說明\n\n%s\n" % sections['輸入說明'])
        if sections.get('輸出說明'):
            md.append("## 輸出說明\n\n%s\n" % sections['輸出說明'])
        for k in sorted(samples, key=int):
            s = samples[k]
            md.append("## 範例輸入 #%s\n\n```\n%s\n```\n" % (k, s.get('in','').rstrip('\n')))
            md.append("## 範例輸出 #%s\n\n```\n%s\n```\n" % (k, s.get('out','').rstrip('\n')))
        open(os.path.join(d, "problem.md"), "w", encoding="utf-8").write("\n".join(md))
        # write test cases
        for k in sorted(samples, key=int):
            s = samples[k]
            if 'in' in s:
                open(os.path.join(d, "%s.in" % k), "w", encoding="utf-8").write(s['in'])
            if 'out' in s:
                open(os.path.join(d, "%s.out" % k), "w", encoding="utf-8").write(s['out'])
        ncase = len(samples)
        clean = re.sub(r'^[a-z]\d+\.\s*', '', title)
        print("[OK] %3d/%d %s  %s  (%d cases)" % (n, len(ids), pid, clean, ncase))
        time.sleep(0.4)
    build_index(ids)
    print("done ->", OUT)

def build_index(ids):
    with open(os.path.join(OUT, "README.md"), "w", encoding="utf-8") as f:
        f.write("# 題目範例測資\n\n")
        f.write("由 ZeroJudge (https://zerojudge.tw) 抓取，供本地試跑範例測資使用。\n\n")
        f.write("每題資料夾含 `problem.md`（標題與敘述）與 `N.in`/`N.out`（第 N 組範例測資）。\n\n")
        f.write("共 %d 題。\n\n" % len(ids))
        f.write("| 題號 | 標題 | 範例組數 |\n|---|---|---|\n")
        for pid in ids:
            d = os.path.join(OUT, pid)
            mp = os.path.join(d, "problem.md")
            if not os.path.exists(mp):
                f.write("| %s | (抓取失敗) | - |\n" % pid)
                continue
            # 標題取自 problem.md 首行 "# a002. 簡易加法"
            first = open(mp, encoding="utf-8").readline().lstrip("# ").strip()
            clean = re.sub(r'^[a-z]\d+\.\s*', '', first)
            ncase = len(glob.glob(os.path.join(d, "*.in")))
            f.write("| [%s](%s/problem.md) | %s | %d |\n" % (pid, pid, clean, ncase))

if __name__ == "__main__":
    main()
