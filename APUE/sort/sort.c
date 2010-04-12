#include <stdio.h>
#include <stdlib.h>
//using namespace std;

typedef unsigned long long PedSector;
#define MAX_PARTITION_NUMBER 16

static int compare(const void *p1, const void *p2)
{
    PedSector x = *(PedSector *)p1;
    PedSector y = *(PedSector *)p2;
    if (x < y) return -1;
    if (x == y) return 0;
    if (x > y) return 1;
}

int main()
{
    int i;
    PedSector a[MAX_PARTITION_NUMBER];

    for (i = 0; i < MAX_PARTITION_NUMBER; ++i) {
        a[i] = 0;
    }
    
    a[0] = 38946529280LL;
    a[1] = 11721125888LL;
    a[6] = 9164627968LL;
        
    fprintf(stderr, "%s %d %s before soriting\n", __FILE__, __LINE__, __func__);
    for (i = 0; i < MAX_PARTITION_NUMBER; ++i) {
        fprintf(stderr, "a[%d] %lld\n", i, a[i]);
    }

    qsort(a, MAX_PARTITION_NUMBER, sizeof(PedSector), compare);

    fprintf(stderr, "%s %d %s after soriting\n", __FILE__, __LINE__, __func__);
    for (i = 0; i < MAX_PARTITION_NUMBER; ++i) {
        fprintf(stderr, "a[%d] %lld\n", i, a[i]);
    }
}
