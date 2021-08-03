#include <stdio.h>
#include <stdlib.h>

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


int main(int argc, char** argv) {
    singleLinkList * original = initSingleLinkList();
    appendSingleListNode(original,10);
    appendSingleListNode(original,20);
    appendSingleListNode(original,30);
    printf("Original:\n");
    printSingleLinkList(original);
    singleLinkList * copy = copySingleLinkList(original);
    printf("Copied:\n");
    printSingleLinkList(copy);
    return 0;

}
