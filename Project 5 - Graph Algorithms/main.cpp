#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define pii pair<ll,ll>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
const ll INF = 1e18;
vector<pii > adj[N], inv_adjs[N], adj2[N];
vector<pair<pii, int>> shortest_path_edges, all_edges, cut_edges;
long long dist_from_1[N];
long long dist_from_n[N];
int visited[N], h[N], low[N], par[N];
set<pii > s;

void dfs(int v) {
    visited[v] = 1;
    low[v] = h[v];
    for (auto u : adj2[v]) {
        if (!visited[u.first]) {
            par[u.first] = v;
            h[u.first] = h[v] + 1;
            dfs(u.first);
            low[v] = min(low[v], low[u.first]);
            if (low[u.first] > h[v])
                cut_edges.push_back({{v, u.first}, u.second});
        } else if (u.first != par[v])
            low[v] = min(low[v], h[u.first]);
    }
}

bool is_in_cut(pair<pii, int> e) {
    bool b1 = (find(cut_edges.begin(), cut_edges.end(), e) != cut_edges.end());
    pair<pii, int> e2 = {{e.first.second, e.first.first}, e.second};
    bool b2 = (find(cut_edges.begin(), cut_edges.end(), e2) != cut_edges.end());
    return b1 || b2;
}

int main() {
    int n, m;
    int a, b, c;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        inv_adjs[b].push_back({a, c});
        all_edges.push_back({{a, b}, c});
    }
    s.insert({0, 1});
    fill_n(dist_from_1, n, INF);
    fill_n(dist_from_n, n, INF);
    while (!s.empty()) {
        auto ptr = s.begin();
        pii x = *ptr;
        s.erase(ptr);
        if (visited[x.second] == 1) continue;
        visited[x.second] = 1;
        dist_from_1[x.second] = x.first;
        for (auto u : adj[x.second]) {
            if (!visited[u.first]) {
                s.insert({u.second + dist_from_1[x.second], u.first});
            }
        }
    }
    fill_n(visited, n + 1, 0);
    s.insert({0, n});
    while (!s.empty()) {
        auto ptr = s.begin();
        pii x = *ptr;
        s.erase(ptr);
        if (visited[x.second] == 1) continue;
        visited[x.second] = 1;
        dist_from_n[x.second] = x.first;
        for (auto u : inv_adjs[x.second]) {
            if (!visited[u.first]) {
                s.insert({u.second + dist_from_n[x.second], u.first});
            }
        }
    }
    ll shortest_path = dist_from_1[n];
    for (auto u : all_edges) {
        if (dist_from_1[u.first.first] + dist_from_n[u.first.second] + u.second == shortest_path) {
            shortest_path_edges.push_back(u);
            adj2[u.first.first].push_back({u.first.second, u.second});
            adj2[u.first.second].push_back({u.first.first, u.second});
        }
    }
    fill_n(visited, n + 1, 0);
    par[1] = -1;
    dfs(1);
    for (auto u :all_edges) {
        int a = u.first.first;
        int b = u.first.second;
        int weight = u.second;
        ll dist = dist_from_1[a] + dist_from_n[b] + weight;
        if (dist == shortest_path) {
            if (is_in_cut(u))
                cout << 0 << endl;
            else if (weight == 1)
                cout << -1 << endl;
            else
                cout << 1 << endl;
        } else if (dist - shortest_path + 1 < weight) {
            cout << dist - shortest_path + 1 << endl;
        } else {
            cout << -1 << endl;
        }

    }

}
