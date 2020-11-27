---
title: ACM ICPC Central European Regional Contest 2016 D题
tags:
  - OI
  - codeforces
  - 构造
date: 2020-11-26 12:20:33
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101173)

记 $f_{i,j}$ 表示在 $(i,j)$ 这个位置上最多放多少个东西，可以顺序的放在 $(6,6)$ 上。

对于每个位置，可以把在它上面的棋子分成连续的若干段，放在所有后继节点上，每个后继节点都放上限个，就达到了这个位置的上限。

方案递推即可。

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
int f[10][10],n;
vector<int> h[10][10];
pair<int,int> used[N];
void work(int x,int y,int s,int k){
	printf("%d %d %c %d\n",x,y,k==0?'D':'R',s);
	int tx=x+(k==0),ty=y+(k==1);
	for(int i=0;i<s;i++)
		h[tx][ty].push_back(h[x][y].back()),h[x][y].pop_back();
}
void solve(int x,int y,int s){
	if(x==6&&y==6) return;
	if(x==5&&y==6&&s==2){
		if(h[x][y].back()>h[x][y][h[x][y].size()-2]) work(x,y,1,0),work(x,y,1,0);
		else work(x,y,2,0);
		return;
	}
	if(x==6&&y==5&&s==2){
		if(h[x][y].back()>h[x][y][h[x][y].size()-2]) work(x,y,1,1),work(x,y,1,1);
		else work(x,y,2,1);
		return;
	}
	int mx=0;
	for(int i=1;i<=s;i++)
		mx=max(mx,h[x][y][h[x][y].size()-i]);
	int sum[10][10]={},now=s;
	for(int i=6;i>=x;i--)
		for(int j=6;j>=y;j--)
			if(i>x||j>y){
				sum[i][j]=min(now,f[7-i][7-j]);
				for(int k=0;k<sum[i][j];k++)
					used[mx-s+now-k]=make_pair(i,j);
				now-=sum[i][j];
			}
	for(int i=1;i<=s;i++){
		int tx,ty;tie(tx,ty)=used[h[x][y].back()];
		int nx=x,ny=y;
		while(nx<tx) work(nx,ny,1,0),nx++;
		while(ny<ty) work(nx,ny,1,1),ny++;
	}
	for(int i=6;i>=x;i--)
		for(int j=6;j>=y;j--)
			if((i>x||j>y)&&sum[i][j]) solve(i,j,sum[i][j]);
}
int main(){
	for(int i=1;i<=6;i++)
		for(int j=1;j<=6;j++){
			if(i==1&&j==1) f[i][j]=1;
			else if(i+j==3) f[i][j]=2;
			else{
				for(int k1=1;k1<=i;k1++)
					for(int k2=1;k2<=j;k2++)
						if(k1<i||k2<j) f[i][j]+=f[k1][k2];
			}
		}
	read(n);
	for(int i=1;i<=n;i++){
		int x;read(x);
		h[1][1].push_back(x);
	}
	solve(1,1,n);
	return 0;
}
```

