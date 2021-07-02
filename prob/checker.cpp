#include "testlib.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <deque>
#include <set>
using namespace std;

typedef long long int64;

const int B = 1000000000;
const int L = 9;

inline int intcmp(int a, int b)
{
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

struct ulint
{
	vector<int> a;

	ulint(){}
	ulint(int n)
	{
		while (n > 0)
			a.push_back(n % B), n /= B;
	}
	ulint(int64 n)
	{
		while (n > 0)
			a.push_back(n % B), n /= B;
	}

	inline void clr0()
	{
		while (!a.empty() && a.back() == 0)
			a.pop_back();
	}

	inline ulint &operator+=(const ulint &rhs)
	{
		a.resize(max(a.size(), rhs.a.size()));
		int t = 0;
		for (int i = 0; i < (int)rhs.a.size(); i++)
		{
			a[i] += rhs.a[i] + t;
			t = a[i] >= B;
			a[i] -= B & (-t);
		}
		for (int i = (int)rhs.a.size(); t != 0 && i < (int)a.size(); i++)
		{
			a[i] += t;
			t = a[i] >= B;
			a[i] -= B & (-t);
		}
		if (t != 0)
			a.push_back(t);
		return *this;
	}
	inline ulint &operator-=(const ulint &rhs)
	{
		a.resize(max(a.size(), rhs.a.size()));
		int t = 0;
		for (int i = 0; i < (int)rhs.a.size(); i++)
		{
			a[i] -= rhs.a[i] + t;
			t = a[i] < 0;
			a[i] += B & (-t);
		}
		for (int i = (int)rhs.a.size(); t != 0 && i < (int)a.size(); i++)
		{
			a[i] -= t;
			t = a[i] < 0;
			a[i] += B & (-t);
		}
		clr0();
		return *this;
	}
	inline ulint &operator*=(const ulint &rhs)
	{
		int na = (int)a.size();
		a.resize(na + rhs.a.size());
		for (int i = na - 1; i >= 0; i--)
		{
			int ai = a[i];
			int64 t = 0;
			a[i] = 0;
			for (int j = 0; j < (int)rhs.a.size(); j++)
			{
				t += a[i + j] + (int64)ai * rhs.a[j];
				a[i + j] = t % B;
				t /= B;
			}
			for (int j = (int)rhs.a.size(); t != 0 && i + j < (int)a.size(); j++)
			{
				t += a[i + j];
				a[i + j] = t % B;
				t /= B;
			}
			assert(t == 0);
		}
		clr0();
		return *this;
	}
	inline ulint &operator/=(const ulint &rhs)
	{
		return *this = div(rhs);
	}
	inline ulint &operator%=(const ulint &rhs)
	{
		return div(rhs), *this;
	}

	inline ulint &shlb(int l = 1)
	{
		if (a.empty())
			return *this;
		a.resize(a.size() + l);
		for (int i = (int)a.size() - 1; i >= l; i--)
			a[i] = a[i - l];
		for (int i = 0; i < l; i++)
			a[i] = 0;
		return *this;
	}
	inline ulint &shrb(int l = 1)
	{
		for (int i = 0; i < (int)a.size() - l; i++)
			a[i] = a[i + l];
		a.resize(max((int)a.size() - l, 0));
		return *this;
	}

	inline int cmp(const ulint &rhs) const
	{
		if (a.size() != rhs.a.size())
			return intcmp(a.size(), rhs.a.size());
		for (int i = (int)a.size() - 1; i >= 0; i--)
			if (a[i] != rhs.a[i])
				return intcmp(a[i], rhs.a[i]);
		return 0;
	}
	inline ulint div(const ulint &rhs)
	{
		assert(!rhs.a.empty());

		if (rhs > *this)
			return 0;

		ulint q, r;
		q.a.resize((int)a.size() - (int)rhs.a.size() + 1);
		for (int i = (int)a.size() - 1; i > (int)a.size() - (int)rhs.a.size(); i--)
		{
			r.shlb();
			r += a[i];
		}
		for (int i = (int)a.size() - (int)rhs.a.size(); i >= 0; i--)
		{
			r.shlb();
			r += a[i];

			if (r.cmp(rhs) < 0)
				q.a[i] = 0;
			else
			{
				int le = 0, ri = B;
				while (le != ri)
				{
					int mi = (le + ri) / 2;
					if ((rhs * mi).cmp(r) <= 0)
						le = mi + 1;
					else
						ri = mi;
				}
				q.a[i] = le - 1;
				r -= rhs * q.a[i];
			}
		}
		q.clr0();
		*this = r;
		return q;
	}


	friend inline ulint operator+(const ulint &lhs, const ulint &rhs)
	{
		ulint res = lhs;
		return res += rhs;
	}
	friend inline ulint operator-(const ulint &lhs, const ulint &rhs)
	{
		ulint res = lhs;
		return res -= rhs;
	}
	friend inline ulint operator*(const ulint &lhs, const ulint &rhs)
	{
		ulint res = lhs;
		return res *= rhs;
	}
	friend inline ulint operator/(const ulint &lhs, const ulint &rhs)
	{
		ulint res = lhs;
		return res.div(rhs);
	}
	friend inline ulint operator%(const ulint &lhs, const ulint &rhs)
	{
		ulint res = lhs;
		return res.div(rhs), res;
	}

	friend inline ostream &operator<<(ostream &out, const ulint &rhs)
	{
		if (rhs.a.size() == 0)
			out << "0";
		else
		{
			for (int i = (int)rhs.a.size() - 1; i >= 0; i--)
				out << setfill('0') << setw(L) << rhs.a[i];
		}
		return out;
	}

	friend inline bool operator<(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) < 0;
	}
	friend inline bool operator<=(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) <= 0;
	}
	friend inline bool operator>(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) > 0;
	}
	friend inline bool operator>=(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) >= 0;
	}
	friend inline bool operator==(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) == 0;
	}
	friend inline bool operator!=(const ulint &lhs, const ulint &rhs)
	{
		return lhs.cmp(rhs) != 0;
	}
};

