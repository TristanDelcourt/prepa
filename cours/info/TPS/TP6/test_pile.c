#include "pile.h"
#include <stdio.h>

int main(){

    pile_t* p = pile_vide();
    empiler(p, 10);
    empiler(p, 3);
    print_pile(p);
    printf("%d\n", depiler(p));
    print_pile(p);
    free_pile(p);

    return 0;
}