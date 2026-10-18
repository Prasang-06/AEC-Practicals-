#include <iostream>
using namespace std;
#define size 5
int queue[size],rear=-1,front=0;
int index=-1;
void enqueue(){
    int element;
    if(rear==size-1){
        cout<<"queue is overflow";
    }else{
        cout<<"enter any  element for queue:";
        cin>>element;
        rear++;
        queue[rear]=element;
    }
}
void dequeue(){
    if(front>rear){
        cout<<"queue is empty"<<endl;
    }
    else{
        cout<<"Element is deleted"<<queue[front]<<endl;
        front++;
    }
}

void print_queue(){
    if(front>rear){
    cout<<"queue is empty"<<endl;
}
else{
    cout<<"elements of queue is:";
    for (int i=front;i<=rear;i++){
        cout<<queue[i]<<endl;
    }
}

}

int main(){
    int choice;
    do{
        cout<<"1.ADD DATA"<<endl;
        cout<<"2.DELETE DATA"<<endl;
        cout<<"3.PRINT QUEUE"<<endl;
        cout<<"4.enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1: enqueue();break;
            case 2: dequeue();break;
            case 3: print_queue();break;
            case 4: cout<<"program is stopped..."<<endl;
            break;

            default:cout<<"invalid choice"<<endl;
        }

    }while(choice!=4);
}