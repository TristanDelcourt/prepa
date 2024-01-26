#include "dico_hash.h"
#include "dico_chaine.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    // TEST hash

    char* str = strdup("bonjour");
    unsigned int nbr = hash(str)%101;
    assert(nbr==60);

    str = strdup("voici un texte a hacher");
    nbr = hash(str)%503;
    assert(nbr==151);

    str = strdup("voici un texte a macher");
    nbr = hash(str)%503;
    assert(nbr==156);

    // END TEST

    // TEST equal

    str = strdup("bonjour");
    char* str2 = strdup("bonjour");
    char* str3 = strdup("bonsoir");

    assert(equal(str, str2));
    assert(!equal(str, str3));

    // END TEST

    // --- TEST DICO CHAINE ---

    chain_t* d = chain_create();

    char* str1 = strdup("bonjour");
    str2 = strdup("bonsoir");

    chain_set(d, str1, str2);
    char** output = malloc(sizeof(char*));
    assert(chain_get(d, str1, output));

    assert(!strcmp(*output, "bonsoir"));

    chain_print(d);

    assert(d->n == 1);
    assert(chain_delete(d, str1));
    assert(d->n == 0);

    chain_print(d);

    assert(!chain_delete(d, str2));

    // END TEST
    printf("--------------------\n");
    
    str = strdup("bonjour");
    str2 = strdup("bonjour");

    hashtable_t* ht = hash_create();
    hash_set(ht, str, str2);
    hash_print(ht);

    hash_delete(ht, str);
    hash_print(ht);

    return 0;
}