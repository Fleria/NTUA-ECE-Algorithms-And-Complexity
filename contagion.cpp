#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{
    int N, F, comp = 0, c = 0, d = 0;
    bool flag = false;

    cin >> N >> F;

    int visited[N];
    int compcount[N];
    vector<vector<bool>> pairs(N, vector<bool>(N, false));

    for (int i = 0; i < N; i++) {
        visited[i] = -1;
        compcount[i] = 0;
    }

    F = F / 100.0 * N;

    int P[63];
    vector <pair<int, int>> vec;
    int a, b;

    for (int i = 0; i < 63; i++) cin >> P[i];

    int i = 0;

    while (flag == false) {
        if (i > 31) P[2 * i % 63] = (P[(2 * i - 63) % 63] + P[(2 * i - 31) % 63]) % N;
        if (i > 30) P[(2 * i + 1) % 63] = (P[(2 * i - 62) % 63] + P[(2 * i - 30) % 63]) % N;

        if (P[2 * i % 63] == P[(2 * i + 1) % 63]) c++;
        else {
            a = min(P[2 * i % 63], P[(2 * i + 1) % 63]);
            b = max(P[2 * i % 63], P[(2 * i + 1) % 63]);

            if (pairs[a][b] == false) {
                pairs[a][b] = true;

                if (visited[a] == -1 && visited[b] == -1) {
                    visited[a] = comp;
                    visited[b] = comp;
                    compcount[comp++] = 2;
                }
                else if (visited[a] != -1 && visited[b] == -1) {
                    visited[b] = visited[a];
                    compcount[visited[a]]++;
                    if (compcount[visited[a]] >= F) flag = true;
                }
                else if (visited[a] == -1 && visited[b] != -1) {
                    visited[a] = visited[b];
                    compcount[visited[b]]++;
                    if (compcount[visited[b]] >= F) flag = true;
                }
                else if (visited[a] != -1 && visited[b] != -1 && visited[a] != visited[b]) {
                    compcount[visited[a]] += compcount[visited[b]];
                    if (compcount[visited[a]] >= F) {
                        flag = true;
                    }
                    compcount[visited[b]] = 0;
                    int newcomp = visited[b];
                    for (int i = 0; i < N; i++) {
                        if (visited[i] == newcomp) visited[i] = visited[a];
                    }
                }
            }
            else d++;
        }

        i++;
    }

    cout << i - d - c << " " << d << " "<<c<<endl; 
    return 0;
}