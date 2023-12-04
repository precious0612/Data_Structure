/*
    This template file is using the C to mimic the template class in C++ 
    in which some functions do not be defined.
*/

#include <stdio.h>
#include <string.h> // For memcpy()
#include <stdlib.h> // For free() rand()
// #include <stdbool.h>

#define DEFAULT_CAPACITY 3
#define True 1
#define False 0

typedef int Rank;
typedef int Bool;

typedef struct {
    Rank _size;     // the size of vector
    int _capacity;  // the capacity of vector
    void* _elem;    // the data of vector
    size_t _elementSize; //Size of each element in bytes
} Vector;

// _vector_* is the proteceted function

void _vector_shift_element ( Vector* vec, int fromIndex, int toIndex ); // shift one element locally
void _vector_copyFrom ( Vector* vec, const void* A, Rank low, Rank high, size_t elementSize ); // copy data from A[low, high)
void _vector_expand ( Vector* vec );  // expand space when not enough
void _vector_shrink ( Vector* vec );  // shrink when the filling factor is too small
Bool _vector_bubble ( Vector* vec, Rank low, Rank high );    
void _vector_bubbleSort ( Vector* vec, Rank low, Rank high );    // bubble sort algorithm
Rank _vector_max ( Vector* vec, Rank low, Rank high );   // select the maximum item
void _vector_selectionSort ( Vector* vec, Rank low, Rank high ); // selection sorting algorithm
void _vector_merge ( Vector* vec, Rank low, Rank high ); // merging algorithm
void _vector_mergeSort ( Vector* vec, Rank low, Rank high ); // merging sorting algorithm
Rank _vector_partition ( Vector* vec, Rank low, Rank high ); // axis point pole-building algorithm
void _vector_quickSort ( Vector* vec, Rank low, Rank high ); // quick sort algorithm
void _vector_heapSort ( Vector* vec, Rank low, Rank high );  // heap sort

// vector_* is the public function

// Initialization

void vector_init ( Vector* vec, int c, int s, size_t elementSize, void* v ); // initialize vector with full of v
void vector_initFromArray ( Vector* vec, const void* A, Rank n, size_t elementSize ); // initialize vector with first n element of array A
void vector_initFromArrayRange ( Vector* vec, const void* A, Rank low, Rank high, size_t elementSize ); // initialize vector with elements of array A[low,high)
void vector_initFromVector ( Vector* vec, const Vector* V );   // initialize vector by copying another vector V
void vector_initFromVectorRange ( Vector* vec, const Vector* V, Rank low, Rank high);  // initialize vector with a part of another vector V[low, high)

// Print

void vector_print ( const Vector* vec ); 

// Destructor

void vector_destory ( Vector* vec ) { free ( vec->_elem ); }

// Read-Only Access Interface

void swap ( void* a, void* b, size_t size ); // swap array elements

Bool vector_empty ( const Vector* vec ) { return vec->_size == 0; } // check if the vector is empty
Rank vector_size ( const Vector* vec ) { return vec->_size; }   // return the size of the vector
int vector_disordered( const Vector* vec ); // check if the vector is sorted
Rank vector_find ( const Vector* vec, const void* e, Rank low, Rank high ); // find an element in the vector (unsorted)
// Rank vector_find_full ( const Vector* vec, const void *e ) { return vector_find ( vec, e, 0, vec->_size ); }    // wrapper function for find
Rank vector_search ( const Vector* vec, const void* e, Rank low, Rank high );   // search for an element in the vector (sorted)
// Rank vector_search_full ( const Vector* vec, const void* e ) { return vector_search ( vec, e, 0, vec->_size ); }    // wrapper functions for search

// Writable Access Interface

void* vector_at ( const Vector* vec, Rank r );   // mimic subscript operator ( just like overloading "[]" )
void vector_assign ( Vector* dest, const Vector* src );  // clone vector ( just like overloading "==" )
Bool vector_element_equals ( const void* a, const void* b, size_t size ); // check two elements if they are equal ( just like overloading "=" )
void* vector_remove ( Vector* vec, Rank r );  // remove element at position r
Rank vector_remove_range ( Vector* vec, Rank low, Rank high );   // remove elements in range [low,high)
Rank vector_insert ( Vector* vec, Rank r, const void* e );  // insert element at position r
Rank vector_insert_last ( Vector* vec, const void* e ) { return vector_insert ( vec, vec->_size, e ); } // insert element at last
void vector_sort ( Vector* vec, Rank low, Rank high );  // sort part of vector in [low,high)
// void vector_sort_all ( Vector* vec ) { vector_sort ( vec, 0, vec->_size ); }   // sort the whole vector
void vector_unsort ( Vector* vec, Rank low, Rank high );    // unsort part of vector in [low,high)
void vector_unsort_all ( Vector* vec ) { vector_unsort ( vec, 0, vec->_size ); }    // unsort the whole vector
int deduplicate ( Vector* vec );    // remove duplicates (unsorted)
int uniquify ( Vector* vec );   // remove duplicates (sorted)

