---
title: codeforces 587D
tags:
  - OI
  - codeforces
  - 二分答案
  - 2-sat
date: 2020-01-28 15:57:25
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/587/problem/D)

对于一个点，如果存在两种颜色，和这个点相连的边数都超过1条或者存在一种颜色邻边超过2条，那么一定无解。那么现在就有两种点，第一种是不存在相同颜色邻边的点，另一种是存在2条邻边颜色相同的点，我们记这两条边为$e_{i,0},e_{i,1}$，他们的颜色为$col_i$。

考虑$2-sat$如何建图：

- 把每一个2类点拆除2个，表示摧毁$e_{i,0}$还是$e_{i,1}$。
- 对于点$i,j$，$i,j$都是2类点，如果一条边$p$满足$p\in e_i,p\in e_j$，那么要么$i,j$都选他，要么$i,j$都不选他。
- 对于点$i,j$，$i,j$都是2类点，如果一条边$p$满足$p\in e_i,p\notin e_j$，那么一定不能选$p$。
- 对于点$i$，$i$是1类点，$a_1..a_k$表示与$i$相邻的2类点，他们之间只能有一个选和$i$相连的边，所以要互相连边，这里的连边要建虚点优化。

建好图后就可以二分答案了，强制时间大于二分值的边一定不选，$2-sat$求解即可。

时间复杂度$O(n\log V)$，其中$V$是值域。

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
const int N = 201000;
namespace two_sat{
	int dfn[N],low[N],st[N],in[N],tim,cnt,top,n,h[N],ans[N],tot;
	vector<int> e[N];
	void init(int num){
		n=num;tot=n*2+1;
	}
	void add(int x,int k0,int y,int k1){
		e[x<<1|k0].push_back(y<<1|k1);
		e[y<<1|!k1].push_back(x<<1|!k0);
	}
	void add(vector<pair<int,int> > p){
		int bg1=tot+1,bg2=tot+1+p.size();
		tot+=2*p.size();
		for(int i=0;i<p.size();i++){
			if(i+1<p.size()){
				e[p[i].first].push_back(bg1+i+1);
				e[bg1+i].push_back(bg1+i+1);
			}
			if(i){
				e[p[i].first].push_back(bg2+i-1);
				e[bg2+i].push_back(bg2+i-1);
			}
			e[bg1+i].push_back(p[i].second);
			e[bg2+i].push_back(p[i].second);
		}
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;in[x]=1;st[++top]=x;
		for(int v:e[x])
			if(!dfn[v]){
				tarjan(v);
				low[x]=min(low[x],low[v]);
			}
			else if(in[v]) low[x]=min(low[x],dfn[v]);
		if(low[x]==dfn[x]){
			h[x]=++cnt;in[x]=0;
			for(;st[top]!=x;top--)
				h[st[top]]=cnt,in[st[top]]=0;
			top--;
		}
	}
	bool check(){
		memset(dfn,0,sizeof(dfn));
		tim=0;cnt=0;
		for(int i=2;i<=tot;i++)
			if(!dfn[i]) tarjan(i);
		for(int i=1;i<=n;i++)
			if(h[i<<1]==h[i<<1|1]) return 0;
		for(int i=1;i<=n;i++)
			ans[i]=h[i<<1]>h[i<<1|1];
		return 1;
	}
	void ban(int x,int k0){
		e[x<<1|k0].push_back(x<<1|!k0);
	}
	void clear(int x,int k0){
		e[x<<1|k0].pop_back();
	}
}
int n,m,tag[N],pos[N][2],u[N],v[N],col[N],w[N];
vector<int> e[N];
bool check(int lim){
	for(int i=1;i<=n;i++)
		if(tag[i]&&w[pos[i][0]]>lim&&w[pos[i][1]]>lim) return 0;
	for(int i=1;i<=n;i++)
		if(tag[i]&&(w[pos[i][0]]>lim||w[pos[i][1]]>lim))
				two_sat::ban(i,w[pos[i][1]]>lim);
	int flag=two_sat::check();
	for(int i=1;i<=n;i++)
		if(tag[i]&&(w[pos[i][0]]>lim||w[pos[i][1]]>lim))
				two_sat::clear(i,w[pos[i][1]]>lim);
	return flag;
}
int main(){
	read(n);read(m);
	two_sat::init(n);
	for(int i=1;i<=m;i++){
		read(u[i]);read(v[i]);read(col[i]);read(w[i]);
		e[u[i]].push_back(i);
		e[v[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		unordered_map<int,int> sum;
		for(int j:e[i]){
			++sum[col[j]];
			if(sum[col[j]]>2){puts("No");return 0;}
			if(sum[col[j]]==2){
				if(tag[i]){puts("No");return 0;}
				tag[i]=col[j];
			}
		}
		if(tag[i]){
			for(int j:e[i])
				if(col[j]==tag[i]) (pos[i][0]?pos[i][1]:pos[i][0])=j;
		}
	}
	for(int i=1;i<=n;i++)
		if(tag[i])
			for(int j:e[i]){
				if(col[j]!=tag[i]) continue;
				int p=u[j]==i?v[j]:u[j];
				if(!tag[p]) continue;
				if(tag[p]!=tag[i]) two_sat::ban(i,j==pos[i][1]);
				if(tag[p]==tag[i])
					two_sat::add(i,j==pos[i][1],p,j==pos[p][1]);
			}
		else{
			vector<pair<int,int> > V;
			for(int j:e[i]){
				int p=u[j]==i?v[j]:u[j];
				if(col[j]==tag[p])
					V.emplace_back(p<<1|pos[p][0]!=j,p<<1|pos[p][0]==j);
			}
			two_sat::add(V);
		}
	if(!two_sat::check()){puts("No");return 0;}
	int l=-1,r=1e9;
	while(l+1<r){
		int mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	check(r);
	cout<<"Yes\n";
	vector<int> P;
	for(int i=1;i<=n;i++)
		if(tag[i]) P.push_back(pos[i][two_sat::ans[i]]);
	sort(P.begin(),P.end());
	P.resize(unique(P.begin(),P.end())-P.begin());
	cout<<r<<' '<<P.size()<<'\n';
	for(int x:P) cout<<x<<' ';
	cout<<'\n';
	return 0;
}
```

