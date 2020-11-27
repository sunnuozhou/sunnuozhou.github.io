---
title: ACM ICPC Northeastern European Regional Contest 2015 C题
tags:
  - OI
  - codeforces
  - 仙人掌
  - 计数
date: 2020-11-13 12:28:27
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

对于是桥的边，删完后贡献为两边大小相乘。

对于不是桥的边，删完后贡献为 $\frac{\sum (S-1)(S-2)}2$，$S$ 为每个由桥构成的联通块大小。

tarjan完直接做即可。

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
struct edge{int v,nxt;}e[N*10];
int head[N],s[N],siz[N],b[N],dfn[N],low[N],st[N],top,n,m,cnt,tim,tot;
ll ans,S;
vector<int> E[N];
void add(int x,int y){
	e[++tot]=(edge){y,head[x]};
	head[x]=tot;
}
void tarjan(int x){
	dfn[x]=low[x]=++tim;st[++top]=x;
	for(int v:E[x])
		if(dfn[v]) low[x]=min(low[x],dfn[v]);
		else{
			tarjan(v);low[x]=min(low[x],low[v]);
			if(low[v]==dfn[x]){
				add(x,++cnt);add(cnt,x);s[cnt]+=2;
				for(;st[top]!=v;top--)
					add(st[top],cnt),add(cnt,st[top]),s[cnt]++;
				add(v,cnt);add(cnt,v);top--;
			}
		}
}
void dfs(int x,int dad){
	b[x]=siz[x]=x<=n;
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].v!=dad){
			dfs(e[i].v,x);siz[x]+=siz[e[i].v];
			if(e[i].v<=n||s[e[i].v]==2) b[x]+=b[e[i].v];
			if(x>n&&s[x]>2) S+=1ll*(b[e[i].v]-1)*(b[e[i].v]-2)/2;
		}
	if(x>n){
		if(s[x]==2) ans+=1ll*siz[x]*(n-siz[x])-1;
	}
}
void dfs2(int x,int dad,int up){
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].v!=dad){
			int nxt=up;
			if(e[i].v>n&&s[e[i].v]>2) nxt+=b[x];
			else if(x<=n||s[x]==2) nxt+=b[x]-b[e[i].v];
			else nxt=0;
			dfs2(e[i].v,x,nxt);
		}
	if(x>n&&s[x]>2){
		ll sum=S-1ll*(up-1)*(up-2)/2;
		for(int i=head[x];i;i=e[i].nxt)
			if(e[i].v!=dad) sum-=1ll*(b[e[i].v]-1)*(b[e[i].v]-2)/2;
		sum+=1ll*(b[x]+up-1)*(b[x]+up-2)/2;
		ans+=1ll*s[x]*(sum-1);
	}
}
int main(){
	read(n);read(m);cnt=n;
	for(int i=1;i<=m;i++){
		int k;read(k);
		int lst=0;
		for(int j=1;j<=k;j++){
			int x;read(x);
			if(lst) E[x].push_back(lst),E[lst].push_back(x);
			lst=x;
		}
	}
	tarjan(1);
	dfs(1,0);
	S+=1ll*(b[1]-1)*(b[1]-2)/2;
	dfs2(1,0,0);
	cout<<ans<<'\n';
	return 0;
}


```

