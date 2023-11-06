#include <bits/stdc++.h>
#include <math.h>
using namespace std;
using ld = long double;
using ll = long long;
const char nl = '\n';
ll cnt;
struct data {
    ll id;
    explicit data(ll _id = -1) : id(_id) {}
    data operator*(const data &b) const {
        cout << "* " << id << " " << b.id << nl;
        return data{++cnt};
    }
    data operator+(const data &b) const {
        cout << "+ " << id << " " << b.id << nl;
        return data{++cnt};
    }
    data operator+(const ld &b) const {
        cout << "C " << id << " " << b << nl;
        return data{++cnt};
    }
    data operator+(const string &b) const {
        cout << "C " << id << " " << b << nl;
        return data{++cnt};
    }
    data operator-() const {
        cout << "- " << id << nl;
        return data{++cnt};
    }
    data operator<<(const ll &b) const {
        cout << "< " << id << " " << b << nl;
        return data{++cnt};
    }
    data operator>>(const ll &b) const {
        cout << "> " << id << " " << b << nl;
        return data{++cnt};
    }
};
data s(data x) {
    cout << "S " << x.id << nl;
    return data{++cnt};
}
data read() {
    cout << "I" << nl;
    return data{++cnt};
}
void prt(data x) {
    ++cnt;
    cout << "O " << x.id << nl;
}

ld s(ld x) { return (ld)1 / (expl(-x) + 1); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.flags(ios::fixed);
    cout.precision(30);
    ll tp;
    cin >> tp;
    if (tp == 1) {
        data x, y;
        x = read();
        y = read();
        prt(-((x + y) << 1));
    } else if (tp == 2) {
        data x = read();
        prt(s(-(x + (x << 4))));
    } else if (tp == 3) {
        prt((s(read() << 100) + (-0.5)) << 1);
    } else if (tp == 4) {
        /* data x = read(); */
        /* data res = (S(x << 100) + (-0.5)) << 1; */
        /* prt(res * x); */

        /* ld a; */
        /* cin >> a; */
        /* ld b = sigmoid(a * powl(2, 20)); */
        /* ld c = sigmoid(a * powl(0.5, 20) + b * powl(2, 20)); */
        /* cerr << c << nl; */
        /* ld d = (-c + 0.5) * powl(2, 23); */
        /* ld e = a + d + b * powl(2, 22); */
        /* cerr << e << nl; */

        data x = read();
        data p = s((x + 1e-20) << 100) << 102; //非零
        data r1 = s((x >> 100) + p);           // x>=0等于1，x<0等于x>>102+0.5
        data r2 = (-r1 + 0.5) << 103;          // x>=0等于-0.5*2^103,x<0等于-2x
        data r3 = x + r2 + p;                  //大于0的时候加上2^102
        prt(r3);
        /* cerr << cnt; */
    } else if (tp == 5) {
        data last = read();
        for (int i = 1; i < 32; i++) {
            data cur = read();
            last = (last << 1) + cur;
        }
        prt(last);
    } else if (tp == 6) {
        //我们可以判断大数的正负
        //因此先把x乘大了
        data x = read();
        x = x << 30;
        for (ll i = 31; ~i; i--) {
            //减去对应位，判断正负
            data res = i ? s(x + (1e6 - powl(2, i + 30))) : x >> 30;
            prt(res);
            //删除当前位置
            if (i) x = x + (-(res << (i + 30)));
        }
    } else if (tp == 7) {
    } else if (tp == 8) {
        //导数=e^(-x)/(1+e^(-x))^2
        /* ld magic = log(sqrtl(15) + 4); */
        /* data x = (read() >> 60) + magic; */
        /* x = S(x) + (-sigmoid(magic)); */
        /* prt(x << 60); */
        // not ok！！！！

        string magic = "2.06343706889556054672728117262013187145659144988339249983603269276590284284740991";
        data x = (read() >> 100) + magic;
        x = s(x) + "-0.887298334620741688517926539978239961083292170529159082658757376611348309193697903351";
        prt(x << 100);
    } else if (tp == 9) {
        auto mx0 = [](data x) {
            x = -x;
            data p = s((x + 1e-20) << 100) << 101; //非零
            data r1 = s((x >> 100) + p);           // x>=0等于1，x<0等于x>>102+0.5
            data r2 = (-r1 + 0.5) << 102;          // x>=0等于-0.5*2^102,x<0等于-x
            data r3 = r2 + p;                      // x>=0=0,x<0=-x
            return r3;
        };
        auto swp = [&](data &x, data &y) {
            data delt = (-x) + y;
            data tmp = mx0(delt);
            data sum = x + y;
            y = x + tmp;
            x = sum + (-y);
        };
        data arr[20];
        for (ll i = 1; i <= 16; i++) {
            arr[i] = read();
            for (ll j = i; j > 1; j--) swp(arr[j - 1], arr[j]);
        }
        for (ll i = 1; i <= 16; i++) prt(arr[i]);
    } else if (tp == 10) {
        /* using data = ld; */
        /* auto mult = [](data x, data y) { // x=0/1,y=任意 */
        /*     //(s(-INF+x*INF+y/INF)-x*0.5)*4INF:x=0时，0，x=1时，x */
        /*     return (s((x * powl(2, 50)) + (-powl(2, 50)) + (y * powl(0.5, 50))) + (-x / 2)) * powl(2, 52); */
        /* }; */
        /* auto mod = [&](data x, data y) { */
        /*     data delt = s((x + (-y) + 0.5) * 2e9); */
        /*     x = x + (-mult(delt, y)); */
        /*     return x; */
        /* }; */
        /* data x, y, p, ans = 0; */
        /* cin >> x >> y >> p; */
        /* for (ll i = 31; ~i; i--) y = mod(y, p * powl(2, i)); */
        /* x = x * powl(2, 50); */
        /* for (ll i = 31; ~i; i--) { */
        /*     //减去对应位，判断正负 */
        /*     data res = i ? s(x + (1e6 - powl(2, i + 50))) : x * powl(0.5, 50); */
        /*     ans = ans == 0 ? mult(res, y) : (ans + ans + mult(res, y)); */
        /*     ans = mod(ans, p); */
        /*     ans = mod(ans, p); */
        /*     /1* cout<<res<<" "<<y<<" "<<ans<<endl; *1/ */
        /*     //删除当前位置 */
        /*     if (i) x = x + (-(res * powl(2, i + 50))); */
        /* } */
        /* cout << ans; */
        auto mult = [](data x, data y) { // x=0/1,y=任意
            //(s(-INF+x*INF+y/INF)-x*0.5)*4INF:x=0时，0，x=1时，x
            return (s((x << 60) + (-powl(2, 60)) + (y >> 60)) + (-x >> 1)) << 62;
        };
        auto mod = [&](data x, data y) {
            data delt = s((x + (-y) + 0.5) << 100);
            x = x + (-mult(delt, y));
            return x;
        };
        data x, y, p, ans;
        x = read();
        y = read();
        p = read();
        for (ll i = 31; ~i; i--) y = mod(y, p << i);
        x = x << 60;
        for (ll i = 31; ~i; i--) {
            //减去对应位，判断正负
            data res = i ? s(x + (1e6 - powl(2, i + 60))) : x >> 60;
            ans = ans.id == -1 ? mult(res, y) : (ans + ans + mult(res, y));
            ans = mod(ans, p);
            ans = mod(ans, p);
            //删除当前位置
            if (i) x = x + (-(res << (i + 60)));
        }
        prt(ans);
    }
    return 0;
}
