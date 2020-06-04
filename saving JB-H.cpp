#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<math.h>
using namespace std;
int path[105] = {-1};
int visited[105] = {0};
struct node
{
    int x;
    int y;
};
const float minLength =  42.5;
int N;
int dis;
node nodes[105];
int isSave(int tmp)
{
    if ((nodes[tmp].x - dis <= -50) || (nodes[tmp].x + dis >= 50) || (nodes[tmp].y - dis <= -50) || (nodes[tmp].y + dis >= 50))
        return 1;
    return 0;
}
bool jump(int x, int y) {
    int p1 = pow(nodes[x].x - nodes[y].x, 2);
    int p2 = pow(nodes[x].y - nodes[y].y, 2);
    int r = dis * dis;
    if (p1 + p2 <= r)
        return true;
    return false;
}
int firstJump(int tmp)
{
    int xSquare = nodes[tmp].x *nodes[tmp].x;
    int ySquare = nodes[tmp].y *nodes[tmp].y;
    int rSquare = (dis+7.5)*(dis+7.5);
    if(xSquare + ySquare <= rSquare)
        return (xSquare+ySquare);
    return 0;
}
bool cmp(int x,int y){
    return firstJump(x)<firstJump(y);
}
void Bfs()
{
    int step = 2;
    int last;
    int b[105];
    queue<int>q;
    for (int i = 1; i<=N; i++)
    {
        b[i] = i;
    }
    sort(b+1,b+N+1,cmp);
    for(int i = 1; i<=N; i++)
    {
        if(firstJump(b[i]))
        {
            q.push(b[i]);
            visited[b[i]] = 1;
            last = b[i];
        }
    }
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        int tail;
        if(isSave(p))
        {
            stack<int> s;
            while (p!=-1)
            {
                s.push(p);
                p = path[p];
            }
            s.pop();
            cout<<step<<endl;
            while (!s.empty())
            {
                p = s.top();
                s.pop();
                cout << nodes[p].x << " " << nodes[p].y << endl;
            }
            return;
        }
        else
        {
            for (int i = 1; i <= N; i++)
            {
                if (!visited[i]&&jump(p, i))
                {
                    q.push(i);
                    path[i] = p;
                    visited[i] = 1;
                    tail = i;
                }
            }
            if(last==p){
                last = tail;
                step++;
            }
        }
    }
    if(q.empty())
        cout<<0<<endl;
}
int main()
{
    cin>>N>>dis;
    for(int i = 1; i<=N; i++)
    {
        cin>>nodes[i].x>>nodes[i].y;
    }
    if (dis >= minLength) {
        cout << "1" << endl;
        return 0;
    }
    Bfs();
    return 0;
}
