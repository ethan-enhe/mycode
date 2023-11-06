auto bsgs = [](ll x, ll y, ll z) -> ll {
    // x^k=y(mod z) 求最小 z
    auto cmp = [](const pi &x, const pi &y) {
        if (x.fi != y.fi) return x.fi < y.fi;
        return x.se > y.se;
    };
    ll sq = sqrtl(z) + 1, va = 1;
    vector<pi> bs;
    for (ll i = 0; i < sq; i++) {
        bs.push_back({y * va % z, i});
        va = va * x % z;
    }
    sort(all(bs), cmp);
    y = 1;
    for (ll i = 1; i <= sq; i++) {
        y = y * va % z;
        auto it = lower_bound(all(bs), pi{y, INF}, cmp);
        if (it != bs.end() && it->fi == y) return i * sq - it->se;
    }
    return -1;
};
