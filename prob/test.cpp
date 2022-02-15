#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
const int Mod = 1000000007;
const int Inv100 = 570000004;

inline LL Inv(LL b) {
	LL a = 1;
	for (int e = Mod - 2; e; e >>= 1, b = b * b % Mod)
		if (e & 1) a = a * b % Mod;
	return a;
}

int N;
LL P, Q;

int main() {

	scanf("%d", &N);
	P = 1, Q = 0;
	while (N--) {
		LL a, b;
		scanf("%lld%lld", &a, &b);
		a = a * Inv100 % Mod, b = b * Inv100 % Mod;
		LL W = Inv((1 - Q * b % Mod + Mod) % Mod);
		Q = (b + a * a % Mod * Q % Mod * W) % Mod;
		P = P * a % Mod * W % Mod;
        cout<<P<<" "<<Q<<endl;
	}
	printf("%lld\n", P);
	return 0;
}
