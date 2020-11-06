---
title: ACM ICPC World Finals 2019 K题
tags:
  - OI
  - codeforces
date: 2020-11-06 11:37:50
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/K)

首先考虑好处理的情况，即所有周期两两互质或相同，由于周期互质的灯是相互独立的，周期相同的灯也可以枚举时间单独考虑，所以可以在 $O(np)$ 的时间内处理完。

如果两个周期是倍数关系，那么也可以扩展为周期相同。

考虑怎么将一般情况变为好处理的情况，如果找到一个 $X$，枚举 $t$，把所有 $t,X+t,2X+T\cdots$ 一起考虑，那么一个原本周期为 $p$ 的灯周期会变为 $\frac{p}{\gcd(p,X)}$，如果取 $X=2^3\times3^2\times5\times 7=2520$，那么所有周期会变动要么互质要么一个是另一个的倍数，即号处理的情况。

时间复杂度 $O(Xnp)$。

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
struct node{
	int p,x;
	int h[110];
	void clear(){memset(h,0,sizeof(h));}
}a[510],b[510];
int n,vis[110];
double ans[510],ps[510];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
void solve(){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) vis[b[i].p]=1;
	for(int i=1;i<=n;i++){
		int mx=b[i].p;
		for(int j=b[i].p;j<=100;j+=b[i].p)
			if(vis[j]) mx=j;
		for(int j=b[i].p;j<mx;j++)
			b[i].h[j]=b[i].h[j-b[i].p];
		b[i].p=mx;
	}
	memset(vis,0,sizeof(vis));
	double now=1;
	for(int i=1;i<=n;i++){
		ps[i]=0;
		int S=0;
		for(int j=0;j<b[i].p;j++){
			if(vis[b[i].p]) b[i].h[j]|=b[vis[b[i].p]].h[j],S-=b[vis[b[i].p]].h[j];
			ps[i]+=b[i].h[j];
			S+=b[i].h[j];
		}
		ps[i]/=b[i].p;
		if(vis[b[i].p]) now/=1-ps[vis[b[i].p]];
		ans[i]+=now*S/b[i].p;
		now*=1-ps[i];
		if(fabs(now)<1e-10) return;
		vis[b[i].p]=i;
	}
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i].x);
		int k1,k2;read(k1);read(k2);
		a[i].p=k1+k2;
		for(int j=0;j<k1;j++) a[i].h[j]=1;
	}
	a[++n].p=1;
	a[n].h[0]=1;
	for(int t=0;t<2520;t++){
		for(int i=1;i<=n;i++){
			int P=a[i].p/gcd(a[i].p,2520);
			b[i].clear();
			b[i].x=a[i].x;
			b[i].p=P;
			for(int j=0;j<P;j++)
				b[i].h[j]=a[i].h[(j*2520+t+a[i].x)%a[i].p];
		}
		solve();
	}
	for(int i=1;i<=n;i++) printf("%.8lf\n",ans[i]/2520);
	return 0;
}

```

