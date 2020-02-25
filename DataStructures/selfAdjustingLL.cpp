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
    void changePosition(int pos) {
        if(pos == 1)
            return;
        else if(pos >= 2) {
            Node *prev = head;
            Node *temp = head->getNext();
            while(pos > 2) {
                pos--;
                prev = temp;
                temp = temp->getNext();
                if(temp == NULL)
                    return;
            }
            prev->setNext(temp->getNext());
            temp->setNext(head);
            head = temp;
        }
    }
};

int main() {
    LinkedList l;
    cout<<"Enter data to LL. (0 to stop)"<<endl;
    int choice, data;
    while(true) {
        cout<<"Choice ";
        cin>>choice;
        if(choice == 0)
            break;
        cout<<"Data ";
        cin>>data;
        l.insert(data);
    }
    // index starts from 1, if length < changePosition remains same
    cout<<"Enter updated position"<<endl;
    cin>>data;
    l.changePosition(data);
    l.display();
}