#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int n, m;
char map[21][21];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

typedef pair<int, int> pp;

pp coin1, coin2;

typedef struct node {
	pp cp1;
	pp cp2;
	int cnt;
};

bool is_wall(pp point) {
	if (map[point.second][point.first] == '#')
		return true;
	return false;
}

bool is_fall(pp point) {
	if (point.first < 0 || point.first >= m)
		return true;
	if (point.second < 0 || point.second >= n)
		return true;
	return false;
}

int bfs() {
	queue<node> q;

	q.push({ coin1, coin2, 0 });

	while (!q.empty()) {
		pp curr1 = q.front().cp1;
		pp curr2 = q.front().cp2;
		int curr_cnt = q.front().cnt;
		q.pop();

		if (curr_cnt > 10)
			return -1;

		if (is_fall(curr1) || is_fall(curr2)) {
			return curr_cnt;
		}

		for (int i = 0; i < 4; i++) {
			pp tp1 = curr1;
			tp1.first += dx[i];
			tp1.second += dy[i];
			pp tp2 = curr2;
			tp2.first += dx[i];
			tp2.second += dy[i];
            
			if (is_fall(tp1) && is_fall(tp2))
				continue;

			if (is_wall(tp1) && !is_wall(tp2)) {
				q.push({ curr1, tp2, curr_cnt + 1 });
			}
			else if (is_wall(tp2) && !is_wall(tp1)) {
				q.push({ tp1, curr2, curr_cnt + 1 });
			}
			else if (!is_wall(tp1) && !is_wall(tp2)) {
				q.push({ tp1, tp2, curr_cnt + 1 });
			}
			else if (is_wall(tp1) && is_wall(tp2))
				continue;
		}
	}
	return -1;
}

void find_coin() {
	int temp = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 'o') {
				if (temp == 0) {
					coin1.first = j;
					coin1.second = i;
					temp++;
				}
				else {
					coin2.first = j;
					coin2.second = i;
					return;
				}
			}
		}
	}
}

int main(void) {

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	find_coin();

	int ret = bfs();

	cout << ret;

	return 0;
}