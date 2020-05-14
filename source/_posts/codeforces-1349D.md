---
title: codeforces 1349D
tags:
  - OI
  - 概率
  - DP
date: 2020-05-14 12:59:20
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/1349/problem/D)

令 $P_i$ 表示在第 $i$ 个人结束的概率，$E_i$ 表示在第 $i$ 个人结束的概率乘上在第 $i$ 个人结束的期望时间。

令 $E'_i$ 表示只有在第 $i$ 个人处才可以结束的情况下，需要的期望时间。

令 $C$ 表示手中没有饼干的情况下，获得全部饼干的期望时间。（这显然对所有人是一样的）

$$E_i=E'_i-\sum\limits_{j=1}^{n}[i\ne j](E_j+C\times P_j)$$

$$\sum\limits_{j=1}^nE_j=E'_i-\sum\limits_{j=1}^n [i\ne j]C\times P_j$$

$$n\times\sum\limits_{i=1}^nE_i=\sum\limits_{i=1}^nE'_i-(n-1)\sum\limits_{j=1}^n C\times P_j$$

$$n\times ans=\sum\limits_{i=1}^nE'_i-(n-1)\times C$$

令 $f_x$ 表示现在手里有 $x$ 个饼干，期望过多久变成 $x+1$。

显然 $E'_i=f_{a_i},C=f_0$

递推求出 $f$ 即可。

时间复杂度 $O(n+\sum a_i \log 998244353)$。

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
const int N = 301000,mod = 998244353;
int n,sum;
ll a[N],f[N];
ll fp(ll a,ll k){
	ll ans=1;
	a%=mod;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),sum+=a[i];
	f[0]=fp(1-(n-2)*fp(n-1,mod-2)%mod,mod-2);
	ll inv=fp(sum,mod-2);
	for(int i=1;i<sum;i++)
		f[i]=(1+i*inv%mod*f[i-1])%mod*fp(1-i*inv%mod-(n-2)*fp(n-1,mod-2)%mod*(sum-i)%mod*inv,mod-2)%mod;
	for(int i=sum-2;~i;i--)
		f[i]=(f[i]+f[i+1])%mod;
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans=(f[a[i]]+ans)%mod;
	ans=(ans-(n-1)*f[0])%mod;
	cout<<(ans*fp(n,mod-2)%mod+mod)%mod<<'\n';
	return 0;
}
```

