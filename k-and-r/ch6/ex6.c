#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int buf_char_set = 0;
int buf_char;

int getch(void) {
    if (buf_char_set) {
        buf_char_set = 0;
        return buf_char;
    } else {
        return getchar();
    }
}

void ungetch(char c) {
    buf_char_set = 1;
    buf_char = c;
}

int next_tok(char *tok) {
    int c = getch();
    if (isalpha(c) || c == '_') {
        *tok++ = c;
        while ((c = getch()) != EOF && (isalnum(c) || c == '_')) {
            *tok++ = c;
        }
        ungetch(c);
        c = '\0'; // Not EOF.
    } else if (c != EOF) {
        *tok++ = c;
    }

    *tok = '\0';
    return c;
}

#define MAX_TOKEN 100

void define(void) {
    char token[MAX_TOKEN];
    char name[MAX_TOKEN];
    char defn[MAX_TOKEN] = "";

    while (next_tok(name) != EOF) {
        if (!isspace(name[0])) {
            break;
        }
    }

    while (next_tok(token) != EOF) {
        if (!isspace(token[0])) {
            break;
        }
    }

    do {
        if (token[0] == '\n') {
            install(name, defn);
            return;
        }
        strcat(defn, token);
    } while (next_tok(token) != EOF);
}

int main(void) {
    char token[MAX_TOKEN];

    int last_tok_nl = 1;

    while (next_tok(token) != EOF) {
        struct nlist *replace;
        if (last_tok_nl && strcmp(token, "#") == 0) {
            next_tok(token);
            if (strcmp(token, "define") == 0) {
                define();
                // define() consumes last newline.
                last_tok_nl = 1;
                continue;
            } else {
                putchar('#');
            }
        } else if ((replace = lookup(token)) != NULL) {
            strcpy(token, replace->defn);
        }

        last_tok_nl = !strcmp(token, "\n");
        printf("%s", token);
    }

    return 0;
}
