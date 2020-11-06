---
title: ACM ICPC World Finals 2019 I题
tags:
  - OI
  - codeforces
  - DP
date: 2020-11-05 13:06:50
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/I)

藏在模拟中的DP题，我一开始以为直接模拟可以过，结果发现根本不行。

记录 $f_{x,y,d,p,l}$ 表示在 $(x,y)$ 处，面向 $d$，在执行第 $p$ 个命令，执行到了第 $l$ 个字符，在执行完后会到哪里。直接按模拟的方式转移即可。

时间复杂度 $O(RCd\times 4\times 100)$。

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
const int N = 101000,dx[]={0,-1,0,1},dy[]={1,0,-1,0};
string p[110],cmd[1100];
int n,m,R,C,Flag,CNT,top;
struct node{int x:8,y:8,k:8;};
node f[51][51][4][28][110];
short in[51][51][4][28][110];
char mp[110][110];
int get_d(char D){
	if(D=='e') return 0;
	if(D=='n') return 1;
	if(D=='w') return 2;
	return 3;
}
char get_D(int d){
	if(d==0) return 'e';
	if(d==1) return 'n';
	if(d==2) return 'w';
	return 's';
}
bool chk_safe(int x,int y){
	return x>=1&&x<=R&&y>=1&&y<=C&&mp[x][y]=='.';
}
bool chk_cd(int x,int y,int k,char cd){
	if(cd=='b') return !chk_safe(x+dx[k],y+dy[k]);
	return get_d(cd)==k;
}
node Exec(node now,int l,int r,int dep){
	int x=now.x,y=now.y,k=now.k;
	if(in[x][y][k][dep>0?dep-'A'+1:0][l]==-1) return f[x][y][k][dep>0?dep-'A'+1:0][l];
	if(in[x][y][k][dep>0?dep-'A'+1:0][l]==1) Flag=1;
	CNT++;
//	if(CNT>100000000) Flag=1;
	if(Flag) return node{-1,-1,-1};
	if(l==r) return node{x,y,k};
	in[x][y][k][dep>0?dep-'A'+1:0][l]=1;
	if(cmd[dep][l]>='A'&&cmd[dep][l]<='Z'){
		now=Exec(now,0,cmd[cmd[dep][l]].length(),cmd[dep][l]);
		if(Flag) return node{-1,-1,-1};
		now=Exec(now,l+1,r,dep);	
		if(Flag) return node{-1,-1,-1};	
		in[x][y][k][dep>0?dep-'A'+1:0][l]=-1;
		f[x][y][k][dep>0?dep-'A'+1:0][l]=now;
		return now;
	}
	else if(cmd[dep][l]=='m'){
		if(chk_safe(x+dx[k],y+dy[k])) now.x+=dx[k],now.y+=dy[k];
		now=Exec(now,l+1,r,dep);
		if(Flag) return node{-1,-1,-1};	
		in[x][y][k][dep>0?dep-'A'+1:0][l]=-1;
		f[x][y][k][dep>0?dep-'A'+1:0][l]=now;
		return now;
	}
	else if(cmd[dep][l]=='l'){
		now.k=(now.k+1)%4;	
		now=Exec(now,l+1,r,dep);
		if(Flag) return node{-1,-1,-1};	
		in[x][y][k][dep>0?dep-'A'+1:0][l]=-1;
		f[x][y][k][dep>0?dep-'A'+1:0][l]=now;
		return now;
	}
	else if(cmd[dep][l]=='u'){
		char cd=cmd[dep][l+1];
		int cnt=1,pos=l+3;
		while(cnt){
			cnt+=cmd[dep][pos]=='(';
			cnt-=cmd[dep][pos]==')';
			pos++;
		}
		if(!chk_cd(x,y,k,cd)){
			now=Exec(now,l+3,pos-1,dep);
			if(Flag) return node{-1,-1,-1};
//			cerr<<dep<<' '<<l<<' '<<r<<' '<<now.x<<' '<<now.y<<' '<<now.k<<'\n';
			now=Exec(now,l,r,dep);
			if(Flag) return node{-1,-1,-1};
		}else{
			now=Exec(now,pos,r,dep);
			if(Flag) return node{-1,-1,-1};
		}
		in[x][y][k][dep>0?dep-'A'+1:0][l]=-1;
		f[x][y][k][dep>0?dep-'A'+1:0][l]=now;
		return now;
	}
	else if(cmd[dep][l]=='i'){
		char cd=cmd[dep][l+1];
		int cnt=1,pos1=l+3,pos2;
		while(cnt){
			cnt+=cmd[dep][pos1]=='(';
			cnt-=cmd[dep][pos1]==')';
			pos1++;
		}
		cnt=1;pos2=pos1+1;
		while(cnt){
			cnt+=cmd[dep][pos2]=='(';
			cnt-=cmd[dep][pos2]==')';
			pos2++;
		}
		if(chk_cd(x,y,k,cd)) now=Exec(now,l+3,pos1-1,dep);
		else now=Exec(now,pos1+1,pos2-1,dep);
		if(Flag) return node{-1,-1,-1};
		now=Exec(now,pos2,r,dep);	
		if(Flag) return node{-1,-1,-1};	
		in[x][y][k][dep>0?dep-'A'+1:0][l]=-1;
		f[x][y][k][dep>0?dep-'A'+1:0][l]=now;
		return now;
	}
	cerr<<"error\n";
	return node{-1,-1,-1};
}
int main(){
	ios::sync_with_stdio(0);
	cin>>R>>C>>n>>m;
	for(int i=1;i<=R;i++)
		cin>>mp[i]+1;
	for(int i=1;i<=n;i++){
		string tmp;cin>>tmp;
		cmd[tmp[0]]=tmp.substr(2);
	}
	while(m--){
		int x,y;char ch;
		cin>>x>>y>>ch;
		int k=get_d(ch);
		cin>>cmd[0];
		Flag=0;CNT=0;
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				for(int k=0;k<4;k++)
					for(int L=0;L<100;L++)
						in[i][j][k][0][L]=0;
		node ans=Exec(node{x,y,k},0,cmd[0].length(),0);
		if(Flag) cout<<"inf\n";
		else cout<<ans.x<<' '<<ans.y<<' '<<get_D(ans.k)<<'\n';
	}
//	while(1);
	return 0;
}
```

