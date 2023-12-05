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

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG,
    TYPE_SHORT,
    TYPE_UNSIGNED_INT,
    TYPE_UNSIGNED_CHAR,
    TYPE_UNSIGNED_LONG,
    TYPE_UNSIGNED_SHORT,
} ElementType;

// create a fibonacci struct
typedef struct {
    int f, g;
} Fib;

void fib_init ( Fib* fib, int n ) {
    fib->f = 1; // f(0)
    fib->g = 0; // f(-1)
    while ( fib->g < n ) {
        // f = f(n-1) + f(n-2)
        fib->f += fib->g;
        fib->g = fib->f - fib->g;
    }
}

void fib_prev ( Fib* fib ) {
    // g = f(n-1) - f(n-2)
    fib->g = fib->f - fib->g;
    fib->f -= fib->g;
}

int fib_get ( Fib* fib ) {
    return fib->f;
}

typedef struct {
    Rank _size;     // the size of vector
    int _capacity;  // the capacity of vector
    void* _elem;    // the data of vector
    size_t _elementSize; //size of each element in bytes
    ElementType _type; // store the type of elements
} Vector;

// _vector_* is the proteceted function

void _vector_shift_element ( Vector* vec, Rank fromRank, Rank toRank ); // shift one element locally
void _vector_copyFrom ( Vector* vec, const void* A, Rank low, Rank high, size_t elementSize ); // copy data from A[low, high)
void _vector_expand ( Vector* vec );  // expand space when not enough
void _vector_shrink ( Vector* vec );  // shrink when the filling factor is too small
Rank _vector_bubble ( Vector* vec, Rank low, Rank high );    
void _vector_bubbleSort ( Vector* vec, Rank low, Rank high );    // bubble sort algorithm
Rank _vector_max ( Vector* vec, Rank low, Rank high );   // select the maximum item
void _vector_selectionSort ( Vector* vec, Rank low, Rank high ); // selection sorting algorithm
void _vector_merge ( Vector* vec, Rank low, Rank high ); // merging algorithm
void _vector_mergeSort ( Vector* vec, Rank low, Rank high ); // merging sorting algorithm
Rank _vector_partition ( Vector* vec, Rank low, Rank high ); // axis point pole-building algorithm
void _vector_quickSort ( Vector* vec, Rank low, Rank high ); // quick sort algorithm
void _vector_heapSort ( Vector* vec, Rank low, Rank high );  // heap sort

// comparison functions for single type are also protected functions

