#include<stdio.h>
 #include<stdlib.h>

 struct Node {
     int value;
     struct Node *address;
 };
 struct Node *Starting_node = NULL;
 struct Node *createnode() {
    struct Node *n;
    n=(struct Node *)malloc(sizeof(struct Node));
    return n;
 }
 void insertnode(){
    struct Node *temp, *t1;
    temp=createnode();
    printf("enter the value of node:");
    scanf("%d",&temp->value);
    temp->address=NULL;
    if(Starting_node==NULL){
        Starting_node=temp;
    }
    else{
        t1=Starting_node;
        t1->address=temp;
    }
 }