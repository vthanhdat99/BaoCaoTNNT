/*
NHÓM 35
Thành viên 1: Võ Thành Đạt			MSSV: N20DCCN015
Thành viên 2: Nguyễn Văn Hoài Nam 	MSSV: N20DCCN043
Thành viên 3: Đồng Nguyễn Bút Giang MSSV: N19DCCN042
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxN = 100 + 7;
int m, n, p;
int R[maxN][maxN];
int nD[maxN][maxN];
bool T[maxN][maxN], C[maxN][maxN], D[maxN][maxN], g[maxN][maxN];
int value[maxN];
vector < pair < int, int >> vec;
map < int, int > vs;
int idx = 0;
int siz;
int cnt1 = 1;
int cnt2 = 10;
int cnt3 = 100;
int mod = 1e9 + 7;
int value_of_answer;

int H() {
	int ans = 0;
	for (int i = 1; i <= siz; i++) {
		int u = vec[i].first;
		int v = vec[i].second;
		int px = value[i];
		for (int j = 1; j <= siz; j++) {
			if (g[i][j] == 1 && value[i] == value[j]) {
				ans -= cnt1;
			}
			if (g[i][j] == 1 && value[i] != value[j]) {
				ans += cnt1;
			}
		}
		if (T[v][px]) {
			ans += cnt2;
		} else {
			ans -= cnt2;
		}
		if (C[u][px]) {
			ans += cnt2;
		} else {
			ans -= cnt2;
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			nD[i][j] = 0;
		}
	}
	for (int i = 1; i <= siz; i++) {
		int u = vec[i].first;
		int px = value[i];
		nD[u][px]++;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			if (D[i][j] == 1) {
				ans += (nD[i][j] != 1) ? abs(nD[i][j] - 1) * -1 * cnt3 : cnt3;
			}
		}
	}
	return ans;
}

void find_value_of_answer() {
	int ans = 0;
	for (int i = 1; i <= siz; i++) {
		for (int j = 1; j <= siz; j++) {
			if (g[i][j] == 1) {
				ans += cnt1;
			}
		}
		ans += cnt2;
		ans += cnt2;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			if (D[i][j] == 1) {
				ans += cnt3;
			}
		}
	}
	value_of_answer = ans;
}

int F() {
	int ans = 0;
	for (int i = 1; i <= siz; i++) {
		ans = ans * p + value[i];
		ans %= mod;
	}
	return ans;
}

void inp() {
	freopen("inCK2.txt", "r", stdin);
	cin >> m >> n >> p;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> R[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= p; j++) {
			cin >> T[i][j];
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			cin >> C[i][j];
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			cin >> D[i][j];
		}
	}
	vec.push_back({0,0});
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int z = 1; z <= R[i][j]; z++) {
				vec.push_back({
					i,
					j
				});
			}
		}
	}
	siz = vec.size() - 1;
	for (int i = 1; i <= siz; i++) {
		for (int j = i + 1; j <= siz; j++) {
			if (vec[i].first == vec[j].first || vec[i].second == vec[j].second) {
				g[i][j] = 1;
				g[j][i] = 1;
			}
		}
	}
}

void print_of_timetable() {
	for (int i = 1; i <= p; i++) {
		cout << "**Tiet " << i << ": \n";
		for (int j = 1; j <= siz; j++) {
			if (value[j] == i) {
				cout << "(LOP" << vec[j].first << " - " << "GV" << vec[j].second << ")\n";
			}
		}
		cout << "\n";
	}
}

void creat_of_timetable() {
	for (int i = 1; i <= siz; i++) {
		for (int j = 1; j <= p; j++) {
			bool ok = 1;
			for (int z = 1; z <= siz; z++) {
				if (g[i][z] == 1 && value[z] == j) {
					ok = 0;
					break;
				}
			}
			if (ok == 1 || j == p) {
				value[i] = j;
				break;
			}
		}
	}
}

void solution() {
	creat_of_timetable();
	int h = H();
	while(H() != value_of_answer && idx <= 30000) {
		idx++;
		bool is_next = 0;
		for (int i = 1; i <= siz && is_next == 0; i++) {
			int px = value[i];
			for (int j = 1; j <= p && is_next == 0; j++) {
				value[i] = j;
				int hc = H();
				if (hc > h && vs[F()] == 0) {
					is_next = 1;
					h = hc;
				} else {
					value[i] = px;
				}
			}
		}
		if(is_next == 1) continue;
		vs[F()] = 1;
		while (vs[F()] == 1) {
			for(int i=1; i<=siz; i++) {
				value[i] = rand() % p + 1;
			}
		}
		vs[F()] = 1;
	}
}

main() {
	inp();
	solution();
	print_of_timetable();

}
