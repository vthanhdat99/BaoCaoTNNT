/*
NHÓM 35
Thành viên 1: Võ Thành Đạt			MSSV: N20DCCN015
Thành viên 2: Nguyễn Văn Hoài Nam 	MSSV: N20DCCN043
Thành viên 3: Đồng Nguyễn Bút Giang MSSV: N19DCCN042
*/
#include <bits/stdc++.h>

using namespace std;
const int maxN = 100;

vector<int> g[maxN];
vector<int> color(maxN), colorFinal(maxN);
int deg[maxN], arrSorted[maxN];
int MIN = INT_MAX;
int n, m;
int maxNum = 9;
int checkNumberColor() {
	bool rt[maxNum + 1];
	for (int i = 0; i <= maxNum; i++)
		rt[i] = false;
	for (int i = 1; i <= n; i++) {
		if(color[i] != -1) rt[color[i]] = true;
	}
	int ans = 0;
	for (int i = 0; i <= maxNum; i++) {
		if (rt[i] == true)
			ans++;
	}
	return ans;
}
int change = 0;
void graphColoring(int k) {
	int nF = 0;
	int s = arrSorted[k];
	if (k == n + 1) {
		int ch = checkNumberColor();
		if (ch < MIN) {
			MIN = ch;
			maxNum = MIN - 1;
			colorFinal = color;
		}
		return;
	}
	
	for (int i = 0; i <= maxNum; i++) {
		if (change != 0) {
			if (find(g[s].begin(), g[s].end(), change) != g[s].end()) {
				change = 0;
			} else {
				return;
			}
		}
		color[s] = i;
		bool isok = true;
		bool isokmin = checkNumberColor() < MIN;
		for (int u : g[s]) {
			if (color[u] == color[s]) {
				isok = false;
				break;
			}
		}
		if (isok == false) nF++;
		if (isok == true && isokmin == true) {
			graphColoring(k + 1);
		}
	}
	if (nF != maxNum + 1) {
		change = s;
	}
	color[s] = -1;
}
bool cmp(int a, int b) {
	return deg[a] > deg[b];
}
main() {
	freopen("inGK1.txt", "r", stdin);
	cin >> n >> m;
//	n = rand() % 1000;
//	m = (n*20);
	for (int i = 1; i <= n; i++) {
		arrSorted[i] = i;
		deg[i] = 0;
		color[i] = -1;
	}
	while(m--) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	int MAX = 0;
	for (int i = 1; i <= n; i++) {
		MAX = max(MAX, deg[i]);
	}
	maxNum = MAX;
	sort(arrSorted + 1, arrSorted + n + 1, cmp);
	graphColoring(1);
	cout << "So mau it nhat can dung la: " << MIN << "\n";
	for (int i = 1; i <= n; i++) {
		cout << "Dinh " << i << " co mau: " << colorFinal[i] << "\n";
	}
	bool okF = true;
	for (int i = 1; i <= n; i++) {
		for (int u : g[i]) {
			if(colorFinal[u] == colorFinal[i]) okF = false;
		}
	}
	cout<<okF;
}
