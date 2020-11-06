---
title: ACM ICPC World Finals 2017 G题
tags:
  - OI
  - codeforces
date: 2020-10-30 10:46:32
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101471)

先考虑没有突变的情况，可以使用高斯消元求解每个局面的前驱。更进一步，可以发现每个局面的前驱的第一行，第一列，最后一行，最后一列一定是空，所以可以使用递推来求出前驱状态。

考虑有突变的情况，可以证明每个局面的前驱只有一个，考虑先尝试求一次前驱，可以得到突变位置的横坐标，将矩阵转置后再求一遍，就可以得到突变位置的纵坐标，也就得到突变的位置了。

时间复杂度 $O(n^3)$。

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
const int N = 310,dx[]={0,1,0,-1,1,1,-1,-1},dy[]={1,0,-1,0,1,-1,1,-1};
int a[N][N],res[N][N],tmp[N][N],n,m;
char mp[N][N];
int check(int x1,int x2,int y1,int y2){
	auto cnt=[&](int x,int y){
		int s=res[x][y];
		for(int i=0;i<8;i++){
			int tx=x+dx[i],ty=y+dy[i];
			s+=res[tx][ty];
		}
		return s;
	};
	for(int i=x1-1;i<=x2+1;i++)
		for(int j=y1-1;j<=y2+1;j++)
			res[i][j]=0;
	for(int i=x1;i+2<=x2;i++){
		for(int j=y1;j+2<=y2;j++)
			res[i+1][j+1]=cnt(i,j)+tmp[i][j]&1;
		if(cnt(i,y2-1)+tmp[i][y2-1]&1) return i; 
		if(cnt(i,y2)+tmp[i][y2]&1) return i; 
	}
	for(int i=x2-1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			if(cnt(i,j)+tmp[i][j]&1) return i;
	return 0;
}
void Copy(int&x1,int&x2,int&y1,int&y2){
	for(int i=x1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			a[i][j]=res[i][j];
	int flag=1;
	while(flag){
		flag=1;
		for(int i=y1;i<=y2;i++) flag&=!a[x1][i];
		x1+=flag;
	}
	flag=1;
	while(flag){
		flag=1;
		for(int i=y1;i<=y2;i++) flag&=!a[x2][i];
		x2-=flag;
	}
	flag=1;
	while(flag){
		flag=1;
		for(int i=x1;i<=x2;i++) flag&=!a[i][y1];
		y1+=flag;
	}
	flag=1;
	while(flag){
		flag=1;
		for(int i=x1;i<=x2;i++) flag&=!a[i][y2];
		y2-=flag;
	}
}
bool solve(int&x1,int&x2,int&y1,int&y2){
	if(x2-x1<2||y2-y1<2) return 0;
	for(int i=x1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			tmp[i][j]=a[i][j];
	int kx=check(x1,x2,y1,y2);
	if(!kx){
		Copy(x1,x2,y1,y2);
		return 1;
	}
	for(int i=x1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			tmp[j][i]=a[i][j];
	int ky=check(y1,y2,x1,x2);
	a[kx][ky]^=1;
	for(int i=x1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			tmp[i][j]=a[i][j];
	int flag=check(x1,x2,y1,y2);
	if(flag){a[kx][ky]^=1;return 0;}
	Copy(x1,x2,y1,y2);
	return 1;
}
int main(){
	read(m);read(n);
	for(int i=1;i<=n;i++)
		scanf(" %s",mp[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=mp[i][j]=='#';
	int x1=1,y1=1,x2=n,y2=m;
	while(solve(x1,x2,y1,y2));
	for(int i=x1;i<=x2;i++){
		for(int j=y1;j<=y2;j++)
			cout<<".#"[a[i][j]];
		cout<<'\n';
	}
	return 0;
}
 
```

