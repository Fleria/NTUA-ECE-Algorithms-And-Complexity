#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define intpair pair<int, int>  
#define Nmax 10000
#define MAX 10000000

vector<vector<intpair>> geitones(Nmax);
vector<vector<int>> dist(Nmax);
vector<vector<bool>> vis(Nmax);
set<pair<int, intpair>> queue;
int N, M, s, t, B;


int main() {
    cin >> N >> M >> s >> t >> B;
    for (int i = 1; i <= M; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        geitones[u].push_back(make_pair(v, l));
    }

    for (int i = 0; i <= N; i++) {
        dist[i].assign(N + 1, MAX);
        vis[i].assign(N + 1, false);
    }

    dist[0][s] = 0;
    queue.insert(make_pair(0, make_pair(s, 0)));
    

    //start k-Dijkstra
    while (!queue.empty()) {
        pair<int, intpair> front = *queue.begin();
        queue.erase(queue.begin());

        int u = front.second.first;   // current vertex
        int ud = front.first;    // distance from s
        int sc = front.second.second;  // shortcuts used
        vis[sc][u] = true;

        for (auto n : geitones[u]) {
            int v = n.first;
            int l = n.second;

            if (!vis[sc][v]){
                if (dist[sc][v] > dist[sc][u] + l) {
                if (dist[sc][v] != MAX) {queue.erase(queue.find(make_pair(dist[sc][v], make_pair(v, sc))));}

                dist[sc][v] = dist[sc][u] + l;
                queue.insert(make_pair(dist[sc][v], make_pair(v, sc)));
                }
            }

            
            if (!vis[sc + 1][v] ){
                if (sc + 1 < N && dist[sc + 1][v] > dist[sc][u]) {

                if (dist[sc + 1][v] != MAX){queue.erase(queue.find(make_pair(dist[sc + 1][v], make_pair(v, sc + 1))));}

                dist[sc + 1][v] = dist[sc][u];
                queue.insert(make_pair(dist[sc + 1][v], make_pair(v, sc + 1)));
                }
            }
        }
    }

    for (int j = 0; j <= N; j++) {
        if (dist[j][t] <= B) {
            cout << j << endl;
            return 0;
        }
    }

    return 0;
}