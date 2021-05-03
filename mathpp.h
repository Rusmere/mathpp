//The functions in this header file is compatible with unsigned long long(ull).
#ifndef _MATHPP_H
#define _MATHPP_H
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
typedef unsigned long long ull;
typedef long long ll;
using namespace std;
class intinf {
	public:
		static const int BASE = 100000000;
		static const int WIDTH = 8;
		vector<int> s;

		intinf(long long num = 0) {
			*this = num; 
		}
		intinf operator = (long long num) {
			s.clear();
			do {
				s.push_back(num % BASE);
				num /= BASE;
			} while(num > 0);
			return *this;
		}
		intinf operator = (const string& str) {
			s.clear();
			int x, len = (str.length() - 1) / WIDTH + 1;
			for(int i = 0; i < len; i++) {
				int end = str.length() - i*WIDTH;
				int start = max(0, end - WIDTH);
				sscanf(str.substr(start, end-start).c_str(), "%d", &x);
				s.push_back(x);
			}
			return *this;
		}
		intinf operator + (const intinf& b) const {
			intinf c;
			c.s.clear();
			for(int i = 0, g = 0; ; i++) {
				if(g == 0 && i >= s.size() && i >= b.s.size()) break;
				int x = g;
				if(i < s.size()) x += s[i];
				if(i < b.s.size()) x += b.s[i];
				c.s.push_back(x % BASE);
				g = x / BASE;
			}
			return c;
		}
};

ostream& operator << (ostream &out, const intinf& x) {
	out << x.s.back();
	for(int i = x.s.size()-2; i >= 0; i--) {
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for(int j = 0; j < strlen(buf); j++) out << buf[j];
	}
	return out;
}

istream& operator >> (istream &in, intinf& x) {
	string s;
	if(!(in >> s)) return in;
	x = s;
	return in;
}
bool odd(ull a) {
	return a%2==0?0:1;
}
bool even(ull a) {
	return a%2==0?1:0;
}
ull gcd(ull a,ull b) {
	return b>0?gcd(b,a%b):a;
}
ull lcm(ull a,ull b) {
	return a*b/gcd(a,b);
}
int legendre(ull a,ull p) { //Legendre symbol
	return (ull)pow(a,(p-1)/2)%p;
}
int jacobi(ull a,ull n) { //Jacobi symbol

}
bool lehmann(ull p) { //The Lehmann prime test
	srand(unsigned(time(0)));
	ull a=rand()%p;
	if((ull(pow(a,(p-1)/2))%p)!=1||(ull(pow(a,(p-1)/2))%p)!=p-1) {
		return false;
	}
	for(int i=0; i<=6; i++) {
		if(!lehmann(p)) {
			return false;
		}
	}
	return true;
}
bool rabinmiller(ull n) {
	if(n%2==0) {
		return false;
	}
	srand(unsigned(time(0)));
	ull s=n-1;
	ull t=0;
	while(s%2==0) {
		s/=2;
		t+=1;
	}
	for(int k=0; k<=4; k++) {
		ull a=rand()%(n-3)+2;
		ull v=((ull)pow(a,s))%n;
		if(v!=1) {
			ull i=0;
			while(v!=(n-1)) {
				if(i==(t-1)) {
					return false;
				} else {
					i++;
					v=((ull)pow(v,2))%n;
				}
			}
		}
	}
	return true;
}
ull modinv(ull a,ull b) { //Todo
	if(gcd(a,b)!=1) {
		return;
	}
	ull* tmp=new ull[3];
	ull u1=1,u2=0,u3=a,v1=0,v2=1,v3=b;
	while(v3!=0) {
		ull q=u3/v3;
		tmp[0]=v1;
		tmp[1]=v2;
		tmp[2]=v3;
		v1=u1-q*v1;
		v2=u2-q*v2;
		v3=u3-q*v3;
		u1=tmp[0];
		u2=tmp[1];
		u3=tmp[2];
	}
	delete[] tmp;
	return b%u1;
}
#endif
