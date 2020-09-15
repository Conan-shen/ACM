// Source : [D. Carousel](https://codeforces.com/contest/1328/problem/D)
// Author : shenguo
// Date   : 2020-09-15

#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int t[maxn];
int ans[maxn];
bool check1(int n) {
    for(int i =2;i<=n;i++) {
       if(t[i]!=t[i-1])return false; 
    }
    for(int i =1;i<=n;i++) ans[i] =1;
    return true;
}

bool check2(int n) {
    if(n%2==0||t[1]==t[n]) {
        ans[1]=1;
        for(int i =2;i<=n;i++)ans[i]=3-ans[i-1];
        return true;
    }
    bool f=false;
    ans[1]=1;
    for(int i =2;i<=n;i++) {
        if(!f&&t[i]==t[i-1]) {
            f=true;
            ans[i]=ans[i-1];
        } else {
            ans[i] = 3- ans[i-1];
        }
    }
    if(!f)return false;
    return true;
}

void check3(int n) {
    ans[1]=1;
    for(int i =2;i<=n;i++) {
        ans[i]=3-ans[i-1];
    }
    ans[n]=3;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 1;i<=n;i++) {
            scanf("%d", &t[i]);
        }
        if(check1(n)) {
            puts("1");
        } else if (check2(n)) {
            puts("2");
        } else  {
            check3(n);
            puts("3");
        }
        for(int i =1;i<=n;i++) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
    return 0;
}