#include "file.h"
#include <stdio.h>

int main(){

    file_t* p = file_vide();
    enfiler(p, 10);
    enfiler(p, 3);
    affiche_file(p);
    printf("%d\n", defiler(p));
    affiche_file(p);
    free_file(p);

    return 0;
}