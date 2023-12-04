/* the linear list consisted by chain structure*/

#define MAXSIZE 20      /* the initial storage space */
#define OK 1
#define ERROR 0

typedef int ElemType;   /* not must be int, it's up to particular situation */
typedef int Status;

typedef struct
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList;      /* define LinkList */

/* read the element of the LinkList */

/* Initial conditions: the sequential linear list has already existed, and 1<=i<=ListLength(L) */
/* Operation result: return the value of the i-th element using e */

Status GetElem (LinkList L, int i, ElemType *e)
{
    int j;
    
}