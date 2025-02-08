from math import log10, floor

num_len = lambda x: floor(log10(x)) + 1


def div(a: int, b: int) -> tuple[int, int]:
    """
    n = len(a)
    m = len(b)

    Худший случай:
        n итераций внешнего цикла:
        - m итераций первого вложенного цикла
        - 10 итераций второго вложенного цикла
        T(n, m) = O(n*(m+10)) = O(m*n)
    Лучший случай:
        a = b, T(n, m) = O(1)

    """
    quotient = 0

    while a >= b:
        for l in range(num_len(b), num_len(a) + 1):
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
