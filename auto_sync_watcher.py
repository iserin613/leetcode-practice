import argparse
import json
import subprocess
import time
from pathlib import Path


ROOT = Path(r"d:\CODING\practice")
STATE_FILE = ROOT / ".cursor" / "leetcode_sync_state.json"
FETCH_SCRIPT = ROOT / "fetch_problem_statements.py"
CLASSIFY_SCRIPT = ROOT / "classify_leetcode.py"


def load_state():
    if not STATE_FILE.exists():
        return {}
    try:
        return json.loads(STATE_FILE.read_text(encoding="utf-8"))
    except Exception:
        return {}


def save_state(state):
    STATE_FILE.parent.mkdir(parents=True, exist_ok=True)
    STATE_FILE.write_text(json.dumps(state, ensure_ascii=False, indent=2), encoding="utf-8")


def collect_changed_ids(prev_state):
    current = {}
    changed_ids = []
    for path in sorted(ROOT.glob("leetcode*.cpp")):
        stem = path.stem
        qid = stem.replace("leetcode", "")
        if not qid.isdigit():
            continue
        mtime = path.stat().st_mtime
        current[qid] = mtime
        if qid not in prev_state or prev_state[qid] != mtime:
            changed_ids.append(qid)
    return current, changed_ids


def run_sync(ids):
    ids_arg = ",".join(sorted(ids, key=lambda x: int(x)))
    print(f"[SYNC] ids={ids_arg}")
    subprocess.run(
        ["python", str(FETCH_SCRIPT), "--ids", ids_arg, "--overwrite"],
        cwd=str(ROOT),
        check=False,
    )
    subprocess.run(
        ["python", str(CLASSIFY_SCRIPT), "--ids", ids_arg, "--include-md"],
        cwd=str(ROOT),
        check=False,
    )


def main():
    parser = argparse.ArgumentParser(description="Watch leetcode*.cpp and auto sync markdown/tags.")
    parser.add_argument("--interval", type=float, default=3.0, help="Polling interval in seconds.")
    parser.add_argument("--once", action="store_true", help="Run one scan and exit.")
    args = parser.parse_args()

    state = load_state()

    if args.once:
        current, changed = collect_changed_ids(state)
        if changed:
            run_sync(changed)
        save_state(current)
        return

    print(f"[WATCH] Start watching {ROOT} every {args.interval}s")
    while True:
        current, changed = collect_changed_ids(state)
        if changed:
            run_sync(changed)
            state = current
            save_state(state)
        else:
            state = current
            save_state(state)
        time.sleep(args.interval)


if __name__ == "__main__":
    main()
