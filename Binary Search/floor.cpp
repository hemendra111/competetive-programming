#include <iostream>

using namespace std;

/* finds index in arr where value is just greater than equal to key
if key is less than min element, returns -1
*/

int floor(int arr[], int key) {
	int l = 0, r = 6, mid;
	if(key > arr[6]) return -1;
	while(l < r) {
		if(r - l == 1) {
			if(key > arr[r]) return r + 1;
			else if(key > arr[l]) return r;
			else return l;	
		}
		mid = l + (r - l) / 2;              // this method for mid only required when overflow may happen
		if(key > arr[mid]) l = mid + 1;
		else if(key == arr[mid]) l = mid;
		else r = mid;
	}
	return l;                                   // l will be equal to r at this point 
}

int main() {
	int arr[7] = {2, 5, 10, 10, 10, 20, 25};
	for(int i = 0; i < 7; i++) cout << arr[i] << ' ';
	cout << endl;
	cout << "floor for 0 is found at index " << floor(arr, 0) << endl;
	cout << "floor for 2 is found at index " << floor(arr, 2) << endl;
	cout << "floor for 3 is found at index " << floor(arr, 3) << endl;
	cout << "floor for 5 is found at index " << floor(arr, 5) << endl;
	cout << "floor for 6 is found at index " << floor(arr, 6) << endl;
	cout << "floor for 10 is found at index " << floor(arr, 10) << endl;
	cout << "floor for 12 is found at index " << floor(arr, 12) << endl;
	cout << "floor for 20 is found at index " << floor(arr, 20) << endl;
	cout << "floor for 23 is found at index " << floor(arr, 23) << endl;
	cout << "floor for 25 is found at index " << floor(arr, 25) << endl;
	cout << "floor for 30 is found at index " << floor(arr, 30) << endl;
	return 0;
}
