---
title: atcoder grand contest 044E
tags:
  - OI
  - atcoder
  - 概率
  - 计算几何
date: 2020-05-27 14:19:32
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc044/tasks/agc044_e)

在 $A_{max}$ 的位置破环为链，将 $A_{max}$ 放在链的两头，就可以使环上的问题转换为链上的问题。

考虑期望方程：

$E_i=\max(A_i,\frac{E_{i-1}+E_{i+1}}2-B_i)$

假设 $l,r$ 满足 $E_i=A_i$，而对于 $l<i<r$ 满足 $E_i=\frac{E_{i-1}+E_{i+1}}2-B_i$，就有 $E_i-E_{i-1}=E_{i+1}-E_i-2\times B_i$。

如果存在 $C_i$ 满足 $(E_i+C_i)-(E_{i-1}+C_{i-1})=(E_{i+1}+C_{i+1})-(E_i+C_i)$，那么在坐标系中，所有满足 $l<i<r$ 的 $(i,E_i+C_i)$ 在一条线段上。而对于 $0\le i\le n$ 的所有点来说，$(i,E_i+C_i)$ 在一个凸包上。

如果我们知道了 $C_i$ ，那只要对 $(i,A_i+C_i)$ 求一个凸包就可以解出答案，考虑如何得到 $C_i$。

根据上述式子，$C_{i+1}=2\times C_i-2\times B_i-C_{i-1}$，任意定 $i=0,1$ 时的初始值即可。

时间复杂度 $O(n)$。

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
const int N = 501000;
struct point{
	ll x,y;
}p[N],st[N];
int top,n;
ll a[N],b[N],c[N],B[N];
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
lld operator * (point a,point b){return 1.l*a.x*b.y-1.l*a.y*b.x;}
void solve(){
	for(int i=0;i<=n;i++){
		while(top>1&&(p[i]-st[top-1])*(st[top]-st[top-1])<=0) top--;
		st[++top]=p[i];
	}
	lld ans=0;
	int now=1;
	for(int i=0;i<n;i++){
		while(st[now+1].x<=i) now++;
		ans+=1.l*((st[now+1].x-i)*st[now].y+(i-st[now].x)*st[now+1].y)/(st[now+1].x-st[now].x)-c[i];
	}
	printf("%.12Lf\n",ans/n);
}
int main(){
	read(n);
	int k=0;ll mx=-1;
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(a[i]>mx) k=i,mx=a[i];
	}
	for(int i=1;i<=n;i++)
		read(b[i]);
	for(int i=0;i<n;i++)
		p[i]={i,a[(i+k-1)%n+1]},B[i]=b[(i+k-1)%n+1];
	p[n]=p[0];p[n].x=n;
	c[0]=c[1]=0;
	for(int i=1;i<n;i++){
		c[i+1]=2*c[i]-2*B[i]-c[i-1];
	}
	for(int i=0;i<=n;i++) p[i].y+=c[i];
	solve();
	return 0;
}


```

