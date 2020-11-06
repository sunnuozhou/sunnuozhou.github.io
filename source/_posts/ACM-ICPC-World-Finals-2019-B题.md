---
title: ACM ICPC World Finals 2019 B题
tags:
  - OI
  - codeforces
  - DP
date: 2020-11-04 11:48:49
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/B)

由于时限足够大，$O(n^2)$ 的算法可以通过本题。

记 $f_{i}$ 表示最后一个柱子在 $i$ 的最优答案，转移时枚举前一个柱子。考虑到每一个柱子的限制都是一个区间，从后到前枚举上一个柱子，并不断更新可以转移的区间。

<!--more-->

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 101000;
int n;
ll H,A,B,x[N],y[N],f[N];
ll Sqrt(ll x){
	ll y=sqrt(x);
	while(y*y>x) y--;
	while((y+1)*(y+1)<=x) y++;
	return y;
}
int main(){
	read(n);read(H);read(A);read(B);
	for(int i=1;i<=n;i++) read(x[i]),read(y[i]);
	memset(f,63,sizeof(f));
	f[1]=A*(H-y[1]);
	for(int i=2;i<=n;i++){
		ll L=x[i]-2*(H-y[i]),R=x[i];
		ll h1=H-y[i];
		for(int j=i-1;j;j--){
			ll len=x[i]-x[j],h2=H-y[j];
			ll a=1,b=-2*h2-2*len,c=h2*h2+len*len;
			L=max(L,x[i]-(-b+Sqrt(b*b-4*a*c)));
			if(2*(H-y[j])<x[i]-x[j]) R=min(R,x[i]-(-b-Sqrt(b*b-4*a*c)));
	//		cerr<<i<<' '<<j<<' '<<L<<' '<<R<<'\n';
			if(L<=x[j]&&x[j]<=R)
				f[i]=min(f[i],f[j]+h1*A+len*len*B);
		}
	}
	if(f[n]>1e18) cout<<"impossible\n";
	else cout<<f[n]<<'\n';
	return 0;
}
```

