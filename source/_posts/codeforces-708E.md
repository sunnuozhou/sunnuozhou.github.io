---
title: codeforces 708E
tags:
  - OI
  - codeforces
  - DP
date: 2020-01-26 16:42:05
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/708/problem/E)

初始时，记录$dp_{i,l,r}$表示第$i$行，依然存在的区间是$(l,r]$的时候和最上面连通的概率，显然有

$dp_{i,l,r}=p_{l,r}\sum_{(l',r']\cap(l,r]}dp_{i-1,l',r'}$

其中$p_{l,r}$表示最后剩下区间$(l,r]$的概率。

记录$f_{i,r}$表示$\sum_{l<r}dp_{i,l,r}$，$sumf_{i,j}$表示$\sum_{r\le j}f_{i,r}$。

那么有$dp_{i,l,r}=p_{l,r}( sumf_{i-1,m}-sumf_{i-1,l}-sumf_{i-1,m-r})$，即消去和$(l,r]$不相交的区间。

$f_{i,j}=\sum_{r\le j}p_{l,r}( sumf_{i-1,m}-sumf_{i-1,l}-sumf_{i-1,m-r})$

记录多个前缀和即可优化DP，时间复杂度$O(nm+k)$。

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
const int N = 2010,K = 201000,mod = 1e9+7;
int s[N],n,m,a,b,k,f[N][N];
ll fac[K],ifac[K],q[K];
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
int main(){
	read(n);read(m);
	read(a);read(b);
	read(k);
	ll P=a*fp(b,mod-2)%mod;
	fac[0]=1;
	for(int i=1;i<=k;i++) fac[i]=fac[i-1]*i%mod;
	ifac[k]=fp(fac[k],mod-2);
	for(int i=k;i;i--) ifac[i-1]=ifac[i]*i%mod;
	for(int i=0;i<=m&&i<=k;i++) q[i]=fp(P,i)*fp(1-P,k-i)%mod*fac[k]%mod*ifac[i]%mod*ifac[k-i]%mod;
	f[0][m]=1;
	for(int i=1;i<=n;i++){
		s[0]=f[i-1][0];
		for(int j=1;j<=m;j++)
			s[j]=(s[j-1]+f[i-1][j])%mod;
		ll s1=q[0],s2=0;
		for(int j=1;j<=m;j++){
			f[i][j]=((s[m]-s[m-j])*s1-s2)%mod*q[m-j]%mod;
			s1=(s1+q[j])%mod;
			s2=(s2+s[j]*q[j])%mod;
		}
	}
	ll ans=0;
	for(int i=1;i<=m;i++) ans=(ans+f[n][i])%mod;
	cout<<(ans+mod)%mod<<'\n';
	return 0;
}
```