// Traverse

void vector_traverse ( Vector* vec, void (*func)(void*) );  // traverse the vector wuth a function pointer

// Defination

void _vector_shift_element ( Vector* vec, int fromIndex, int toIndex ) {
    if ( fromIndex < 0 || fromIndex >= vec->_size || toIndex < 0 || toIndex >= vec->_capacity ) {
        return; // Handle invalid indices
    }
    memcpy ( ( char* ) vec->_elem + ( toIndex * vec->_elementSize ),
             ( char* ) vec->_elem + ( fromIndex * vec->_elementSize ),
             vec->_elementSize );
}

void _vector_copyFrom ( Vector* vec, const void* A, Rank low, Rank high, size_t elementSize) {
    // calculate the new size
    Rank newSize = high - low;

    // Allocate memory for the new elements
    vec->_elem = malloc(newSize * elementSize);
    if ( !vec->_elem ) {
        // Handle memory allocation failure
        // Depending on error handling strategy
        return;
    }

    // Update the vector's capacity and size
    vec->_capacity = newSize * 2;
    vec->_size = newSize;
    vec->_elementSize = elementSize;

    // Copy elements from A to the vector
    for ( Rank i = 0; i < newSize; ++i ) {
        memcpy(( char* )vec->_elem + ( i * elementSize ),
               ( char* )A + ( ( low + i ) * elementSize ),
               elementSize);
    }
}

void _vector_expand ( Vector * vec ) {
    if ( vec->_size < vec->_capacity ) return; //no need to expand if not full

    // ensure capacity is at least DEFAULT_CAPACITY
    vec->_capacity = ( vec->_capacity > DEFAULT_CAPACITY ) ? ( vec->_capacity << 1 ) : DEFAULT_CAPACITY;

    // allocate new memory block
    void* newElem = malloc ( vec->_capacity * vec->_elementSize );
    if ( !newElem ) {
        // Handle memory allocation failure
        return;
    }

    // Copy elements to new memory block
    for ( int i = 0; i < vec->_size; ++i) {
        memcpy( ( char* ) newElem + ( i * vec->_elementSize ),
                ( char* ) vec->_elem + ( i * vec->_elementSize ),
                vec->_elementSize );
    }

    // Free old memory block and update pointer
    free ( vec->_elem );
    vec->_elem = newElem;
}

void _vector_shrink( Vector* vec ) {
    // Prevent shrinking below DEFAULT_CAPACITY
    if ( vec->_capacity < DEFAULT_CAPACITY << 1 ) return;

    // Only shrink if the size is significantly smaller than the capacity
    if ( vec->_size << 2 > vec->_capacity ) return;

    // Calulate new capacity
    int newCapacity = vec->_capacity >> 1;
    if (newCapacity < DEFAULT_CAPACITY) {
        newCapacity = DEFAULT_CAPACITY;
    }
    
    // Calculate new memory block
    void* newElem = malloc ( newCapacity * vec->_elementSize );
    if ( !newElem ) {
        // Handle memory allocation failure
        return;
    }

    // Copy elements to new memory block
    for ( int i = 0; i < vec->_size; ++i ) {
        memcpy ( ( char* ) newElem + ( i * vec->_elementSize ),
                 ( char* ) vec->_elem + ( i * vec->_elementSize ),
                 vec->_elementSize );
    }

    // Free old memory block and update pointer
    free ( vec->_elem );
    vec->_elem = newElem;
    vec->_capacity = newCapacity;
}

void vector_init ( Vector* vec, int c, int s, size_t elementSize, void* v ) { // initialize vector with full of v
    vec->_capacity = c;
    vec->_size = s > c ? c : s;
    vec->_elementSize = elementSize;
    vec->_elem = malloc ( elementSize * c );

    for (int i = 0; i < vec->_size; i++) 
        memcpy ( (char*)vec->_elem + (i * elementSize), v, elementSize );
}

void vector_initFromArray ( Vector* vec, const void* A, Rank n, size_t elementSize ) { // initialize vector with first n element of array A
    _vector_copyFrom ( vec, A, 0, n, elementSize ); 
}

void vector_initFromArrayRange ( Vector* vec, const void* A, Rank low, Rank high, size_t elementSize ) { // initialize vector with elements of array A[low,high)
    _vector_copyFrom( vec, A, low, high, elementSize );
}

void vector_initFromVector ( Vector* vec, const Vector* V ) {   // initialize vector by copying another vector V
    _vector_copyFrom ( vec, V->_elem, 0, V->_size, V->_elementSize );
}

