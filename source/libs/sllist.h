/*****************************************
 * sllist.h 
 * Interface of linked list
 * Josias Moukpe
 ****************************************/


#ifndef SLLIST_H
#define SLLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32 //size of data stored in each node

typedef unsigned int uint; //unsigned integer alias
typedef struct node Node; // node alias
typedef struct sllist SLList; // list alias

struct node {
    void* data; // data carried by node
    // struct tnode *parent; // pointer to parent node
    struct node *next; // pointer to next
    // struct tnlist* children; // list of children
};

struct sllist {
    uint size; // size of the list
    struct node* head; // pointer to parent
};


/****************************************
 * METHODS PROTOTYPES
 ***************************************/ 

// NODE METHODS
Node* initNode(char* data);
void destroyNode(Node* to_del); // clear memory of Taxonomic node

//LIST METHODS
SLList* initList(); // initialize a list of TNodes
SLList* parseWords(char* line); //parse the input into SLList
Node* traverse(SLList* List,  uint index);  //return the pointer to the node previous to the node at index 
void destroyList(SLList* to_del); //clear memory of Taxonomic node
void insert(SLList* List, uint index, char* data); //_insert a node with payload data at position index
void pushfront(SLList* List, char* data); //_insert node at the front of the list
void pushback(SLList* List, char* data); //_insert node at the end of the list
void printlist(SLList* List); //print all elements in the list
char* suppress(SLList* List, uint index);  //deletes a node at position index
char* popfront(SLList* List);  //delete node at the back of the list
char* popback(SLList* List);  //delete node at the front of the list
char* getAt(SLList* List,  uint index); //get the data at index 


/****************************************
 * Node Methods
 ***************************************/ 


/* Creates a new node for the tree */
Node* initNode(char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(SIZE*sizeof(char));
    strcpy((char*)(new_node->data), data);
    new_node->next = NULL;
    return new_node;
}

/* Destroy to_del node */ 
void destroyNode(Node* to_del) {
   free(to_del);
}




/*******************************************
 * SLList Methods
 ******************************************/


/* get data at index */
char* getAt(SLList* List,  uint index) {
    return ((char*)(traverse(List, index)->data));
}


/* initialize size to 0 and head to NULL */
SLList* initList(void) {
   SLList* List = (SLList*)malloc(sizeof(SLList));
   List->size = 0;
   List->head = NULL;
   return List;
}

/* clear all nodes in the list then the list itself */
void destroyList(SLList* List) {
    while(List->size != 0) popback(List);
    free(List);
}


/* print all elements in the list */
void printlist(SLList* List) {
    if(List == NULL || List->size == 0 ) {
        printf("empty list\n");
        return;
    }

    Node* tmp = List->head;
    if(List->size != 0) {
        while(tmp != NULL) {
            printf("%s ", (char*)(tmp->data));
            tmp = tmp->next;
        }
    }
}

/* give an index N, traverse() traverse the list until N and return pointer to N-1 */
Node* traverse(SLList* List,  uint index) {
    // case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n"); 
        return NULL;
    }
    // case 2: index is not present
    if(index < 0 || index >= List->size) {
        printf("Invalid index!\n");
        return NULL;
    }

    // case 3: index present
    Node* tmp = List->head; 
    for(uint i = 0; i < index; ++i) tmp = tmp->next; 

    return tmp;
}

/* insert a node with data at index */
void insert(SLList* List,  uint index, char* data) {
    Node* new_node = initNode(data);
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else 
    if(index == 0) { //case 2: front _insertion
        new_node->next = List->head;
        List->head = new_node;
    } 
    else { //case 3: Non empty list with _insert at middle
        Node* prev = traverse(List, index);
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}

/* insert node at the front of the list */
void pushfront(SLList* List, char* data) {
   insert(List, 0, data);
} 


/* insert node at the end of the list */
void pushback(SLList* List, char* data) {
    if(List->size == 0) {
        Node* new_node = initNode(data);
        new_node->next = NULL;
        List->head = new_node;
        ++List->size;
    }
    else 
    if(List->size == 1) { //edge case for single node list
        Node* new_node = initNode(data);
        new_node->next = List->head->next;
        List->head->next = new_node;
        ++List->size;

    } else insert(List, List->size - 1, data);
}  


/* suppress() deletes node at index */ 
char* suppress(SLList* List, uint index) {
    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n");
        return NULL;
    }
    //case 2: invalid index
    if(index < 0 || index >= List->size) {
        printf("invalid index");
        return NULL;
    }

    Node* to_del;
    char* tmp = (char*)malloc(SIZE*sizeof(char));
    
    if(index == 0) { //case 3: deleting head
       to_del = List->head;
       List->head = (List->head)->next;

    } 
    else {  //case 4: deleting any node that is not head
        Node* prev = traverse(List, index - 1);
        to_del = prev->next;
        prev->next = to_del->next;

    }

    strcpy(tmp, (char*)(to_del->data));
    free(to_del);
    --List->size;
    return tmp;
}

/* delete node at the back of the list */
char* popfront(SLList* List) {
    return suppress(List,0);
}  


/* delete node at the front of the list */
char* popback(SLList* List) {
    return suppress(List, List->size - 1);
}  


/* Parses the input line for relevant commands */ 
SLList* parseWords(char* line) {
    SLList* tmp = initList(); //command created with be used by then freed by parseCmd()
    char* word_token;
    char* delim = " \r\n";

    //get the first token 
    word_token = strtok(line, delim);

    //walk through other tokens 
    while(word_token != NULL) {
        //add new words to end of the list
        pushback(tmp, word_token); 
        word_token = strtok(NULL, delim);
    }
    return tmp; //return pointer to list containing commands
} 


#endif //SLLIST_H