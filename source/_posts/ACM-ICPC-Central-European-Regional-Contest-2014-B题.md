---
title: ACM ICPC Central European Regional Contest 2014 B题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-12-02 11:42:39
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100543)

如果在位置 $p$ 处可以看到区间 $(l,r)$ 中的线段，意味着可以看到区间 $(l,r)$ 构成的凸包，这可以快速检测。

对于区间 $(l,r)$，考虑二分，如果可以看到 $(l,mid)$，就向左走，否则向右。

时间复杂度 $O(n\log^2 n)$。

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
struct point{int x,y;}p[N];
int L[N*4],R[N*4],n,ans[N];
vector<point> v[N*4];
ll operator * (point a,point b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
bool check(point a,point b,vector<point>&v){
	int l=-1,r=v.size()-1;
	while(l+1<r){
		int mid=l+r>>1;
		if((v[mid+1]-v[mid])*(b-a)<=0) l=mid;
		else r=mid;
	}
	return (v[l+1]-a)*(b-a)<0;
}
void build(int l,int r,int x){
	L[x]=l;R[x]=r;
	if(l==r){
		v[x].push_back(p[l]);
		v[x].push_back(p[l+1]);
		return;
	}
	int mid=l+r>>1;
	build(l,mid,x<<1);build(mid+1,r,x<<1|1);
	v[x]=v[x<<1];
	for(auto&pt:v[x<<1|1]){
		while(v[x].size()>1&&(v[x].back()-v[x][v[x].size()-2])*(pt-v[x][v[x].size()-2])>=0) v[x].pop_back();
		v[x].push_back(pt);
	}
}
void solve(int l,int r,int x){
	if(l==r){
		int y=x;
		while(y>1&&(y&1||!check(p[l],p[l+1],v[y|1]))) y>>=1;
		if(y>1){
			y|=1;
			while(R[y]!=L[y]){
				if(check(p[l],p[l+1],v[y<<1])) y=y<<1;
				else y=y<<1|1;
			}
			ans[l]=R[y];
		}
		else ans[l]=0;
		return;
	}
	int mid=l+r>>1;
	solve(mid+1,r,x<<1|1);solve(l,mid,x<<1);
}
int main(){
	int T;read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++)
			read(p[i].x),read(p[i].y);
		build(1,n-1,1);
		solve(1,n-1,1);
		for(int i=1;i<=4*n;i++) v[i].clear();
		for(int i=1;i<n;i++)
			cout<<ans[i]<<" \n"[i==n-1];
	}
	return 0;
}


```

