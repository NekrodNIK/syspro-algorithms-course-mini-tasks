import sys
import os
import subprocess
import shlex
import io


def check_commit(commit_hash: str, command: list[str]):
    subprocess.run(["git", "checkout", commit_hash])
    print(subprocess.run(command).returncode)
    return subprocess.run(command).returncode == 0


def get_hash_list(start: str, end: str):
    return [start] + subprocess.check_output(
        ["git", "--no-pager", "log", "--pretty=%h", f"{start}..{end}"]
    ).decode().splitlines()


if len(sys.argv) != 5:
    print("need four arguments")

_, repo, start, end, command = sys.argv
command = shlex.split(command)

try:
    os.chdir(repo)
except FileNotFoundError:
    print("Directory does not exist")
    exit()

if ".git" not in os.listdir():
    print("Directory exists, but is not a repository")
    exit()

hash_list = get_hash_list(start, end)
l = 0
r = len(hash_list)


while l < r:
    mid = (l + r) // 2
    is_good_commit = check_commit(hash_list[mid], command)
    if is_good_commit:
        l = mid + 1
    else:
        r = mid


print(f"first bad commit: {hash_list[l]}")

    

