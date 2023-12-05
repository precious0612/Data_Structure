// BitMap

typedef int Bool;

#define True 1
#define False 0

typedef struct {
    char* M;  // Array to store the bitmap
    int N;    // Size of the array
    int capacity; // Current capacity in bits
} Bitmap;

void Bitmap_init(Bitmap* bmp, int n); // Initializes the Bitmap with a given size
Bitmap* Bitmap_new(int n); // Creates a new Bitmap with a specified size
void Bitmap_destroy(Bitmap* bmp); // Destroys the Bitmap and frees allocated memory

void Bitmap_set(Bitmap* bmp, int k); // Sets a specific bit in the Bitmap
void Bitmap_clear(Bitmap* bmp, int k); // Clears a specific bit in the Bitmap
Bool Bitmap_test(Bitmap* bmp, int k); // Tests if a specific bit is set in the Bitmap

void Bitmap_expand(Bitmap* bmp, int k); // Expands the Bitmap's capacity if needed
void Bitmap_shrink(Bitmap* bmp); // Shrinks the Bitmap's capacity if possible

Bitmap* Bitmap_new_from_file(char* file, int n); // Creates a new Bitmap from a file input
void Bitmap_dump(Bitmap* bmp, char* file); // Dumps the Bitmap's content to a file
char* Bitmap_bits_to_string(Bitmap* bmp, int n); // Converts the Bitmap's bits to a string representation

void Bitmap_init ( Bitmap* bmp, int n ) {
    bmp->capacity = n;
    bmp->N = ( n + 7 ) / 8;
    bmp->M = (char*) malloc ( bmp->N );
    memset ( bmp->M, 0, bmp->N );
}

// Constructor with size
Bitmap* Bitmap_new ( int n ) {
    Bitmap* bmp = (Bitmap*) malloc ( sizeof ( Bitmap ) );
    Bitmap_init ( bmp, n );
    return bmp;
}

// Constructor with file input
Bitmap* Bitmap_new_from_file ( char* file, int n ) {
    Bitmap* bmp = Bitmap_new ( n );
    FILE* fp = fopen ( file, "r" );
    fread ( bmp->M, sizeof ( char ), bmp->N, fp );
    fclose ( fp );
    return bmp; 
}

// Destructor
void Bitmap_destroy ( Bitmap* bmp ) {
    free ( bmp->M );
    free ( bmp );
}

void Bitmap_expand ( Bitmap* bmp, int k ) {
    if ( k < bmp->capacity ) return; // No need to expand if capacity is sufficient

    int newCapacity = bmp->capacity;
    while ( k >= newCapacity ) {
        newCapacity *= 2; // Double the capacity
    }

    char* newM = (char*) realloc ( bmp->M, ( newCapacity + 7 ) / 8 );
    if ( !newM ) return; // Handle memory allocation failure

    memset ( newM + bmp->N, 0, ( newCapacity + 7 ) / 8 - bmp->N ); // Initialize new space to 0
    bmp->M = newM;
    bmp->capacity = newCapacity;
    bmp->N = ( newCapacity + 7 ) / 8;
}

void Bitmap_shrink ( Bitmap* bmp ) {
    int lastUsedIndex = -1;
    for ( int i = bmp->capacity - 1; i >= 0; i-- ) {
        if ( Bitmap_test ( bmp, i ) ) {
            lastUsedIndex = i;
            break;
        }
    }

    if ( lastUsedIndex == -1 ) {
        // All bits are clear, can free the memory
        free ( bmp->M );
        bmp->M = NULL;
        bmp->N = 0;
        bmp->capacity = 0;
    } else {
        int newCapacity = lastUsedIndex + 1;
        int newSize = ( newCapacity + 7 ) / 8;
        if ( newSize < bmp->N ) {
            char* newM = (char*) realloc ( bmp->M, newSize );
            if (!newM) return; // Handle memory allocation failure

            bmp->M = newM;
            bmp->N = newSize;
            bmp->capacity = newCapacity;
        }
    }
}

// Set a bit
void Bitmap_set ( Bitmap* bmp, int k ) {
    Bitmap_expand ( bmp, k ); // Ensure capacity before setting a bit
    if ( k >= 0 && k < bmp->capacity )
        bmp->M[k >> 3] |= ( 0x80 >> ( k & 0x07 ) );
}

// Clear a bit
void Bitmap_clear ( Bitmap* bmp, int k ) {
    if ( k >= 0 && k < bmp->capacity )
        bmp->M[k >> 3] &= ~( 0x80 >> ( k & 0x07 ) );
    Bitmap_shrink ( bmp ); // Shrink the bitmap if a lot of space is unused
}

// Test a bit
Bool Bitmap_test ( Bitmap* bmp, int k ) {
    if ( k >= 0 && k < bmp->capacity ) 
        return bmp->M[k >> 3] & ( 0x80 >> ( k & 0x07 ) );
    return False;
}

// Dump bitmap to file
void Bitmap_dump ( Bitmap* bmp, char* file ) {
    FILE* fp = fopen ( file, "w" );
    fwrite ( bmp->M, sizeof ( char ), bmp->N, fp );
    fclose ( fp );
}

// Convert bitmap to string
char* Bitmap_bits_to_string ( Bitmap* bmp, int n ) {
    if ( n > bmp->N * 8 ) n = bmp->N * 8;
    char* s = (char*) malloc ( n + 1 );
    s[n] = '\0';
    for ( int i = 0; i < n; i++ )
        s[i] = Bitmap_test ( bmp, i ) ? '1' : '0';
    return s;
}
