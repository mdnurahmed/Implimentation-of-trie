#include<bits/stdc++.h>
using namespace std;

struct node {
    //endmark true means a word ends in this node 
    //overstepped counts how many words go through this node 
    int endmark, overstepped;
    unordered_map<char, node*> next;
    node() {
        overstepped = 0;
        next.clear();
    }
} * root;
void insert(string& str) {
    node* curr = root;
    curr->overstepped++;
    for (int i = 0; i < str.size(); i++) {
        if (curr->next.find(str[i]) == curr->next.end()) {
            curr->next[str[i]] = new node();
        }
        curr = curr->next[str[i]];
        curr->overstepped++;
    }
    curr->endmark++;
}
bool search(string& str) {
    node* curr = root;
    for (int i = 0; i < str.size(); i++) {
        if (curr->next.find(str[i]) == curr->next.end()) return false;
        curr = curr->next[str[i]];
    }
    return curr->endmark;
}

//destroying the trie tree using dfs
void destroy(node* cur) {  
    for (auto it = cur->next.begin(); it != cur->next.end(); it++)
        destroy(it->second);
    delete (cur);
}

void del(string& str) {
    vector<node*> will_be_deleted;
    node* curr = root;
    curr->overstepped--;
    for (int i = 0; i < str.size(); i++) {
        curr = curr->next[str[i]];
        curr->overstepped--;
        if (curr->overstepped == 0)
            will_be_deleted.push_back(curr);
    }
    //endmark will decrease by 1 
    curr->endmark--; 
    for (int i = 0; i < will_be_deleted.size(); i++)
        delete (will_be_deleted[i]);
    will_be_deleted.clear();
}

int main() {
    puts("ENTER NUM OF OPERATION");
    root = new node();
    string str;
    int no_op, type;  //no of operations
    cin >> no_op;
    puts("1 <word> to insert \n2 <word> to query if it exists \n3 <word> to delete a word\n");

    for (int i = 1; i <= no_op; i++) {
        cin >> type >> str;
        if (type == 1) {
            insert(str);
            cout << "INSERTED " << str << endl;
        } else if (type == 2) {
            if (search(str))
                cout << "FOUND => " << str << endl;
            else
                cout << "NOT FOUND => " << str << endl;
        } else {
            if (search(str)) {  //thakle delete korbo
                del(str);
                cout << "DELETED " << str << endl;
            } else {
                cout << str << " DOESNT EXIST" << endl;
            }
        }
    }
    destroy(root);  //destroyed the trie 
    return 0;
}