void vector_initFromVectorRange ( Vector* vec, const Vector* V, Rank low, Rank high) {  // initialize vector with a part of another vector V[low, high)
    _vector_copyFrom ( vec, V->_elem, low, high, V->_elementSize);
}

void vector_print ( const Vector* vec ) {
    for ( int i = 0; i < vec->_size; i++ ) {
        void* currentElement = ( char* ) vec->_elem + ( i * vec->_elementSize );

        if ( vec->_elementSize == sizeof ( int ) ) {
            printf ( "%d ", *( ( int* ) currentElement ) );
        } else if ( vec->_elementSize == sizeof ( double ) ) {
            printf ( "%lf ", *( ( double* ) currentElement ) );
        } else if ( vec->_elementSize == sizeof ( char ) ) {
            printf ( "%c ", *( ( char* ) currentElement ) );
        }
        // and more cases for other data types ...
    }
    printf ( "\n" );
}

void swap ( void* a, void* b, size_t size ) {
    char temp[size];
    memcpy ( temp, a, size );
    memcpy ( a, b, size );
    memcpy ( b, temp, size );
}

// the type of elem is base type, otherwise define equivalence operation
Rank vector_find ( const Vector* vec, const void* e, Rank low, Rank high ) { // 0 <= low < high <= _size
    if ( low < 0 || vec->_size < high || high <= low ) return low - 1; // Invalid range

    while ( ( low < high-- ) && ( !vector_element_equals ( ( char* ) vec->_elem + ( high * vec->_elementSize ), e, vec->_elementSize ) ) ); // Reserve find

    return high; // If high < low means lose, otherwise high is the rank
}

// Mimic the subscript operator
void* vector_at ( const Vector* vec, Rank r ) {
    if ( r < 0 || r >= vec->_size ) return NULL;
    return ( char* ) vec->_elem + ( r * vec->_elementSize );
}

// Assignment ( clone a vector )
void vector_assign ( Vector* dest, const Vector* src ) {
    vector_destory ( dest );
    _vector_copyFrom ( dest, src->_elem, 0, src->_size, src->_elementSize );
}

Bool vector_element_equals ( const void* a, const void* b, size_t size) {
    return memcmp ( a, b, size ) == 0 ? True : False;
}

void* vector_remove ( Vector* vec, Rank r ) { // Remove the element with rank r in vector, 0 <= r < size
    if (r < 0 || r >= vec->_size) return NULL; // Invalid rank

    // Allocate memory for the removed element
    void* removedElement = malloc(vec->_elementSize);
    if (!removedElement) return NULL; // Allocation failure

    // Copy the element to be removed
    memcpy(removedElement, (char*)vec->_elem + (r * vec->_elementSize), vec->_elementSize);

    // Remove the element at rank r
    vector_remove_range ( vec, r, r + 1 );

    return removedElement; // Returm the copy of the removed element
}

Rank vector_remove_range ( Vector* vec, Rank low, Rank high ) {
    if ( low < 0 || high > vec->_size ) return -1; // Invalid range

    if ( low == high ) return 0; // for efficiency, degradation cases are treated separately

    while ( high < vec->_size )
        _vector_shift_element ( vec, high++, low++ ); // elements in [high, size) move high-low forward in sequence

    vec->_size = low; // Update size
    _vector_shrink( vec ); // Shrink if necessary
    
    return high - low; 
}

Rank vector_insert ( Vector* vec, Rank r, const void* e ) { // assert: 0 <= r <= size
    if ( r < 0 || r > vec->_size ) return -1; // Invalid rank

    _vector_expand( vec ); // Expand if necessary 

    // Shift elements to make space
    for ( int i = vec->_size; i > r; i-- )
        _vector_shift_element ( vec, i - 1, i );
    
    // Insert the new element
    memcpy ( ( char* ) vec->_elem + ( r * vec->_elementSize), e, vec->_elementSize );

    vec->_size++; // Update size
    return r; // Return the rank
}  

void vector_unsort ( Vector* vec, Rank low, Rank high ) {
    if ( low < 0 || high > vec->_size || low >= high ) return;

    for ( Rank i = high - low; i > 0; --i ) {
        Rank j = rand() % i;
        Rank swapIndex = low + j;
        Rank currentIndex = low + i - 1;

        // Use vector_at to get pointers to the elements
        void* addrA = vector_at(vec, swapIndex);
        void* addrB = vector_at(vec, currentIndex);

        // Swap the elements
        if (addrA && addrB) {
            swap(addrA, addrB, vec->_elementSize);
        }
    }
}

int main() {
    Vector test;
    int initialValue = 10;
    vector_init ( &test, DEFAULT_CAPACITY, 5, sizeof(int), &initialValue );
    vector_print( &test );
    printf("%d\n", vector_find ( &test, &initialValue, 1, test._size ));

    vector_destory( &test );
    return 0;
}