struct lint
{
	ulint u;
	int s;

	lint(){}
	lint(int n)
	{
		if (n == 0)
			s = 0;
		else if (n < 0)
			s = -1, u = -n;
		else
			s = 1, u = n;
	}
	lint(int64 n)
	{
		if (n == 0)
			s = 0;
		else if (n < 0)
			s = -1, u = -n;
		else
			s = 1, u = n;
	}
	lint(ulint n)
	{
		s = 1, u = n;
		upds();
	}

	inline void upds()
	{
		if (u.a.empty())
			s = 0;
	}

	inline lint operator-() const
	{
		lint res = *this;
		res.s = -res.s;
		return res;
	}

	inline lint &operator+=(const lint &rhs)
	{
		if (s == 0)
			return *this = rhs;
		if (rhs.s == 0)
			return *this;
		if (s == rhs.s)
			u += rhs.u;
		else
			*this -= -rhs;
		upds();
		return *this;
	}
	inline lint &operator-=(const lint &rhs)
	{
		if (s == 0)
			return *this = -rhs;
		if (rhs.s == 0)
			return *this;
		if (s == rhs.s)
		{
			if (u > rhs.u)
				u -= rhs.u;
			else
			{
				s = -s;
				u = rhs.u - u;
			}
		}
		else
			*this += -rhs;
		upds();
		return *this;
	}
	inline lint &operator*=(const lint &rhs)
	{
		s *= rhs.s;
		u *= rhs.u;
		upds();
		return *this;
	}
	inline lint &operator/=(const lint &rhs)
	{
		s *= rhs.s;
		u /= rhs.u;
		upds();
		return *this;
	}
	inline lint &operator%=(const lint &rhs)
	{
		u %= rhs.u;
		upds();
		return *this;
	}

	inline int cmp(const lint &rhs) const
	{
		if (s != rhs.s)
			return intcmp(s, rhs.s);
		return u.cmp(rhs.u) * s;
	}

	friend inline lint operator+(const lint &lhs, const lint &rhs)
	{
		lint res = lhs;
		return res += rhs;
	}
	friend inline lint operator-(const lint &lhs, const lint &rhs)
	{
		lint res = lhs;
		return res -= rhs;
	}
	friend inline lint operator*(const lint &lhs, const lint &rhs)
	{
		lint res = lhs;
		return res *= rhs;
	}
	friend inline lint operator/(const lint &lhs, const lint &rhs)
	{
		lint res = lhs;
		return res /= rhs;
	}
	friend inline lint operator%(const lint &lhs, const lint &rhs)
	{
		lint res = lhs;
		return res %= rhs;
	}

