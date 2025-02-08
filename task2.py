def karatsuba(n: int, m: int):
    if n < 10 or m < 10:
        return n * m

    x = len(str(max(n, m))) // 2

    a = n // 10**x
    b = n % 10**x
    c = m // 10**x
    d = m % 10**x

    z0 = karatsuba(a, c)
    z1 = karatsuba(a + b, c + d)
    z2 = karatsuba(b, d)

    return z0 * 10 ** (x * 2) + (z1 - z0 - z2) * 10**x + z2


if __name__ == "__main__":
    for i in range(1, 1000):
        for j in range(1, 1000):
            assert karatsuba(i, j) == i * j

    assert karatsuba(1234567899876543323112213323232321, 367676767362785) == (
        1234567899876543323112213323232321 * 367676767362785
    )
