/*
        This is a template file for Linked List based on C.
*/

#include "listNodeForC.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

bool _data_smaller ( void* num1, void* num2, NodeType type1, NodeType type2 ) {
    if ( type1 != type2 ) return false; // different type data

    // Perform comparison based on type
    switch (type1) {
        case _INT:
            return *_to_int_ptr(num1) < *_to_int_ptr(num2);
        case _CHAR:
            return *_to_char_ptr(num1) < *_to_char_ptr(num2);
        case _FLOAT:
            return *_to_float_ptr(num1) < *_to_float_ptr(num2);
        case _DOUBLE:
            return *_to_double_ptr(num1) < *_to_double_ptr(num2);
        case _LONG:
            return *_to_long_ptr(num1) < *_to_long_ptr(num2);
        case _SHORT:
            return *_to_short_ptr(num1) < *_to_short_ptr(num2);
        case _UNSIGNED_INT:
            return *_to_unsigned_int_ptr(num1) < *_to_unsigned_int_ptr(num2);
        case _UNSIGNED_CHAR:
            return *_to_unsigned_char_ptr(num1) < *_to_unsigned_char_ptr(num2);
        case _UNSIGNED_LONG:
            return *_to_unsigned_long_ptr(num1) < *_to_unsigned_long_ptr(num2);
        case _UNSIGNED_SHORT:
            return *_to_unsigned_short_ptr(num1) < *_to_unsigned_short_ptr(num2);
        default:
            return false; // Unknown type or not comparable
    }
}

typedef struct {
    int _size;
    ListNodePosition header;
    ListNodePosition trailer;
} List;

// Function prototypes

// protected functions

void _list_init ( List* list ); // initialization
int _list_clear ( List* list ); // clear all of nodes
void _list_copyNodes ( List* list, ListNodePosition p, int n ); // Copy n nodes starting from the node p into the list
ListNodePosition _list_merge ( List* list, ListNodePosition p, int n, List* L, ListNodePosition q, int m ); // merge two sorted portions of the list - one starting at *p with n elements and another from list starting at q with m elements
void _list_mergeSort ( List* list, ListNodePosition* p, int n ); // perform merge sort on n nodes starting from *p
void _list_selectionSort ( List* list, ListNodePosition p, int n ); // perform selection sort on n nodes starting from p
void _list_insertionSort ( List* list, ListNodePosition p, int n ); // perform insertion sort on n nodes starting from p

// public functions

// constructor

void list_create( List* list ) { _list_init ( list ); } // create a new list, initializing its members ( default )
void list_copy ( List* list,  List* L ); // create a deep copy of the list L
void list_copyPartial ( List* list, List* L, Rank r, int n ); // copy n elements starting from rank r in list L into a new list
void list_copyFromNode ( List* list, ListNodePosition p, int n ); // create a new list by copying n nodes starting from the node p

// destructor

void list_destroy ( List* list ); // free the memory allocated for the list, including all its nodes

// read-only access interface

Rank list_size ( const List* list ) { return list->_size; } // return the size of the list
bool list_empty ( const List* list ) { return list->_size <= 0; } // check if the list is empty
void* list_get ( const List* list, int r ); // get the data from the node at rank r in the list ( just like overleading [] )
ListNodePosition list_first ( const List* list ) { return list->header->succ; } // get the first node of the list
ListNodePosition list_last ( const List* list ) { return list->trailer->pred; } // get the last node of the list
bool list_node_valid ( const List* list, ListNodePosition p) // check if the node p is a valid node in the list
{ return p && ( list->trailer != p ) && ( list->header != p ); } // the first and last nodes are treated as NULL
int list_disordered ( const List* list ); // check if the list is sorted
ListNodePosition list_find ( const List* list, const void* e, int n, ListNodePosition p); // find element e in n nodes starting from p in the list
ListNodePosition list_find_all ( const List* list, const void* e ) // find an element e in the list
{ return list_find ( list, e, list->_size, list->trailer ); }
ListNodePosition list_search ( const List* list, void* e, int n, ListNodePosition p ); // search for element e in n nodes starting from p in the sorted part of the list
ListNodePosition list_search_all ( const List* list, void* e ) // search for element e in the sorted list
{ return list_search ( list, e, list->_size, list->trailer ); }
ListNodePosition list_selectMax ( List* list, ListNodePosition p, int n ); // find the maximum node in n nodes starting from p
ListNodePosition list_selectMax_all ( const List* list ) { return list_selectMax ( list, list->header->succ, list->_size ); } // find the maximum node in the list

