#include<iostream>
using namespace std;
#define size 4

void swap(int arr[][size], int posX, int posY, int &temp) {
    int temp1 = arr[posX][posY];
    arr[posX][posY] = temp;
    temp = temp1;
}

void display(int arr[size][size]) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) 
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }  
}
void rotateAntiClockWise(int arr[][size]) {
    int temp = arr[0][0];
    // top-down
    int col = 0;
    for(int j=1; j<size; j++)
        swap(arr, j, col, temp);
    // left-right
    int row = 3;
    for(int j=1; j<size; j++)
        swap(arr, row, j, temp);
    // bottom-top
    col = 3;
    for(int j=2; j>=0; j--)
        swap(arr, j, col, temp);
    // right-left
    row = 0;
    for(int j=2; j>=0; j--)
        swap(arr, row, j, temp);
}

void clockWiseRotation(int arr[size][size]) {
    int temp = arr[1][1];
    swap(arr, 1, 2, temp);
    swap(arr, 2, 2, temp);
    swap(arr, 2, 1, temp);
    swap(arr, 1, 1, temp);
}

int main() {
    int arr[size][size];
    int count = 1;
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            arr[i][j] = count++;
    display(arr);
    int n;
    while(true) {
        cout<<"Enter choice( 0 for exit) ";
        cin>>n;
        if(n == 0)
            break;
        rotateAntiClockWise(arr);
        clockWiseRotation(arr);
        display(arr);
    }
}
