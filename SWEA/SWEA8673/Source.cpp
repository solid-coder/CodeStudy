#include <iostream>
using namespace std;

int abs(int a){
	return a >= 0 ? a : a*-1;
}

int main(int argc, char** argv){
	cin.tie(NULL);	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	int arr[1024];
	for (int testcase = 1; testcase <= T; testcase++){
		int K, num = 1;
		cin >> K;

		num <<= K;
		for (int i = 0; i < num; i++)
			cin >> arr[i];
		
		int ans = 0;
		while (num > 1){
			for (int i = 0; i < num; i += 2){
				ans += abs(arr[i] - arr[i + 1]);
				arr[i / 2] = arr[i] > arr[i + 1] ? arr[i] : arr[i + 1];
			}
			num >>= 1;
		}
		
		cout << "#" << testcase << " " << ans << "\n";
	}

	return 0;
}