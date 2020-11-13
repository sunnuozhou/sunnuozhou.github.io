---
title: ACM ICPC Northeastern European Regional Contest 2016 K题
tags:
  - OI
  - codeforces
date: 2020-11-11 11:10:54
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

考虑每个图片最左上角的点。

存在3种情况，C中的最左上角的点是从A来的，C中的最左上角的点是从B来的，AB最左上角的点抵消了，每种情况可能性都是唯一的，直接判断即可。

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
struct Graph{
	bool a[3010][3010];
	int x,y;
	Graph(){memset(a,0,sizeof(a));x=y=0;}
	Graph move(int dx,int dy){
		int n=3000-dx,m=3000-dy;
		Graph ans;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				ans.a[i+dx][j+dy]=a[i][j];
		ans.x=x+dx;
		ans.y=y+dy;
		return ans;
	}
	void init(){
		int n,m;read(n);read(m);
		char c[1010];
		for(int i=1;i<=n;i++){
			scanf(" %s",c+1);
			for(int j=1;j<=m;j++){
				a[i][j]=c[j]=='*';
				if(a[i][j]&&!x) x=i,y=j;
			}
		}
	}
	void print(int n,int m){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				cout<<".*"[a[i][j]];
			cout<<'\n';
		}
	}
}G1,G2,G3;
Graph operator + (Graph a,Graph b){
	Graph ans;
	for(int i=1;i<=3000;i++)
		for(int j=1;j<=3000;j++){
			ans.a[i][j]=a.a[i][j]^b.a[i][j];
			if(ans.a[i][j]&&!ans.x) ans.x=i,ans.y=j;
		}
	return ans;
}
bool operator == (Graph a,Graph b){
	int dx=a.x,dy=a.y;
	a=a.move(b.x,b.y);b=b.move(dx,dy);
	for(int i=1;i<=3000;i++)
		for(int j=1;j<=3000;j++)
			if(a.a[i][j]!=b.a[i][j]) return 0;
	return 1;
}
int main(){
	freopen("kids.in","r",stdin);
	freopen("kids.out","w",stdout);
	G1.init();
	G2.init();
	G3.init();
	if(G1.move(G2.x,G2.y)+G2.move(G1.x,G1.y)==G3){
		cout<<"YES\n";
		cout<<G1.y-G2.y<<' '<<G1.x-G2.x<<'\n';
		return 0;
	}
	if(G3.x){
		auto G=G3.move(G1.x,G1.y)+G1.move(G3.x,G3.y);
		if(G==G2){
			cout<<"YES\n";
			cout<<G.y-G3.y-G2.y<<' '<<G.x-G3.x-G2.x<<'\n';
			return 0;
		}
		G=G3.move(G2.x,G2.y)+G2.move(G3.x,G3.y);
		if(G==G1){
			cout<<"YES\n";
			cout<<-G.y+G3.y+G1.y<<' '<<-G.x+G3.x+G1.x<<'\n';
			return 0;
		}
	}
	cout<<"NO\n";
	return 0;
}
```

