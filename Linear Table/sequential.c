#define MAXSIZE 20      /* the initial storage space */

typedef int ElemType;   /* not must be int, it's up to particular situation */
typedef struct
{
    ElemType data[MAXSIZE];     /* using array to store data elements, the maximum is MAXSIZE */
    int length;                 /* the current length of linear table */
}SqList;

/* Get the element */

#define OK 1
#define ERROR 0

typedef int Status;

/* Status is a type of function, and its value will be the result of function, such as OK */
/* Initial conditions: the sequential linear list has already existed, and 1<=i<=ListLength(L) */
/* Operation result: return the value of the ith element by using e */

Status GetElem (SqList L, int i, ElemType *e)
{
    if (L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e=L.data[i-1];
    return OK;
}

/* insert element */

/* Initial conditions: the sequential linear list has already existed, and 1<=i<=ListLength(L) */
/* Operation result: insert a new one in front of the i-th element of L, and the length of L plus 1 */

Status ListInsert (SqList *L, int i, ElemType e)
{
    int k;
    if (L->length==MAXSIZE)     /* Sequential linear list is already full. */
        return ERROR;
    if (i<1 || i>L->length+1)   /* i is not located at legal place. */
        return ERROR;
    if (i<=L->length)   /* If the data is not located at the end, which is inserted */
    {
        for (k=L->length-1; k>=i-1; k-- /* place the data element after i-th one into the next position */)
            L->data[k+1]=L->data[k+2];
    }
    L->data[i-1]=e;     /* insert the new element */
    L->length++;
    return OK;
}

/* Delete the element */

/* Initial conditions: the sequential linear list has already existed, and 1<=i<=ListLength(L) */
/* Operation result: delete the i-th data element, and return its value using e, then the length of L minus 1 */

Status ListDelete (SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length==0)       /* The linear list was empty. */
        return ERROR;
    if (i<0 || i>L->length) /* The position was wrong. */
        return ERROR;
    *e=L->data[i-1];
    if (i<L->length)
    {
        for (k=i; k<L->length; k++)
            L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

int main()
{
    return 0;
}

