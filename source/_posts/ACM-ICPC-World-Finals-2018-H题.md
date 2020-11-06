---
title: ACM ICPC World Finals 2018 H题
tags:
  - OI
  - codeforces
  - 贪心
date: 2020-11-03 12:20:44
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102482/)

首先注意到2刀一定可以切完所有，考虑如何判断是否可以切一刀。

把题目转变为在环上有 $n$ 对点，要找到一个包含 $n$ 个点区间恰好包含每对中的一个。直接排序即可。

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
const int N = 1001000;
struct node{int x,y,w,tag;}p[N*2];
int tot,n,H,W,vis[N];
int get_w(int x,int y){
	if(x==0) return y;
	else if(y==H) return H+x;
	else if(x==W) return H+W+H-y;
	else return W+W+H+H-x;
}
pair<double,double> mv(node p,double k){
	if(p.x==0) return make_pair(p.x,p.y+k);
	if(p.y==H) return make_pair(p.x+k,p.y);
	if(p.x==W) return make_pair(p.x,p.y-k);
	return make_pair(p.x-k,p.y);
}
int main(){
	read(n);read(W);read(H);
	for(int i=1;i<=n;i++){
		int x1,y1,x2,y2;
		read(x1);read(y1);read(x2);read(y2);
		p[++tot]={x1,y1,get_w(x1,y1),i};
		p[++tot]={x2,y2,get_w(x2,y2),i};
	}
	sort(p+1,p+tot+1,[](node a,node b){
		return a.w<b.w;
	});
	int now=0;
	for(int i=1;i<=tot;i++){
		if(++vis[p[i].tag]==1) now++;
		if(i>n&&!--vis[p[i-n].tag]) now--;
		if(now==n&&i>n){
			puts("1");
			pair<double,double> P1=mv(p[i],0.5),P2=mv(p[i-n],0.5);
			printf("%lf %lf %lf %lf\n",P1.first,P1.second,P2.first,P2.second);
			return 0;
		}
	}
	printf("2\n%lf %d %lf %d\n%lf %d %lf %d\n",0.5,0,W-0.5,H,W-0.5,0,0.5,H);
	return 0;
}
 
```

