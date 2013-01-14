//
//  a1p1.cpp
//  HelloWorld
//
//  Created by Mohammad Rauf on 12-01-15.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>
#include <cassert>

using namespace std;

typedef vector<string> Stew;

bool isEmpty(Stew s);
bool isEmpty(Stew s) {
	return s.empty();
}

Stew push(string element, Stew s);
Stew pop(Stew s);
string top(Stew s);
Stew enter(string element, Stew s);
Stew leave(Stew s);
string first(Stew s);
void print(Stew s, char direction);
Stew nuke(Stew s);

Stew push(string element, Stew s) {
    s.push_back(element);
    return s;
}

Stew pop(Stew s) {
    assert(!isEmpty(s));
    s.pop_back();
    return s;
}

string top(Stew s) {
    assert(!isEmpty(s));
    return s.back();
}

Stew enter(string element, Stew s) {
    
    s.push_back(element);
    vector<string>::iterator it;
    it = s.begin();
    s.insert (it, element);
    s.pop_back();
    
    return s;
}

Stew leave(Stew s) {
    assert(!isEmpty(s));
    vector<string>::iterator it;
    it = s.begin();
    s.erase(it);
    
    return s;
}

string first(Stew s) {
    assert(!isEmpty(s));
    return s.front();
}

void print(Stew s, char direction) {
    vector<string>::iterator fwd;
    vector<string>::reverse_iterator rev;
    
    fwd = s.begin();
    rev = s.rbegin();
    
    if (direction == 'f') {
        
        for (; fwd < s.end(); fwd++) {
            cout << *fwd;
            if (fwd < s.end()-1)
                cout << " ";
        }
        cout << endl;
    }
    else if (direction == 'r') {
        
        for (; rev < s.rend(); rev++) {
            cout << *rev;
            if (rev < s.rend()+1)
                cout << " ";
        }
        cout << endl;
    }
    else {
        cerr << "Error, illegal direction: '" << direction << "'" << endl;
        assert(false);
    }
}

Stew nuke(Stew s) {
    vector<string>::iterator it1;
    vector<string>::iterator it2;
    it1 = s.begin();
    it2 = s.end();
    s.erase(it1, it2);
    return s;
}

/*
int main (int argc, char* argv[]) {
	Stew s1;
	s1 = push("alpha", s1);
	s1 = push("beta", s1);
	s1 = push("gamma", s1);
	s1 = enter("delta", s1);
	// This prints "delta alpha beta gamma" on one line
	print (s1, 'f');
	// This prints "gamma beta alpha delta" on one line
	print (s1, 'r');
	s1 = pop (s1);
	s1 = leave (s1);
	// This prints "beta alpha"
	cout << top (s1) << " " << first (s1) << endl;
	// This has no output, but is good form to call when done.
	s1 = nuke (s1);
	// This should now succeed.
	assert(isEmpty (s1));
    
    return 0;
}
 */
