#include <iostream>

using namespace std;

struct node {
	char val;
	node *next;
	node(char c = 0, node *p = nullptr) : val(c), next(p) {};
};

class linkedlist {
	node *head, *tail;
public:
	linkedlist() : head(nullptr), tail(nullptr) {};
	
	void init(node **n, char c) {
		*n = new node(c);
		head = tail = *n;
	}

	void insertAfter(node **n, char c) {
		if(*n == nullptr) {
			init(n, c);
			return;
		}
		node *temp = new node(c, (*n)->next);
		node *temp1 = *n;
		(*n)->next = temp;
		if(temp1 == tail) tail = tail->next;
		*n = (*n)->next;
	}

	void insertAtBeginning(node **n, char c) {
		if(*n == nullptr) {
			init(n, c);
			return;
		}
		node *temp = new node(c, *n);
		*n = head = temp;
	}
	
	void print() {
		node *n = head;
		while(n) {
			cout << n->val;
			n = n->next;
		}
		cout << endl;
	}

	void movetohead(node **n) { *n = head; }

	void movetotail(node **n) { *n = tail; }

#if 1
	~linkedlist() {
		node *n = head, *del;
		while(n) {
			del = n;
			n = n->next;
			delete del;
		}
		
	}
#endif
};

int main() {
	string s;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(1) {
		getline(cin, s);
		if(cin.eof()) break;
		//cout << "input string is " << s << endl;
		linkedlist l;
		node *cur = nullptr;
		bool insertatbegin = false;
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == '[') {
				l.movetohead(&cur);
				insertatbegin = true;
			}
			else if(s[i] == ']') {
				l.movetotail(&cur);
				insertatbegin = false;
			}
			else {
				if(insertatbegin) {
					insertatbegin = false;
					l.insertAtBeginning(&cur, s[i]);
				}
				else {
					l.insertAfter(&cur, s[i]);
				}
			}
		}
		l.print();
	}
	return 0;
}

