#include <string.h>
#include <stdlib.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned int hash(char *s) {
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; ++s) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

char *string_dup(char *s) {
    char *dup = malloc(strlen(s) + 1);
    strcpy(dup, s);
    return dup;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL || (np->name = string_dup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    if ((np->defn = string_dup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

void undef(char *s) {
    struct nlist **np;

    for (np = &hashtab[hash(s)]; *np != NULL; np = &(*np)->next) {
        if (strcmp(s, (*np)->name) == 0) {
            struct nlist *del = *np;
            *np = (*np)->next;
            free(del);
        }
    }
}
