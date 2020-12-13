---
title: ACM ICPC Central European Regional Contest 2013 A题
tags:
  - OI
  - codeforces
  - 搜索
date: 2020-12-03 10:29:49
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100299)

可以发现，一个位置上的数最多被换到4个位置，于是可以对不同的4个位置单独做。

首先，对4个角做的时候是没有限制的；对边上的点做的时候有限制：行或列交换次数为偶数；对中间的点做的时候行列都只能换偶数次。

将这些情况在预处理时都处理好即可。

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
map<pair<vector<int>,int>,vector<int> > mp;
set<pair<vector<int>,int> > vis;
int n,m,a[110][110],Flag;
vector<pair<char,int> > ans;
void init(){
	queue<pair<vector<int>,vector<int> > > q;
	vector<int> v1={1,2,3,4},v2;
	q.emplace(v1,v2);
	vis.emplace(v1,0);
	for(int i=0;i<4;i++)
		mp[make_pair(q.front().first,i)];
	vector<pair<int,int> > tn={make_pair(0,1),make_pair(0,2),make_pair(2,3),make_pair(1,3)};
	while(!q.empty()){
		auto p=q.front().first,k=q.front().second;q.pop();
		for(int i=0;i<tn.size();i++){
			auto pr=tn[i];
			auto v=p,nxt=k;
			swap(v[pr.first],v[pr.second]);
			nxt.push_back(i);
			int h[4]={};
			for(auto&x:nxt) h[x]^=1;
			for(int tag=0;tag<4;tag++){
				if(tag&1&&(h[1]||h[3])) continue;
				if(tag&2&&(h[0]||h[2])) continue;
				if(!mp.count(make_pair(v,tag))){
					mp[make_pair(v,tag)]=nxt;
				}
			}
			int tag=h[0]<<3|h[1]<<2|h[2]<<1|h[3];
			if(!vis.count(make_pair(v,tag))){
				vis.emplace(v,tag);
				q.emplace(v,nxt);
			}
		}
	}
	for(auto&pr:mp){
//		cout<<pr.first.second<<'\n';
//		for(auto&x:pr.first.first) cout<<x<<' ';cout<<'\n';
		reverse(pr.second.begin(),pr.second.end());
//		for(auto&x:pr.second) cout<<x<<' ';cout<<'\n';
//		cout<<'\n';
	}
}
void modify(int w,int k){
	if(k) for(int i=1;i*2<=n;i++) swap(a[i][w],a[n+1-i][w]);
	else reverse(a[w]+1,a[w]+m+1);
}
void work(int x,int y,int tag){
	int tx=n+1-x,ty=m+1-y;
	int val[4]={a[x][y],a[x][ty],a[tx][y],a[tx][ty]};
	vector<int> v={0,1,2,3},p;p.resize(4);
	sort(v.begin(),v.end(),[&](int a,int b){return val[a]<val[b];});
	for(int i=0;i<4;i++) p[v[i]]=i+1;
//	for(int i=0;i<4;i++) cout<<p[i]<<'\n';
	if(!mp.count(make_pair(p,tag))){Flag=1;return;}
	for(int k:mp[make_pair(p,tag)]){
		if(k==0) ans.emplace_back('R',x),modify(x,0);
		if(k==1) ans.emplace_back('C',y),modify(y,1);
		if(k==2) ans.emplace_back('R',tx),modify(tx,0);
		if(k==3) ans.emplace_back('C',ty),modify(ty,1);
	}
}
void debug(){
	cout<<"**************************\n";
	cout<<Flag<<'\n';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cout<<a[i][j]<<" \n"[j==m];
}
void solve(){
	work(1,1,0);
	for(int i=2;i*2<=n;i++) work(i,1,1);
	if(n&1&&a[n+1>>1][1]>a[n+1>>1][m]) ans.emplace_back('R',n+1>>1),modify(n+1>>1,0);
	for(int i=2;i*2<=m;i++) work(1,i,2);
	if(m&1&&a[1][m+1>>1]>a[n][m+1>>1]) ans.emplace_back('C',m+1>>1),modify(m+1>>1,1);
	for(int i=2;i*2<=n;i++)
		for(int j=2;j*2<=m;j++)
			work(i,j,3);
	int tim=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=++tim) Flag=1;
}
int main(){
	init();
	int T;read(T);
	while(T--){
		read(m);read(n);
		ans.clear();Flag=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				read(a[i][j]);
		solve();
		if(Flag) puts("IMPOSSIBLE");
		else{
			printf("POSSIBLE %d",(int)ans.size());
			for(auto&pr:ans) printf(" %c%d",pr.first,pr.second);
			puts("");
		}
	}
	return 0;
}


```

