// Copyright 2018 Coman Diana
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 501;

class Task {
 public:
	void solve() {
		compute();
	}

 private:
	int q, m, n;
	int d[kNmax][kNmax];
	int a[kNmax][kNmax];

// functie principala
	void compute() {
        int x, y;
// citire
        ifstream fin("revedges.in");
		fin >> n >> m >> q;
// initiere cu -1 pt ca 0 e un cost
        for (int i = 1; i <= n; i++) {
			for (int j = 1; j<= n; j++) {
				a[i][j] = -1;
		    }
		}
        ofstream fout("revedges.out");
// creere matrice
// cost original = 0, cost inversat = 1
		for (int i = 1; i <= m; i++) {
			fin >> x >> y;
            a[x][y] = 0;
            if (a[y][x] == 0) {
                a[y][x] = 0;
            } else {
                a[y][x] = 1;
            }
        }
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j<= n; j++) {
				if (a[i][j] == -1) {
					d[i][j] = 10000000;
                } else {d[i][j] = a[i][j];}
			}
			d[i][i] = 0;
		}
        int k;
// se utilizeaza Roy-Floyd pt costul minim
        for (k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <=n ; j++) {
                    if (i != j) {
                        if (d[i][j] > d[i][k] + d[k][j]) {
						    d[i][j] = d[i][k] + d[k][j];
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
			for (int j = 1; j<= n; j++) {
				if (d[i][j] == 10000000) {
                    d[i][j] = 0;
                }
			}
		}
// printare solutie
        for (int k1 = 1; k1 <=q; k1++) {
		    fin >> x >> y;
            fout << d[x][y] << "\n";
        }
        fin.close();
        fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
