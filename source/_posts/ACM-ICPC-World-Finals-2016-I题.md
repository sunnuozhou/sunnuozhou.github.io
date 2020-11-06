---
title: ACM ICPC World Finals 2016 I题
tags:
  - OI
  - codeforces
  - 最短路
  - 线性规划
date: 2020-10-28 12:26:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242)

由于最短路唯一，求出任意两点间走最短路经过的路径。

然后设经过路径的时长为变量，有 $len_i\le x_i\le 2\times len_i$。

对于给定的每条路径，有 $\sum_{x\in e} x_i=Len$，这可以用大于等于和小于等于表示。

然后最优化的就是 $\sum_{x \in E} x_i$，直接单纯形法就可以了。

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
const int N = 510;
namespace Simplex{
	const long double eps = 1e-10;
	int n,m,id[N],p[N],cnt;
	long double ans[N],a[N][N];
	void clear(){
		for(int i=0;i<=m;i++)
			for(int j=0;j<=n;j++)
				a[i][j]=0;
		for(int i=1;i<=n+m;i++) ans[i]=id[i]=0;
	}
	void pivot(int x,int y){
		swap(id[x+n],id[y]);
		long double res=-a[x][y];a[x][y]=-1;
		for(int i=0;i<=n;i++) a[x][i]/=res;
		for(int i=0;i<=m;i++)
			if(i!=x&&(a[i][y]>eps||a[i][y]<-eps)){
				res=a[i][y];a[i][y]=0;
				for(int j=0;j<=n;j++) a[i][j]+=res*a[x][j];
			}
	}
	double solve(){
		for(int i=1;i<=n;i++) id[i]=i;
		while(1){
			cnt=0;
			for(int i=1;i<=m;i++)
				if(a[i][0]<-eps) p[cnt++]=i;
			if(!cnt) break;
			int x=p[rand()%cnt],y=0;
			for(int i=1;i<=n;i++)
				if(a[x][i]>eps){y=i;break;}
			if(!y) return -1;
			pivot(x,y);
		}
		while(1){
			cnt=0;
			for(int i=1;i<=n;i++)
				if(a[0][i]>eps) p[cnt++]=i;
			if(!cnt) break;
			int y=p[rand()%cnt],x=0;
			long double now=1e20;
			for(int i=1;i<=m;i++)
				if(a[i][y]<-eps&&-1*a[i][0]/a[i][y]<now) now=-1*a[i][0]/a[i][y],x=i;
			if(!x) return -2;
			pivot(x,y);
		}
		for(int i=n+1;i<=n+m;i++) if(id[i]) ans[id[i]]=a[i-n][0];
		return a[0][0];
	}
}
int n,m,Q,f[N][N],len[N];
vector<int> e[N][N];
int bg[N],ed[N],tim[N];
int main(){
	srand(24893249);
	read(n);
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int x;read(x);
			if(x>=0) f[i][j]=x;
			else f[i][j]=1e9;
			if(x>0) e[i][j].push_back(++cnt),len[cnt]=x;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(f[i][k]+f[k][j]<f[i][j]){
					f[i][j]=f[i][k]+f[k][j];
					e[i][j].clear();
					for(int x:e[i][k]) e[i][j].push_back(x);
					for(int x:e[k][j]) e[i][j].push_back(x);
				}
	read(m);
	for(int i=1;i<=m;i++){
		read(bg[i]);read(ed[i]);read(tim[i]);
		bg[i]++;ed[i]++;
	}
	read(Q);
	while(Q--){
		int x,y;read(x);read(y);
		x++;y++;
		Simplex::clear();
		Simplex::n=cnt;Simplex::m=2*m+2*cnt;
		for(int k:e[x][y]) Simplex::a[0][k]=-1;
		for(int i=1;i<=m;i++){
			for(int k:e[bg[i]][ed[i]])
				Simplex::a[i][k]=-1;
			Simplex::a[i][0]=tim[i];
		}
		for(int i=1;i<=m;i++){
			for(int k:e[bg[i]][ed[i]])
				Simplex::a[i+m][k]=1;
			Simplex::a[i+m][0]=-tim[i];
		}
		for(int i=1;i<=cnt;i++)
			Simplex::a[m*2+i][i]=-1,Simplex::a[m*2+i][0]=2*len[i];
		for(int i=1;i<=cnt;i++)
			Simplex::a[m*2+cnt+i][i]=1,Simplex::a[m*2+cnt+i][0]=-len[i];
		cout<<x-1<<' '<<y-1<<' ';
		printf("%.8lf ",-Simplex::solve());
		Simplex::clear();
		Simplex::n=cnt;Simplex::m=2*m+2*cnt;
		for(int k:e[x][y]) Simplex::a[0][k]=1;
		for(int i=1;i<=m;i++){
			for(int k:e[bg[i]][ed[i]])
				Simplex::a[i][k]=-1;
			Simplex::a[i][0]=tim[i];
		}
		for(int i=1;i<=m;i++){
			for(int k:e[bg[i]][ed[i]])
				Simplex::a[i+m][k]=1;
			Simplex::a[i+m][0]=-tim[i];
		}
		for(int i=1;i<=cnt;i++)
		for(int i=1;i<=cnt;i++)
			Simplex::a[m*2+i][i]=-1,Simplex::a[m*2+i][0]=2*len[i];
		for(int i=1;i<=cnt;i++)
			Simplex::a[m*2+cnt+i][i]=1,Simplex::a[m*2+cnt+i][0]=-len[i];
		printf("%.8lf\n",Simplex::solve());
	}
	return 0;
}

```

