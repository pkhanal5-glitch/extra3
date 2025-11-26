// Journey to the Moon — Hackerrank
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rnk, comp_sz;
    explicit DSU(int n): parent(n), rnk(n,0), comp_sz(n,1){
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x){ return parent[x]==x? x : parent[x]=find(parent[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(rnk[a]<rnk[b]) swap(a,b);
        parent[b]=a;
        comp_sz[a]+=comp_sz[b];
        if(rnk[a]==rnk[b]) rnk[a]++;      // why: keep trees shallow
    }
    int size(int x){ return comp_sz[find(x)]; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    if(!(cin >> n >> p)) return 0;
    DSU dsu(n);
    for(int i=0;i<p;++i){
        int a,b; cin >> a >> b;
        dsu.unite(a,b);
    }

    unordered_map<int,int> countByRoot;
    countByRoot.reserve(n*2);
    for(int i=0;i<n;++i){
        countByRoot[dsu.find(i)]++;
    }

    long long totalPairs = 1LL*n*(n-1)/2;
    long long sameCountry = 0;
    for(auto &kv : countByRoot){
        long long sz = kv.second;
        sameCountry += sz*(sz-1)/2;
    }
    cout << (totalPairs - sameCountry) << "\n";
    return 0;
}
