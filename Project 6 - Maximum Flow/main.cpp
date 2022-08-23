#include <iostream>
#include <vector>
#include <queue>

#define pii pair<int, int>
using namespace std;
const int N = 1005;
const int INF = 1e9 + 7;
int v[N], c[6 * N], parent[2 * N], visited[2 * N], parent_edge[2 * N];
int n, m;
vector<pii > adj[2 * N];
vector<pair<pii, int>> w, max_flow_edges;

void create_residual_graph() {
    for (int i = 0; i <= 2001; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < max_flow_edges.size(); i++) {
        adj[max_flow_edges[i].first.first].push_back(make_pair(max_flow_edges[i].first.second, i));
        adj[max_flow_edges[i].first.second].push_back(make_pair(max_flow_edges[i].first.first, i));
    }

}
int get_direction_in_residual_graph(int u, int edge) {
    if (max_flow_edges[edge].first.first == u) {
        return 1;
    } else {
        return 0;
    }

}
int get_min(vector<pii> x) {
    int min = INF;
    for (int i = 0; i < x.size(); i++) {
        if (x[i].second == 1 && min > c[x[i].first]) {
            min = c[x[i].first];
        }
        if (x[i].second == 0 && min > max_flow_edges[x[i].first].second - c[x[i].first]) {
            min = max_flow_edges[x[i].first].second - c[x[i].first];
        }
    }
    return min;
}

vector<pii> bfs() {
    vector<pii> ans;
    queue<pii > q;
    q.push(make_pair(0, -1));
    while (!q.empty()) {
        pii cur = q.front();
//        cout << cur.first << " " << cur.second << endl;
        q.pop();
        if (visited[cur.first]) continue;
        visited[cur.first] = 1;
        if (max_flow_edges[cur.second].first.first == cur.first) {
            parent[cur.first] = max_flow_edges[cur.second].first.second;
        } else parent[cur.first] = max_flow_edges[cur.second].first.first;
        parent_edge[cur.first] = cur.second;
        if (cur.first == 2001) {
            int node = cur.first;
            while (node != 0) {
                ans.push_back({parent_edge[node], get_direction_in_residual_graph(parent[node], parent_edge[node])});
                node = parent[node];
            }
            return ans;
        }
        for (auto u : adj[cur.first]) {
            if (visited[u.first]) continue;
            if (cur.first == max_flow_edges[u.second].first.first) {
                if (c[u.second] > 0) {
                    q.push(make_pair(u.first, u.second));
                }
            } else {
                if (c[u.second] < max_flow_edges[u.second].second) {
                    q.push(make_pair(u.first, u.second));
                }
            }
        }
    }
    return ans;
}

int main() {
    int sum = 0;
    cin >> n >> m;
//    if (n>1000 || m > 1000) return cout << "meow",0;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        sum += c;
        w.push_back({{a, b}, c});
    }
    for (int i = 1; i <= n; i++) {
//        adj[0].push_back({i, v[i]});
        max_flow_edges.push_back({{0, i}, v[i]});
    }
    for (int i = 0; i < w.size(); i++) {
//        adj[w[i].first.first].push_back({1001+i,INF});
//        adj[w[i].first.second].push_back({1001+i,INF});
        max_flow_edges.push_back({{w[i].first.first, 1001 + i}, INF});
        max_flow_edges.push_back({{w[i].first.second, 1001 + i}, INF});
    }
    for (int i = 0; i < m; i++) {
//        adj[i+1001].push_back({2001,w[i].second});
        max_flow_edges.push_back({{i + 1001, 2001}, w[i].second});
    }
    for (int i = 0; i < max_flow_edges.size(); i++) {
        c[i] = max_flow_edges[i].second;
    }
    int max_flow = 0;
    create_residual_graph();
//    for (auto edge: max_flow_edges) {
//        cout << edge.first.first << " " << edge.first.second << " " << edge.second << endl;
//    }
    while (true) {
        fill_n(visited, 2 * N, 0);
        fill_n(parent, 2 * N, -1);
        vector<pii> path = bfs();
        if (path.empty()) break;
        int min = get_min(path);
//        cout << min << endl;
        if (min == 0) break;
        for (auto edge: path) {
            if(edge.second == 1) {
                c[edge.first] -= min;
            } else {
                c[edge.first] += min;
            }
        }
        max_flow += min;
    }
    return cout << sum - max_flow, 0;


}
