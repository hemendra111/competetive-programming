/*
******* copied from https://saicheems.wordpress.com/2013/07/10/uva-10567-helping-fill-bates/ *******
**Process
The problem asked for some query text SS to be present in some single large string S. My solution to this problem involved creating a vector of vectors to represent the 52 possible characters. For each character in the string S, we add the index of that character to its respective vector within the vector of vectors. For example, if a char ‘a’ appears within S at index 3, vii[‘a’].push_back(3); Given this setup, we then iterate through the query string SS and for each character we search through the respective character vector for the next highest index (we start at 0). Using this setup, we can grab the first and last index as we iterate through the entire string SS. We know there is “no match” if we cannot find a index greater than the current one within the vector of the current character.
**
*/

#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
 
using namespace std;
 
vector<vector<int> > vvi;
string c; string q;
 
int main() {
 
    vvi.resize(256);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> c; int Q;
    for(int i = 0; i < c.size(); i++) {
        vvi[c[i]].push_back(i);
    }
    //for(int i = 0; i < vvi['c'].size(); i++) cout << vvi['c'][i] << ' ';
    //cout << endl;
    scanf("%d", &Q);
    for(int i = 0; i < Q; i++) {
        cin >> q;
        int ind = -1, a = 0; bool fin = true;
        for(int j = 0; j < q.size(); j++) {
            vector<int>::iterator low = upper_bound(vvi[q[j]].begin(), vvi[q[j]].end(), ind);  // finds iterator "low" where val \
												  greater than ind"
            ind = low - vvi[q[j]].begin();						       // gives "ind" true ind in the char vector
            if(low == vvi[q[j]].end()) fin = false;					       // if iterator is pointing to end interator \
												  , than cur char in SS not found, loop can \
												  be broken here
            ind = vvi[q[j]][ind];							       // gives the next increasing "ind" to find in \
												  the char vector
            if(j == 0) a = ind;								       // gives the initial "ind" to output in the ans
        }
 
        if(fin) {
            printf("Matched %d %d\n", a, ind);
        } else printf("Not matched\n");
    }

    return 0;
}
