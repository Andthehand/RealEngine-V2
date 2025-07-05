import os
import re
from pathlib import Path
from collections import defaultdict

SOURCE_DIR = Path("../src").resolve()
OUTPUT_FILE = Path("FILES.md")

CLASS_PATTERN = re.compile(
    r'^\s*(namespace|enum class|enum|class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)\s*[:{]?', re.MULTILINE
)

subdir_classes = defaultdict(set)

def extract_classes(filepath, relative_path):
    found = []
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            lines = f.readlines()

        brace_depth = 0
        brace_stack = []
        scope_stack = []

        for idx, line in enumerate(lines):
            if re.search(r'\btemplate\s*<.*?>', lines[idx - 1] if idx > 0 else ''):
                continue

            stripped = line.strip()

            # Detect class/struct/namespace/enum
            match = CLASS_PATTERN.match(stripped)
            if match:
                kind, name = match.groups()
                if kind != "namespace":
                    subdir = filepath.parent.relative_to(SOURCE_DIR)
                    fq_name = "::".join(scope_stack)
                    subdir_classes[str(subdir)].add((name, fq_name))
                    found.append((fq_name + "::" + name, relative_path, idx + 1, stripped))

                scope_stack.append(name)
                brace_stack.append(brace_depth)
                
            # Count braces to maintain depth
            brace_depth += line.count("{")
            brace_depth -= line.count("}")

            # Pop scopes when exiting their brace block
            while brace_stack and brace_depth <= brace_stack[-1]:
                scope_stack.pop()
                brace_stack.pop()
    except UnicodeDecodeError:
        print(f"⚠️ Skipped unreadable file: {relative_path}")
    return found

def collect_classes():
    print("🔍 Searching for class/struct declarations...\n")
    for root, dirs, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith((".h", ".hpp")):
                path = Path(root) / file
                rel_path = path.relative_to(SOURCE_DIR)

                # Read and process the file
                print(f"🔎 Scanning {rel_path}...")
                class_infos = extract_classes(path, rel_path)
                
                #debug output
                for name, rel_path, line_no, line_text in class_infos:
                    print(f"📄 {rel_path}:{line_no:3} — found {name} → {line_text}")
                print("\n")

    print("\n✅ Finished scanning files.\n")

def write_markdown():
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        # Add header name
        index_name = SOURCE_DIR.parent.name
        f.write(f"# 📁 {index_name} File Index\n\n")

        # add list of files
        for subdir in sorted(subdir_classes.keys()):
            f.write(f"## `{subdir}`\n\n")
            for cls, scope in sorted(subdir_classes[subdir]):
                ref = f"{scope}::{cls}" if scope else cls
                f.write(f"- [{cls}](@ref {ref})\n")
            f.write("\n")
    print(f"✅ Wrote output to {OUTPUT_FILE}")

if __name__ == "__main__":
    collect_classes()
    write_markdown()