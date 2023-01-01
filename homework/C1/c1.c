#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,bmi,bmi2,lzcnt,popcnt")

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ull unsigned long long
#define ui unsigned int
#define bool _Bool

#define SIZE 4200               // 实际二进制位数，要求必须是运算中被除数大小两倍以上
#define BIT 28                  // 每一个unsigned int 压缩的位数
#define MASK ((1u << BIT) - 1u) // 蒙版，用来快速取模
#define LEN (SIZE) / (BIT) + 1  // unsigned int的个数
#define _LEN LEN + 1            // 实际多一位，便于处理边界情况

//进位，写成宏避免函数调用
#define carry(x, i)              \
    (x)[i + 1] += (x)[i] >> BIT; \
    (x)[i] &= MASK;
//借位
#define borrow(x, i)            \
    (x)[i + 1] -= (x)[i] >> 31; \
    (x)[i] &= MASK;

// rand 效率较低，手写一个
ull k1, k2;
ull myrand() {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

typedef struct bigint {
    ui v[_LEN];
} lll;
lll zero, one, two, four;

//用y初始化x
void init(lll* x, ui y) {
    *x = zero;
    x->v[0] = y;
}
//造一个随机数
void makernd(lll* x, int y) {
    *x = zero;
    for (int i = 0; i * BIT < y; i++) x->v[i] = myrand() & MASK;
    x->v[y / BIT] &= (1u << (y % BIT)) - 1;
}
//得到某一位
bool get(lll* x, ui y) { return (x->v[y / BIT] >> (y % BIT)) & 1; }
//置1
void set(lll* x, ui y) { x->v[y / BIT] |= 1u << (y % BIT); }
//置0
void reset(lll* x, ui y) { x->v[y / BIT] &= ~(1u << (y % BIT)); }
//最高位
ui highbit(lll* x) {
    ui ind = LEN - 1;
    ++x->v[0];
    while (x->v[ind] == 0) --ind;
    --x->v[0];
    if (x->v[ind]) return ind * BIT + 31 - __builtin_clz(x->v[ind]);
    return -1;
}
//最低位
ui lowbit(lll* x) {
    ui ind = 0;
    ++x->v[LEN];
    while (x->v[ind] == 0) ++ind;
    --x->v[LEN];
    if (x->v[ind]) return ind * BIT + __builtin_ctz(x->v[ind]);
    return -1;
}
//二进制输出
void prtbin(lll* x) {
    bool f = 0;
    for (int ind = highbit(x); ind >= 0; ind--) {
        ui cv = get(x, ind);
        if (f || cv) {
            f = 1;
            putchar('0' + cv);
        }
    }
    if (!f) putchar('0');
}
void prthex(lll* x) {
    bool f = 0;
    ui v = 0;
    for (int ind = highbit(x); ind >= 0; ind--) {
        ui cv = get(x, ind);
        if (f || cv) {
            v = (v << 1) | cv;
            if ((ind & 3) == 0) {
                putchar("0123456789ABCDEF"[v]);
                v = 0;
            }
            f = 1;
        }
    }
    if (!f) putchar('0');
}
//十进制输出
void prtdec(lll* x) {
    static ull tmp[SIZE];
    for (int i = 0; i < SIZE; i++) tmp[i] = 0;
    for (int i = LEN - 1; i >= 0; i--) {
        for (int j = 0; j < SIZE; j++) tmp[j] <<= BIT;
        tmp[0] += x->v[i];
        for (int j = 0; j < SIZE; j++)
            if (tmp[j] >= 10) {
                tmp[j + 1] += tmp[j] / 10;
                tmp[j] %= 10;
            }
    }
    bool f = 0;
    for (int i = SIZE - 1; i >= 0; i--)
        if (f || tmp[i]) {
            putchar('0' + tmp[i]);
            f = 1;
        }
}
void add(lll* x, lll* y) {
    for (ui i = 0; i < LEN; i++) {
        x->v[i] += y->v[i];
        carry(x->v, i);
    }
}
void sub(lll* x, lll* y) {
    for (ui i = 0; i < LEN; i++) {
        x->v[i] -= y->v[i];
        borrow(x->v, i);
    }
}
void mult(lll* x, lll* y) {
    static lll tmp;
    ui hx = 0, hy = 0;
    for (ui i = 0; i < LEN; i++) {
        if (x->v[i]) hx = i;
        if (y->v[i]) hy = i;
    }
    register ull s = 0;
    for (register ui i = 0; i < LEN; i++) {
        register ui jr = hx < i ? hx : i, j = hy < i ? i - hy : 0;
#define op(k) s += (ull)x->v[j + k] * y->v[i - j - k]
        for (; j + 7 <= jr; j += 8) {
            op(0);
            op(1);
            op(2);
            op(3);
            op(4);
            op(5);
            op(6);
            op(7);
        }
        for (; j <= jr; j++) op(0);
        tmp.v[i] = s & MASK;
        s >>= BIT;
    }
    *x = tmp;
}
void leftshift(lll* x, ui y) {
    static lll tmp;
    ui r = y % BIT;
    y /= BIT;
    tmp = zero;
    for (ui i = y + 1; i < LEN; i++) tmp.v[i] = MASK & ((x->v[i - y] << r) | (x->v[i - y - 1] >> (BIT - r)));
    tmp.v[y] = MASK & (x->v[0] << r);
    *x = tmp;
}
void rightshift(lll* x, ui y) {
    static lll tmp;
    ui r = y % BIT;
    y /= BIT;
    tmp = zero;
    for (ui i = 0; i + y + 1 <= LEN; i++) tmp.v[i] = MASK & ((x->v[i + y] >> r) | (x->v[i + y + 1] << (BIT - r)));
    *x = tmp;
}
bool equal(lll* x, lll* y) {
    for (ui i = 0; i < LEN; i++)
        if (x->v[i] != y->v[i]) return 0;
    return 1;
}
bool lessequal(lll* x, lll* y) {
    for (int i = LEN - 1; i >= 0; i--) {
        if (x->v[i] > y->v[i])
            return 0;
        else if (x->v[i] < y->v[i])
            return 1;
    }
    return 1;
}
//朴素除法，结果存到x
void plaindiv(lll* x, lll* y) {
    static lll tmp;
    tmp = *x;
    *x = zero;
    int delt = (int)highbit(&tmp) - highbit(y);
    if (delt < 0) return;
    if (delt >= 0) leftshift(y, delt);
    while (1) {
        if (lessequal(y, &tmp)) {
            sub(&tmp, y);
            set(x, delt);
        }
        if (delt == 0) break;
        rightshift(y, 1);
        --delt;
    }
}

// Barrett reduction 取模优化
typedef struct barrett {
    lll m, inv;
} brt;
//初始化，求逆元
void initb(brt* x, lll* y) {
    x->m = *y;
    x->inv = one;
    leftshift(&x->inv, SIZE >> 1);
    plaindiv(&x->inv, &x->m);
}
//取模，存储到x
void mod(lll* x, brt* y) {
    static lll tmp;
    tmp = *x;
    mult(&tmp, &y->inv);
    rightshift(&tmp, SIZE >> 1);
    mult(&tmp, &y->m);
    sub(x, &tmp);
    while (lessequal(&y->m, x)) sub(x, &y->m); //正常来说执行次数<=1
}

void qpow(lll* x, lll* y, brt* m) {
    static lll tmp;
    tmp = one;
    ui hy = highbit(y);
    for (ui i = 0; i <= hy; i++) {
        if (get(y, i)) {
            mult(&tmp, x);
            mod(&tmp, m);
        }
        mult(x, x);
        mod(x, m);
    }
    *x = tmp;
}

bool millerrabin(lll* n, int test) {
    if (equal(n, &one)) return 0;
    if (equal(n, &two)) return 1;
    if ((n->v[0] & 1) == 0) return 0;
    static lll x, y, rnd;
    static brt p;
    x = *n;
    initb(&p, &x);
    sub(&x, &one);
    y = x;
    int h = lowbit(&y);
    rightshift(&y, h);

    int i = 0;
    while (i++ < test) {
        makernd(&rnd, 1024);
        mod(&rnd, &p);
        if (equal(&rnd, &zero)) {
            --i;
            continue;
        }
        qpow(&rnd, &y, &p);
        bool f = 0;
        if (equal(&rnd, &one) || equal(&rnd, &x))
            f = 1;
        else
            for (int j = 1; j < h; j++) {
                mult(&rnd, &rnd);
                mod(&rnd, &p);
                if (equal(&rnd, &x)) {
                    f = 1;
                    break;
                }
            }
        if (!f) {
            printf("failed on test: %d\n", i);
            return 0;
        }
    }
    puts("passed all tests");
    return 1;
}

#define MXN 1
int passed_cnt;

lll x, p1, p2;
int main() {
    int t0 = clock();
    k1 = time(0), k2 = 1919810;
    for (int i = 1; i <= 100; i++) myrand(); //前面生成的随机数太小，略过不用

    init(&one, 1);
    init(&two, 2);
    init(&four, 4);

    for (int i = 1; i <= MXN; i++) {
        int cnt = 0;
        puts("prime p:");
        while (1) {
            int _t = clock();
            makernd(&x, 512);
            set(&x, 511);
            set(&x, 0);
            set(&x, 1);
            if (millerrabin(&x, 10)) {
                if (cnt == 0) {
                    ++cnt;
                    p1 = x;
                    puts("\nprime q:");
                } else if (cnt == 1) {
                    printf("time cost: %.3f\n", (double)(clock() - _t) / CLOCKS_PER_SEC);
                    p2 = x;
                    break;
                }
            }
            printf("time cost: %.3f\n", (double)(clock() - _t) / CLOCKS_PER_SEC);
        }
        printf("p: 0x");
        prthex(&p1);
        printf("\nq: 0x");
        prthex(&p2);
        mult(&p1, &p2);
        printf("\nblum: 0x");
        prthex(&p1);

        puts("\n\ntesting blum:");
        millerrabin(&p1, 20);
        /* if (millerrabin(&p1, 20)) passed_cnt++; */
    }
    /* printf("%d\n", passed_cnt); */
    printf("\n\ntotal time: %.3f s", (double)(clock() - t0) / CLOCKS_PER_SEC);

    return 0;
};
