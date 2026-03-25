from pathlib import Path

LENGTHS = [1000, 5000, 10000, 20000, 30000, 40000, 50000,
           60000, 70000, 80000, 90000, 100000]

OUT_DIR = Path("timing_cases")
OUT_DIR.mkdir(exist_ok=True)


def make_valid(total_len: int, idx: int) -> str:
    rel = f"R{idx}"
    base = f"create {rel} ()"
    attr_len = total_len - len(base)
    if attr_len < 1:
        raise ValueError(f"Too small length for valid command: {total_len}")

    attr = "a" + "x" * (attr_len - 1)
    cmd = f"create {rel} ({attr})"

    assert len(cmd) == total_len
    return cmd


def make_invalid(total_len: int, idx: int) -> str:
    rel = f"E{idx}"
    base = f"create {rel} ()"
    attr_len = total_len - len(base)
    if attr_len < 1:
        raise ValueError(f"Too small length for invalid command: {total_len}")

    # Некорректно: атрибут начинается с цифры
    attr = "1" + "x" * (attr_len - 1)
    cmd = f"create {rel} ({attr})"

    assert len(cmd) == total_len
    return cmd


for n in LENGTHS:
    lines = []

    # 5 корректных
    for i in range(5):
        lines.append(make_valid(n, i))

    # 5 некорректных
    for i in range(5):
        lines.append(make_invalid(n, i))

    out_file = OUT_DIR / f"cases_{n}.txt"
    with out_file.open("w", encoding="utf-8", newline="\n") as f:
        for line in lines:
            f.write(line + "\n")

print("Done.")




