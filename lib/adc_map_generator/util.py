import math


def distance(a, b):
    return abs(a - b)


def find_approx_key(m: dict, value):
    closest = list(m.keys())[0]
    for k in m:
        if distance(closest, value) > distance(k, value):
            closest = k
    return closest
