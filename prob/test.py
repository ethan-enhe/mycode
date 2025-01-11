import sys
import math
from math import gcd
from functools import reduce
from collections import defaultdict

def compute_mobius(n):
    mu = [1] * (n + 1)
    is_prime = [True] * (n + 1)
    for p in range(2, n + 1):
        if is_prime[p]:
            for multiple in range(p, n + 1, p):
                is_prime[multiple] = False
                mu[multiple] *= -1
            p_square = p * p
            for multiple in range(p_square, n + 1, p_square):
                mu[multiple] = 0
    return mu

def get_divisors(x):
    divs = set()
    for i in range(1, int(math.isqrt(x)) + 1):
        if x % i == 0:
            divs.add(i)
            divs.add(x // i)
    return divs

def main():
    input = sys.stdin.read
    data = input().split()
    index = 0
    t = int(data[index])
    index += 1
    mu_max = 3_000_000
    mu = compute_mobius(mu_max)
    for _ in range(t):
        a = int(data[index])
        b = int(data[index + 1])
        c = int(data[index + 2])
        k = int(data[index + 3])
        index += 4
        d = list(map(int, data[index:index + k]))
        index += k
        # Precompute divisors
        div_a = sorted(get_divisors(a))
        div_b = sorted(get_divisors(b))
        div_c = sorted(get_divisors(c))
        total = 0
        for da in div_a:
            for db in div_b:
                for dc in div_c:
                    m = a // da
                    n = b // db
                    p = c // dc
                    lcm_mnp = reduce(math.lcm, [m, n, p])
                    if all(di % lcm_mnp == 0 for di in d):
                        # Compute multinomial coefficient
                        cycles = (da * db * dc)
                        if cycles == 0:
                            continue
                        term = math.factorial(cycles)
                        for di in d:
                            term //= math.factorial(di // lcm_mnp)
                        total += mu[m] * mu[n] * mu[p] * term
        print(total)

if __name__ == '__main__':
    main()
