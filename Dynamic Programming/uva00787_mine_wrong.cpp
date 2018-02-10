#include <iostream>
#include <string>
#include <vector>

using namespace std;

string add(string a, string b) {
	string c = "";
	//cout << "a is " << a << ", b is " << b << endl;
	int i = a.length() - 1, j = b.length() - 1;
	int car = 0;
	while(i >= 0 && j >= 0) {
		int temp = a[i] - '0' + b[j] - '0' + car;
		car = temp / 10;
		c = static_cast<char>((temp % 10) + '0') + c;
		i--; 
		j--;
	}
	//cout << "c is " << c << endl;
	while(i >= 0) {
		int temp = a[i] - '0' + car;
		car = temp / 10;
		c = static_cast<char>((temp % 10) + '0') + c;
		i--; 
	}
	//cout << "c is " << c << endl;
	while(j >= 0) {
		int temp = b[j] - '0' + car;
		car = temp / 10;
		c = static_cast<char>((temp % 10) + '0') + c;
		j--; 
	}
	//cout << "c is " << c << endl;
	return c;
}

string multiply(string a, string b) {
	bool plus_sign = true;
	//cout << "In multiply, a is " << a << ", b is " << b << endl;
	if(!a.compare("0") || !b.compare("0")) return "0";
	if(a[0] == '-') {
		plus_sign = static_cast<bool>(1 - static_cast<int>(plus_sign));
		a = a.substr(1, a.length() - 1);
	}
	if(b[0] == '-') {
		plus_sign = static_cast<bool>(1 - static_cast<int>(plus_sign));
		b = b.substr(1, b.length() - 1);
	}
	while(a[0]== '0') a = a.substr(1, a.length() - 1);
	while(b[0]== '0') b = b.substr(1, b.length() - 1);
	//cout << "After removing -ve signs, a is " << a << ", b is " << b << ", plus_sign is " << plus_sign << endl;
	string res = "0", temp;
	int car;
	for(int i = b.length() - 1; i >= 0; i--) {
		temp = "";
		car = 0;
		for(int j = a.length() - 1; j >= 0; j--) {
			int temp1 = ((a[j] - '0') * (b[i] - '0') + car);
			car = temp1 / 10;
			temp = static_cast<char>((temp1 % 10) + '0') + temp;
			//cout << "temp is " << temp << endl;
		}
		if(car) temp = static_cast<char>(car + '0') + temp;
		for(int j = i; j < b.length() - 1; j++) temp += '0';
		res = add(res, temp);
		//cout << "res is " << res << endl;
	}
	//cout << "car is " << car << endl;
	//if(car) res = static_cast<char>(car + '0') + res;
	if(plus_sign == false) res = '-' + res;
	return res;
}

string max(string a, string b) {
	if(a[0] == '-' && b[0] != '-') return b;
	if(b[0] == '-' && a[0] != '-') return a;
	string c = a, d = b;
	if(a[0] == '-' && b[0] == '-') {
		a.substr(1, a.length() - 1);
		b.substr(1, b.length() - 1);
		while(static_cast<char>(a[0]) == '0') a = a.substr(1, a.length() - 1);		
		while(static_cast<char>(b[0]) == '0') b = b.substr(1, b.length() - 1);
		if(a.length() < b.length()) return c;		
		if(a.length() > b.length()) return d;
		int i = 0, j = 0;
		while(i < a.length() && j < b.length()) {
			if(a[i] > b[j]) return d;
			if(a[i] < b[j]) return c;
			i++;
			j++;
		}
		if(i == a.length()) return c;
		return d;		
	}
	else {
		while(static_cast<char>(a[0]) == '0') a = a.substr(1, a.length() - 1);		
		while(static_cast<char>(b[0]) == '0') b = b.substr(1, b.length() - 1);
		if(a.length() < b.length()) return d;		
		if(a.length() > b.length()) return c;
		int i = 0, j = 0;
		while(i < a.length() && j < b.length()) {
			if(a[i] > b[j]) return c;
			if(a[i] < b[j]) return d;
			i++;
			j++;
		}
		if(i == a.length()) return d;
		return c;		
	}
}

string find_msp(vector<string> v) {
	string maxP = "-99999999999999999999999", prod = "";
	for(int start = 0; start < v.size(); start++) {
		prod = "1";
		for(int i = start; i < v.size(); i++) {
			prod = multiply(prod, v[i]);
			maxP = max(maxP, prod);
		}
	}
	return maxP;
#if 0
	string ans = v[0], max_candidate = "";
	for(int i = 1; i < v.size(); i++) {
		cout << "i is " << i << endl;
		ans = max(ans, multiply(ans, v[i]));
		if(!ans.compare("0")) {
			max_candidate = "0";
			if(i < v.size() - 1) { 
				ans = v[i + 1]; 
				i++; 
			} 
		}
	}	
	return !max_candidate.empty() && static_cast<char>(ans[0]) == '-' ? "0" : ans;
#endif
}

int main() {
	vector<string> v;
	string s;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#if 1
	cout << multiply("12321", "221929") << endl;
	cout << multiply("321", "9929") << endl;
	cout << multiply("-112321", "00221929") << endl;
	cout << multiply("-12321", "-23232929") << endl;
	cout << multiply("13322321", "1221929") << endl;
	cout << multiply("12321", "2321929") << endl;
#endif
	while(cin >> s) {
		if(!s.compare("-999999")) {
			//if(v.empty()) cout << "v is empty" << endl; else cout << v.size() << endl;
			//cout << s << endl;
			cout << find_msp(v) << endl;
			v.clear();
		}
		else { 
			//cout << s << ' ';
			v.push_back(s);
		}
	}
	return 0;
}
