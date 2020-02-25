#include <iostream>
using namespace std;
#define size 5
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

class Queue {
    Node *front=NULL, *rear=NULL;
    int limit=size;
    public:
        void insert(int data) {
            if(limit == 0) {
                cout<<"Stack overflow";
                return;
            }
            limit--;
            if(rear == NULL) {
                rear = new Node(data);
                front = rear;
                return;
            }
            rear->setNext(new Node(data));
            rear = rear->getNext();
            rear->setNext(front);
        }
        void del() {
            if(front == NULL) {
                cout<<"Queue is empty"<<endl;
                return;
            }
            if(front == front->getNext()) {
                cout<<"Deleted "<<front->getData()<<endl;
                front = NULL;
                return;
            }
            int data = front->getData();
            front = front->getNext();
            rear->setNext(front);
            cout<<"Successfully deleted "<<data<<endl;
        }
        void display() {
            if(front == NULL) {
                cout<<"Queue is empty"<<endl;
                return;
            }
            Node *temp = front;
            while(temp != rear) {
                cout<<temp->getData()<<" ";
                temp = temp->getNext();
            }
            cout<<rear->getData()<<endl;
        }
        int getRear() {
            return rear->getData();
        }
};

int main() {
    Queue q;
    bool run = true;
    int choice;
    cout<<"1.Insert"<<endl;
    cout<<"2.Delete"<<endl;
    cout<<"3.Display"<<endl;
    cout<<"4.getRear"<<endl;
    cout<<"5.Exit"<<endl;
    while(run) {
        cout<<"Enter choice ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            int data;
            cout<<"Enter data ";
            cin>>data;
            q.insert(data);
            break;
        case 2:
            q.del();
            break;
        case 3:
            q.display();
            break;
        case 4:
            q.getRear();
            break;
        case 5:
            run = false;
            break;
        }
    }
}