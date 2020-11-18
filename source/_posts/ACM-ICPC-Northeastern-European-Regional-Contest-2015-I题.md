---
title: ACM ICPC Northeastern European Regional Contest 2015 I题
tags:
  - OI
  - codeforces
  - 模拟
date: 2020-11-16 11:30:31
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

如果暴力模拟，可能会出现一个物品被出售/购买多次，导致超时。

在一轮购买结束，可以二分这些物品被买了多少轮，然后直接加上买这么多轮的贡献，就可以了。

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
struct node{int id,typ,p,v,tv,cv,q;};
struct trade{int bid,sid,p,v;};
vector<trade> ans;
int lim[N],sum[N],n,tot;
set<int> S[2];
deque<node> h[2][N];
bool check(vector<node>&C,node p,int tm){
	for(int i=0;i<C.size();i++){
		ll SS=0;
		if(lim[i]<tm) SS=C[i].v;
		else SS=1ll*C[i].tv*tm;
		if(SS>p.v) return 0;
		sum[i]=SS;
		p.v-=SS;
	}
	return 1;
}
void solve(deque<node>&v,node&p){
	vector<node> C;
	while(v.size()){
		node tmp=v.front();v.pop_front();
		int V=min(p.v,tmp.cv);
		ans.push_back({p.typ==1?p.id:tmp.id,p.typ==1?tmp.id:p.id,tmp.p,V});
		p.v-=V;tmp.v-=V;tmp.cv-=V;
		if(!tmp.cv&&tmp.v){
			C.push_back(tmp);
		}
		if(tmp.cv) v.push_front(tmp);
		if(!p.v) break;
	}
	if(v.size()){
		for(auto&x:C){
			x.cv=min(x.v,x.tv);
			x.q=++tot;
			v.push_back(x);
		}
		return;
	}
	for(int i=0;i<C.size();i++) lim[i]=C[i].v/C[i].tv;
	int l=-1,r=1000000001;
	while(l+1<r){
		int mid=l+r>>1;
		if(check(C,p,mid)) l=mid;
		else r=mid;
	}
	check(C,p,l);
	for(int i=0;i<C.size();i++){
		ans.push_back({p.typ==1?p.id:C[i].id,p.typ==1?C[i].id:p.id,C[i].p,sum[i]});
		C[i].v-=sum[i];
		p.v-=sum[i];
		if(C[i].v){
			C[i].cv=min(C[i].v,C[i].tv);
			C[i].q=++tot;
			v.push_back(C[i]);
		}
	}
}
int main(){
	freopen("iceberg.in","r",stdin);
	freopen("iceberg.out","w",stdout);
	read(n);
	while(n--){
		node p;read(p.id);read(p.typ);read(p.p);read(p.v);read(p.tv);
		ans.clear();
		if(p.typ==1){
			while(S[0].size()&&*S[0].begin()<=p.p&&p.v){
				solve(h[0][*S[0].begin()],p);
				if(h[0][*S[0].begin()].size()==0) S[0].erase(S[0].begin());
			}
			if(p.v){
				p.q=++tot;p.cv=min(p.tv,p.v);
				h[1][p.p].push_back(p);
				S[1].insert(p.p);
			}
		}
		if(p.typ==2){
			while(S[1].size()&&*--S[1].end()>=p.p&&p.v){
				solve(h[1][*--S[1].end()],p);
				if(h[1][*--S[1].end()].size()==0) S[1].erase(--S[1].end());
			}
			if(p.v){
				p.q=++tot;p.cv=min(p.v,p.tv);
				h[0][p.p].push_back(p);
				S[0].insert(p.p);
			}
		}
		sort(ans.begin(),ans.end(),[&](trade a,trade b){
			return a.bid<b.bid||a.bid==b.bid&&a.sid<b.sid;
		});
		for(int i=0;i<ans.size();i++){
			if(i+1==ans.size()||ans[i].bid!=ans[i+1].bid||ans[i].sid!=ans[i+1].sid)
				printf("%d %d %d %d\n",ans[i].bid,ans[i].sid,ans[i].p,ans[i].v);
			else ans[i+1].v+=ans[i].v;
		}
	}
	puts("");
	for(int i=1;i<=100000;i++){
		while(h[1][i].size()){
			auto p=h[1][i].front();h[1][i].pop_front();
			printf("%d %d %d %d %d %d\n",p.id,p.typ,p.p,p.v,p.tv,p.cv);
		}
	}
	for(int i=1;i<=100000;i++){
		while(h[0][i].size()){
			auto p=h[0][i].front();h[0][i].pop_front();
			printf("%d %d %d %d %d %d\n",p.id,p.typ,p.p,p.v,p.tv,p.cv);
		}
	}
	return 0;
}


```

