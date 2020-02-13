// Copyright 2018 Coman Diana
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		get_result();
	}

 private:
	int n;
	int m; int rez = 0;
	vector<int> adj[kNmax];
    vector<int> adjt[kNmax];
    vector<int> adj1[kNmax];
	struct Edge {
		int x;
		int y;
	};

// citire
// vectorul adj se construiecte in ordine lexicografica
	void read_input() {
		ifstream fin("disjcnt.in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y); adjt[y].push_back(x);
            adjt[x].push_back(y); adj[y].push_back(x);
		}
		fin.close();
	}
// se face DFS pe adj transpus - ptr ctc
    void DFS_tr(int node, vector<int> &visited, vector<int> &tc) {
		visited[node] = 1;
		tc.push_back(node);
		for (auto j : adjt[node]) {
			if (!visited[j]) {
				DFS_tr(j, visited, tc);
			}
		}
	}
// DFS pe adj - ptr ctc
	void DFS(int node, vector<int> &visited, vector<int> &topsort) {
		visited[node] = 1;
		for (auto j : adj[node]) {
			if (!visited[j]) {
				DFS(j, visited, topsort);
			}
		}
		topsort.push_back(node);
	}
// functie principala
// se indeparteaza muchiile critice, apoi se face ctc pe graful ramas
	void get_result() {
		vector<Edge> sol;
		int timp = 0;
		vector<int> idx(n + 1, 0), low(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			if (idx[i] == 0) {
				dfsPA(i, 0, timp, sol, idx, low);
			}
		}
        for (int i = 0; i < sol.size(); i++) {
			int b = sol[i].x; int c = sol[i].y;
            int k2 = 0; bool ok = true;
            while (ok == true) {
// se cauta daca sunt mai multe "drumuri" pe muchia b - c
// daca da, se readauga muchia, o singura data
            if ((std::find(adj[b].begin(), adj[b].end(), c) != adj[b].end())) {
                auto it = find(adj[c].begin(), adj[c].end(), b);
                adj[c].erase(it);
                auto iz = find(adjt[b].begin(), adjt[b].end(), c);
                adjt[b].erase(iz);
                auto ia = find(adj[b].begin(), adj[b].end(), c);
                adj[b].erase(ia);
                auto is = find(adjt[c].begin(), adjt[c].end(), b);
                adjt[c].erase(is);
                k2++;
            } else {
                ok = false;
            }
            }
            if (k2 > 1) {
                adj[b].push_back(c); adj[c].push_back(b);
                adjt[b].push_back(c); adjt[c].push_back(b);
             }
		}
// aici incepe ctc
        vector<vector<int>> result;
        vector<int> visited1(n + 1, 0), topsort;
		for (int i = 1; i <= n; ++i) {
			if (!visited1[i]) {
				DFS(i, visited1, topsort);
			}
		}
        visited1 = vector<int>(n + 1, 0);
		std::reverse(topsort.begin(), topsort.end());
        for (auto node : topsort) {
            if (!visited1[node]) {
				vector<int> TC;
				DFS_tr(node, visited1, TC);
				result.push_back(TC);
			}
		}
// calcularea rezultatului dupa ctc
// in cazul in care exista o muchie multipla cu mai multe drumuri
// care e retinuta in adj1, se tine cont de ea, prin k4, k5
		for (auto ctc : result) {
            long k1 = ctc.size();
		    rez = k1*(k1-1)/2 + rez;
		}
        ofstream fout("disjcnt.out");
		fout << rez << '\n';
		fout.close();
	}
// functie pt muchii critice
	void dfsPA(int node, int parent, int &timp, vector<Edge> &sol,
			vector<int> &idx, vector<int> &low) {
		idx[node] = low[node] = ++timp;
		for (auto v : adj[node]) {
			if (v != parent) {
				if (idx[v] == 0) {
					dfsPA(v, node, timp, sol, idx, low);
					low[node] = min(low[node], low[v]);
					if (low[v] > idx[node]) {
						sol.push_back({node, v});
					}
				} else {
					low[node] = min(low[node], idx[v]);
				}
			}
		}
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
