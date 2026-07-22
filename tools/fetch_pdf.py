#!/usr/bin/env python3
"""Mac 端：抓外部 PDF 題目，轉文字補進 problems/<pid>/problem.md。

只處理「題面缺失（body < 300 字）且 problem.md 內含 PDF URL」的題。
策略：
  1. 解析 problem.md 找 PDF URL（含 (zh_TW).pdf 這類含空白括號的）
  2. curl 下載 PDF 到 /tmp
  3. pdftotext 轉純文字
  4. 把文字插入 problem.md「## 內容」段落後方（保留原範例）
  5. 同步 rsync 到 VM

用法：
  python3 fetch_pdf.py                # 自動掃所有缺題面的題
  python3 fetch_pdf.py r393 r394      # 指定
"""
import os, re, ssl, subprocess, sys, tempfile, urllib.parse, urllib.request
from pathlib import Path

ROOT = Path(os.environ.get('ZJ_ROOT', str(Path.home() / 'code/Young-TW/zerojudge')))
UA = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)'
# 某些站（tpmso.org）SSL 憑證缺 Subject Key Identifier，Mac Python 預設 strict
_SSL_CTX = ssl.create_default_context()
_SSL_CTX.check_hostname = False
_SSL_CTX.verify_mode = ssl.CERT_NONE

def find_pdf_url(md):
    """從 problem.md 抓 PDF URL，含 (zh_TW) 等括號 suffix。"""
    m = re.search(r'(https?://[^\s\n]+?(?:\s*\([^)]+\))?\.pdf)', md)
    return m.group(1) if m else None

def is_thin(md):
    """題面本體太薄（缺實質內容）。"""
    body = re.sub(r'##\s*範例.*', '', md, flags=re.S)
    body = re.sub(r'!\[.*?\]\(.*?\)', '', body)
    return len(body.strip()) < 300

def fetch_pdf_text(url):
    """下載 PDF 並轉文字。回傳 (text, error)。"""
    # URL 含空白/括號需 quote，但 scheme/host 不能被 quote
    p = urllib.parse.urlsplit(url)
    url = urllib.parse.urlunsplit((p.scheme, p.netloc,
                                   urllib.parse.quote(p.path),
                                   urllib.parse.quote(p.query, safe='=&'),
                                   urllib.parse.quote(p.fragment)))
    try:
        req = urllib.request.Request(url, headers={'User-Agent': UA})
        with urllib.request.urlopen(req, timeout=30, context=_SSL_CTX) as r:
            data = r.read()
    except Exception as e:
        return '', f'下載失敗: {e}'
    if not data.startswith(b'%PDF'):
        return '', f'非 PDF 內容 ({len(data)} bytes, 開頭 {data[:20]!r})'
    with tempfile.NamedTemporaryFile(suffix='.pdf', delete=False) as f:
        f.write(data)
        pdf_path = f.name
    try:
        r = subprocess.run(['pdftotext', '-layout', pdf_path, '-'],
                           capture_output=True, text=True, timeout=30)
        if r.returncode != 0:
            return '', f'pdftotext 失敗: {r.stderr[:200]}'
        return r.stdout.strip(), ''
    finally:
        os.unlink(pdf_path)

def patch_problem_md(pid, pdf_text):
    """把 PDF 文字插進 problem.md 的「## 內容」段落。
    若已在 md 內有 PDF body 標記則覆寫，否則新增。"""
    p = ROOT / 'problems' / pid / 'problem.md'
    md = p.read_text()
    marker_begin = '<!-- PDF_BODY_BEGIN -->'
    marker_end = '<!-- PDF_BODY_END -->'
    block = f'{marker_begin}\n{pdf_text}\n{marker_end}'
    if marker_begin in md:
        md = re.sub(re.escape(marker_begin) + r'.*?' + re.escape(marker_end),
                    block, md, flags=re.S)
    else:
        # 插在「## 內容」之後、「## 輸入說明」或「## 範例」之前
        if '## 輸入說明' in md:
            md = md.replace('## 輸入說明', block + '\n\n## 輸入說明', 1)
        elif '## 範例' in md:
            md = md.replace('## 範例', block + '\n\n## 範例', 1)
        else:
            md = md.rstrip() + '\n\n' + block + '\n'
    p.write_text(md)

def process(pid):
    md_p = ROOT / 'problems' / pid / 'problem.md'
    if not md_p.exists():
        return 'no-md'
    md = md_p.read_text()
    if not is_thin(md):
        return 'skip-not-thin'
    url = find_pdf_url(md)
    if not url:
        return 'no-url'
    text, err = fetch_pdf_text(url)
    if not text:
        return f'fetch-fail: {err}'
    if len(text) < 100:
        return f'text-too-short ({len(text)} chars): {text[:80]!r}'
    patch_problem_md(pid, text)
    return f'ok ({len(text)} chars)'

def main():
    args = sys.argv[1:]
    if args:
        pids = [p for p in args if re.fullmatch(r'[a-z]\d+', p)]
    else:
        pids = []
        for d in sorted((ROOT / 'problems').iterdir()):
            if not d.is_dir() or not re.fullmatch(r'[a-z]\d+', d.name): continue
            md_p = d / 'problem.md'
            if not md_p.exists(): continue
            md = md_p.read_text()
            if is_thin(md) and find_pdf_url(md):
                pids.append(d.name)
    print(f'處理 {len(pids)} 題', flush=True)
    ok, fail = 0, 0
    for pid in pids:
        r = process(pid)
        print(f'{pid}: {r}', flush=True)
        if r.startswith('ok'): ok += 1
        elif r.startswith('skip'): pass
        else: fail += 1
    print(f'完成: 成功 {ok}, 失敗 {fail}')

if __name__ == '__main__': main()
