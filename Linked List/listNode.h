
/*
    A header file for Linked List ( ListNode )
*/

typedef int Rank;

#define ListNodePosi(T) ListNode<T>*    // the position of node

template <tyename T> struct ListNode {  // a template class for listNode ( achievement based on Bidirectional linked list )
// Member
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ; // data, precursor, successor
// Constructor
    ListNode() {}; // for header and trailer
    ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
        : data ( e ), pred ( p ), succ ( s ) {} // default constructor
// API
    ListNodePosi(T) insertAsPred ( T const& e );    // insert a new node close to the current node
    ListNodePosi(T) insertAsSucc ( T const& e );    // insert a new node follow the current node
};

