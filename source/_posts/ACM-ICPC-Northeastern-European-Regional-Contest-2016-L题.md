---
title: ACM ICPC Northeastern European Regional Contest 2016 L题
tags:
  - OI
  - codeforces
  - DP
date: 2020-11-12 10:43:20
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

记 $f_{i,j}$ 表示用了大于等于 $prime_i$ 的质数，和为 $j$ 的方案数和长度。

考虑输出答案，先从小到大枚举和，如果当前枚举的和与答案区间有交集，那么就处理这一段。

处理的时候也枚举当前质数取不取，并判断和答案区间有没有交。

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
	ll s,l;
}f[3010][3010];
int w[3010],pri[3010],tot,st[3010],top,F[3010];
node operator + (node a,node b){return node{a.s+b.s,a.l+b.l};}
node operator * (node a,node b){return node{a.s*b.s,a.l*b.s+a.s*b.l};}
void init(int n){
	for(int i=2;i<=n;i++){
		if(!F[i]){F[i]=i;pri[++tot]=i;}
		for(int j=1;pri[j]*i<=n;j++){
			F[pri[j]*i]=pri[j];
			if(F[i]==pri[j]) break;
		}
	}
	w[0]=2;
	for(int i=1;i<=n;i++) w[i]=w[i/10]+1;
	f[tot+1][0]={1,0};
	for(int i=tot;i;i--){
		for(int j=n;~j;j--){
			f[i][j]=f[i+1][j];
			if(j>=pri[i]) f[i][j]=f[i][j]+f[i+1][j-pri[i]]*node{1,w[pri[i]]};
		}
	}
}
void solve(ll L,ll R,ll S,int k,int dep,int lst){
	if(dep>tot){
		char ch[1010],*c=ch+2;
		ch[1]='[';
		for(int i=1;i<top;i++) sprintf(c,"%d, ",st[i]),c+=w[st[i]];
		sprintf(c,"%d], ",st[top]);
		for(int i=L-S;i<=R-S;i++) putchar(ch[i]); 
		return;
	}
	if(k>=pri[dep]){
		auto tmp=f[dep+1][k-pri[dep]]*node{1,w[pri[dep]]};
		ll len=tmp.l+tmp.s*(2+lst);
		if(len&&L<=S+len&&S+1<=R){
			st[++top]=pri[dep];
			solve(max(L,S+1),min(R,S+len),S,k-pri[dep],dep+1,lst+w[pri[dep]]);
			top--;
		}
		S+=len;
	}
	if(f[dep+1][k].s) solve(L,R,S,k,dep+1,lst);
}
int main(){
	freopen("list.in","r",stdin);
	freopen("list.out","w",stdout);
	init(2200);
	ll L,R,S=0;read(L);read(R);
	for(int i=1;i<=2200;i++){
		if(f[1][i].s&&L<=S+f[1][i].l+f[1][i].s*2&&S+1<=R) 
			solve(max(S+1,L),min(S+f[1][i].l+f[1][i].s*2,R),S,i,1,0);
		S+=f[1][i].l+f[1][i].s*2;
	}
	return 0;
}
```

