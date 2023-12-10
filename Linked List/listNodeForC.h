#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../convert_type.h"

typedef enum {
    _INT,
    _CHAR,
    _FLOAT,
    _DOUBLE,
    _LONG,
    _SHORT,
    _UNSIGNED_INT,
    _UNSIGNED_CHAR,
    _UNSIGNED_LONG,
    _UNSIGNED_SHORT,
} NodeType;

typedef int Rank;

// Forward declaration of the struct
typedef struct ListNode ListNode;

// Define a type for a pointer to a ListNode
typedef ListNode* ListNodePosition;

// Definition of the ListNode struct
struct ListNode {
    void* data;             // void pointer to store any data type
    NodeType type;       // Store the data type
    ListNodePosition pred;  // Predecessor
    ListNodePosition succ;  // Successor
};

// Function prototypes

ListNode* _listNode_createNode ( void* data, NodeType type, ListNodePosition pred, ListNodePosition succ );
ListNodePosition _listNode_insertAsPred ( ListNodePosition node, const void* e, NodeType type );
ListNodePosition _listNode_insertAsSucc ( ListNodePosition node, const void* e, NodeType type );

bool listNode_data_equals ( ListNodePosition p1, ListNodePosition p2 );
bool listNode_data_smaller ( ListNodePosition p1, ListNodePosition p2 );

// Function implementations
ListNodePosition _listNode_createNode ( void* data, NodeType type, ListNodePosition pred, ListNodePosition succ ) {
    ListNodePosition newNode = (ListNode*) malloc (sizeof(ListNode));
    if ( newNode != NULL ) {
        newNode->data = data;
        newNode->type = type; // Assign the NodeType
        newNode->pred = pred;
        newNode->succ = succ;
    }
    return newNode;
}

ListNodePosition _listNode_insertAsPred ( ListNodePosition node, const void* e, NodeType type ) {
    ListNode* newNode = _listNode_createNode ( e, type, node->pred, node );
    if ( node->pred )
        node->pred->succ = newNode;

    node->pred = newNode;
    return newNode;
}

ListNodePosition _listNode_insertAsSucc ( ListNodePosition node, const void* e, NodeType type ) {
    ListNode* newNode = _listNode_createNode ( e, type, node, node->succ );
    if ( node->succ )
        node->succ->pred = newNode;

    node->succ = newNode;
    return newNode;
}

bool listNode_data_equals ( ListNodePosition p1, ListNodePosition p2 ) {
    if ( p1->type != p2->type ) return false; // different type data
    return memcmp ( p1->data, p2->data, sizeof(p1->data) ) == 0 ? true : false;
}

bool listNode_data_smaller ( ListNodePosition p1, ListNodePosition p2 ) {
    if ( p1->type != p2->type ) return false; // different type data

    // Perform comparison based on type
    switch (p1->type) {
        case _INT:
            return *_to_int_ptr(p1->data) < *_to_int_ptr(p2->data);
        case _CHAR:
            return *_to_char_ptr(p1->data) < *_to_char_ptr(p2->data);
        case _FLOAT:
            return *_to_float_ptr(p1->data) < *_to_float_ptr(p2->data);
        case _DOUBLE:
            return *_to_double_ptr(p1->data) < *_to_double_ptr(p2->data);
        case _LONG:
            return *_to_long_ptr(p1->data) < *_to_long_ptr(p2->data);
        case _SHORT:
            return *_to_short_ptr(p1->data) < *_to_short_ptr(p2->data);
        case _UNSIGNED_INT:
            return *_to_unsigned_int_ptr(p1->data) < *_to_unsigned_int_ptr(p2->data);
        case _UNSIGNED_CHAR:
            return *_to_unsigned_char_ptr(p1->data) < *_to_unsigned_char_ptr(p2->data);
        case _UNSIGNED_LONG:
            return *_to_unsigned_long_ptr(p1->data) < *_to_unsigned_long_ptr(p2->data);
        case _UNSIGNED_SHORT:
            return *_to_unsigned_short_ptr(p1->data) < *_to_unsigned_short_ptr(p2->data);
        default:
            return false; // Unknown type or not comparable
    }
}
