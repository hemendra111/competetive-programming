#include <iostream>

using namespace std;

int binary_search(int arr[], int key) {
	int l = 0, r = 4, mid;
	while(l <= r) {
		mid = l + (r - l) / 2;              // this method for mid only required when overflow may happen
		if(key == arr[mid]) return mid;
		if(key < arr[mid]) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}

int main() {
	int arr[5] = {2, 5, 10, 20, 25};
	for(int i = 0; i < 5; i++) cout << arr[i] << ' ';
	cout << endl;
	cout << "0 is found at index " << binary_search(arr, 0) << endl;
	cout << "2 is found at index " << binary_search(arr, 2) << endl;
	cout << "3 is found at index " << binary_search(arr, 3) << endl;
	cout << "5 is found at index " << binary_search(arr, 5) << endl;
	cout << "6 is found at index " << binary_search(arr, 6) << endl;
	cout << "10 is found at index " << binary_search(arr, 10) << endl;
	cout << "12 is found at index " << binary_search(arr, 12) << endl;
	cout << "20 is found at index " << binary_search(arr, 20) << endl;
	cout << "23 is found at index " << binary_search(arr, 23) << endl;
	cout << "25 is found at index " << binary_search(arr, 25) << endl;
	cout << "30 is found at index " << binary_search(arr, 30) << endl;
	return 0;
}
