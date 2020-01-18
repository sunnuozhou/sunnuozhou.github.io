---
title: codeforces 698D
tags:
  - OI
  - codeforces
  - 计算几何
  - 搜索
date: 2020-01-16 16:16:50
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/698/problem/D)

先求出每一个射击位置射每一个怪物有哪些点会阻拦它。

对于第$i$个点暴力求解这个点是否可能被射到，方法如下：

- 建立一个队列，初始时只有$i$。
- 枚举队列里未确定的位置由哪些位置射。
- 加入新的障碍点。
- 重复以上过程。

注意在队列大小大于$k$的时候要剪枝。

时间复杂度$O(n^2k+nk\times k!)$

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
const int N = 1010;
struct point{
	ll x,y;
}p[N],q[N];
int pos[N],used[N],flag,ans,n,K,vis[N];
vector<int> P,v[N][10];
ll operator * (point a,point b){return a.y*b.x-a.x*b.y;}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void work(int now){
	if(P.size()>K) return;
	if(now==P.size()) flag=1;
	if(flag) return;
	for(int i=1;i<=K;i++)
		if(!used[i]){
			used[i]=1;pos[P[now]]=i;
			int siz=P.size(),ok=1;
			for(int x:v[P[now]][i])
				if(!vis[x]) P.push_back(x),vis[x]=1;
			if(ok) work(now+1);
			while(P.size()>siz) vis[P.back()]=0,P.pop_back();
			pos[P[now]]=0;
			used[i]=0;
		}
}
int main(){
	read(K);read(n);
	for(int i=1;i<=K;i++)
		read(q[i].x),read(q[i].y);
	for(int i=1;i<=n;i++)
		read(p[i].x),read(p[i].y);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int l=1;l<=K;l++)
				if(i!=j&&(p[i]-q[l])*(p[j]-q[l])==0&&min(q[l].x,p[i].x)<=p[j].x&&p[j].x<=max(p[i].x,q[l].x)&&min(q[l].y,p[i].y)<=p[j].y&&p[j].y<=max(q[l].y,p[i].y))
					v[i][l].push_back(j);
	for(int i=1;i<=n;i++){
		P.clear();flag=0;
		P.push_back(i);vis[i]=1;
		work(0);vis[i]=0;
		ans+=flag;
	}
	cout<<ans<<'\n';
	return 0;
}
```

