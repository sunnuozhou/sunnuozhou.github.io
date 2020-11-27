---
title: ACM ICPC World Finals 2014 G题
tags:
  - OI
  - codeforces
  - 2-sat
date: 2020-10-21 10:52:04
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221)

枚举从小到大 $D(A)$，令 $D(B)$ 递减，找到最小的可行 $D(B)$。

假设枚举了 $D(A),D(B)$，要判断存不存在一组可行解。可以发现这是一个2-sat问题，直接上2-sat板子即可。

时间复杂度 $O(n^4)$，刚好可以卡着时限过题。

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
int e[410][410],d[410],a[410][410],n,in[410],st[410],top,cnt,h[410],dfn[410],low[410],tim;
vector<int> v;
void add(int x,int y){
	e[x][++d[x]]=y;
}
void tarjan(int x){
	low[x]=dfn[x]=++tim;in[x]=1;st[++top]=x;
	for(int i=1;i<=d[x];i++){
		int v=e[x][i];
		if(!dfn[v]){
			tarjan(v);
			low[x]=min(low[v],low[x]);
		}
		else if(in[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x]){
		in[x]=0;
		for(h[x]=++cnt;st[top]!=x;top--)
			h[st[top]]=cnt,in[st[top]]=0;
		top--;
	}
}
bool check(int k1,int k2){
	memset(e,0,sizeof(e));
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(a[i][j]>k1) add(i,j+n),add(j,i+n);
			if(a[i][j]>k2) add(i+n,j),add(j+n,i);
		}
	tim=cnt=0;
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	for(int i=1;i<=2*n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		if(h[i]==h[i+n]) return 0;
	return 1;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			read(a[i][j]);
			a[j][i]=a[i][j];
			v.push_back(a[i][j]);
		}
	v.push_back(0);
	sort(v.begin(),v.end());
	v.resize(unique(v.begin(),v.end())-v.begin());
	int ans=2e9,k=(int)v.size()-1;
	for(int i=0;i<v.size();i++){
		while(k>=i&&check(v[i],v[k])) ans=min(ans,v[i]+v[k]),k--;
	}
	cout<<ans<<'\n';
	return 0;
}
```

