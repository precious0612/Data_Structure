/*
    The main file for Linked List
*/

#include "listNode.h"

template <typename T> class List { // List template class

private:
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; // size, header and trailer of list

protected:
    void init(); // initialization
    int clear(); // clear all of nodes
    void copyNodes ( ListNodePosi(T), int ); // copy the nth item from position p
    void merge ( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int ); // merge
    void mergeSort ( ListNodePosi(T)&, int ); // merge and sort n consecutive nodes from p
    void selectionSort ( ListNodePosi(T), int ); // selection sort n consecutive nodes from p
    void insertionSort ( ListNodePosi(T), int ); // Insert sort n consecutive nodes from p

public:
// Constructor
    List() { init(); } // default
    List ( List<T> const& L ); // copy the whole list L
    List ( List<T> const& L, Rank r, int n ); // copy n nodes of List L from r
    List ( ListNodePosi(T) p, int n ); // copy n nodes from position p
// Destructor
    ~List(); // release all of nodes ( include header and trailer )
// Read-Only Access Interface
    Rank size() const { return _size; } // size of List
    bool empty() const { return _size <= 0; } // check if empty
    T& operator[] ( Rank r ) const; // overleading, support for calling by rank ( ineffective )
    ListNodePosi(T) first() const { return header->succ; } // the position of first node
    ListNodePosi(T) last() const { return trailer->pred; } // the position of last node
    bool valid ( ListNodePosi(T) p ) // check if position p is valid
    { return p && ( trailer != p ) && ( header != p ); } // set header and trailer as NULL
    int disordered() const; // check if list is sorted
    ListNodePosi(T) find ( T const& e ) const // find from unsorted list
    { return find ( e, _size, trailer ); }
    ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const; // find from interior ( unsorted list )
    ListNodePosi(T) search ( T const& e ) const // search from sorted list
    { return search ( e, _size, trailer ); }
    ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; // search from interior ( sorted list )
    ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ); // select the maximum node from p during its n - 1 successors
    ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } // the maximum among all nodes
// Writable Access Interface
    ListNodePosi(T) insertAsFirst ( T const& e ); // insert e as first node
    ListNodePosi(T) insertAsLast ( T const& e ); // insert e as last node
    ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); // insert e as the successor of p
    ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); // insert e as the precursor of p
    T remove ( ListNodePosi(T) p ); // delete node in valid position p, and return the node
    void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } // merge the whole list
    void sort ( ListNodePosi(T) p, int n ); // sort the interior of list
    void sort() { sort ( first(), _size ); } // sort the whole list
    int deduplicate(); // remove the duplicates ( unsorted )
    int uniquify(); // remove the duplicates ( sorted )
    void reverse(); // reserve
// Traversal 
    void traverse ( void (* ) ( T& ) ); // traverse, in order to implement visit operations in sequence (function Pointers, read-only or local modifications)
    template <typename VST> // operator
    void traverse ( VST& ); // traversal, in order to implement the visit operation (function object, can be modified globally)
}; // List