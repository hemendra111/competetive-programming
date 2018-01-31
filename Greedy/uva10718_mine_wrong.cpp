/* Greedy and Ad-hoc */
#include <iostream>
#include <cstdio>

using namespace std;

int msb(long long int m) {					// the function returns the msb position, function is unnecessary \
								   in the present context
	m = m | m >> 1; 				// makes adjacent 1 bit to every set bit 1
	m = m | m >> 2; 				// makes adjacent 2 bits to every set bit 1
	m = m | m >> 4; 				// makes adjacent 4 bits to every set bit 1
	m = m | m >> 8; 				// makes adjacent 8 bit to every set bit 1
	m = m | m >> 16; 				// makes adjacent 16 bits to every set bit 1, at this point every \
							   every bit to the right of msb is 1
	m = m & (~m >> 1);
	//m = m & ((~m >> 1)^0x80000000);		// take 1's complement, right shifts by 1 and "AND" with m \
							   the final manipulation ensures that you don't kill the top bit if it exists. 
	cout << "m is now " << m << endl;		// ans is something like 000001000000
	int ret = 0;
	while(m) {
		ret++;
		m >>= 1;
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	long long int n, l , u, ans;
	bool flag;					// flag = true means 1 has been converted to 0 in ans once or more
	while(cin >> n >> l >> u) {
		//cout << "hey" << endl;
		//cout << n << ' ' << l << ' ' << u << endl;
		ans = u;				// set ans to u and minimize it such that "OR" with n is maximum
		flag = false;
		int rstart = -1; 
		unsigned int m = u;
		while(m) {
			rstart++;
			m >>= 1;
		}
		//cout << "rstart is " << rstart << endl; 
		for(int i = rstart; i >= 0; i--) {
			//cout << "In Loop, ans is " << ans << endl;
			if(!(n & (1LL << i))) {		// if bit not set in n, try to set the bit in ans
				if(!(ans & (1LL << i))) {	// if bit not set in ans, try to set it
					//cout << "bit not set in our no, try to set in ans" << endl;
					if(flag) {
						ans += (1LL << i); // only set when flag has been set, i.e., 1 one has been converted to 0
						//if(ans > u) ans -= (1LL << i);	// if setting makes the value greater than u, unset it 
					}
					 
				}
			}
			else if(ans & (1LL << i)) {	// if bit already set in n
				//cout << "bit set in ans, try to unset it" << endl;
				//cout << ans << ' ' << (1LL << i) << endl;
				ans -= (1LL << i);		// try to unset it
				//cout << "Before subtract, ans is " << ans << endl;
				if(ans < l) ans += (1LL << i);	// if unsetting makes the value less than l, set it 
				else flag = true;	// flag is set here
				//cout << "Final, ans is " << ans << endl;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
