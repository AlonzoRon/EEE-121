def g(x, n):
    return (x ** 2 + 1) % n


def gcd(m, n):
    if m < 0:
        m = -m
    if n < 0:
        n = -n

    if n == 0:
        return m
    return gcd(n, m % n)


def maybe_prime(n):
    x, y, d = 2, 2, 1

    while d == 1:
        x = g(x, n)
        y = g(g(y, n), n)
        d = gcd(x - y, n)

    return d == n


for i in range(100, 200):
    if maybe_prime(i):
        print(i)
