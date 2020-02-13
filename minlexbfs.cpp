// Copyright 2018 Coman Diana
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<int> adj[kNmax];

// citire
	void read_input() {
		ifstream fin("minlexbfs.in");
		fin >> n >> m;
        source = 1;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1, -1);
        vector<int> d1(n + 1, -1); int i1 = 0;
        int node, j, k, aux;
        queue<int> q;
        d[source] = 0;
// ordonare a vectorului de adiacenta
        for (k = 1; k <= n; k++) {
        for (int i = 0; i < adj[k].size() - 1; ++i) {
            for (int j = i+1; j < adj[k].size(); ++j) {
			if (adj[k][i] > adj[k][j]) {
                aux = adj[k][i];
                adj[k][i] = adj[k][j];
                adj[k][j] = aux;
            }
			}
	    }
        }
// BFS din nodul 1
        q.push(source);
        while (!q.empty()) {
            node = q.front();
            i1++;
            d1[i1] = node;
            cout << node;
            q.pop();
            for (int i = 0; i < adj[node].size(); i++) {
                j = adj[node][i];
                if (d[j] == -1) {
                    d[j] = d[node] + 1;
                    q.push(j);
                }
            }
        }
		return d1;
	}
// printare output
	void print_output(vector<int> result) {
		ofstream fout("minlexbfs.out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
