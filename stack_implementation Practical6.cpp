#include <iostream>
using namespace std;
#define size 5
int stack[size];
int index=-1;
void PUSH(){
    int number;
    if(index==size-1){cout<<"stack is overflow";}
    else{
        cout<<"enter the number to push in stack:"<<endl;
        cin>>number;
        index++;
        stack[index]=number;
    }

}
void POP(){
    if(index==-1){cout<<"stack is empty"<<endl;}
        else{
            int n=stack[index];
            index--;
            cout<<"stack element is deleted: "<<n<<endl;
        }

}
void print_stack(){
    if (index==-1){cout<<"stack is empty"<<endl;}
    else{cout<<"element of stack is:"<<endl;
        for(int i=index;i>=0;i--){
            cout<<stack[i]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    int choice;
    do{cout<<"1.PUSH"<<endl;
    cout<<"2.pop"<<endl;
    cout<<"3.print stack"<<endl;
    cout<<"4.exit"<<endl;
    cout<<"enter your choice:"<<endl;
    cin>>choice;
    switch(choice){
        case 1:PUSH();break;
        case 2:POP();break;
        case 3:print_stack();break;
        case 4:cout<<"sopped the program..."<<endl;break;
        default:cout<<"invalid choice"<<endl;}
    }while(choice!=4);
}