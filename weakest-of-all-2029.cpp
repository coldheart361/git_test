// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long


signed main() {
	int n;
	cin >> n;
	int mod = 10e9 + 7;
	int arr[n];
	for (int i = 0; i < n; i = i + 1) cin >> arr[i];
	sort(arr, arr + n);
	int count = n;
	int ans = 0;
	while(count != 1) {
		ans = (ans + arr[0] * (int) pow(2, count - 1)) % mod; //the -2.x^n-1 thing
		int knt = arr[0];
		for (int i = 0; i < count; i ++) {
			arr[i] = arr[i] - knt;
		}
		priority_queue <int> pq;
		for (int k = 1; k < count; k ++) {pq.push(arr[0] + arr[k]);} 
		int tt = 1;
		// for (int i = 0; i < count; i ++) {
		// 	cout << "ugh " << arr[i] << endl;
		// }
		while (arr[tt] + arr[tt+1] < pq.top()) {
			for (int j = tt + 1; arr[tt] + arr[j] < pq.top(); j ++) {
				pq.push(arr[tt] + arr[j]);
				pq.pop();
			}
			tt += 1;
		}
		// cout << pq.top() << endl;
		
		for (int i = count - 2; i > -1; i = i - 1) {
			arr[i] = pq.top();
			pq.pop();
		}
		count = count - 1;
	}
	cout << ans << endl;

}
