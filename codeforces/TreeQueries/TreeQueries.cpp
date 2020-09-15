// Source : [E. Tree Queries](https://codeforces.com/contest/1328/problem/E)
// Author : shenguo
// Date   : 2020-09-15

#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int>V[maxn];
int d[maxn];
int fa[maxn][20];
int v[maxn];
void dfs(int u,int pre) {
    for(int i =0;i<V[u].size();i++) {
        int v= V[u][i];
        if(v==pre)continue;
        d[v] = d[u] + 1;
        fa[v][0] = u;
        dfs(v, u);
    }
}

void init(int n) {
    for(int i=1;i<20;i++) {
        for(int j =1;j<=n;j++) {
            if((1<<i)>d[j]) continue;
            int k = fa[j][i-1];
            fa[j][i] = fa[k][i-1];
        }
    }
}

void query(int &x,int y) {
    if(d[x]==d[y]) {
        return ;
    }
    for(int j = 19;j>=0&&d[x] != d[y];j--) {
        if(d[x] - (1<<j) < d[y]) continue;
        x = fa[x][j];
    }
}



bool cmp1(int a,int b) {
    return d[a] > d[b];
}
int main() {
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n-1;i++) {
        int u,v;
        scanf("%d %d", &u, &v);
        V[u].push_back(v);
        V[v].push_back(u);       
    }
    dfs(1, -1);
    init(n);
    while(m--) {
        int k;
        scanf("%d", &k);
        for(int i =0;i<k;i++) {
            int tmp;
            scanf("%d", &tmp);
            v[i] = tmp;
        }
        sort(v, v+k, cmp1);
        int bef = v[0];
        int now = 1;
        bool flag = true;
        while(now<k&&flag) {
            while(now<k&&d[v[now]]==d[bef]) {
                if(fa[v[now]][0]!=fa[bef][0]) {
                    flag = false;
                    break;
                }
                now++;
            }
            if(now<k) {
                query(bef, v[now]);
            }
            // cout<<bef<<endl;
        }
        if(flag) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}