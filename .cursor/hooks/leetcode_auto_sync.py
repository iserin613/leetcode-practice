import json
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
FETCH_SCRIPT = ROOT / "fetch_problem_statements.py"
CLASSIFY_SCRIPT = ROOT / "classify_leetcode.py"


def collect_ids(obj, out):
    if isinstance(obj, dict):
        for value in obj.values():
            collect_ids(value, out)
        return
    if isinstance(obj, list):
        for item in obj:
            collect_ids(item, out)
        return
    if isinstance(obj, str):
        for match in re.findall(r"leetcode(\d+)\.cpp", obj, flags=re.IGNORECASE):
            out.add(match)


def main():
    raw = sys.stdin.read().strip()
    if not raw:
        return

    try:
        payload = json.loads(raw)
    except Exception:
        return

    ids = set()
    collect_ids(payload, ids)
    if not ids:
        return

    ids_arg = ",".join(sorted(ids, key=lambda x: int(x)))

    subprocess.run(
        [sys.executable, str(FETCH_SCRIPT), "--ids", ids_arg, "--overwrite"],
        cwd=str(ROOT),
        check=False,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    subprocess.run(
        [sys.executable, str(CLASSIFY_SCRIPT), "--ids", ids_arg, "--include-md"],
        cwd=str(ROOT),
        check=False,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )


if __name__ == "__main__":
    main()
