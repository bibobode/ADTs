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

class Node {
public:
	int uw_id;
	string info;
	Node* left;
	Node* right;
	Node(int uw_id, const string& info);
};

class BST {
public:
	BST();
	~BST();
    string lookup(Node *&main, int uw_id);
    void insert(Node*& main, int uw_id, string info);
    void remove(Node* &main, int uw_id);
    void print(Node * &main);
	void insert(int uw_id, const string& info);
	string lookup(int uw_id) ;
	void remove(int uw_id);
	void print();
    Node* findLargestLeaf (Node *&main);
    Node* findSmallestLeaf (Node *&main);
    Node* lookupParentLocation (Node *&main, int uw_id);
    Node* lookupLocation(Node *&main, int uw_id);
	Node* root;
};

Node::Node(int uw_id, const string& info) {
    this->uw_id = uw_id;
    this->info = info;
}

BST::BST() {
    root = NULL;
}

BST::~BST() {
    delete root;
}

void BST::insert(int uw_id, const string& info) {
    insert(root, uw_id, info);
}
string BST::lookup(int uw_id)  {
    return lookup(root, uw_id);
}
void BST::remove(int uw_id) {
    remove(root, uw_id);
}
void BST::print() {
    print(root);
}

Node* BST::findLargestLeaf (Node *&main) {
    if (main->right == NULL) {
        return main;
    }
    else {
        return findLargestLeaf(main->right);
    }
}


Node* BST::findSmallestLeaf (Node *&main) {
    if (main->left == NULL) {
        return main;
    }
    else {
        return findSmallestLeaf(main->left);
    }
}

Node * BST::lookupParentLocation(Node *&main, int uw_id) {
    if (main == NULL) {
        return NULL;
    }
    else if (main->uw_id == uw_id) {
        return NULL;
    }
    else if (uw_id > main->uw_id) {
        if (main->right) {
            if (main->right->uw_id == uw_id) {
                return main;
            }
        }
        if (main->left) {
            if (main->left->uw_id == uw_id) {
                return main;
            }
        }
        return lookupParentLocation(main->right, uw_id);
    }
    else {
        if (main->right) {
            if (main->right->uw_id == uw_id) {
                return main;
            }
        }
        if (main->left) {
            if (main->left->uw_id == uw_id) {
                return main;
            }
        }
        return lookupParentLocation(main->left, uw_id);
    }
}

Node * BST::lookupLocation(Node *&main, int uw_id) {
    if (main == NULL) {
        return NULL;
    }
    else if (main->uw_id == uw_id) {
        return main;
    }
    else if (uw_id > main->uw_id) {
        return lookupLocation(main->right, uw_id);
    }
    else {
        return lookupLocation(main->left, uw_id);
    }
}

string BST::lookup(Node *&main, int uw_id) {
    if (main == NULL) {
        return "";
    }
    else if (main->uw_id == uw_id) {
        return main->info;
    }
    else if (uw_id > main->uw_id) {
        return lookup(main->right, uw_id);
    }
    else {
        return lookup(main->left, uw_id);
    }
}

void BST::insert(Node *& main, int uw_id, string info) {
    if (main == NULL) {
        main = new Node (uw_id, info);
        main->uw_id = uw_id;
        main->info = info;
        main->left = NULL;
        main->right = NULL;
    }
    else if (main->uw_id == uw_id) {
        cout << "Duplicate uw_id " << uw_id << endl;
    }
    else if (uw_id > main->uw_id) {
        insert(main->right, uw_id, info);
    }
    else if (uw_id < main->uw_id) {
        insert(main->left, uw_id, info);
    }
}


void BST::remove(Node* &main, int uw_id) {
    Node * nodeToBeRemoved = lookupLocation(main, uw_id);
    if (nodeToBeRemoved == NULL) {
        //not found
        return;
    }
    else {
        if (nodeToBeRemoved->right != NULL && nodeToBeRemoved->left != NULL) {
            //has two children
            Node * replacingNode = findSmallestLeaf(nodeToBeRemoved->right);
            int temp = replacingNode->uw_id;
            string temp2 = replacingNode->info;
            
            remove (main, replacingNode->uw_id);
            
            nodeToBeRemoved->uw_id = temp;
            nodeToBeRemoved->info = temp2;
            
        }
        else if (nodeToBeRemoved->right != NULL && nodeToBeRemoved->left == NULL) {
            //has one child to the right
            
            Node *parent = lookupParentLocation(main, nodeToBeRemoved->uw_id);
            if (parent) {
                if (nodeToBeRemoved->uw_id < parent->uw_id) {
                    parent->left = nodeToBeRemoved->right;
                }
                else if (nodeToBeRemoved->uw_id > parent->uw_id) {
                    parent->right = nodeToBeRemoved->right;
                }
            }
            else {
                //deleting main node with one child to the right
                main = nodeToBeRemoved->left;
                //delete nodeToBeRemoved;
            }
            
        }
        else if (nodeToBeRemoved->right == NULL && nodeToBeRemoved->left != NULL) {
            //has one child to the left
            
            Node *parent = lookupParentLocation(main, nodeToBeRemoved->uw_id);
            if (parent) {
                if (nodeToBeRemoved->uw_id < parent->uw_id) {
                    parent->left = nodeToBeRemoved->left;
                }
                else if (nodeToBeRemoved->uw_id > parent->uw_id) {
                    parent->right = nodeToBeRemoved->left;
                }
            } 
            else {
                //deleting main node with one child to the left
                main = nodeToBeRemoved->left;
                //delete nodeToBeRemoved;
            }
            
        }
        else if (nodeToBeRemoved->right == NULL && nodeToBeRemoved->left == NULL) {
            //has no children
            Node * parent = lookupParentLocation(main, nodeToBeRemoved->uw_id);
            if (parent) {
                if (nodeToBeRemoved->uw_id < parent->uw_id) {
                    parent->left = NULL;
                }
                else if (nodeToBeRemoved->uw_id > parent->uw_id) {
                    parent->right = NULL;
                }
            }
            else {
                //deleting main node with no children
                main = NULL;
            }
            //delete nodeToBeRemoved;
        }
    }
    
}

void BST::print(Node * &main) {
    if (main != NULL) {
        print(main->left);
        cout << main->uw_id << " " << main->info << endl;
        print(main->right);
    }
}





