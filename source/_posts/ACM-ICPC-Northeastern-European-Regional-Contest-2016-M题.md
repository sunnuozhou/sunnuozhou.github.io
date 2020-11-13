---
title: ACM ICPC Northeastern European Regional Contest 2016 M题
tags:
  - OI
  - codeforces
  - 贪心
date: 2020-11-12 10:43:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190/)

先考虑暴力费用流，每次对新加入的点求最短路，被逆向走过的边的边权会被当成-1。

考虑优化它，记录 $mn_i$ 表示从 $i$ 走到 $i$ 子树中有剩余的点，最短路是多少。

枚举往上跳了几级父亲，求出最短路。

然后更新每条边的正负流量，对于最短路可能变化的点重新求出 $mn$。

由于树的深度为 $O(\log n)$， 时间复杂度 $O(n\log n)$。

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
int n,m,mn[N],w[N],a[N],fw[N];
void get_mn(int x){
	if(a[x]) mn[x]=0,w[x]=x;
	else mn[x]=1e9,w[x]=0;
	if(x*2<=n&&mn[x*2]+(fw[x*2]>0?-1:1)<mn[x]) mn[x]=mn[x*2]+(fw[x*2]>0?-1:1),w[x]=w[x*2];
	if(x*2+1<=n&&mn[x*2+1]+(fw[x*2+1]>0?-1:1)<mn[x]) mn[x]=mn[x*2+1]+(fw[x*2+1]>0?-1:1),w[x]=w[x*2+1];
}
int main(){
	freopen("mole.in","r",stdin);
	freopen("mole.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=n;i;i--) get_mn(i);
	ll ans=0;
	while(m--){
		int Mn=1e9,W=0,z=0;
		int x;read(x);
		for(int i=x,L=0;i;L+=fw[i]<0?-1:1,i>>=1)
			if(mn[i]+L<Mn) Mn=mn[i]+L,W=w[i],z=i;
		ans+=Mn;
		cout<<ans<<' ';
		for(int i=x;i!=z;i>>=1) fw[i]++;
		for(int i=W;i!=z;i>>=1) fw[i]--;
		a[W]--;
		for(int i=x;i!=z;i>>=1) get_mn(i);
		for(int i=W;i!=z;i>>=1) get_mn(i);
		for(int i=z;i;i>>=1) get_mn(i);
	}
	cout<<'\n';
	return 0;
}


```

