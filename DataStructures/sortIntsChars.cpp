#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

bool comparator(string a, string b) {
    if(isalpha(a[0]) && isalpha(b[0])) {
        int temp = b.compare(a);
        return (temp>0)?true:false; 
    }
    else if(isdigit(a[0]) && isdigit(b[0])) {
        return stoi(a)<stoi(b);
    }
    else {
        if(isdigit(a[0]) || isalpha(b[0]))
            return false;
        if(isdigit(b[0]) || isalpha(a[0]))
            return true;
        cout<<"Invalid input type"<<endl;
        exit(0);
        return true;
    }
}

int main() {
    int size;
    cout<<"Enter size ";
    cin>>size;
    string arr[size];
    cout<<"Enter data ";
    for(int i=0; i<size; i++)
        cin>>arr[i];
    sort(arr, arr+size, comparator);
    for(int i=0; i<size; i++)
        cout<<arr[i]<<" ";
}