// writable access interface

ListNodePosition list_insert_as_first ( List* list, const void* e, NodeType type ); // Insert an element e as the first node in the list
ListNodePosition list_insert_as_last ( List* list, const void* e, NodeType type ); // insert an element e as the last node in the list
ListNodePosition list_insert_after ( List* list, ListNodePosition p, const void* e, NodeType type ); // insert an element e after the node p
ListNodePosition list_insert_before ( List* list, ListNodePosition p, const void* e, NodeType type ); // insert an element e before the node p
void* list_remove ( List* list, ListNodePosition p ); // remove the node p from its list and return its data
void list_merge ( List* list, List* L ) { _list_merge ( list, list_first(list), list->_size, L, list_first(L), L->_size ); } // merge list L into list
void list_sort ( List* list, ListNodePosition p, int n ); // sort n nodes starting from p
void list_sort_all ( List* list ) { list_sort ( list, list_first(list), list->_size ); } // sort the entire list
int list_deduplicate ( List* list ); // remove duplicate elements from the unsorted list
int list_uniquify ( List* list ); // remove duplicate elements from the sorted list 
void list_reverse ( List* list ); // reverse the order of elements in the list 

// traverse 

void list_traverse ( List* list, void (*visit)(ListNodePosition) ); // traverse the list, applying the function func to each element

void print_node( ListNodePosition node );

// function implementation

void _list_init ( List* list ) {
    // Allocate memory for the header and trailer nodes
    list->header = (ListNodePosition)malloc(sizeof(ListNode));
    list->trailer = (ListNodePosition)malloc(sizeof(ListNode));

    // Check if memory allocation was successful
    if ( list->header == NULL || list->trailer == NULL ) {
        // Handle memory allocation failure if needed
        // For simplicity, I'm returning early, but you might want to do more error handling
        return;
    }

    // Initialize the header node
    list->header->data = NULL; // Since it's a sentinel node, it doesn't hold data
    list->header->pred = NULL; // No predecessor for the header
    list->header->succ = list->trailer; // Successor is the trailer

    // Initialize the trailer node
    list->trailer->data = NULL; // Since it's a sentinel node, it doesn't hold data
    list->trailer->pred = list->header; // Predecessor is the header
    list->trailer->succ = NULL; // No successor for the trailer

    // Set the size of the list to 0
    list->_size = 0;
}

int _list_clear ( List* list ) {
    if ( list == NULL ) return 0;

    int oldSize = list->_size;
    while ( list->_size > 0 ) 
        list_remove ( list, list->header->succ ); // Assuming list_remove handles decrementing _size
    
    return oldSize;
}

void _list_copyNodes ( List* list, ListNodePosition p, int n ) {
    if ( !list || !p ) return;

    _list_init ( list ); // Initialize the list with header and trailer

    while ( n-- > 0 && p != NULL ) {
        list_insert_as_last ( list, p->data, p->type ); // Insert the data of p as the last element of the new list
        p = p->succ; // Move to the next node in the source list
    }
}