Bool _compare_ints(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_chars(const void* a, const void* b) {
    char valA = *(const char*)a;
    char valB = *(const char*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_floats(const void* a, const void* b) {
    float valA = *(const float*)a;
    float valB = *(const float*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_doubles(const void* a, const void* b) {
    double valA = *(const double*)a;
    double valB = *(const double*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_longs(const void* a, const void* b) {
    long valA = *(const long*)a;
    long valB = *(const long*)b;
    return (valA < valB) ? True : False ;
}  
Bool _compare_shorts(const void* a, const void* b) {
    short valA = *(const short*)a;
    short valB = *(const short*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_unsigned_ints(const void* a, const void* b) {
    unsigned valA = *(const unsigned*)a;
    unsigned valB = *(const unsigned*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_unsigned_chars ( const void* a, const void* b ) {
    unsigned char valA = *(const unsigned char*)a;
    unsigned char valB = *(const unsigned char*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_unsigned_longs ( const void* a, const void* b ) {
    unsigned long valA = *(const unsigned long*)a;
    unsigned long valB = *(const unsigned long*)b;
    return (valA < valB) ? True : False ;
}
Bool _compare_unsigned_shorts ( const void* a, const void* b ) {
    unsigned short valA = *(const unsigned short*)a;
    unsigned short valB = *(const unsigned short*)b;
    return (valA < valB) ? True : False ;
} 

// vector_* is the public function

// Initialization

void vector_init ( Vector* vec, int c, int s, size_t elementSize, void* v, ElementType type ); // initialize vector with full of v
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
Rank vector_find_full ( const Vector* vec, const void *e ) { return vector_find ( vec, e, 0, vec->_size ); }    // wrapper function for find
Rank vector_search ( const Vector* vec, const void* e, Rank low, Rank high );   // search for an element in the vector (sorted)
Rank vector_search_full ( const Vector* vec, const void* e ) { return vector_search ( vec, e, 0, vec->_size ); }    // wrapper functions for search
Rank binSearch ( const Vector* vec, const void* e, Rank low, Rank high );
Rank fibSearch ( const Vector* vec, const void* e, Rank low, Rank high );

// Writable Access Interface

void* vector_at ( const Vector* vec, Rank r );   // mimic subscript operator ( just like overloading "[]" )
void vector_assign ( Vector* dest, const Vector* src );  // clone vector ( just like overloading "=" )
Bool vector_element_equals ( const Vector* first, const Vector* last, Rank first_rank, Rank last_rank ); // check two elements if they are equal ( just like overloading "==" )
Bool vector_element_smaller ( const Vector* first, const Vector* last, Rank first_rank, Rank last_rank ); // check if a smaller than b ( just like overloading "<" )
void* vector_remove ( Vector* vec, Rank r );  // remove element at position r
Rank vector_remove_range ( Vector* vec, Rank low, Rank high );   // remove elements in range [low,high)
Rank vector_insert ( Vector* vec, Rank r, const void* e );  // insert element at position r
Rank vector_insert_last ( Vector* vec, const void* e ) { return vector_insert ( vec, vec->_size, e ); } // insert element at last
void vector_sort ( Vector* vec, Rank low, Rank high );  // sort part of vector in [low,high)
// void vector_sort_all ( Vector* vec ) { vector_sort ( vec, 0, vec->_size ); }   // sort the whole vector
void vector_unsort ( Vector* vec, Rank low, Rank high );    // unsort part of vector in [low,high)
void vector_unsort_all ( Vector* vec ) { vector_unsort ( vec, 0, vec->_size ); }    // unsort the whole vector
int vector_deduplicate ( Vector* vec );    // remove duplicates (unsorted)
int vector_uniquify ( Vector* vec );   // remove duplicates (sorted)

// Traverse

void vector_traverse ( Vector* vec, void ( *func ) ( void* ) );  // traverse the vector wuth a function pointer
void vector_traverse_with_context ( Vector* vec, void ( *func ) ( void*, void*), void* context ); //traverse using a function pointer with context ( just like function object )

// Defination

void _vector_shift_element ( Vector* vec, Rank fromRank, Rank toRank ) {
    if ( fromRank < 0 || fromRank >= vec->_size || toRank < 0 || toRank >= vec->_capacity ) {
        return; // Handle invalid indices
    }

    memcpy ( ( char* ) vec->_elem + ( toRank * vec->_elementSize ),
             ( char* ) vec->_elem + ( fromRank * vec->_elementSize ),
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
    vec->_capacity = ( vec->_capacity >= DEFAULT_CAPACITY ) ? ( vec->_capacity << 1 ) : DEFAULT_CAPACITY;

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

Rank _vector_bubble ( Vector* vec, Rank low, Rank high ) {
    Rank last = low; // initialization
    while ( ++low < high )  // From left to right, check each pair of adjacent elements one by one
        if ( vector_element_smaller ( vec, vec, low, low - 1 ) ) { // If the order is reversed, then
            last = low; // Update the right-most reverse pair position record and
            swap ( vector_at ( vec, low - 1 ), vector_at ( vec, low ), vec->_elementSize ); // exchange
        }
    return last; // Return the reverse pair position on the far right
}

void _vector_bubbleSort ( Vector* vec, Rank low, Rank high ) 
{ while ( low < ( high = _vector_bubble ( vec, low, high ) ) ) ; }  // Scan the exchange, trip by trip, until full order

void vector_init(Vector* vec, int c, int s, size_t elementSize, void* v, ElementType type) { // initialize vector with full of v
    vec->_capacity = c;
    vec->_size = s > c ? c : s;
    vec->_elementSize = elementSize;
    vec->_elem = malloc(elementSize * c);
    vec->_type = type; // Set the type of elements

    for (int i = 0; i < vec->_size; i++) 
        memcpy((char*)vec->_elem + (i * elementSize), v, elementSize);
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

int vector_disordered( const Vector* vec ) {
    int n = 0;
    for ( int i = 1; i < vec->_size; i++ )
        if ( !vector_element_smaller ( vec, vec, i, i - 1 ) ) n++;
    return n; // if and only if n = 0, the vector is oredered
}

// the type of elem is base type, otherwise define equivalence operation
Rank vector_find ( const Vector* vec, const void* e, Rank low, Rank high ) { // 0 <= low < high <= _size
    if ( low < 0 || vec->_size < high || high <= low ) return low - 1; // Invalid range

    // create a temp vector only own one element for e
    Vector temp;
    vector_init ( &temp, 1, 1, sizeof(vec->_elementSize), e, vec->_type );

    while ( ( low < high-- ) && ( !vector_element_equals ( vec, &temp, high, 0 ) ) ); // Reserve find

    vector_destory ( &temp );
    return high; // If high < low means lose, otherwise high is the rank
}

Rank vector_search ( const Vector* vec, const void* e, Rank low, Rank high ) { // assert: 0 <= low < high <= _size
    return ( rand() % 2 ) ? // Randomly use the binary search and Fibonacci search with each 50% probability
        binSearch ( vec, e, low, high ) : fibSearch ( vec, e, low, high );
}

// Binary search algorithm: Find element e in the interval of ordered vectors [lo, hi), 0 <= lo <= hi <= _size
Rank binSearch ( const Vector* vec, const void* e, Rank low, Rank high ) {
    Vector temp;
    vector_init ( &temp, 1, 1, sizeof(vec->_elementSize), e, vec->_type );

    while ( low < high ) {
        Rank mid = ( low + high ) >> 1;
        ( vector_element_smaller ( &temp, vec, 0, mid ) ) ? ( high = mid ) : ( low = mid + 1 );
    }
    return --low; 
}

Rank fibSearch ( const Vector* vec, const void* e, Rank low, Rank high ) {
    if ( !vec || high - low < 0 ) return -1;

    Fib fib;
    fib_init ( &fib, high - low );

    Vector temp;
    vector_init ( &temp, 1, 1, sizeof(vec->_elementSize), e, vec->_type );

    while ( low < high ) {
        while ( high - low < fib_get ( &fib ) ) fib_prev ( &fib );
        Rank mid = low + fib_get ( &fib ) - 1;

        if ( vector_element_smaller ( &temp, vec, 0, mid ) ) high = mid; // Element is in the lower half
        else if ( vector_element_smaller ( vec, &temp, mid, 0 ) ) low = mid + 1; // Element is in the upper half
        else return mid; // Element found
    }

    return -1; // Element not found
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

Bool vector_element_equals ( const Vector* first, const Vector* last, Rank first_rank, Rank last_rank ) {
    return memcmp ( vector_at ( first, first_rank ), vector_at ( last, last_rank ), first->_elementSize ) == 0 ? True : False;
}

Bool vector_element_smaller ( const Vector* first, const Vector* last, Rank first_rank, Rank last_rank ) {
    if ( !vector_at ( first, first_rank ) || !vector_at ( last, last_rank ) ) return False; // Null check

    if ( vector_element_equals ( first, last, first_rank, last_rank ) ) return False; // first = last

    // based on type of first vector
    switch (first->_type) {
        case TYPE_INT:
            return _compare_ints ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_CHAR:
            return _compare_chars ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_FLOAT:
            return _compare_floats ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_DOUBLE:
            return _compare_doubles ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_LONG:
            return _compare_longs ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_SHORT:
            return _compare_shorts ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_UNSIGNED_INT:
            return _compare_unsigned_ints ( vector_at( first, first_rank ), vector_at( last, last_rank ) );

        case TYPE_UNSIGNED_CHAR:
            return _compare_unsigned_chars ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_UNSIGNED_LONG:
            return _compare_unsigned_longs ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        case TYPE_UNSIGNED_SHORT:
            return _compare_unsigned_shorts ( vector_at( first, first_rank ), vector_at( last, last_rank ) );
        default:
            return False; // Unknown type or not comparable
    }
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

// void vector_sort ( Vector* vec, Rank low, Rank high ) { 
//     switch ( rand() % 5 ) {
//         case 1 : _vector_bubbleSort ( vec, low, high ); break; // Bubble sort
//         case 2 : _vector_selectionSort ( vec, low, high ); break; // Selection sort
//         case 3 : _vector_mergeSort ( vec, low, high ); break; // Merge sort
//         case 4 : _vector_heapSort ( vec, low, high ); break; // Heap sort
//         default : _vector_quickSort ( vec, low, high ); break; // Quick sort
//     }
// }

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

int vector_deduplicate ( Vector* vec ) {
    if ( vec->_size < 2 ) return 0; // No duplicates possible in a vector with less than 2 elements

    int oldSize = vec->_size;
    Rank i = 1; // Start from the second element

    while ( i < vec->_size ) {
        // Check if vec[i] is a duplicate of any element before it
        ( vector_find ( vec, vector_at(vec, i), 0, i ) < 0 ) ? 
            i++     // No duplicate found, move to next element
        : vector_remove ( vec, i ) ; // Do not increment i, as the next element has shifted into the current position
}
    return oldSize - vec->_size;  // Return the number of removed elements
}

int vector_uniquify ( Vector* vec ) {  // iterate over the elements of sorted vector and remove duplicates2
    if (vec->_size < 2) return 0;  // No duplicates in a vector of size 0 or 1

    Rank i = 0, j = 0;
    while ( ++j < vec->_size)
        // Compare elements at i and j
        if ( !vector_element_equals (vec, vec, i, j ) )
            // If elements are different, move j to i + 1
            _vector_shift_element ( vec, j, ++i );
    
    vec->_size = ++i; // Update the size
    _vector_shrink ( vec ); // Shrink if necessary

    return j - i;   // Return the number of removed elements
}

// Traverse using a function pointer
void vector_traverse(Vector* vec, void (*func)(void*)) {
    for (int i = 0; i < vec->_size; ++i) {
        func((char*)vec->_elem + (i * vec->_elementSize));
    }
}

// Traverse using a function pointer with context
void vector_traverse_with_context(Vector* vec, void (*func)(void*, void*), void* context) {
    for (int i = 0; i < vec->_size; ++i) {
        func((char*)vec->_elem + (i * vec->_elementSize), context);
    }
}

// Function to increment an integer
void increment_int(void* e) {
    if (e != NULL) {
        (*(int*)e)++; // change e to an integer pointer
    }
}

// Function to increment each element in the vector
void increase_vector(Vector* vec) {
    vector_traverse(vec, increment_int);
}

int main() {
    Vector test;
    int initialValue = 10;
    vector_init ( &test, DEFAULT_CAPACITY, 5, sizeof(int), &initialValue , TYPE_INT );
    vector_print( &test );
    _vector_expand ( &test );
    int nums[] = {3,9,11};
    int nums2[] = {4,7,5};
    for ( int i = 0; i < (int) ( sizeof(nums)/sizeof(nums[0]) ); i++ ) {
        vector_insert ( &test, vector_search_full ( &test, nums + i ) + 1, nums + i );
        vector_insert_last ( &test, nums2 + i );
    }
    _vector_bubbleSort ( &test, 0, test._size );
    vector_print ( &test );
    printf( "%d\n", vector_disordered ( &test ) );
    printf( "%d\n", vector_find_full ( &test, &initialValue ) );
    increase_vector ( &test );

    vector_deduplicate ( &test );
    vector_print( &test );

    vector_destory( &test );
    return 0;
}
