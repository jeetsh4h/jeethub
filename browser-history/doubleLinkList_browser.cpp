#include <iostream>
using namespace std;

class node {
public:
    string str;
    node *next;
    node *prev;

    node (string data) {
        str = data;
        next = NULL;
        prev = NULL;
    }
    node () {
        str = "";
        next = NULL;
        prev = NULL;
    }
};

class dblList {
    node *head;
    node *tail;
    node *current;

public:
    dblList() { 
        NULL; NULL; NULL; 
    }
    node *get_head() { return head; }
    node *get_tail() { return tail; }
    node *get_curr() { return current; }

    void init_list(int n);
    void appendNode(string data);
    void printList();
    void forward();
    void backward();
};

void dblList::appendNode(string data) {
    node *newNode = new node(data);
    node *now = head;
    if (head == NULL) { 
        head = newNode;
        tail = newNode;
        current = tail;
        return; 
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    current = tail;
}

void dblList::init_list(int n) {
    if (n == 0) {
        head = NULL;
        tail = NULL;
        current = NULL;
        return;
    }

    string data;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        cout << "Enter data: ";
        getline(cin, data);
        appendNode(data);
    }
    current = tail;
    return;
}

void dblList::printList() {
    if (head == NULL) { cout << "\nNull List\n"; return; }
    node *now = head;
    while (now != NULL) {
        cout << now->str << endl;
        now = now->next;
    }
}

void dblList::backward() {
    if (current->prev == NULL) { 
        cout << "No prior history\n" << "Current URL: " << current->str << endl;
        return;
    }
    current = current->prev;
    cout << "Current URL: " << current->str << endl;
    return;
}

void dblList::forward() {
    if (current->next == NULL) { 
        cout << "No forward history; Current URL: " << current->str << endl;
        return;
    }
    current = current->next;
    cout << "Current URL: " << current->str << endl;
    return;
}


int main() {
    dblList browserHist;

    browserHist.init_list(0);
    cout << "Initialised List -->";
    browserHist.printList();
    cout << endl;

    int num;
    cout << "Reinitialising list with value: ";
    cin >> num;
    cout << endl;
    browserHist.init_list(num);
    cout << "Reinitialised List -->\n";
    browserHist.printList();
    cout << endl;

    browserHist.forward();
    browserHist.backward();
    browserHist.backward();
    browserHist.backward();
    browserHist.forward();
}