	friend inline ostream &operator<<(ostream &out, const lint &rhs)
	{
		if (rhs.s == -1)
			out << "-";
		out << rhs.u;
		return out;
	}

	friend inline bool operator<(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) < 0;
	}
	friend inline bool operator<=(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) <= 0;
	}
	friend inline bool operator>(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) > 0;
	}
	friend inline bool operator>=(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) >= 0;
	}
	friend inline bool operator==(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) == 0;
	}
	friend inline bool operator!=(const lint &lhs, const lint &rhs)
	{
		return lhs.cmp(rhs) != 0;
	}
};

const int MaxN = 10000;
const int FL = 10;
const int FDL = 10 * L;

lint fone()
{
	return ulint(1).shlb(FL);
}

void ign(lint &x, int k = 1)
{
	if ((int)x.u.a.size() < k)
		x = 0;
	else
	{
		int p = x.u.a[k - 1];
		x.u.shrb(k);
		if (p * 2 >= B)
			x.u += 1;
		x.upds();
	}
}

lint sigmoid(lint x)
{
	int sgn = x.s;
	if (x < 0)
		x = -x;

	int exL = 5;
	lint res = 0;

	if (x >= 256 * fone())
		res = 1, res.u.shlb(FL + exL + FL + exL);
	else
	{
		lint term = 1;
		term.u.shlb(FL + exL);
		for (int i = 0; (int)term.u.a.size() >= exL && (int)res.u.a.size() <= FL + exL + FL + exL; i++)
		{
			if (i > 0)
			{
				term *= x;
				term /= i * 256;
				ign(term, FL);
			}
			res += term;
		}
		for (int k = 0; k < 8; k++)
		{
			res = res * res;
			ign(res, FL + exL);
		}
	}

	lint one = 1;
	lint lone = 1;
	one.u.shlb(FL + exL);
	lone.u.shlb(FL + exL + FL + exL);

	lint sx = lone / (one + res);
	if (sgn > 0)
		sx = one - sx;
	ign(sx, exL);
	return sx;
}

int n = 0;
lint x[MaxN + 1];

int opadd(int i, int j)
{
	x[++n] = x[i] + x[j];
	return n;
}
int opneg(int i)
{
	x[++n] = -x[i];
	return n;
}
int opaddc(int i, lint c)
{
	x[++n] = x[i] + c;
	return n;
}
int opshl(int i, int k)
{
	x[++n] = x[i];
	while (k--)
		x[n] *= 2;
	return n;
}
int opshr(int i, int k)
{
	x[++n] = x[i];
	while (k--)
	{
		x[n] *= B / 2;
		ign(x[n]);
	}
	return n;
}
int opsig(int i)
{
	x[++n] = sigmoid(x[i]);
	return n;
}
int opflr(int i) // it's wrong
{
	x[++n] = x[i];
	x[n].u.shrb(FL);
	x[n].u.shlb(FL);
	x[n].upds();
	return n;
}
int opcmp(int i, int j)
{
	if (x[i] < x[j])
		x[++n] = -fone();
	else if (x[i] > x[j])
		x[++n] = fone();
	else
		x[++n] = 0;
	return n;
}
int opmax(int i, int j)
{
	if (x[i] < x[j])
		x[++n] = x[j];
	else
		x[++n] = x[i];
	return n;
}
int opmul(int i, int j)
{
	x[++n] = x[i] * x[j];
	ign(x[n], FL);
	return n;
}

lint readLInt(InStream &in)
{
	pattern lintpat("-?([0-9]{0,1000}.[0-9]{0,90}|[0-9]{0,1000})");

	string orig_s = in.readToken();
	if (!lintpat.matches(orig_s))
		in.quitf(_pe, "Expected real number, but \"%s\" found", orig_s.c_str());

	string s = orig_s;
	if (s.empty())
		in.quitf(_pe, "Expected real number, but \"%s\" found", orig_s.c_str());

	int xp = s.find('.');
	if (xp != -1)
	{
		s.erase(s.begin() + xp);
		xp = (int)s.size() - xp;
	}
	else
		xp = 0;
	if (s.empty())
		in.quitf(_pe, "Expected real number, but \"%s\" found", orig_s.c_str());

	lint v;
	if (s[0] == '-')
	{
		v.s = -1;
		s = s.substr(1);
	}
	else
		v.s = 1;
	if (s.empty())
		in.quitf(_pe, "Expected real number, but \"%s\" found", orig_s.c_str());

	v.u = 0;
	for (int i = 0; i < (int)s.size(); i++)
		v.u = v.u * 10 + (s[i] - '0');
	while (xp < FDL)
		v *= 10, xp++;
	v.upds();
	return v;
}

