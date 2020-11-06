---
title: ACM ICPC World Finals 2018 I题
tags:
  - OI
  - codeforces
  - 树状数组
date: 2020-11-03 12:20:49
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102482)

先考虑向下的三角，求出每个点向左，向左上，向右上分别可以延长多少。然后对于在同一条右斜线上的点，一起统计答案。暴力的做法是对于枚举的一个三角的下顶点，令 $len=\min(L_{ul},L_{ur})$，检查前 $len$ 个点有几个点可以和它组成三角形。

考虑用树状数组优化，差分出每个点可以有贡献的区间，并用树状数组维护每个位置上当前是否有贡献，这样求可以快速检查前 $len$ 个点有几个点可以和它组成三角形了。

时间复杂度 $O(rc\log min(r,c))$。

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
int fl[3100][3100],fu1[3100][3100],fu2[3100][3100],bl[3100][3100],d[6100][3100],cnt,n,m;
char c[6100][12100];
ll ans;
vector<pair<int,int> > V[3100];
void modify(int p,int x,int k){
	for(int i=x;i<=n;i+=i&-i) d[p][i]+=k;
}
int query(int p,int x){
	int ans=0;
	for(int i=x;i;i-=i&-i) ans+=d[p][i];
	return ans;
}
void solve(){
	memset(fl,0,sizeof(fl));
	memset(fu1,0,sizeof(fu1));
	memset(fu2,0,sizeof(fu2));
	memset(bl,0,sizeof(bl));
	memset(d,0,sizeof(d));
	cnt=0;
	for(int i=1;i<=n;i++){
		int bgx=2*i-1,bgy=i&1?1:3;
		for(int j=1;j<=(m+(i&1))/2;j++){
			int nx=bgx,ny=bgy+4*j-4;
			if(j>1) fl[i][j]=(c[nx][ny-1]=='-')?fl[i][j-1]+1:0;
			if(i>1) fu1[i][j]=(c[nx-1][ny-1]=='\\')?fu1[i-1][j-(i&1)]+1:0;
			if(i>1) fu2[i][j]=(c[nx-1][ny+1]=='/')?fu2[i-1][j+1-(i&1)]+1:0;
			bl[i][j]=bl[i-1][j+1-(i&1)];
			if(!bl[i][j]) bl[i][j]=++cnt;
			int len=min(fu1[i][j],fu2[i][j]);
//			cerr<<query(bl[i][j],i)<<' '<<query(bl[i][j],i-len-1)<<'\n';
			ans+=query(bl[i][j],i)-query(bl[i][j],i-len-1);
//			cerr<<i<<' '<<j<<' '<<fl[i][j]<<' '<<fu1[i][j]<<' '<<fu2[i][j]<<' '<<bl[i][j]<<'\n';
			if(fl[i][j]){
				if(fl[i][j]+i<=n) V[fl[i][j]+i].emplace_back(i,j);
				modify(bl[i][j],i,1);
			}
		}
		for(auto&x:V[i]) modify(bl[x.first][x.second],x.first,-1);
		V[i].clear();
	}
}
int main(){
	read(n);read(m);
	for(int i=1;i<2*n;i++)
		fgets(c[i]+1,12010,stdin);
	solve();
	if(~n&1) n++;
	reverse(c+1,c+2*n);
	for(int i=1;i<2*n;i++){
		int len=strlen(c[i]+1);
		for(int j=1;j<=len;j++)
			if(c[i][j]=='\\') c[i][j]='/';
			else if(c[i][j]=='/') c[i][j]='\\';
	}
	solve();
	cout<<ans<<'\n';
	return 0;
}
```

