#include <stdio.h>
#include <stdlib.h>
typedef struct htlnode* hashtable;
struct htlnode
{
    int size;
    int *a;
};
int isprime(int x)
{
    int i;
    for(i=2; i*i<=x; i++)
        if(x%i == 0) return 0;
    return 1;
}
int nextprime(int n)
{
    if(n == 1) return 2;
    if(isprime(n)) return n;
    int x = (n%2)?n+2:n+1, i;
    while(x <= 20000)
    {
        if(isprime(x)) return x;
        x += 2;
    }
}
hashtable create(int maxsize)
{
    hashtable h = (hashtable)malloc(sizeof(struct htlnode));
    h->size = nextprime(maxsize);
    h->a = (int*)malloc(h->size*sizeof(int));
    int i;
    for(i=0; i<h->size; i++) h->a[i] = -1;
    return h;
}
int Hash(int x,int p)
{
    return x % p;
}
int Insert(hashtable h, int x)
{
    int pos = Hash(x, h->size);
    if(h->a[pos] == -1) h->a[pos] = 1;
    else
    {
        int i;
        for(i=1; i<=h->size; i++)
        {
            pos = Hash(x+i*i, h->size);
            if(h->a[pos] == -1)
            {
                h->a[pos] = 1;
                break;
            }
        }
        if(i > h->size/2) pos = -1;
    }
    return pos;
}
int main()
{
    int n, i, x, maxsize;
    scanf("%d%d", &maxsize, &n);
    hashtable h = create(maxsize);
    for(i=0; i<n; i++)
    {
        scanf("%d", &x);
        int pos = Insert(h, x);
        if(pos == -1) printf("-");
        else printf("%d", pos);
        printf("%c", i == n-1?'\n':' ');
    }
    return 0;
}
