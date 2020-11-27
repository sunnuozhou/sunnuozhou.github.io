---
title: ACM ICPC Central European Regional Contest 2017 K题
tags:
  - OI
  - codeforces
  - 贪心
  - DP
date: 2020-11-25 10:48:21
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

由于环长为7，一个物品要么只有一个可行的旋转角度，要么所有数字相同。所有数字相同的情况可以忽略。

考虑差分，操作就变为了某个位置 $+k$，某个位置 $-k$。这时序列的先后顺序已经没有影响了。

考虑对于一个权值和模7余0的集合，如果对其他位置操作一次 $+k$，并把 $-k$ 给到剩余的一个位置，那么就节省了一次操作次数。

也就是题目被转换为了给 $n$ 个数，找到最多的模7余0的集合。首先 $(0),(1,6),(2,5),(3,4)$ 都是必然不亏的，先把这些匹配掉，然后就只剩3种数了，DP即可。

时间复杂度 $O(n^3k)$，其中 $k$ 为转移个数。

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
int h[3],p[3],n,a[7],f[510][510][510];
struct tran{int k[3];};
vector<tran> E;
void init(){
	int m,lst=0;read(m);
	for(int i=1;i<=m;i++){
		int x;read(x);
		int mx=0,w=0,s=0;
		for(int j=0;j<7;j++){
			if(x>mx) mx=x,w=j,s=1;
			else if(x==mx) s++;
			x=x/10+(x%10)*1000000;
		}
		if(s>1) continue;
		a[(w-lst+7)%7]++;
		n++;
		lst=w;
	}
//	for(int j=0;j<7;j++) cerr<<a[j]<<'\n';
	n-=a[0]+min(a[1],a[6])+min(a[2],a[5])+min(a[3],a[4]);
	if(a[1]>a[6]) p[0]=1,h[0]=a[1]-a[6];
	else p[0]=6,h[0]=a[6]-a[1];
	if(a[2]>a[5]) p[1]=2,h[1]=a[2]-a[5];
	else p[1]=5,h[1]=a[5]-a[2];
	if(a[3]>a[4]) p[2]=3,h[2]=a[3]-a[4];
	else p[2]=4,h[2]=a[4]-a[3];
	for(int i=0;i<=7;i++)
		for(int j=0;j<=7;j++)
			for(int k=0;k<=7;k++)
				if((p[0]*i+p[1]*j+p[2]*k)%7==0&&i+j+k>0){
					int flag=0;
					for(auto&p:E)
						if(p.k[0]<=i&&p.k[1]<=j&&p.k[2]<=k) flag=1;
					if(!flag) E.push_back(tran{i,j,k});
				}
}
void upd(int&a,int b){if(a<b) a=b;}
void solve(){
	memset(f,192,sizeof(f));
	f[h[0]][h[1]][h[2]]=0;
	for(int i=h[0];~i;i--)
		for(int j=h[1];~j;j--)
			for(int k=h[2];~k;k--)
				for(auto&t:E)
					if(i>=t.k[0]&&j>=t.k[1]&&k>=t.k[2])
						upd(f[i-t.k[0]][j-t.k[1]][k-t.k[2]],f[i][j][k]+1);
	int mx=0;
	for(int i=0;i<=7;i++)
		for(int j=0;j<=7;j++)
			for(int k=0;k<=7;k++)
				mx=max(mx,f[i][j][k]);
	cout<<n-mx<<'\n';
}
int main(){
	init();	
	solve();
	return 0;
}


```