// merge of an ordered list: Merge n elements from p in the current list with m elements from q in list L
ListNodePosition _list_merge ( List* list, ListNodePosition p, int n, List* L, ListNodePosition q, int m ) {
    ListNodePosition head = p->pred; // with the help of the front drive (possibly neader), in order to return before...

    while ( 0 < m ) // q has moved out of the interval
        if ( ( 0 < n ) && ( listNode_data_smaller ( p, q ) ) ) // if p is still in the interval and v(p)<=v(q), then
            { if ( q == ( p = p->succ ) ) break; n--; } // p is subsumed into the merged list and replaced with its immediate successor
        else // if p has exceeded the right bound or v(q)<v(p), then
            {   list_insert_before ( list, p, list_remove ( L, ( q = q->succ )->pred ), p->type ); m--; } // transfer q before p

    return head->succ;
}

// list merge sort algorithm: Sort n elements starting at position p
void _list_mergeSort ( List* list, ListNodePosition* p, int n ) { // valid(p) && rank(p) + n <= size

    if ( n < 2 ) return; // if the range to be sorted is small enough, return directly; Otherwise...
    int m = n >> 1; // it's bounded by the midpoint
    ListNodePosition q = *p; 
    for ( int i = 0; i < m; i++ ) q = q->succ; // equalization list

    _list_mergeSort ( list, p, m ); _list_mergeSort ( list, &q, n - m ); // sort the first and second sublists separately

    *p = _list_merge(list, *p, m, list, q, n - m);  // merge the two sorted lists and update p to point to the newly merged starting point

} // Notice: After sorting, p still points to the (new) starting point of the post-merge interval

void _list_selectionSort ( List* list, ListNodePosition p, int n ) { // valid(p) && rank(p) + n <= size
    ListNodePosition head = p->pred; ListNodePosition tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->succ; // the interval to be sorted is (head, tail)
    while ( 1 < n ) { // until there are at least two nodes left, in the interval to be sorted
        ListNodePosition max = list_selectMax ( list, head->succ, n ); // find the maximum
        list_insert_before ( list, tail, list_remove ( list, max ), max->type ); // move it to the end of the unordered interval (as the new first element of the ordered interval)
        tail = tail->pred; n--;
    }
}

// void _list_insertionSort ( List* list, ListNodePosition p, int n ) { // valid(p) && rank(p) + n <= size
//     for ( int r = 0; r < n; r++ ) {
//         list_insert_after ( list, list_search ( list, p->data, r, p ), p->data, p->type ); // search the right place to insert
//         p = p->succ; list_remove ( list, p->pred ); // turn to the next node
//         list_traverse(list, print_node);
//         printf("\n");
//     }
// }

void list_copy ( List* list, List* L ) { _list_copyNodes ( list, list_first(L), L->_size ); }

void list_copyPartial ( List* list, List* L, Rank r, int n ) {
    _list_copyNodes ( list, list_get ( L, r ), n );
}

void list_copyFromNode ( List* list, ListNodePosition p, int n ) {
    _list_copyNodes ( list, p, n );
}

void list_destroy ( List* list ) {
    if ( list == NULL ) return;

    // Clear the list first (assumes _list_clear is implemented)
    _list_clear ( list );

    // Free the header and trailer nodes
    free ( list->header );
    free ( list->trailer );

    // Optionally, set the list's pointers to NULL for safety
    list->header = NULL;
    list->trailer = NULL;
}

void* list_get ( const List* list, int r ) {
    // Check if the rank is within bounds
    if ( r < 0 || r >= list->_size ) return NULL; // Handle the error appropriately, perhaps by returning NULL or an error code

    ListNodePosition p = list->header->succ; // Start from the first node (after the header)

    while ( r-- > 0 && p != list->trailer ) 
        p = p->succ; // Move to the next node

    // Check if the node is valid (not the trailer)
    if ( p != list->trailer ) return p; // Return the data of the node at rank r
    else return NULL; // If we reached the trailer, the rank was out of bounds, handle the error

}

int list_disordered ( const List* list ) {
    if ( list->_size < 2 ) return 0; // A list with fewer than 2 elements is always sorted

    int count = 0;
    ListNodePosition p = list->header->succ;
    while ( p->succ != list->trailer ) {
        // Cast data to the appropriate type before comparison
        int *currentData = (int *)(p->data);
        int *nextData = (int *)(p->succ->data);

        if ( *currentData > *nextData ) count++;

        p = p->succ;
    }
    return count;
}

