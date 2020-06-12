---
title: atcoder grand contest 045D
tags:
  - OI
  - atcoder
date: 2020-06-11 16:33:54
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc045/tasks/agc045_d)

将排列 $p$ 抽象为若干个环。

最优策略如下：

- 选择一个编号最小的亮的灯，并按下按钮。

- 如果没有亮的灯，游戏结束。

- 如果改变状态的灯是它自己，那么游戏结束。

- 否则你可以将环上的点全部点亮，然后重复以上操作。

那么，一个可以获胜的局面要满足以下要求：


- 所有环中，都至少有一个位置 $w\le A$。

- 令 $k$ 表示最小的 $p_k=k$。
- 如果 $k$ 存在，如果一个环中有不亮的位置，那么它至少要有一个位置 $w\lt k$。

先考虑 $k$ 存在的情况。

枚举 $k$ 的大小，因为要求比 $k$ 小的位置要满足 $p_i\ne i$ 这个限制难以计算，我们对这个限制进行容斥。

$ans=\sum\limits_{1\le k\le A} \sum\limits_{0\le j\lt k}(-1)^jC(i-1,j)G(i-j-1,A-i)$

其中 $G(a,b)$ 表示 $k$ 左侧有 $a$ 个亮着的位置，右侧有 $b$ 个亮着的位置，不一定满足"比 $k$ 小的位置要满足 $p_i\ne i$ "，但满足上述其他限制的方案数。

考虑如何计算 $G(a,b)$，先排列左侧的 $a$ 个位置，有 $a!$ 种方法，然后考虑插入灭着的 $n-A$ 个位置，方案数为 $\frac{(n-A+a-1)!}{(a-1)!}$，最后考虑 $k$ 后面的 $b$ 个，由于这 $b$ 个构成的环不一定要和前 $a$ 个连通，方案数为 $\frac{(n-A+a+b)}{(n-A+a)!}$。

对于 $k$ 不存在的情况，也可以对“前 $A$ 个不存在 $p_i=i$” 这个限制进行容斥，计算方法大体类似。

时间复杂度 $O(A^2+n)$。

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
const int N = 101000,mod = 1e9+7;
int n,K;
ll fac[10000010],ifac[10000010];
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
ll UP(int n,int m){
	if(n==0) return 0;
	return fac[n+m-1]*ifac[n-1]%mod;
}
ll C(int n,int m){
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int main(){
	read(n);read(K);
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n]=fp(fac[n],mod-2);
	for(int i=n;i;i--) ifac[i-1]=ifac[i]*i%mod;
	ll ans=0;
	for(int i=1;i<=K;i++){
		for(int j=0;j<i;j++)
			ans=(ans+(j&1?-1:1)*C(i-1,j)*fac[i-1-j]%mod*UP(i-1-j,n-K)%mod*UP(i-j-K+n,K-i))%mod;
	}
	for(int i=0;i<=K;i++){
		ans=(ans+(i&1?-1:1)*C(K,i)*fac[K-i]%mod*UP(K-i,n-K))%mod;
	}
	cout<<(ans+mod)%mod<<'\n';
	return 0;
}


```

