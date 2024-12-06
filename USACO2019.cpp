// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long

struct cow {
	int x, w, d, i;
	bool operator<(const cow &y) const { return x < y.x; }
};

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n, l;
		cin >> n >> l;
		l = 2 * l;
		vector <cow> cc(n);
		vector <cow> left; //yang arah kekiri
		vector <cow> right; //arah kekanan
		vector <pair<int, int>> time; //time and weight
		int weight = 0;

		for (int i = 0; i < n; i = i + 1) {
			int x, w, d;
			cin >> x >> w >> d;
			cc[i].x = 2 * x;
			cc[i].w = 2 * w;
			cc[i].d = d;
			weight += cc[i].w;
		}

		sort(cc.begin(), cc.end()); //sort based on left to right on the axis

		for (int i = 0; i < n; i = i + 1) {
			cc[i].i = i;
		} //giving index to cows

		for (int i = 0; i < n; i = i + 1) {
			if (cc[i].d == -1) {
				left.push_back(cc[i]);
			} else {
				right.push_back(cc[i]);
			}
		}

		sort(right.begin(), right.end());
		sort(left.begin(), left.end());

		//initializing time from left 
		for (int i = 0; i < n; i = i + 1) {
			if (cc[i].d == -1) {
				time.push_back({cc[i].x, cc[i].w});
			} else {
				break;
			}
		}
		
		//focus on the clashes
		vector <cow> filtered_overall;
		vector <cow> filtered_left;
		vector <cow> filtered_right;

		//berada sebelum sapi kekanan yang pertama && kirinya kiri terakhir
		for (int i = right[0].i; i <= left[left.size() - 1].i; i = i  + 1) {
				filtered_overall.push_back(cc[i]);
		}

		for (int i = 0; i < (int) filtered_overall.size(); i = i + 1) {
			if (filtered_overall[i].d == -1) {
				filtered_left.push_back(filtered_overall[i]);
			} else {
				filtered_right.push_back(filtered_overall[i]);
			}
		}

		for (int i = 0; i < filtered_right[0].i; i = i + 1) {
			int tt = cc[i].x;
			time.push_back({tt, cc[i].w});
		}

		for (int i = 0; i < (int) filtered_overall.size(); i = i + 1) {
			if (i < (int) filtered_left.size()) {
				int tt = filtered_left[i].x;
				time.push_back({tt, filtered_overall[i].w});
			} else {
				int tt = filtered_right[i - filtered_left.size()].x;
				time.push_back({l - tt, filtered_overall[i].w}); 
			}
		}

		for (int i = filtered_left[filtered_left.size() - 1].i + 1; i < n; i = i + 1) {
			int tt = l - cc[i].x;
			time.push_back({tt, cc[i].w});
		}

		sort(time.begin(), time.end());

		// for (int i = 0; i < time.size(); i = i + 1) {
		// 	cout << time[i].first << endl;
		// }

		//initializing time && weight for the rest
		
		int half_weight = weight / 2; //target weight

		sort(time.begin(), time.end()); //sorted time with its weight

		

		int wdone = 0; //weight sum till done
		int tdone = 0; //time till done
		int curr = 0;
		while (wdone < half_weight) {
			wdone += time[curr].second;
			tdone = time[curr].first;
			curr += 1;
		}


		// for (int i = 0; i < filtered_left.size(); i = i + 1) {
		// 	cout << filtered_left[i].i << "what" << endl ;
		// }

		//number of collisions based on those moving right		
		vector <int> vuk(filtered_right.size(), 0);
		int p1 = 0;
		int p2 = 0;
		while (p1 < filtered_right.size()) {
			if (filtered_right[p1].i < filtered_left[p2].i && p1 > 0)  {
				vuk[p1] = vuk[p1 - 1] - (filtered_right[p1].i - filtered_right[p1 - 1].i - 1);
			}

			if (p2 == filtered_left.size()) {
				vuk[p1] = vuk[p1 - 1] - (filtered_right[p1].i - filtered_right[p1 - 1].i - 1);
			}

			while (p2 < (int)filtered_left.size()) {
				int kanan = filtered_left[p2].x;
				int kiri = filtered_right[p1].x;
				if (kanan - kiri <= 2 * tdone) {
					vuk[p1] += 1;
					p2 += 1;
				} else {
					break;
				}
			}
			p1 += 1;
		}
	
		
		// for (int i = 0; i < (int)vuk.size(); i = i + 1) {
		// 	cout << vuk[i] << endl;
		// }

		int ans = 0;
		for (int i = 0; i < (int)vuk.size(); i = i + 1) {
			ans += vuk[i];
		}
		cout << ans << endl;

	}
}