ListNodePosition list_find ( const List* list, const void* e, int n, ListNodePosition p ) {
    // Ensure that the starting node p is not NULL and within the list
    if (p == NULL || p == list->header) return NULL;

    while ( n-- > 0 && p->pred != list->header ) { // Traverse n predecessors
        p = p->pred; // Move to the predecessor

        // Compare the data of the current node with e
        // Assuming e and p->data are of the same type and can be compared directly
        // You might need a comparison function if they are complex types
        if (e == p->data) return p; // Found the element, return the node
    }

    return NULL; // Element not found, return NULL
}

ListNodePosition list_search ( const List* list, void* e, int n, ListNodePosition p ) {
    while ( 0 <= n-- ) 
        if ( !_data_smaller ( e, ( p = p->pred )->data, p->type, p->type ) ) break;
    return p;
}

ListNodePosition list_selectMax ( List* list, ListNodePosition p, int n ) { // choose the largest of the n elements starting at position p
    ListNodePosition max = p; // the largest is tentatively determined as the first node p
    for ( ListNodePosition cur = p; 1 < n; n-- ) // start from the first node p, the subsequent nodes are compared with max one by one
        if ( !listNode_data_smaller ( ( cur = cur->succ ), max ) ) // if the current element is not less than max
            max = cur; // update the maximum element position record
    return max; 
}

ListNodePosition list_insert_as_first ( List* list, const void* e, NodeType type ) {
    list->_size++;
    return _listNode_insertAsSucc ( list->header, e, type );
}

ListNodePosition list_insert_as_last ( List* list, const void* e, NodeType type ) {
    list->_size++;
    return _listNode_insertAsPred ( list->trailer, e, type );
}

ListNodePosition list_insert_after ( List* list, ListNodePosition p, const void* e, NodeType type) {
    if ( p == NULL || p == list->trailer ) return NULL; // Handle error: p is null or p is the trailer

    list->_size++;
    return _listNode_insertAsSucc ( p, e, type );
}

ListNodePosition list_insert_before ( List* list, ListNodePosition p, const void* e, NodeType type ) {
    if ( p == NULL || p == list->header ) return NULL; // Handle error: p is null or p is the header

    list->_size++;
    return _listNode_insertAsPred ( p, e, type );
}

void* list_remove ( List* list, ListNodePosition p ) {
    if ( list == NULL || p == NULL || p == list->header || p == list->trailer ) return NULL; // Handle error: invalid parameters

    void* e = p->data; // Extract data from the node to be returned

    // Update the links of the predecessor and successor nodes
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;

    free(p); // Free the node

    list->_size--; // Decrement the size of the list

    return e;    // Return the data
}

void list_sort ( List* list, ListNodePosition p, int n ) {
    switch ( rand() % 3 ) {
        // case 1: printf("insert sorting...\n"); _list_insertionSort ( list, p, n ); break;
        case 1: printf("merge sorting...\n"); _list_mergeSort ( list, &p, n ); break;
        case 2: printf("select sorting...\n"); _list_selectionSort ( list, p, n ); break;
        default: printf("merge sorting...\n"); _list_mergeSort ( list, &p, n ); break;
    }
}

int list_deduplicate ( List* list ) {
    if ( list->_size < 2 ) return 0;
    
    int oldSize = list->_size;
    ListNodePosition p = list->header; Rank r = 0;
    while ( list->trailer != ( p = p->succ ) ) {
        ListNodePosition q = list_find ( list, p->data, r, p );
        q ? list_remove ( list, q ) : r++;
    }
    return oldSize - list->_size;
}

int list_uniquify ( List* list ) {
    if ( list->_size < 2 ) return 0;
    int oldSize = list->_size;
    ListNodePosition p = list_first ( list ); ListNodePosition q; // p as the beginning, q is the successor of p
    while ( list->trailer != ( q = p->succ ) )
        if ( p->data != q->data || p->type != q->type ) p = q; // if different, turn into the next interior
        else list_remove ( list, q ); // if not delete q
    return oldSize - list->_size;
}

