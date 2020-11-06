---
title: ACM ICPC World Finals 2017 D题
tags:
  - OI
  - codeforces
  - 分治
  - 决策单调性
date: 2020-10-30 10:46:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101471)

首先，题目相当于一个平面上有若干个A类和B类点，找到一个以A类为左下角，B类为右上角的最大矩形。

将A，B类点X按从小到大排序，如果一个A类点在另一个A类点的右上方，将其删除，如果一个B类点在另一个B类点的左下方，将其删除。

接着可以发现，每个A类点对应的最优B类点有决策单调性，可以使用分治快速解决。

需要注意，为了求出 $mid$ 的真实决策点，需要考虑矩形面积为负的情况。

时间复杂度 $O(n\log n)$。

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
struct point{int x,y;}p[N],q[N];
int n,m,cnt1,cnt2;
ll ans;
ll calc(point a,point b){
	return 1ll*(b.x-a.x)*(b.y-a.y);
}
void solve(int l,int r,int ql,int qr){
	if(l>r) return;
	int mid=l+r>>1,k=0;
	ll mx=-1e18;
	for(int i=ql;i<=qr;i++) if(p[mid].x<=q[i].x&&calc(p[mid],q[i])>mx) mx=calc(p[mid],q[i]),k=i;
	if(!k) k=qr;
	ans=max(ans,mx);
	solve(l,mid-1,ql,k);solve(mid+1,r,k,qr);
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(p[i].x);read(p[i].y);
	}
	sort(p+1,p+n+1,[](point a,point b){return a.x<b.x||a.x==b.x&&a.y<b.y;});
	for(int i=1;i<=n;i++){
		if(cnt1&&p[i].y>=p[cnt1].y) continue;
		p[++cnt1]=p[i];
	}
	for(int i=1;i<=m;i++){
		read(q[i].x);read(q[i].y);
	}
	sort(q+1,q+m+1,[](point a,point b){return a.x<b.x||a.x==b.x&&a.y<b.y;});
	for(int i=1;i<=m;i++){
		while(cnt2&&q[cnt2].y<=q[i].y) cnt2--;
		q[++cnt2]=q[i];
	}
	solve(1,cnt1,1,cnt2);
	cout<<ans<<'\n';
	return 0;
}
 
```