bool io_redirected = false;
deque<lint> prog_in;
deque<lint> prog_out;

int opin()
{
	if (io_redirected)
	{
		if (prog_in.empty())
			quitf(_wa, "The number of input nodes exceeded the number of input values");
		x[++n] = prog_in.front(), prog_in.pop_front();
	}
	else
		x[++n] = readLInt(ouf);
	return n;
}
void opout(int i)
{
	if (io_redirected)
		prog_out.push_back(x[i]);
	else
	{
		if (x[i].s == 0)
			cout << "0";
		else
		{
			if (x[i].s < 0)
				cout << "-";
			if ((int)x[i].u.a.size() <= FL)
				cout << "0";
			else
			{
				cout << x[i].u.a.back();
				for (int k = (int)x[i].u.a.size() - 2; k >= FL; k--)
					cout << setfill('0') << setw(L) << x[i].u.a[k];
			}
			cout << ".";
			for (int k = FL - 1; k >= 0; k--)
				cout << setfill('0') << setw(L) << (k < (int)x[i].u.a.size() ? x[i].u.a[k] : 0);
		}
		cout << endl;
	}

	x[++n] = x[i];
}

struct xvar
{
	int id;

	xvar() {}
	xvar(const int &_id)
		: id(_id) {}

	friend inline xvar operator+(const xvar &lhs, const lint &rhs)
	{
		return opaddc(lhs.id, rhs);
	}
	friend inline xvar operator+(const xvar &lhs, const xvar &rhs)
	{
		return opadd(lhs.id, rhs.id);
	}
	friend inline xvar operator<<(const xvar &lhs, const int &rhs)
	{
		return opshl(lhs.id, rhs);
	}
	friend inline xvar operator>>(const xvar &lhs, const int &rhs)
	{
		return opshr(lhs.id, rhs);
	}
	inline xvar operator-() const
	{
		return opneg(id);
	}
};

inline xvar sig(xvar x)
{
	return opsig(x.id);
}

int n_op;
int opa[MaxN + 1][3];
lint opc[MaxN + 1];

set<char> used_adv_ops;

void init(InStream &in)
{
	while (!in.seekEof())
	{
		int i = ++n_op;
		if (i > MaxN)
			in.quitf(_wa, "Too many nodes!");

		string chs = in.readToken();
		if (!pattern("[IO\\-S+<>PM*C]").matches(chs))
			in.quitf(_pe, "Expected I, O, -, S, +, <, >, P, M, * or C, but \"%s\" found", chs.c_str());
		char ch = chs[0];

		opa[i][0] = (int)ch;
		switch (ch)
		{
			case 'I':
				break;
			case 'O':
			case '-':
			case 'S':
				opa[i][1] = in.readInt();
				if (!(1 <= opa[i][1] && opa[i][1] < i))
					in.quitf(_wa, "i should be in range [1, t-1] at node #%d", i);
				break;
			case '+':
			case 'P':
			case 'M':
			case '*':
				opa[i][1] = in.readInt();
				opa[i][2] = in.readInt();
				if (!(1 <= opa[i][1] && opa[i][1] < i))
					in.quitf(_wa, "i should be in range [1, t-1] at node #%d", i);
				if (!(1 <= opa[i][2] && opa[i][2] < i))
					in.quitf(_wa, "j should be in range [1, t-1] at node #%d", i);
				break;
			case '<':
			case '>':
				opa[i][1] = in.readInt();
				opa[i][2] = in.readInt();
				if (!(1 <= opa[i][1] && opa[i][1] < i))
					in.quitf(_wa, "i should be in range [1, t-1] at node #%d", i);
				if (!(0 <= opa[i][2] && opa[i][2] <= 10000))
					in.quitf(_wa, "k should be in range [0, 10000] at node #%d", i);
				break;
			case 'C':
				opa[i][1] = in.readInt();
				opc[i] = readLInt(in);
				if (!(1 <= opa[i][1] && opa[i][1] < i))
					in.quitf(_wa, "i should be in range [1, t-1] at node #%d", i);
				break;
		}
	}
}

