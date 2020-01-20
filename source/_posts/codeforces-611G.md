---
title: codeforces 611G
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-01-20 15:01:01
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/611/problem/G)

按顺序枚举一个端点，用$two-pointer$维护一个对应点使得在这个范围中的剖分都是顺时针方向较小，同时维护面积和，坐标和来计算答案。因为保证了顺时针方向的较小，可以将绝对值拆开。

时间复杂度$O(n)$。

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
const int N = 501000,mod = 1e9+7;
int n;
ll ans;
struct point{ll x,y;}p[N];
ll operator * (point a,point b){return a.x*b.y-a.y*b.x;}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
point operator + (point a,point b){return point{a.x+b.x,a.y+b.y};}
ll calc(int a,int b,int c){return (p[c]-p[a])*(p[b]-p[a]);}
int nxt(int x){return x==n?1:x+1;}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(p[i].x),read(p[i].y);
	ll Sum=0,nS=0,now=0;point S=p[1];
	for(int i=3;i<=n;i++) Sum+=calc(1,i-1,i);
	for(int i=1,j=1;i<=n;i++){
		S=S-p[i];
		while(1){
			if(now+calc(i,j,nxt(j))>=Sum+1>>1) break;
			now+=calc(i,j,nxt(j));
			j=nxt(j);nS=(nS+now)%mod;
			S=S+p[j];
		}
		int len=(j-i+n)%n;
		//cerr<<i<<' '<<j<<' '<<nS<<' '<<now<<' '<<'\n';
		ans=(ans+Sum%mod*(len-1)-2*nS)%mod;
		point v=S;
		v=v-point{len*p[i].x,len*p[i].y};
		v.x%=mod;v.y%=mod;
		nS=(nS-p[i]*v+p[i+1]*v)%mod;
		now-=calc(i,i+1,j);
	}
	cout<<(ans+mod)%mod<<'\n';
	return 0;
}
```

