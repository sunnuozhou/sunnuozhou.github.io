---
title: codeforces 568C
tags:
  - OI
  - codeforces
  - 2-sat
  - 贪心
date: 2020-01-27 15:34:31
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/568/problem/C)

这题显然是一个$2-sat$模型，先建出图。枚举答案串和$S$的公共前缀长度，添加相应的限制（即前$i$个是元音还是辅音已经确定，第$i+1$可能确定，剩下的随便选），找出最长的公共前缀长度。

然后考虑按位确定，取元音和辅音中可选的字典序小的那个。

如果没有元音或没有辅音要特殊考虑。

时间复杂度$O(nm)$。

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
const int N = 510;
int dfn[N],low[N],st[N],in[N],tim,cnt,top,n,m,h[N],len;
vector<int> e[N];
char typ[30],S[N];
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
	for(int i=2;i<=n*2+1;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		if(h[i<<1]==h[i<<1|1]) return 0;
	return 1;
}
void getans(int beg){
	for(int i=beg;i<=n;i++){
		int k=typ[i==beg?S[i]-'a'+1:0]=='C';
		e[i<<1|!k].push_back(i<<1|k);
		if(check()) putchar(i==beg?S[i]+1:'a');
		else{
			e[i<<1|!k].pop_back();
			int p=i==beg?S[i]+1-'a':0;
			while((typ[p]=='C')==k) p++;
			putchar('a'+p);
		}
	}
}
int main(){
	cin>>typ;
	len=strlen(typ);
	int flag=1;
	for(int i=1;i<len;i++)
		flag&=typ[i]==typ[0];
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;char c1,c2;
		cin>>x>>c1>>y>>c2;
		if(flag&&c1==typ[0]&&c2!=typ[0]){puts("-1");return 0;}
		int k1=c1=='C',k2=c2=='C';
		e[x<<1|k1].push_back(y<<1|k2);
		e[y<<1|!k2].push_back(x<<1|!k1);
	}
	cin>>S+1;
	if(flag){
		cout<<S+1<<'\n';
		return 0;
	}
	int mxC=len-1,mxV=len-1;
	while(typ[mxC]!='C') mxC--;
	while(typ[mxV]!='V') mxV--;
	for(int i=n;~i;i--){
		for(int j=1;j<=i;j++)
			e[j<<1|typ[S[j]-'a']!='C'].push_back(j<<1|typ[S[j]-'a']=='C');
		if(i<n&&S[i+1]-'a'>=mxC)
			e[i+1<<1|1].push_back(i+1<<1);
		if(i<n&&S[i+1]-'a'>=mxV)
			e[i+1<<1].push_back(i+1<<1|1);
		if(check()){
			for(int j=1;j<=i;j++)
				putchar(S[j]);
			getans(i+1);
			return 0;
		}
		if(i<n&&S[i+1]-'a'>=mxC)
			e[i+1<<1|1].pop_back();
		if(i<n&&S[i+1]-'a'>=mxV)
			e[i+1<<1].pop_back();
		for(int j=1;j<=i;j++)
			e[j<<1|typ[S[j]-'a']!='C'].pop_back();
	}
	puts("-1");
	return 0;
}
```

