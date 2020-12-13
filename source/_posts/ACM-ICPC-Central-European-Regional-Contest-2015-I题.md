---
title: ACM ICPC Central European Regional Contest 2015 I题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-11-30 12:01:54
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101480)

由于坐标范围小，圆的半径小，坐标是整点，可能的圆心位置数量并不多，暴力即可。

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
int n,m,mp[510][510],tim,vis[N];
double r[N];
struct point{int x,y;}A,B;
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
ll operator * (point a,point b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
ll dis(point p){return 1ll*p.x*p.x+1ll*p.y*p.y;}
int check(int x,int y){
	if(!mp[x][y]) return 0;
	if(vis[mp[x][y]]==tim) return 0;
	if(x<min(A.x,B.x)||x>max(A.x,B.x)) return 0;
	if(y<min(A.y,B.y)||y>max(A.y,B.y)) return 0;
	vis[mp[x][y]]=tim;
	int flag=0;
	point pt={x,y};
	if((pt-A)*(B-A)==0) flag=1;
	if(!flag&&((pt-A)*(B-A))*((pt-A)*(B-A))<r[mp[x][y]]*r[mp[x][y]]*dis(B-A)) flag=1;
	if(flag)return 1;
	return 0;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		int x,y;read(x);read(y);mp[x][y]=i;
		scanf("%lf",r+i);
	}
	read(m);
	tim=0;
	while(m--){
		read(A.x);read(A.y);read(B.x);read(B.y);
		++tim;
		int ans=check(A.x,A.y)+check(B.x,B.y);
		double K=A.x==B.x?0.:1.*(B.y-A.y)/(B.x-A.x);
		for(int i=min(A.x,B.x);i<=max(A.x,B.x);i++){
			double y=(i-A.x)*K+A.y;
			ans+=check(i,floor(y));
			ans+=check(i,ceil(y));
			ans+=check(i,floor(y)-1);
			ans+=check(i,ceil(y)+1);
		}
		K=A.y==B.y?0.:1.*(B.x-A.x)/(B.y-A.y);
		for(int i=min(A.y,B.y);i<=max(A.y,B.y);i++){
			double x=(i-A.y)*K+A.x;
			ans+=check(floor(x),i);
			ans+=check(ceil(x),i);
			ans+=check(floor(x)-1,i);
			ans+=check(ceil(x)+1,i);
		}
		cout<<ans<<'\n';
	}
	return 0;
}


```

