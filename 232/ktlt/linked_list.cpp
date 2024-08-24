#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};



node *createLinkedList(int n){
    node* head = NULL;
    for(int i = 0; i < n - 1; i++){
        node* newNode = new node();
        cin>> newNode->data;
        if(head == NULL){
            head = newNode;
        }else{
            newNode->next = head->next;
            head = newNode;
        }
    }
    return head;
}; 

bool isEqual(node *head1, node *head2)
{
   node* ptr1 = head1;
   node* ptr2 = head2;
   while(ptr1 != NULL && ptr2 != NULL){
       if(ptr1->data != ptr2->data){
           return false;
       }
       ptr1 = ptr1->next;
       ptr2 = ptr2->next;
   }
   return (ptr1 == NULL && ptr2 == NULL);
}

int countNode(node* head)
{
  int count = 0;
  node* ptr = head;
  while(ptr != NULL){
      count++;
      ptr = ptr->next;
  }
  return count;
}


int main()
{
  int n = 0;
  cin>> n;
  node *head1 = createLinkedList(n);
  int m = 0;
  cin>> m;
  node *head2 = createLinkedList(m);
  cout << isEqual(head1, head2) << endl;
  return 0;
}
