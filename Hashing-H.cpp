#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 1000;
int num[N], indegree[N];
struct cmp {
    bool operator()(int i, int j) {
        return num[i] > num[j];
    }};
int main() {
    int i, j, n, m, k, flag = 0;
    scanf("%d", &n);
    vector<vector<int> > g(n);
    priority_queue<int, vector<int>, cmp> q;
    for (i = 0; i < n; i++) 
        scanf("%d", &num[i]);
    for (i = 0; i < n; i++) {
        if (num[i] > 0) {
            k = num[i] % n;
            indegree[i] = (i + n - k) % n;
            if (indegree[i]) {
                for (j = 0; j <= indegree[i]; j++) 
                    g[(k + j) % n].push_back(i);
            }
            else q.push(i);
        }}
    while (!q.empty()) {
        i = q.top();
        q.pop();
        if (!flag) {
            flag = 1;
            printf("%d", num[i]);
        }
        else printf(" %d", num[i]);
        for (j = 0; j < g[i].size(); j++) {
            if (--indegree[g[i][j]] == 0)
                q.push(g[i][j]);
        }
    }
    return 0;}
