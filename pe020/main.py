#!/usr/bin/python3

def factorial2_helper(i, d):
    dbase = 10 ** d;
    if i == 0:
        return 1

    last = factorial2_helper(i-1, d);
    return ((i % dbase) * last) % dbase

def factorial2(i, d):
    res = factorial2_helper(i, d+1)
    dbase = 10 ** (d);
    return res // dbase

sum = sum([factorial2(100, i) for i in range(0, 160)])
print(sum)

