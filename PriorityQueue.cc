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


struct Qnode {
    string val;
    Qnode * next;
};

struct PQnode {
    int pr;
    vector<Qnode> queue;
    PQnode * next;
};


typedef PQnode* PQ;

void init(PQ& pq);
bool isEmpty(const PQ& pq);
string firstVal(const PQ& pq);
int firstPriority(const PQ& pq);
void enter(PQ& pq, const string& val, int priority);
void leave(PQ& pq);
void print(const PQ& pq);
int nPriority(const PQ& pq);
int nVal(const PQ& pq, int priority);


void init(PQ& pq) {
    pq = new PQnode;
    pq->pr = 0;
    pq->next = NULL;
}

bool isEmpty(const PQ& pq) {
    return pq->next == NULL && (pq->queue).size() == 0;
}

string firstVal(const PQ& pq) {
    assert(!isEmpty(pq));
    return pq->queue[0].val;
}

int firstPriority(const PQ& pq) {
    assert(!isEmpty(pq));
    return pq->pr;
}

void enter(PQ& pq, const string& val, int priority) {
    if (isEmpty(pq)) {
        
        //default priority is set to 1
        pq->pr = priority; 
        
        Qnode *node = new Qnode;
        node->val = val;
        
        (pq->queue).push_back(*node);
        
        //pq->first = node;
        //pq->last = node;
        
    }
    else {
        PQ curr = pq;
        PQ currPrev = NULL;
        while (curr != NULL) {
            
            //pq of that priority exists
            if (curr->pr == priority) {
                Qnode *node = new Qnode;
                node->val = val;
                
                (curr->queue).push_back(*node);
                
                break;
            }
            
            //pq of that priority does not exist
            else if (curr->pr < priority && curr->next) {
                
                //adding pq in the middle
                if (curr->next->pr > priority) {
                    Qnode *node = new Qnode;
                    node->val = val;
                    
                    PQnode *q = new PQnode;
                    init(q);
                    
                    q->pr = priority;
                    (q->queue).push_back(*node);
                    
                    q->next = curr->next;
                    curr->next = q;
                    
                    break;
                }
            }
            else if (curr->next == NULL && curr->pr < priority) {
                //adding pq at the end
                Qnode *node = new Qnode;
                node->val = val;
                
                PQnode *q = new PQnode;
                init(q);
                
                q->pr = priority;
                (q->queue).push_back(*node);
                
                curr->next = q;
                
                break;
            }
            else if (currPrev == NULL && curr->pr > priority) {
                //adding pq at the beginning
                Qnode *node = new Qnode;
                node->val = val;
                
                PQnode *q = new PQnode;
                init(q);
                
                q->pr = priority;
                (q->queue).push_back(*node);
                
                pq = q;
                q->next = curr;
                
                break;
            }
            
            currPrev = curr;
            curr = curr->next;
        }
    }
}

void leave(PQ& pq) {
    assert(!isEmpty(pq));
    
    if (pq->queue.size() == 1) {
        if (pq->next != NULL) {
            PQ temp = pq;
            pq = pq->next;
            delete temp;
        }
        else {
            pq = NULL;
        }
    }
    else {
        for (int i = 0; i < pq->queue.size(); i++) {
            if (i != pq->queue.size()-1) {
                pq->queue[i].val = pq->queue[i+1].val;
                pq->queue.pop_back();
            }
        }
    }
}

void print(const PQ& pq) {
    
    PQ curr = pq;
    while (curr != NULL) {
        for (int i = 0; i < (curr->queue).size(); i++) {   
            if (!curr->next && i == (pq->queue).size()-1) {
                cout << "(" << curr->queue[i].val << " " << curr->pr << ")";
            }
            else {
                cout << "(" << curr->queue[i].val << " " << curr->pr << ") ";
            }
        }
        curr = curr->next;
    }
    cout << endl;
}

int nPriority(const PQ& pq) {
    PQ curr = pq;
    int count = 0;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

int nVal(const PQ& pq, int priority) {
    PQ curr = pq;
    while (true) {
        if (curr->pr == priority) {
            break;
        }
        else if (curr->next == NULL) {
            return 0;
        }
        else {
            curr = curr->next;
        }
    }
    return (int) curr->queue.size();
}
/*
int main (int argc, char* argv[]) {
	PQ pq;
	init(pq);
	enter(pq, "a", 3);
	enter(pq, "b", 1);
	enter(pq, "c", 3);
	enter(pq, "d", 4);
	enter(pq, "e", 3);
	// This prints "(b 1) (a 3) (c 3) (e 3) (d 4)"
	print(pq);
	// This prints " (b 1)"
	cout << "(" << firstVal(pq) << " " << firstPriority(pq)
    << ")" << endl;
	// This prints "3 1 3"
	cout << nPriority(pq) << " " << nVal(pq, 1) << " " << nVal(pq, 3)
    << endl;
	// This prints "2 0 2"
	leave(pq); leave(pq);
	cout << nPriority(pq) << " " << nVal(pq, 1) << " " << nVal(pq, 3)
    << endl;
}
 */
