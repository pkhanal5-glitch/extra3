// word ladder
#include <bits/stdc++.h>
using namespace std;

// Extract all substrings enclosed in double quotes, in order.
static vector<string> extract_quoted(const string& s) {
    vector<string> out;
    bool in = false;
    string cur;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (!in) {
            if (c == '"') { in = true; cur.clear(); }
        } else {
            if (c == '"') { in = false; out.push_back(cur); }
            else cur.push_back(c);
        }
    }
    return out;
}

// Generate wildcard patterns by replacing position i with '*'
static inline void add_patterns(const string& w, unordered_map<string, vector<string>>& buck) {
    for (size_t i = 0; i < w.size(); ++i) {
        string pat = w;
        pat[i] = '*';
        buck[pat].push_back(w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read entire input (accepts: beginWord = "hit", endWord = "cog", wordList = ["hot",...])
    string s, line;
    while (getline(cin, line)) s += line;

    vector<string> q = extract_quoted(s);
    if (q.size() < 2) { cout << 0 << "\n"; return 0; }
    const string beginWord = q[0];
    const string endWord   = q[1];

    vector<string> wordList;
    for (size_t i = 2; i < q.size(); ++i) wordList.push_back(q[i]);

    // Build set of words; endWord must exist.
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord)) { cout << 0 << "\n"; return 0; }
    dict.insert(beginWord); // ensure patterns include beginWord

    // All words must be same length per constraints; guard against bad input
    const size_t L = beginWord.size();
    // Remove any words with mismatched length to avoid invalid neighbors
    for (auto it = dict.begin(); it != dict.end();) {
        if (it->size() != L) it = dict.erase(it);
        else ++it;
    }
    if (!dict.count(endWord)) { cout << 0 << "\n"; return 0; }

    // Precompute wildcard buckets
    unordered_map<string, vector<string>> buckets;
    buckets.reserve(dict.size() * L * 2);
    for (const auto& w : dict) add_patterns(w, buckets);

    // BFS
    queue<pair<string,int> > qbf;
    unordered_set<string> seen;
    qbf.push(make_pair(beginWord, 1)); // count includes beginWord
    seen.insert(beginWord);

    while (!qbf.empty()) {
        pair<string,int> cur = qbf.front(); qbf.pop();
        const string& w = cur.first;
        int dist = cur.second;
        if (w == endWord) { cout << dist << "\n"; return 0; }

        for (size_t i = 0; i < L; ++i) {
            string pat = w;
            pat[i] = '*';
            vector<string>& nb = buckets[pat];
            for (size_t j = 0; j < nb.size(); ++j) {
                const string& v = nb[j];
                if (!seen.count(v)) {
                    seen.insert(v);
                    qbf.push(make_pair(v, dist + 1));
                }
            }
            // Optional optimization: clear to reduce repeated scans
            nb.clear();
        }
    }

    cout << 0 << "\n";
    return 0;
}
