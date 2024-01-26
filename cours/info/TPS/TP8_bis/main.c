#include "dict.h"
#include <stdio.h>

int main(){

    //TEST
    dict_t* d = dico_vide();

    set(d, "bob", "tristan");
    set(d, "boob", "laulau");
    char* str = get(d, "boob");
    printf("%s\n", str);

    return 0;
}
