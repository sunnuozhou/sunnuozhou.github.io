---
title: ACM ICPC Northeastern European Regional Contest 2017 I题
tags:
  - OI
  - codeforces
  - 交互
date: 2020-11-09 11:31:37
categories:
top:
---

[题目链接](https://codeforces.com/gym/101630)

给偶数随机一个顺序，对于前 $k-1$ 个偶数，可以将奇数划分为 $k$ 组，考虑第 $k$ 个偶数，可以先二分出这个偶数所在的组，然后在暴力将这个组分为比他大和比他小的两块，操作次数复杂度 $O(n\log n)$。

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
int n,m0,m1,K,f[N],ans0[N],p[N],ans1[N],q[N],q1[N],q2[N];
vector<int> V[N],P;
char tag[N];
char query(int x,int y){
//	char c=q1[x]>q2[y]?'>':'<';
	cout<<"? "<<x<<' '<<y<<endl;
	char c;cin>>c;
	return c;
}
int main(){
	//int sd;cin>>sd;
	//srand(sd);
	read(n);
	//n=100;
	m0=n/2;m1=n-m0;
	/*for(int i=1;i<=n;i++) q[i]=i;
	random_shuffle(q+1,q+n+1);
	int k1=0,k2=0;
	for(int i=1;i<=n;i++)
		if(q[i]&1) q2[++k2]=q[i];
		else q1[++k1]=q[i];
	for(int i=1;i<=m0;i++)
		cerr<<q1[i]<<' ';
	for(int i=1;i<=m1;i++)
		cerr<<q2[i]<<' ';
	cerr<<'\n';*/
	for(int i=1;i<=m0;i++) p[i]=i;
	random_shuffle(p+1,p+m0+1);
	K=1;
	for(int i=1;i<=m1;i++) V[1].push_back(i),f[1]=i;
	P.push_back(1);
	for(int i=1;i<=m0;i++){
		int l=0,r=K;
		while(l+1<r){
			int mid=l+r>>1;
			if(query(p[i],f[P[mid]])=='<') r=mid;
			else l=mid;
		}
		int flag=0;
		for(int&x:V[P[l]]){
			tag[x]=query(p[i],x);
			flag|=tag[x]=='<';
		}
		if(!flag&&l+1<K){
			l++;
			for(int&x:V[P[l]])
				tag[x]=query(p[i],x);
		}
		auto now=V[P[l]];
		vector<int> nxt;
		V[P[l]].clear();
		for(int&x:now)
			if(tag[x]=='>') V[P[l]].push_back(x),f[P[l]]=x;
			else nxt.push_back(x);
		if(nxt.size()){
			swap(V[++K],nxt);
			f[K]=V[K][0];
			P.insert(P.begin()+l+1,K);
		}
		for(int j=0;j<=l;j++)
			ans0[p[i]]+=V[P[j]].size();
	}
//	if(K!=m1) return 1;
	for(int i=0;i<P.size();i++)
		ans1[f[P[i]]]=i*2+1;
	cout<<"! ";
	for(int i=1;i<=m0;i++)
		cout<<ans0[i]*2<<' ';
	for(int i=1;i<=m1;i++)
		cout<<ans1[i]<<' ';
/*	for(int i=1;i<=m0;i++)
		if(ans0[i]*2!=q1[i]){cerr<<"!!\n";return 1;}
	for(int i=1;i<=m1;i++)
		if(ans1[i]!=q2[i]){cerr<<"!!\n";return 1;}*/
	cout<<'\n';
	return 0;
}
```

