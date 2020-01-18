---
title: codeforces 585E
tags:
  - OI
  - codeforces
  - 数论
date: 2020-01-18 08:37:06
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/585/problem/E)

先求出$h_i$表示$gcd$是$i$的倍数的集合有几个，$h_i=2^{cnt_i}$，其中$cnt_i$表示$i$的倍数的个数。

那么考虑容斥，$gcd$不为一的集合数量为$Sum=2^n-\sum\mu_i h_i$。

枚举那单独一个数的位置，令它的值为$x$，那么对于这个$x$可行的集合的数量为$Sum+\sum_{d|x,d\ne1}\mu_d h_d$。

直接求和即可。

时间复杂度$O(V+n\times 2^k)$，其中$V$为值域，$k$为一个数的不同因子个数。

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
const int N = 10001000,mod = 1e9+7;
int n,m,a[N],f[N],h[N],mu[N],pri[N],tot;
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
void init(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!f[i]){f[i]=i;pri[++tot]=i;mu[i]=-1;}
		for(int j=1;pri[j]*i<=n;j++){
			f[pri[j]*i]=pri[j];
			mu[pri[j]*i]=-mu[i];
			if(pri[j]==f[i]){mu[pri[j]*i]=0;break;}
		}
	}
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),h[a[i]]++,m=max(a[i],m);
	init(m);
	for(int i=1;i<=m;i++){
		for(int j=i+i;j<=m;j+=i)
			h[i]+=h[j];
		h[i]=fp(2,h[i])-(i>1);
	}
	ll s1=0,s2=0;
	for(int i=1;i<=m;i++)
		s1=(s1+h[i]*mu[i])%mod;
	s2=fp(2,n)-s1;
	ll ans=0;
	for(int i=1;i<=n;i++){
		int x=a[i];
		vector<int> v;
		while(x>1){
			if(v.empty()||v.back()!=f[x]) v.push_back(f[x]);
			x/=f[x];
		}
		ll now=0;
		for(int j=1;j<1<<v.size();j++){
			ll p=1;
			for(int k=0;k<v.size();k++)
				if(j>>k&1) p*=v[k];
			now=(now+mu[p]*h[p])%mod;
		}
		ans=(ans+now+s2)%mod;
	}
	cout<<(ans+mod)%mod<<'\n';
	return 0;
}


```

