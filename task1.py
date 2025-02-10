from math import log10, floor

num_len = lambda x: floor(log10(x)) + 1


def div(a: int, b: int) -> tuple[int, int]:
    """
    n = len(a)
    m = len(b)

    Худший случай:
        n итераций внешнего цикла:
        - m итерации первого вложенного цикла
        - base = 10 итераций второго вложенного цикла
        - C = const остальных операций

        T(n, m) = O(n*(m+base+C)) = O(n*m)

    Лучший случай:
        a = b, T(n, m) = O(1)

    """
    if b == 0 or b > a:
        return 0, a
        
    quotient = 0

    while a >= b:
        for l in range(1, num_len(a) + 1):
            if int(str(a)[:l]) >= b:
                break
        else:
            break

        factor = 1
        while int(str(a)[:l]) >= b * factor:
            factor += 1
        factor -= 1

        quotient += factor * 10 ** (num_len(a) - l)
        a -= b * factor * 10 ** (num_len(a) - l)

    return quotient, a


if __name__ == "__main__":
    for j in range(1, 1000):
        for i in range(j, j + 400):
            assert div(i, j) == (i // j, i % j)
