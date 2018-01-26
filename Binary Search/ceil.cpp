#include <iostream>

using namespace std;

/* finds index in arr where value is just less than equal to key
if key is greater than max element, returns -1
*/

int ceil(int arr[], int key) {
	int l = 0, r = 6, mid;
	if(key < arr[0]) return -1;
	while(l < r) {
		if(r - l == 1) {
			if(key < arr[l]) return l - 1;
			else if(key < arr[r]) return l;
			else return r;
		}
		mid = l + (r - l) / 2;              // this method for mid only required when overflow may happen
		if(key < arr[mid]) r = mid - 1;
		else if(key == arr[mid]) r = mid;
		else l = mid;
	}
	return l;                                   // l will be equal to r at this point
}

int main() {
	int arr[7] = {2, 5, 5, 5, 10, 20, 25};
	for(int i = 0; i < 7; i++) cout << arr[i]<< ' ';
	cout << endl;
	cout << "ceil for 0 is found at index " << ceil(arr, 0) << endl;
	cout << "ceil for 2 is found at index " << ceil(arr, 2) << endl;
	cout << "ceil for 3 is found at index " << ceil(arr, 3) << endl;
	cout << "ceil for 5 is found at index " << ceil(arr, 5) << endl;
	cout << "ceil for 6 is found at index " << ceil(arr, 6) << endl;
	cout << "ceil for 10 is found at index " << ceil(arr, 10) << endl;
	cout << "ceil for 12 is found at index " << ceil(arr, 12) << endl;
	cout << "ceil for 20 is found at index " << ceil(arr, 20) << endl;
	cout << "ceil for 23 is found at index " << ceil(arr, 23) << endl;
	cout << "ceil for 25 is found at index " << ceil(arr, 25) << endl;
	cout << "ceil for 30 is found at index " << ceil(arr, 30) << endl;
	return 0;
}
