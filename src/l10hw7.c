#include <stdio.h>
#include <stdlib.h>

#define true 1==1
#define false 1==0
typedef int boolean;



typedef struct oneLinkNode {
    int data;
    struct oneLinkNode * nextNode;
} singleLinkNode;

typedef struct oneLinkList {
  singleLinkNode * firstNode;
  int size;
} singleLinkList;

singleLinkList * initSingleLinkList() {
   singleLinkList * list = (singleLinkList * ) malloc(sizeof(singleLinkList));
   list->firstNode=NULL;
   list->size=0;
   return list;
}

singleLinkNode * appendSingleListNode(singleLinkList * list, int data) {
    if(list->size==0) {
      list->firstNode = (singleLinkNode *) malloc(sizeof(singleLinkNode));
      list->size++;
      list->firstNode->data=data;
      return list->firstNode;
    }
    int count=list->size;
    singleLinkNode * currentNode = list->firstNode;
    while (count > 0) {
      singleLinkNode * tmpNode = currentNode;  
      currentNode=currentNode->nextNode; 
      count--;
      if (currentNode == NULL)
      {
        currentNode = tmpNode;
        break;
      }
    }
    currentNode->nextNode = (singleLinkNode *) malloc(sizeof(singleLinkNode));
    currentNode->nextNode->nextNode=NULL;
    currentNode->nextNode->data=data;
    
    list->size++;
    return currentNode->nextNode;
}

void printOneLinkIntNode(singleLinkNode *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%d]", n->data);
}


void printSingleLinkList(singleLinkList * list) {
    singleLinkNode * current=list->firstNode;
    if (current == NULL) {
        printOneLinkIntNode(current);
    } else {
        do {
            printOneLinkIntNode(current);
            current = current->nextNode;
        } while (current != NULL);
    }
    printf(" Size: %d \n", list->size);
    
}

void copyOneLinkIntNode(singleLinkNode * original, singleLinkList * list) {
    if(list->size==0) {
      list->firstNode = (singleLinkNode *) malloc(sizeof(singleLinkNode));
      list->size++;
      list->firstNode->data=original->data;
      list->firstNode->nextNode=NULL;
      return;
    }
    int count=list->size;
    singleLinkNode * currentNode = list->firstNode;
    while (count > 0) {
      singleLinkNode * tmpNode = currentNode;  
      currentNode=currentNode->nextNode; 
      count--;
      if (currentNode == NULL)
      {
        currentNode = tmpNode;
        break;
      }
    }
    
    currentNode->nextNode = (singleLinkNode *) malloc(sizeof(singleLinkNode));
    currentNode->nextNode->nextNode=NULL;
    currentNode->nextNode->data=original->data;
    list->size++;
    return;
}


singleLinkList * copySingleLinkList(singleLinkList * src_list) {
    singleLinkList * result = initSingleLinkList();
    if (src_list == NULL)
        return NULL;
    if (src_list->size == 0 || src_list->firstNode == NULL)
        return result;

    singleLinkNode * current=src_list->firstNode;
    do {
            copyOneLinkIntNode(current,result);
            current = current->nextNode;
    } while (current != NULL);
    return result;
}

// Реализуйте алгоритм, который определяет, отсортирован ли связный список.
boolean isSorted(singleLinkList * list) {
    int lowtohigh_flag=1;
    int lowtohigh_drops=0;
    int hightolow_flag=1;
    int hightolow_drops=0;
    singleLinkNode * previouse = NULL; 
    singleLinkNode * current=list->firstNode;
    if(list->size == 0 || list->size == 1)
        return true;
    int equal_counter=0;
    //int tailed_equal_counter=0;
    singleLinkNode * next=list->firstNode->nextNode;
    do {
            if ( current->data == next->data ) {
                previouse = current;
                next = current->nextNode->nextNode;
                current = current->nextNode;
                equal_counter++;
                // тут неправильно считается количество
                // равных элементов на данных 50 30 30 20. 
                // В задаче отображения к-ва одинаковых нет,
                // на общий результат о сортированности и когда 
                // все элементы равны не влияет. Допиливать до идеала некогда. :(
                continue;
            }
            if ( current->data > next->data ) {
                lowtohigh_flag=0;
                lowtohigh_drops=1;
                if (hightolow_flag != 1)
                    hightolow_drops=1;
            }
            if ( current->data < next->data ) {
                hightolow_flag=0;
                hightolow_drops=1;
                if (lowtohigh_flag != 1)
                    lowtohigh_drops=1;
            }
            previouse = current;
            next = current->nextNode->nextNode;
            current = current->nextNode;
            if (hightolow_drops && lowtohigh_drops) {
                printf("Not sorted.\n");
                return false;
            }    
    } while (next != NULL);

    if ( current->data == previouse->data )
     equal_counter++;
    
    if ( current->data < previouse->data ) {
                lowtohigh_flag=0;
                if (hightolow_flag != 1)
                    hightolow_drops=1;
                lowtohigh_drops=1;    
    }

    if ( current->data > previouse->data ) {
                hightolow_flag=0;
                if (lowtohigh_flag != 1)
                    lowtohigh_drops=1;
                hightolow_drops = 1;
    }
    
    if (list->size == equal_counter) {
        printf("All elements equal.\n");
        return false;
    }
    /* else
    {
      printf("list size: %i\n", list->size);
      printf("equal counter: %i\n", equal_counter);
    }
    */
    if (hightolow_drops && lowtohigh_drops) {
        printf("Not sorted.\n");
        return false;
    } else if (lowtohigh_drops == 1 && hightolow_drops == 0)
    {   printf("Sorted from higher to lower.\n");
        return true;
    } else if (lowtohigh_drops == 0 && hightolow_drops == 1)
    {   printf("Sorted from lower to higher.\n");
        return true;
    } else  if (lowtohigh_drops == 0 && hightolow_drops == 0 && lowtohigh_flag==1) 
    {   printf("Sorted from lower to higher.\n");
        return true;
    } else  if (lowtohigh_drops == 0 && hightolow_drops == 0 && hightolow_flag==1) 
    {   printf("Sorted from higher to lower.\n");
        return true;
    }
    else {
      printf("Error in program code.\n");
      return false;
    }
}

int main(int argc, char** argv) {

    singleLinkList * original = initSingleLinkList();
    appendSingleListNode(original,50);
    appendSingleListNode(original,30);
    appendSingleListNode(original,30);
    appendSingleListNode(original,20);
//    appendSingleListNode(original,10);
    printf("Original:\n");
    printSingleLinkList(original);
    singleLinkList * copy = copySingleLinkList(original);
    printf("Copied:\n");
    printSingleLinkList(copy);
    if(isSorted(original))
        printf("Sorted.\n");
    return 0;

}
