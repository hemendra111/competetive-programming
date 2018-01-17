#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <climits>

using namespace std;

const int MAXSIZE = 100007;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	//cout << INT_MIN << ' ' << INT_MAX << endl;
	int num, med = -1;
	vector<int> mx, mn;
	make_heap(mx.begin(), mx.end());
	make_heap(mn.begin(), mn.end(), [](int a, int b) { return a > b; });
	while(1) {
		cin >> num;
		if(cin.eof()) break;
		if(med == -1) { mx.push_back(num); push_heap(mx.begin(), mx.end()); med = num; }
		else {
			if(num <= med) { mx.push_back(num); push_heap(mx.begin(), mx.end()); }
			else { mn.push_back(num); push_heap(mn.begin(), mn.end(), [](int a, int b) { return a > b; }); }
			int mnsz = mn.size(), mxsz = mx.size();
			if(mnsz != mxsz) {
				if(mnsz > mxsz) {
					while(mn.size() - mx.size() >= 2) { 
						mx.push_back(mn.front()); 
						pop_heap(mn.begin(), mn.end(), [](int a, int b) { return a > b; }); 
						mn.pop_back();
						push_heap(mx.begin(), mx.end());
					}
				}
				else {
					while(mx.size() - mn.size() >= 2) { 
						mn.push_back(mx.front()); 
						pop_heap(mx.begin(), mx.end()); 
						mx.pop_back();
						push_heap(mn.begin(), mn.end(), [](int a, int b) { return a > b; });
					}
				}
			}
#if 0
			cout << "mx front is " << mx.front() << " , mn front is " << mn.front() << endl;
			cout << "mx size is " << mx.size() << " , mn size is " << mn.size() << endl;
			cout << abs(static_cast<int>(mn.size()) - static_cast<int>(mx.size())) << endl;
#endif
			if(abs(static_cast<int>(mn.size()) - static_cast<int>(mx.size())) > 1) assert(0);	
			if(mn.size() == mx.size()) med = (static_cast<long long>(mx.front()) + mn.front()) / 2;
			else if(mx.size() > mn.size()) med = mx.front();
			else med = mn.front();
		}
		cout << med << endl;
	}
	cout << endl;
	return 0;
}
