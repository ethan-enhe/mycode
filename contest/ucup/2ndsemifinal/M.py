def solve(s, mid):
    NO = (-1, ["", ""])
    n = len(s[0]) // 2
    l, r = -1, n
    for i in range(n):
        if s[0][i * 2] == mid[1] or s[1][i * 2] == mid[1]:
            l = max(l, i)
        if s[0][i * 2 + 1] == mid[0] or s[1][i * 2 + 1] == mid[0]:
            r = min(r, i)
        li = [s[0][i * 2], s[0][i * 2 + 1], s[1][i * 2], s[1][i * 2 + 1]]
        if sum(c == "1" for c in li) >= 2 or sum(c == "2" for c in li) >= 2:
            return NO
    l += 1
    r -= 1
    if l > r + 1:
        return NO

    res1 = []
    res2 = []
    for i in range(n):
        if i < l:
            if s[0][i * 2 + 1] != "?" or s[1][i * 2 + 1] != "?":
                return NO
            if s[1][i * 2] == "2" or s[0][i * 2] == "1":
                res1.append("1 ")
                res2.append("2 ")
            else:
                res1.append("2 ")
                res2.append("1 ")
        elif i > r:
            if s[0][i * 2] != "?" or s[1][i * 2] != "?":
                return NO
            if s[1][i * 2 + 1] == "2" or s[0][i * 2 + 1] == "1":
                res1.append(" 1")
                res2.append(" 2")
            else:
                res1.append(" 2")
                res2.append(" 1")
        else:
            if s[1][i * 2] == mid[0]:
                res1.append(" ")
                res2.append(mid[0])
            else:
                res1.append(mid[0])
                res2.append(" ")
            if s[1][i * 2 + 1] == mid[1]:
                res1.append(" ")
                res2.append(mid[1])
            else:
                res1.append(mid[1])
                res2.append(" ")
    s1 = "".join(res1)
    s2 = "".join(res2)
    return (sum(int(i) for i in s1.split()), [s1, s2])


t = int(input())
for _ in range(t):
    n = int(input())
    s1 = input().strip()
    s2 = input().strip()
    s = [s1, s2]
    ans = max(solve(s, "12"), solve(s, "21"))
    if ans[0] == -1:
        print("impossible")
    else:
        print(ans[0])
        print(ans[1][0].replace(" ", "0"))
        print(ans[1][1].replace(" ", "0"))
