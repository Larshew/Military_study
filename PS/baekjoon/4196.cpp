#include <iostream>
#include <vector>
#include <algorithm>
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

bool hasMom[MAX_NM+1];
int main()
{
	int testcase;
	cin >> testcase;
	for (int ts=1;ts<=testcase;ts++){
		int i;

		cin >> n >> m;

		for (i=1;i<=n;i++) hasMom[i]=false;
		for (i=1;i<=m;i++){
			int a,b;

			cin >> a >> b;
			list[a].push_back(b);
			list_rev[b].push_back(a);
		}
		
		for (i=1;i<=n;i++){
			sort(list[i].begin(), list[i].end());
			sort(list_rev[i].begin(), list_rev[i].end());
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
		
		cout << endl;
		int result=0;
		for (i=1;i<=n;i++){
			for (int _n:list_rev[i]){
				if (mom[_n] != mom[i]){
					hasMom[mom[i]]=true;
					break;
				}
			}
		}

		for (i=1;i<=n;i++){
			if (mom[i]==i && !hasMom[i]) result++;
		}
		cout << result << endl;
		
		for (i=1;i<=n;i++) list[i].clear(), list_rev[i].clear();
	}
	return 0;
}
