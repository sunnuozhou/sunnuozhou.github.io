---
title: codeforces 587F
tags:
  - OI
  - codeforces
  - AC自动机
  - 分块
date: 2020-01-14 17:00:09
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/587/problem/F)

这题很简单，但我很菜。

先建一个AC自动机，然后再考虑这道题。把询问差分后离线，现在要求的就是前$i$个串在第$k$个串中出现次数的总和。

对于一个AC自动机，我们把原trie树和fail树分开了看，那么新加入第$i$个串相当于在fail树上的一个子树全体加一。询问就是在原trie树上一个点到根的路径求和。

考虑分块。

先将fail树按dfs序分成根号块，记录下数组$sum_{i,j}$表示第$i$个串在原树上对应的点有几个在第$j$个块中，对于整块加就记录下来。

对于单点加，可以转换为$n\sqrt n$个原树上子树加和$n$个单点求值。再差分一下变为单点加，区间求值，使用分块可以修改$O(1)$，询问$O(\sqrt n)$。

询问时先算出前面单点加的产生的贡献，再算整块。对于一个整块$j$，贡献为$sum_{i,j}\times tag_j$，$tag_j$为整块被修改的次数。

总复杂度$O(n\sqrt n)$。

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
int n,q,K;
vector<pair<int,int> > v[N];
struct blocks{
	int sum[N],val[N];
	void add(int w,int k){
		sum[w/K]+=k;
		val[w]+=k;
	}
	void modify(int l,int r){
		add(l,1);add(r+1,-1);
	}
	int query(int w){
		int ans=0;
		for(int i=0;i<=w;)
			if(i%K==0&&i+K-1<=w){
				ans+=sum[i/K];
				i+=K;
			}
			else ans+=val[i],i++;
		return ans;
	}
}B;
struct ACAM{
	int dfn1[N],s1[N],dfn2[N],s2[N],ch[N][26],sum[N][350],w[N],tim,tot,fl[N],tag[350],pos1[N],pos2[N];
	vector<int> e1[N],e2[N],col[N];
	void enter(string&s,int num){
		int now=0;
		for(int i=0;i<s.length();i++){
			int tmp=s[i]-'a';
			if(!ch[now][tmp]) ch[now][tmp]=++tot;
			now=ch[now][tmp];
			col[now].push_back(num);
		}
		w[num]=now;
	}
	void dfs(int x,vector<int>*e,int*dfn,int*s,int*pos){
		s[x]=1;dfn[x]=tim;pos[tim]=x;tim++;
		for(int v:e[x]) dfs(v,e,dfn,s,pos),s[x]+=s[v];
	}
	void build(){
		queue<int> q;
		for(int i=0;i<=tot;i++)
			for(int j=0;j<26;j++)
				if(ch[i][j]) e1[i].push_back(ch[i][j]);
		for(int i=0;i<26;i++)
			if(ch[0][i]) q.push(ch[0][i]);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
				if(!ch[u][i]) ch[u][i]=ch[fl[u]][i];
				else{
					fl[ch[u][i]]=ch[fl[u]][i];
					q.push(ch[u][i]);
				}
		}
		for(int i=1;i<=tot;i++)
			e2[fl[i]].push_back(i);
		tim=0;
		dfs(0,e1,dfn1,s1,pos1);
		tim=0;
		dfs(0,e2,dfn2,s2,pos2);
		for(int i=1,S=0,cnt=0;i<=tot;i++){
			S++;
			if(S==K) S=0,cnt++;
			for(int x:col[pos2[i]]){
				sum[x][cnt]++;
			}
		}
	}
	void modify(int x){
		x=w[x];
		int l=dfn2[x],r=dfn2[x]+s2[x]-1;
		for(int i=l;i<=r;)
			if(i%K==0&&i+K-1<=r){
				tag[i/K]++;
				i+=K;
			}
			else{
				int p=pos2[i];
				B.modify(dfn1[p],dfn1[p]+s1[p]-1);
				i++;
			}
	}
	ll query(int x){
		ll ans=0;int pt=w[x];
		for(int i=0;i*K<=tot;i++)
			ans+=1ll*tag[i]*sum[x][i];
		return ans+B.query(dfn1[pt]);
	}
}t;
ll ans[N];
int main(){
	read(n);read(q);
	K=320;
	for(int i=1;i<=n;i++){
		string st;
		cin>>st;
		t.enter(st,i);
	}
	for(int i=1;i<=q;i++){
		int l,r,k;read(l);read(r);read(k);
		v[l-1].emplace_back(-k,i);
		v[r].emplace_back(k,i);
	}
	t.build();
	for(int i=1;i<=n;i++){
		t.modify(i);
		for(auto x:v[i]) ans[x.second]+=(x.first>0?1:-1)*t.query(abs(x.first));
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

