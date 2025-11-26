//Longest Word in Dictionary
#include <bits/stdc++.h>
using namespace std;

static vector<string> extract_quoted(const string& s) {
    vector<string> out; string cur; bool in=false;
    for (size_t i=0;i<s.size();++i){
        char c=s[i];
        if(!in){ if(c=='"'){ in=true; cur.clear(); } }
        else { if(c=='"'){ in=false; out.push_back(cur); } else cur.push_back(c); }
    }
    return out;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string all, line; 
    while (getline(cin, line)) all += line;

    vector<string> words = extract_quoted(all);
    if (words.empty()) { cout << "" << "\n"; return 0; }

    unordered_set<string> dict(words.begin(), words.end());
    string best = "";

    // why: sorting ensures deterministic tie-breaking when iterating
    sort(words.begin(), words.end()); 

    for (const string& w : words) {
        bool ok = true;
        for (size_t i = 1; i < w.size(); ++i) {
            if (!dict.count(w.substr(0, i))) { ok = false; break; }
        }
        if (!ok) continue;
        if (w.size() > best.size() || (w.size() == best.size() && w < best)) best = w;
    }

    cout << best << "\n";
    return 0;
}
