---
title: atcoder grand contest 043C
tags:
  - OI
  - atcoder
  - 贪心
  - 博弈
date: 2020-03-23 17:57:16
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc043/tasks/agc043_c)

因为价值不在一个级别上，并且价值相同的点不会互相干扰，所以可以贪心的判断每个点可不可以在独立集中。

而这个贪心的过程和这个博弈问题等价：$X,Y,Z$图上各有一个棋子，先后手轮流移动一枚棋子，棋子的下标不能变小，不能移动就输。

所有在贪心中被选取的点就是在博弈中的先手必败点，而这个博弈问题可以轻松使用$SG$函数解决。

由于$SG$函数不超过$\sqrt{M}$，可以暴力枚举在$X,Y$图中的$SG$函数来计算答案。

时间复杂度$O(N+M)$。

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
const int N = 101000,mod = 998244353;
ll p[N];
int n;
struct graph{
	int hsh[N],f[N],m,n;
	ll h[N];
	vector<int> e[N];
	void init(int S){
		n=S;
		read(m);
		for(int i=1;i<=m;i++){
			int x,y;read(x);read(y);
			if(x>y) swap(x,y);
			e[x].push_back(y);
		}
		for(int i=n;i;i--){
			for(int v:e[i]) hsh[f[v]]++;
			while(hsh[f[i]]) f[i]++;
			h[f[i]]=(h[f[i]]+p[i])%mod;
			for(int v:e[i]) hsh[f[v]]--;
		}
	}
}Gx,Gy,Gz;
int main(){
	read(n);
	p[0]=1;p[1]=1000000000000000000ll%mod;
	for(int i=2;i<=n;i++) p[i]=p[i-1]*p[1]%mod;
	Gx.init(n);
	Gy.init(n);
	Gz.init(n);
	int K=500;
	ll ans=0;
	for(int i=0;i<=K;i++)
		for(int j=0;j<=K;j++)
			ans=(ans+Gx.h[i]*Gy.h[j]%mod*Gz.h[i^j])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

