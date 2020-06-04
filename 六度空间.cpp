#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
struct Node{
	int id,layer;
};
vector<vector<int>> Adj; 
vector<bool> inq;
int BFS(Node tnode){
	queue<Node> q;
	q.push(tnode); //入队 
	inq[tnode.id] = true; //设置已入队
	int count = 1;
	while(!q.empty()){
		Node top = q.front();
		q.pop();
		for(int i = 0; i < Adj[top.id].size(); i++){
			int nextId = Adj[top.id][i];
			if(!inq[nextId] && top.layer < 6){
				Node next = {nextId, top.layer + 1};
				q.push(next);
				inq[nextId] = true; //设置已入队
				count++; 
			}
		}
	}
	return count;
}
int main(){
	int n,m,x,y;
	cin>>n>>m;
	Adj.resize(n+1);
	inq.resize(n+1);
	for(int i = 0; i < m; i++){
		cin>>x>>y;
		Adj[x].push_back(y);
		Adj[y].push_back(x);
	}
	int count;
	for(int i = 1; i <= n; i++){
		inq.assign(n+1,false);
		Node tnode = {i, 0}; //初始化节点的层数为0 
		count = BFS(tnode);
		printf("%d: %.2f%\n",i,((double)count/n)*100); 
	}
}