void run()
{
	lint bound = 1;
	for (int i = 0; i < FDL + 1000; i++)
		bound *= 10;
	for (int i = 1; i <= n_op; i++)
	{
		switch (opa[i][0])
		{
			case 'I':
				opin();
				break;
			case 'O':
				opout(opa[i][1]);
				break;
			case '-':
				opneg(opa[i][1]);
				break;
			case 'S':
				opsig(opa[i][1]);
				break;
			case '+':
				opadd(opa[i][1], opa[i][2]);
				break;
			case '<':
				opshl(opa[i][1], opa[i][2]);
				break;
			case '>':
				opshr(opa[i][1], opa[i][2]);
				break;
			case 'P':
				used_adv_ops.insert('P');
				opcmp(opa[i][1], opa[i][2]);
				break;
			case 'M':
				used_adv_ops.insert('M');
				opmax(opa[i][1], opa[i][2]);
				break;
			case '*':
				used_adv_ops.insert('*');
				opmul(opa[i][1], opa[i][2]);
				break;
			case 'C':
				opaddc(opa[i][1], opc[i]);
				break;
		}
		if (!(-bound <= x[n] && x[n] <= bound))
			quitf(_wa, "The output of node #%d is too large", n);
	}
}

// (-10^9, 10^9)
lint randlr()
{
	lint x;
	x.s = rnd.next(2) ? 1 : -1;
	for (int i = 0; i < FL - 1; i++)
		x.u.a.push_back(0);
	for (int i = 0; i < 2; i++)
		x.u.a.push_back(rnd.next(0, B - 1));
	x.u.clr0();
	x.upds();
	return x;
}
lint randlu()
{
	return rnd.next(1ll << 32) * fone();
}
lint randl01()
{
	return rnd.next(2) * fone();
}

