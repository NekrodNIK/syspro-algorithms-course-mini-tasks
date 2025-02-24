from pathlib import Path

def format_table(rows: list[str], cols: list[str], results: list[list]):
    def get(i: int, j: int) -> str:
        if i == 0 and j == 0:
            return ""

        if i == 0:
            return cols[j - 1]

        if j == 0:
            return rows[i - 1]

        return results[i - 1][j - 1]

    N = len(rows) + 1
    M = len(cols) + 1

    results = [[str(j) for j in i] for i in results]

    length = [0] * M

    for i in range(N):
        for j in range(M):
            length[j] = max(length[j], len(get(i, j)))

    for i in range(N):
        print("|", end="")
        for j in range(M):
            print(f" {get(i,j):<{length[j]}} |", end="")

        print()
        if i % (len(rows) // 3) == 0:
            print(f"|{"-" * (sum(length) + 3 * M - 1)}|")


if __name__ == "__main__":
    data = (Path(__file__).parent / "results.csv").read_text().splitlines()
    data = [line.split(";") for line in data]

    algos = []
    results = []
    for item in data:
        algos.append(item[0])
        results.append(item[1:])


    format_table(algos, ["Sample mean", "Standard deviation", "Geom average"], results)
    
