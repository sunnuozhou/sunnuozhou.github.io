---
title: ACM ICPC Central European Regional Contest 2017 C题
tags:
  - OI
  - codeforces
  - DP
date: 2020-11-23 12:39:29
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

对每个询问单独做。

记 $f_{i,j}$ 表示树深度为 $i$，根有父亲，统计其prufer序列所有下标模 $d$ 为 $j$ 的数的和。

如果令 $i\le \frac k2$，那么状态数是 $2^{\frac k2}$ 级别的，在可接受范围内，将其全部求出。

考虑求答案，如果根没有父亲，递归两边；如果询问区间和子树区间完全不交，返回0；如果询问区间不包含子树区间，递归两边。

可以发现，这个复杂度还是 $O(2^\frac k2)$ 的，可以通过本题。

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
ll K,T,A,D,M;
pair<ll,ll> f[20][1<<17];
int now;
ll nxt(int x){
	ll p=1ll*(x-A)/D*D+A;
	while(p<x) p+=D;
	return p;
}
bool check(int l,int r){
	if(l>A+D*M) return 0;
	if(r<A) return 0;
	if(nxt(l)>r) return 0;
	return 1;
}
ll solveA(int dep,int pre,int x){
//	cerr<<dep<<' '<<pre<<' '<<x<<'\n';
	if(!check(pre+1,pre+(1<<dep)-1)) return 0;
//	cerr<<dep<<' '<<pre<<' '<<x<<'\n';
	if(dep==1) return check(pre+1,pre+1)?x>>1:0;
	int flag=dep<=16&&A<=pre+1&&A+D*M>=pre+(1<<dep)-1;
	if(flag){
		//cerr<<dep<<' '<<x<<' '<<pre+1<<' '<<pre+(1<<dep)-1<<'\n';
		ll k,b;
		tie(k,b)=f[dep][nxt(pre+1)-pre-1];
		return k*x+b+(check(pre+(1<<dep)-1,pre+(1<<dep)-1)?x>>1:0);
	}
	return solveA(dep-1,pre,x<<1)+(check(pre+(1<<dep)-1,pre+(1<<dep)-1)?x>>1:0)+solveA(dep-1,pre+(1<<dep-1)-1,x<<1|1);
}
ll solveB(int dep,int pre,int x){
	if(dep==1) return check(pre+1,pre+1)?x>>1:0;
	else return solveA(dep-1,pre,x<<1)+(check(pre+(1<<dep-1),pre+(1<<dep-1))?x<<1|1:0)+solveB(dep-1,pre+(1<<dep-1),x<<1|1);
}
void dfs(ll k,ll b,int dep,int t){
	if(dep>1){
		dfs(k<<1,b<<1,dep-1,t);
		dfs(k<<1,b<<1|1,dep-1,t);
	}
	f[t][now].first+=k>>1;
	f[t][now].second+=b>>1;
	now++;
}
int main(){
	read(K);read(T);
	while(T--){
		read(A);read(D);read(M);M--;
		memset(f,0,sizeof(f));
		for(int i=1;i<=min(K,16ll);i++){
			now=0;
			dfs(1,0,i,i);
			for(int j=D;j<=now;j++){
				f[i][j%D].first+=f[i][j].first;
				f[i][j%D].second+=f[i][j].second;
			}
		}
		cout<<solveB(K,0,1)<<'\n';
	}
	return 0;
}


```