void list_reverse ( List* list ) {
    if ( list->_size < 2 ) return; // No need to reverse if the list has fewer than 2 elements

    ListNodePosition current = list->header->succ;
    ListNodePosition prev = list->header;
    ListNodePosition next = NULL;

    list->header->succ = list->trailer->pred; // The last node becomes the first
    list->trailer->pred = current; // The first node becomes the last

    while (current != list->trailer) {
        next = current->succ; // Save the next node

        // Reverse the current node's links
        current->succ = prev;
        current->pred = next;

        // Move prev and current forward
        prev = current;
        current = next;
    }

    // After reversal, the new first node's successor should be the trailer
    list->header->succ->pred = list->header;
    list->trailer->pred->succ = list->trailer;
}

void list_traverse ( List* list, void (*visit)(ListNodePosition) ) {
    if ( list == NULL || visit == NULL ) return;

    for ( ListNodePosition p = list->header->succ; p != list->trailer; p = p->succ ) visit(p);
}

// Example function to print list elements (assuming the list stores int data)
void print_node( ListNodePosition node ) {
    if ( node == NULL ) {
        printf("Null node\n"); return;
    }

    if ( node->data == NULL ) {
        printf("Null data"); return;
    }

    switch ( node->type ) {
        case _INT: printf("%d ", *(int*)node->data); break;
        case _CHAR: printf("%c ", *(char*)node->data); break;
        case _FLOAT: printf("%f ", *(float*)node->data); break;
        case _DOUBLE: printf("%lf ", *(double*)node->data); break;
        case _LONG: printf("%ld ", *(long*)node->data); break;
        case _SHORT: printf("%hd ", *(short*)node->data); break;
        case _UNSIGNED_INT: printf("%u ", *(unsigned int*)node->data); break;
        case _UNSIGNED_CHAR: printf("%c ", *(unsigned char*)node->data); break;
        case _UNSIGNED_LONG: printf("%lu ", *(unsigned long*)node->data); break;
        case _UNSIGNED_SHORT: printf("%hu ", *(unsigned short*)node->data); break;
        default:
            printf("Unknown type ");
    }
}

int main() {
    srand(time(NULL)); // Initialize random number generator for sorting

    // Create and initialize lists
    List myList;
    list_create(&myList);
    List copyList;
    list_create(&copyList);

    // Insert elements
    int elements[] = {30, 20, 30, 10, 50, 60, 120, 80, 90, 100};
    for (int i = 0; i < 10; ++i) {
        list_insert_as_last(&myList, &elements[i], _INT);
    }

    // Print the original list
    printf("Original List: ");
    list_traverse(&myList, print_node);
    printf("\n");

    // Check if the list is sorted
    printf("disordered:%d.\n", list_disordered(&myList) );

    // Copy list
    list_copy(&copyList, &myList);
    printf("Copied List: ");
    list_traverse(&copyList, print_node);
    printf("\n");

    // Insertion at different positions
    int newElement = 25;
    list_insert_as_first(&myList, &newElement, _INT);
    list_insert_as_last(&myList, &newElement, _INT);
    printf("After Insertions: ");
    list_traverse(&myList, print_node);
    printf("\n");

    // Removal
    list_remove(&myList, list_first(&myList)); // Removing first element
    list_remove(&myList, list_last(&myList));  // Removing last element
    printf("After Removals: ");
    list_traverse(&myList, print_node);
    printf("\n");

    // Reverse the list
    list_reverse(&myList);
    printf("Reversed List: ");
    list_traverse(&myList, print_node);
    printf("\n");

    // Sort the list
    list_sort_all(&myList);
    printf("Sorted List: ");
    list_traverse(&myList, print_node);
    printf("\n");

    // Destroy the lists
    list_destroy(&myList);
    list_destroy(&copyList);

    return 0;
}