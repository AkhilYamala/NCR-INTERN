#include <iostream>
using namespace std;

class Node {
    int data;
    Node *next;
    public:
    Node(int d) {
        data = d;
        this->next = NULL;
    }
    Node* getNext() {
        return this->next;
    }
    void setNext(Node *n) {
        this->next = n;
    }
    int getData() {
        return this->data;
    }
};

class LinkedList {
    Node *head=NULL;
    public:
    void setHead(Node *h) {
        head = h;
    }
    void insert(int data) {
        if(head == NULL) {
            head = new Node(data);
            return;
        }
        Node *temp = head;
        while(temp->getNext()!=NULL) {
            temp = temp->getNext();
        }
        temp->setNext(new Node(data));
    }

    void display() {
        Node* temp = head;
        while(temp != NULL) {
            cout<<temp->getData()<<" ";
            temp = temp->getNext();
        }
        cout<<endl;
    }
    Node* insertAtPosition(LinkedList l, int position) {
        Node *temp = head;
        while(--position) {
            temp = temp->getNext();
        }
        Node *end = temp->getNext();
        temp->setNext(l.head);
        while(temp->getNext() != NULL)
            temp = temp->getNext();
        temp->setNext(end);
        return head;
    }
};

int main() {
    LinkedList l1, l2;
    int size1, size2;
    cout<<"Enter size of LL1"<<endl;
    cin>>size1;
    cout<<"Enter data"<<endl;
    int data;
    for(int i=0; i<size1; i++) {
        cin>>data;
        l1.insert(data);
    }     
    cout<<"Enter size of LL2"<<endl;
    cin>>size2;
    cout<<"Enter data"<<endl;
    for(int i=0; i<size2; i++) {
        cin>>data;
        l2.insert(data);
    }
    int position;
    cout<<"Position ";
    cin>>position;
    if(position > size1) {
        cout<<"Invalid position"<<endl;
        return 0;
    }
    if(position > 0)
        l1.setHead(l1.insertAtPosition(l2, position));
    else 
        l1.setHead(l2.insertAtPosition(l1, size2));
    l1.display();
}