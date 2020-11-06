---
title: ACM ICPC World Finals 2018 E题
tags:
  - OI
  - codeforces
  - 最短路
date: 2020-11-03 12:20:54
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102482)

解析几何题。

枚举两个位置，检查可不可以从第一个点跳到第二个点。然后连边再BFS求最短路。具体方法是先求出在水平和竖直方向上的速度（取竖直方向上速度最大的），然后判断和每个断面交不交。

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
const double g = 9.80665;
int b[410],h[25][25],n,m,X,Y;
double V,W;
vector<int> e[410];
int id(int x,int y){return x*m-m+y;}
bool check(int x1,int y1,int x2,int y2){
	double dis=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),del=h[x2][y2]-h[x1][y1];
	dis*=W;
	double a=1+del*del/dis/dis,b=-V*V-2*V*V*del*del/dis/dis-del*g,c=del*g*V*V+g*g*dis*dis/4+V*V*V*V*del*del/dis/dis;
	if(b*b-4*a*c<-1e-10) return 0;
	double Vy=sqrt((-b+sqrt(b*b-4*a*c))/2/a),Vx=sqrt(V*V-Vy*Vy);
	int lx=min(x1,x2),rx=max(x1,x2),ly=min(y1,y2),ry=max(y1,y2);
	double v1=Vx/dis*(x2-x1)*W,v2=Vx/dis*(y2-y1)*W;
	if(x1!=x2)
	for(int i=lx;i<=rx;i++){
		int tag=x1<i?-1:1;
		double t=W*(fabs(i-x1)-0.5)/fabs(v1);
		if(i==x1) continue;
		double ny=y1*W-0.5*W+v2*t;
		int k=ny/W+1;
		int mx=max(h[i][k],h[i+tag][k]);
		if(int((ny-1e-3)/W)+1<k) mx=max(mx,max(h[i][k-1],h[i+tag][k-1]));
		if(int((ny+1e-3)/W)+1>k) mx=max(mx,max(h[i][k+1],h[i+tag][k+1]));
		double H=h[x1][y1]-0.5*g*t*t+Vy*t;
	//	cerr<<H<<' '<<mx<<'\n';
		if(H<mx-1e-9) return 0;
	}
	if(y1!=y2)
	for(int i=ly;i<=ry;i++){
		int tag=y1<i?-1:1;
		double t=W*(fabs(i-y1)-0.5)/fabs(v2);
		if(i==y1) continue;
		double nx=x1*W-0.5*W+v1*t;
		int k=nx/W+1;
		int mx=max(h[k][i],h[k][i+tag]);
		if(int((nx-1e-3)/W)+1<k) mx=max(mx,max(h[k-1][i],h[k-1][i+tag]));
		if(int((nx+1e-3)/W)+1>k) mx=max(mx,max(h[k+1][i],h[k+1][i+tag]));
		double H=h[x1][y1]-0.5*g*t*t+Vy*t;
	//	cerr<<H<<' '<<mx<<'\n';
		if(H<mx-1e-9) return 0;
	}
	return 1;
}
int main(){
	read(m);read(n);read(W);read(V);read(Y);read(X);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(h[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k1=1;k1<=n;k1++)
				for(int k2=1;k2<=m;k2++)
					if(i!=k1||j!=k2){
						if(check(i,j,k1,k2)) e[id(i,j)].push_back(id(k1,k2));
					}
	memset(b,63,sizeof(b));
	queue<int> q;q.push(id(X,Y));b[id(X,Y)]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]) if(b[v]>1e9){
			b[v]=b[u]+1;
			q.push(v);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[id(i,j)]>1e9) cout<<'X'<<" \n"[j==m];
			else cout<<b[id(i,j)]<<" \n"[j==m];
	return 0;
}
```

