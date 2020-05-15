#include "../src/ralloc.hpp"
#include "../src/pptr.hpp"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
struct Node {
  pptr<Node> next;
  int data;
};

/**
 * Maintain a linked list and fill it with 1000 new random numbers every time
 * we run. Repeat until assert. If it doesn't assert, then walk the whole list
 * and find the biggest positive number.
 */
int main() {
  srand(time(0));
  int restart = RP_init("lltest", MIN_SB_REGION_SIZE * 2);
  printf("%d", sizeof(Node)*1000);
  Node *list_head;
  if (!restart){
    printf("first time\n");
    list_head = (Node*)RP_malloc(sizeof(Node));
    list_head->next = NULL;
    list_head->data = 0;
    RP_set_root(list_head, 0);
  } else {
    printf("restart\n");
    list_head = RP_get_root<Node>(0);
    RP_recover();
  }
  for(int i = 0; i < 1000; ++i){
    Node *newnode = (Node*)RP_malloc(sizeof(Node));
    newnode->next = list_head->next;
    newnode->data = rand();
    list_head->next = newnode;
  }

  int biggest = 0;
  for(Node *t = list_head; t != NULL; t = t->next){
    if (t->data > biggest)
      biggest = t->data;
  }
  printf("biggest we found is %d\n", biggest);
  RP_close();
}

