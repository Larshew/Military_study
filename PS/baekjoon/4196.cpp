#include <iostream>
#include <vector>
#include <stack>
#include <memory.h>
#define MAX_NM 100000
using namespace std;

int n,m;
vector<int> list[MAX_NM+1];
vector<int> list_rev[MAX_NM+1];

stack<int> searched_node;
bool visit[MAX_NM+1];

void dfs_front(int node){
	visit[node]=true;
	for(int _n:list[node]){
		if (!visit[_n]) dfs_front(_n);
	}
	searched_node.push(node);
}

vector<int> same_mom;
int mom[MAX_NM+1];
void dfs_back(int node){
	visit[node]=true;
	for (int _n:list_rev[node]){
		if (!visit[_n]) dfs_back(_n);
	}
	same_mom.push_back(node);
}

int main()
{
	int testcase;
	cin >> testcase;
	for (int ts=1;ts<=testcase;ts++){
		int i;

		cin >> n >> m;
		for (i=1;i<=m;i++){
			int a,b;

			cin >> a >> b;
			list[a].push_back(b);
			list_rev[b].push_back(a);
		}
		
		memset(visit,0,sizeof(visit));
		for (i=1;i<=n;i++) mom[i]=i;
		for (i=1;i<=n;i++){
			if (!visit[i]) dfs_front(i);
		}
		
		memset(visit,0,sizeof(visit));
		while(!searched_node.empty()){
			int top_node = searched_node.top();
			if (!visit[top_node]){
				dfs_back(top_node);
				while(!same_mom.empty()){
					mom[same_mom.back()]=top_node;
					same_mom.pop_back();
				}
			}
			searched_node.pop();
		}
		
		int result=0;
		for (i=1;i<=n;i++){
			bool hasMom=false;
			if (mom[i] == i){
				for (int _n:list_rev[i]){
					if (mom[_n] != i){
						hasMom=true;
						break;
					}
				}
				if (!hasMom) result++;
			}
		}
		cout << result << endl;
		
		for (i=1;i<=n;i++) list[i].clear(), list_rev[i].clear();
	}
	return 0;
}
