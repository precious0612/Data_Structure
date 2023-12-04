/*
    This is a template class named "Vector".
*/
#include <string.h> // For memcpy()
#include <stdlib.h> // For rand()

typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T> class Vector {
    private: Rank _size; int _capacity; T* _elem;   // size of vector, capacity of vector and data 
    protected:
        void copyFrom ( T const* A, Rank low, Rank high ); // copy from A[low,high)
        void expand(); // expand space when not enough
        void shrink(); // shrink when the filling factor is too small
        bool bubble ( Rank low, Rank high ); 
        void bubbleSort ( Rank low, Rank high ); // bubble sorting algorithm
        Rank max ( Rank low, Rank high ); // select the maximum item
        void selectionSort ( Rank low, Rank high ); // selection sorting algorithm
        void merge ( Rank low, Rank high ); // merging algorithm
        void mergeSort ( Rank low, Rank high ); // merging sorting algorithm
        Rank partition ( Rank low, Rank high ); // axis point pole-building algorithm
        void quickSort ( Rank low, Rank high ); // quick sort algorithm
        void heapSort ( Rank low, Rank high );  // heap sort
    public: // interface
        // initial function
        Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) // initialize the vector with capacity is c, size is s and full of v
        { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } // s<=c 
        Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } // initialize vector with the whole array A
        Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } // initialize vector with elements of array A[low,high)
        Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } // initialize vector by copying another vector V
        Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } // initialize vector with a part of another vector V[low, high)
        // destructor
        ~Vector() { delete [] _elem; }  // free the space
        // read-only access interface
        Rank size() const { return _size; } // size of vector
        bool empty() const { return !_size; } // check if vector is empty
        int disordered() const; // check if vector is sorted
        Rank find ( T const& e ) const { return find ( e, 0, _size ); } // find an element in the whole vector (unsorted)
        Rank find ( T const& e, Rank low, Rank high ) const; // // find an element in the vector[low,high) (unsorted)
        Rank search ( T const& e ) const // // search an element in the whole vector (sorted)
        { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
        Rank search ( T const& e, Rank low, Rank high ) const; // // search an element in the vector[low, high) (sorted)
        // writed access interface
        T& operator[] ( Rank r ) const; // overload subscript operator
        Vector<T> & operator= ( Vector<T> const& ); // overload operator "="
        T remove ( Rank r ); // remove element with rank r
        int remove ( Rank low, Rank high ); // remove the elements in [low,high)
        Rank insert ( Rank r, T const& e ); // insert element
        Rank insert ( T const& e ) { return insert ( _size, e ); } // insert the element at last in default
        void sort ( Rank low, Rank high ); // sort the elements in range [low,high)
        void sort() { sort ( 0, _size ); }  // sort the whole vector
        void unsort ( Rank low, Rank high ); // unsort the element in range [low,high) 
        void unsort() { unsort ( 0, _size ); } // unsort the whole vector
        int deduplicate(); // remove the duplicates in unsorted vector
        int uniquify();  // remove the duplicates in sorted vector
        // traverse
        void traverse ( void (* ) ( T& ) ); // traverse the elements ( using the function pointer, read-only or local modification )
        template <typename VST> void traverse ( VST& ); // the travese the whole vector ( using the function objects, whole-urine modifications are possible )
}; // Vector 

template <typename T>
void Vector<T>::copyFrom ( T const* A, Rank low, Rank high ) {
    _elem = new T[_capacity = 2 * ( high - low ) ]; _size = 0; // allocate the space, empty size
    while ( low < high )    // traverse each element in A[low,high)
        _elem[_size++] = A[low++]; // copy to _elem[0, high - low)
}

template <typename T>
void Vector<T>::expand() {  // expend space when not enough
    if ( _size < _capacity ) return; // if not full, no need to expand
    _capacity = max ( _capacity, DEFAULT_CAPACITY );   // not low than minimum capacity
    T* oldElem = _elem; _elem = new T[_capacity <<= 1]; // double the capacity
    for ( int i = 0; i < _size; i++ ) // copy the original content
        _elem[i] = oldElem[i]; // T is the base type, otherwise define a shift operation
    delete [] oldElem; // free the origin
}

template <typename T> void Vector<T>::shrink() { // When loading factor is too small, shrink the space
    if ( _capacity < DEFAULT_CAPACITY << 1 ) return; // prevent shrinking below DEFAULT_CAPACITY
    if ( _size << 2 > _capacity ) return;
    T* oldElem = _elem; _elem = new T[_capacity >>= 1]; 
    for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; // copy the origin
    delete [] oldElem; // free the origin
}

template <typename T> // returns the position of the last element e if failure, low - 1 is returned （ find for unsorted ）
Rank Vector<T>::find ( T const& e, Rank low, Rank high ) const { // assert: 0 <= low < high <= _size 
    while ( ( low < high-- ) && ( e != _elem[high] ) ); // find from the back to the front
    return high; // if high < low, it is failure, otherwise will return the rank
}

template <typename T> T& Vector<T>::operator[] ( Rank r ) const // overload operator subscript
{ return _elem[r]; } // assert: 0 <= r < _size

template <typename T> Vector<T>& Vector<T>:: operator= ( Vector<T> const& V ) { // overload
    if ( _elem ) delete [] _elem; // free the origin
    copyFrom ( V._elem, 0, V.size() ); // copy the whole vector
    return *this; // return a pointer to the current object for chain assignment
}

template <typename T> void permute ( Vector<T>& V ) {
    for ( int i = V.size(); i > 0; i-- ) // from the back to the front
        swap ( V[i - 1], V[rand() % i] ); // change the element bewteen V[0, i) with V[i - 1] randomly
}

template <typename T> // remove section[low, high), 0 <= low <= high <= size
Rank Vector<T>::remove ( Rank low, Rank high ) { // O(n - high)
    if ( low == high ) return 0; // for efficiency, degradation cases are treated separately
    while ( high < _size ) _elem[low++] = _elem[high++]; // elements in [high, size) move high-low forward in sequence
    _size = low; // update size
    shrink(); // shrink if necessary
    return high - low;
}

template <typename T> // Remove the element with rank r in vector, 0 <= r < size
T Vector<T>::remove ( Rank r ) { // O(n - r)
    T e = _elem[r]; // copy deleted element
    remove ( r, r + 1 ); 
    return e;
}

template <typename T>
Rank Vector<T>::insert ( Rank r, T const& e ) {
    expand(); // expand if necessary
    for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i - 1];
    _elem[r] = e; _size++;
    return r;
}

template <typename T> void Vector<T>::unsort ( Rank low, Rank high ) { 
    T* V = _elem + low;
    for ( Rank i = high - low; i > 0; i-- ) // from the back to the front
        swap ( V[i - 1], V[rand() % i] ); // swap the elements from V[0, i) and V[i - 1] randomly
}
