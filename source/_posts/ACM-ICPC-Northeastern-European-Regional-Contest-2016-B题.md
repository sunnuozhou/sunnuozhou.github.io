---
title: ACM ICPC Northeastern European Regional Contest 2016 B题
tags:
  - OI
  - codeforces
  - 2-sat
  - trie
date: 2020-11-10 12:01:18
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

这是一个2-sat题，每个字符串可以选问号变0还是变1，用trie树优化建图即可，注意同一个trie树节点上的情况要特殊考虑，使用前后缀优化建图。

时间复杂度 $O(n+\sum len)$，常数巨大，注意空间。

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
const int N = 5001000;
int dfn[N],low[N],in[N],St[N],top,cnt,h[N],n,head[N],tot,tim,pos[501000][2],tag[1001000],p[1001000];
struct edge{int v,nxt;}e[N*3];
string st[501000];
vector<int> v[1001000];
struct trie{
	int fa[1001000],ch[1001000][2],tot;
	int get_node(string&s,int k){
		int len=s.length(),x=0;
		for(int i=0;i<len;i++){
			int tmp=s[i]=='?'?k:s[i]-'0';
			if(!ch[x][tmp]) ch[x][tmp]=++tot,fa[tot]=x;
			x=ch[x][tmp];
		}
		return x;
	}
}t;
int id(int x,int k){return x*2+k+2;}
void add(int x,int y){
	e[++tot]={y,head[x]};
	head[x]=tot;
}
void tarjan(int x){
	dfn[x]=low[x]=++tim;in[x]=1;St[++top]=x;
	for(int i=head[x];i;i=e[i].nxt)
		if(!dfn[e[i].v]){
			tarjan(e[i].v);
			low[x]=min(low[x],low[e[i].v]);
		}
		else if(in[e[i].v]) low[x]=min(low[x],dfn[e[i].v]);
	if(low[x]==dfn[x]){
		h[x]=++cnt;
		for(;St[top]!=x;top--)
			h[St[top]]=cnt,in[St[top]]=0;
		in[x]=0;top--;
	}
}
int main(){
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>n;
	int CNT=0;
	for(int i=1;i<=n;i++){
		cin>>st[i];
		if(st[i]=="?") CNT++;
		int w=-1,len=st[i].length();
		for(int j=0;j<len;j++)
			if(st[i][j]=='?') w=j;
		if(w<0){
			int x=t.get_node(st[i],0);
			pos[i][1]=x;
		}
		else{
			pos[i][0]=t.get_node(st[i],0);pos[i][1]=t.get_node(st[i],1);
		}
		//cerr<<pos[i][0]<<' '<<pos[i][1]<<'\n';
	}
	if(CNT>2){cout<<"NO\n";return 0;}
	int num=t.tot+n;
	p[0]=++num;
	for(int i=1;i<=t.tot;i++){
		p[i]=++num;
		add(id(p[i],1),id(t.fa[i],0));
		add(id(t.fa[i],1),id(p[i],0));
		add(id(p[i],1),id(p[t.fa[i]],1));
		add(id(p[t.fa[i]],0),id(p[i],0));
		add(id(i,1),id(p[i],1));
		add(id(p[i],0),id(i,0));
	}
	for(int i=1;i<=n;i++)
		if(!pos[i][0]) add(id(pos[i][1],0),id(pos[i][1],1)),tag[pos[i][1]]=1;
		else{
			add(id(t.tot+i,0),id(pos[i][0],1)),add(id(t.tot+i,1),id(pos[i][1],1));
			add(id(pos[i][0],0),id(t.tot+i,1));add(id(pos[i][1],0),id(t.tot+i,0));
			v[pos[i][0]].push_back(id(t.tot+i,0));
			v[pos[i][1]].push_back(id(t.tot+i,1));
		}
	for(int i=1;i<=t.tot;i++){
		if(tag[i])
			for(int x:v[i]) add(x,x^1);
		else{
			for(int j=0;j<v[i].size();j++){
				++num;
				int x=v[i][j];
				if(j+1<v[i].size()){
					add(x,id(num+1,1)),add(id(num+1,0),x^1);
					add(id(num,1),id(num+1,1));add(id(num+1,0),id(num,0));
				}
				add(id(num,1),x^1);add(x,id(num,0));
			}
			for(int j=(int)v[i].size()-1;~j;j--){
				++num;
				int x=v[i][j];
				if(j>0){
					add(x,id(num+1,1)),add(id(num+1,0),x^1);
					add(id(num,1),id(num+1,1));add(id(num+1,0),id(num,0));
				}
				add(id(num,1),x^1);add(x,id(num,0));
			}
 
		}
	}
	for(int i=1;i<=t.tot;i++) v[i].clear();
	for(int i=2;i<=num*2+3;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=0;i<num;i++)
		if(h[id(i,1)]==h[id(i,0)]){cout<<"NO\n";return 0;}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		if(!pos[i][0]) cout<<st[i]<<'\n';
		else{
			int tag=h[id(t.tot+i,0)]<h[id(t.tot+i,1)],len=st[i].length();
			for(int j=0;j<len;j++)
				if(st[i][j]=='?') st[i][j]='1'-tag;
			cout<<st[i]<<'\n';
		}
	}
	return 0;
}
```

