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

class Stack {
    Node *top = NULL;
    public:
    void insert(int data) {
        if(top == NULL) {
            top = new Node(data);
            return;
        }
        Node *temp = new Node(data);
        temp->setNext(top);
        top = temp;
    }

    void display() {
        Node *temp = top;
        while(temp != NULL) {
            cout<<temp->getData()<<" ";
            temp = temp->getNext();
        }
        cout<<endl;
    }

    void del() { 
        if(top) {
            limit++;
            int data = top->getData();
            top = top->getNext();
            cout<<"Deleted "<<data<<" successfully"<<endl;
            return;
        }     
        cout<<"Cannot delete!! Stack is empty"<<endl;
    }

    int getTop() {
        if(top != NULL)
            return top->getData();
        return -1;
    }

};

int main() {
     Stack s;
     int choice;
     bool run = true;
    cout<<"1.Insert";
    cout<<"2.Delete";
    cout<<"3.Display";
    cout<<"4.Exit";
     while(run) {
        cout<<"Enter choice ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            int data;
            cout<<"Enter data ";
            cin>>data;
            s.insert(data);
            break;
        case 2:
            s.del();
            break;
        case 3:
            s.display();
            break;
        case 4:
            run = false;
            break;
        default:
            return 0;
        }
    }
}

// The newly created objects, sholud be assigned to NULL. They will be pointing to some other locations initially