int main(int argc, char **argv)
{
	if (argc == 3 && strcmp(argv[1], "-f") == 0)
	{
		char *targv[] = {argv[0], argv[2], (char*)"stdout"};
		registerInteraction(3, targv);

		init(inf);

		run();
	}
	else
	{
		if (argc == 2)
		{
			int num;
			ensuref(sscanf(argv[1], "%d", &num) == 1 && 1 <= num && num <= 10, "Invalid <case-no>");

			char inf_name[20];
			char ouf_name[20];
			char ans_name[20];
			sprintf(inf_name, "nodes%d.in", num);
			sprintf(ouf_name, "nodes%d.out", num);
			sprintf(ans_name, "nodes%d.ans", num);

			registerTestlib(3, inf_name, ouf_name, ans_name);

			num = inf.readInt(1, 10, "num");

			init(ouf);

			io_redirected = true;

			lint eps = ulint(1).shlb(FL - 1);

			vector<deque<lint> > ind, oud;
			deque<lint> tq;

			const long long U = (1ll << 32) - 1;

			switch (num)
			{
				case 1:
					tq.clear(), tq.push_back(0 * fone()), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(2 * fone()), tq.push_back(2 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(2 * fone()), tq.push_back(-2 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(B * fone()), tq.push_back(0 * fone()), ind.push_back(tq);
					for (int i = 0; i < 7; i++)
						tq.clear(), tq.push_back(randlr()), tq.push_back(randlr()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back(-(ind[i][0] + ind[i][1]) * 2), oud.push_back(tq);
					break;
				case 2:
					tq.clear(), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(B * fone()), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlr()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back(sigmoid(-ind[i][0] * 17)), oud.push_back(tq);
					break;
				case 3:
					tq.clear(), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(-B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(eps), ind.push_back(tq);
					tq.clear(), tq.push_back(-eps), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlr()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back(ind[i][0].s * fone()), oud.push_back(tq);
					break;
				case 4:
					tq.clear(), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(-B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(eps), ind.push_back(tq);
					tq.clear(), tq.push_back(-eps), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlr()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back(ind[i][0].u), oud.push_back(tq);
					break;
				case 5:
					tq.clear();
					for (int k = 0; k < 32; k++)
						tq.push_back(0);
					ind.push_back(tq);

					tq.clear();
					for (int k = 0; k < 32; k++)
						tq.push_back(fone());
					ind.push_back(tq);

					for (int i = 0; i < 5; i++)
					{
						tq.clear();
						for (int k = 0; k < 32; k++)
							tq.push_back(randl01());
						ind.push_back(tq);
					}

					for (int i = 0; i < (int)ind.size(); i++)
					{
						tq.clear();

						lint res = 0;
						for (int k = 0; k < 32; k++)
							res = res * 2 + ind[i][k];
						tq.push_back(res);

						oud.push_back(tq);
					}
					break;
				case 6:
					tq.clear(), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(U * fone()), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlu()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
					{
						tq.clear();

						lint res = ind[i][0] / fone();
						for (int k = 0; k < 32; k++)
							tq.push_back((res % 2) * fone()), res /= 2;
						reverse(tq.begin(), tq.end());

						oud.push_back(tq);
					}
					break;
				case 7:
					for (int i = 0; i < 7; i++)
					{
						long long va = rnd.next(1ll << 32), vb = rnd.next(1ll << 32);
						if (i == 0)
							vb = va;
						else if (i == 1)
							vb = U ^ va;
						tq.clear(), tq.push_back(va), tq.push_back(vb), ind.push_back(tq);
						tq.clear(), tq.push_back(va ^ vb), oud.push_back(tq);
					}
					break;
				case 8:
					tq.clear(), tq.push_back(0 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(-B * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(eps), ind.push_back(tq);
					tq.clear(), tq.push_back(-eps), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlr()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back(ind[i][0] / 10), oud.push_back(tq);
					break;
				case 9:
					tq.clear();
					for (int k = 0; k < 16; k++)
						tq.push_back(0);
					ind.push_back(tq);

					tq.clear();
					for (int k = 0; k < 16; k++)
						tq.push_back(randlr());
					ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq = ind[i], sort(tq.begin(), tq.end()), oud.push_back(tq);
					break;
				case 10:
					tq.clear(), tq.push_back(0 * fone()), tq.push_back(0 * fone()), tq.push_back(U * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(U * fone()), tq.push_back(U * fone()), tq.push_back(U * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back((U - 1) * fone()), tq.push_back((U - 1) * fone()), tq.push_back(U * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(U * fone()), tq.push_back(U * fone()), tq.push_back(233 * fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(randlu()), tq.push_back(randlu()), tq.push_back(fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(randlu()), tq.push_back(randlu()), tq.push_back(fone()), ind.push_back(tq);
					tq.clear(), tq.push_back(randlu()), tq.push_back(randlu()), tq.push_back(fone()), ind.push_back(tq);
					for (int i = 0; i < 5; i++)
						tq.clear(), tq.push_back(randlu()), tq.push_back(randlu()), tq.push_back(rnd.next(1ll, U) * fone()), ind.push_back(tq);

					for (int i = 0; i < (int)ind.size(); i++)
						tq.clear(), tq.push_back((ind[i][0] / fone()) * (ind[i][1] / fone()) % (ind[i][2] / fone()) * fone()), oud.push_back(tq);
					break;
			}

			for (int i = 0; i < (int)ind.size(); i++)
			{
				prog_in = ind[i], prog_out.clear(), n = 0, run();
				if (prog_out.size() != oud[i].size())
					quitf(_wa, "The number of output values doesn't match");
				for (int k = 0; k < (int)prog_out.size(); k++)
					if ((prog_out[k] - oud[i][k]).u > eps.u)
						quitf(_wa, "Output values don't match");
			}

			int scr = 0;
			for (int i = 1; i <= 10; i++)
				scr += n_op <= ans.readInt();
			scr -= (int)used_adv_ops.size() * 4;
			if (scr < 0)
				scr = 0;

			string adv;
			if (!used_adv_ops.empty())
			{
				adv += ", including type";
				if (used_adv_ops.size() > 1)
					adv += "s";
				adv += " ";
				for (set<char>::iterator it = used_adv_ops.begin(); it != used_adv_ops.end(); it++)
					adv += string(1, *it) + ", ";
				adv.erase(adv.end() - 1);
				adv.erase(adv.end() - 1);
			}

			if (scr == 10)
				quitf(_ok, "The total number of nodes is %d. score: %d", n_op, scr);
			else
				quitp((double)scr / 10, "The total number of nodes is %d%s. score: %d", n_op, adv.c_str(), scr);
		}
		else
			quitf(_fail, "Invalid argument");
	}
}


