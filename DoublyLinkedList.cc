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

struct Node {
    string val;
    Node* next;
    Node* prev;
};

struct Stew {
    Node* first;
    Node* last;
};


Stew push(string element, Stew s);
Stew pop(Stew s);
string top(Stew s);
Stew enter(string element, Stew s);
Stew leave(Stew s);
string first(Stew s);
void print(Stew s, char direction);
Stew nuke(Stew s);
Stew reverse(Stew s);

Stew initStew();
Stew initStew() { 
	Stew s; 
	s.first = s.last = NULL; 
    return s; 
}

bool isEmpty(Stew s);
bool isEmpty(Stew s) { 
	return s.first == NULL; 
}

Stew nuke(Stew s) {
    
    if (s.first->next == NULL && s.first->prev == NULL) {
        return s;
    }
    else {
        s.first = s.last = NULL;
    }
    return s;
}


void print(Stew s, char direction) {
    
    if (direction == 'f') {
        Node *current = new Node;
        current = s.first;
        while (current != NULL) {
            cout << current->val;
            if (current->next != NULL)
                cout << " ";
            current = current->next;
        }
        cout << endl;
    }
    else if (direction == 'r') {
        Node *current = new Node;
        current = s.last;
        while (current != NULL) {
            cout << current->val;
            if (current->prev != NULL)
                cout << " ";
            current = current->prev;
        }
        cout << endl;
    }
    else {
        cerr << "Error, illegal direction: '" << direction << "'" << endl;
        assert(false);
    }
    
    
}

string first(Stew s) {
    assert(!isEmpty(s));
    
    return s.last->val;
}


Stew push(string element, Stew s) {
    
    Node *node = new Node;
    
    if (s.first != NULL)
        s.first->prev = node;
    
    node->val = element;
    node->prev = NULL;
    node->next = s.first;
    
    if (isEmpty(s)) {
        s.first = s.last = node;
    }
    else {
        s.first = node;
    }
    
    return s;
}

Stew enter(string element, Stew s) {
    
    Node *node = new Node;
    
    if (s.last != NULL)
        s.last->next = node;
    
    node->val = element;
    node->next = NULL;
    node->prev = s.last;
    
    if (isEmpty(s)) {
        s.last = s.first = node;
    }
    else {
        s.last = node;
    }
    
    return s;
}


Stew reverse(Stew s) {
    Node *current = new Node;
    Stew t = initStew();
    
    current = s.last;
    
    while (current != NULL) {
        
        if (current->prev != NULL)
            enter(current->val, t);
        
        current = current->prev;
    }
    return t;
}

Stew leave(Stew s) {
    
    assert(!isEmpty(s));
    
    if (s.last->prev == NULL && s.last->next == NULL) {
        s.last = s.first = NULL;
        return s;
    }
    else {
        s.last = s.last->prev;
        s.last -> next = NULL;
    }
    return s;
}

string top(Stew s) {
    
    assert(!isEmpty(s));
    
    return s.first->val;
}

Stew pop(Stew s) {
    
    assert(!isEmpty(s));
    
    if (s.first->next == NULL && s.first->prev == NULL) {
        s.first = s.last = NULL;
        return s;
    }
    else {
        s.first = s.first->next;
        s.first -> prev = NULL;
    }
    
    
    return s;
}
/*
int main (int argc, char* argv[]) {
	Stew s1 = initStew();
	s1 = push("alpha", s1);
	s1 = push("beta", s1);
	s1 = push("gamma", s1);
	s1 = enter("delta", s1);
    s1 = reverse(s1);
    print(s1, 'f');
	
 
    // This prints "gamma beta alpha delta"
	print (s1, 'f');
	// This prints "delta alpha beta gamma"
	print (s1, 'r');
	s1 = reverse(s1);
	// This prints "delta alpha beta gamma"
	print(s1, 'f');
	s1 = pop (s1);
	s1 = leave (s1);
	// This prints "alpha beta"
    
        cout << top (s1) << " " << first (s1) << endl;
    
	// This has no output, but is good form to call when done.
	s1 = nuke (s1);
	// This should now succeed.
	//assert(isEmpty (s1));
     
}
*/



/*

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
