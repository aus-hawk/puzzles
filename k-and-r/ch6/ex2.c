#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100

struct tnode {
    struct tnode *left;
    struct tnode *right;
    char *word;
    int num;
};

void print_tnode_words(struct tnode *n);

int getword(char *word);

int popch(void);
int peekch(void);

int main(int argc, char *argv[]) {
    const int max_depth = (argc > 1) ? atoi(argv[1]) : 6;
    struct tnode root = {NULL, NULL, NULL, 1};

    char word[MAX_WORD];
    while (getword(word) != EOF) {
        // set root initially
        if (root.word == NULL) {
            int len = strlen(word);
            root.word = malloc(max_depth + 1);
            strncpy(root.word, word, max_depth);
            root.word[max_depth] = '\0';
            continue;
        }

        struct tnode *root_ptr = &root;
        struct tnode **wnode = &root_ptr;
        while (*wnode != NULL) {
            int cmp = strncmp(word, (*wnode)->word, max_depth);
            if (cmp < 0) {
                wnode = &(*wnode)->left;
            } else if (cmp > 0) {
                wnode = &(*wnode)->right;
            } else {
                break;
            }
        }

        if (*wnode == NULL) {
            *wnode = malloc(sizeof(**wnode));
            **wnode = (struct tnode){NULL, NULL, malloc(max_depth + 1), 1};
            strncpy((*wnode)->word, word, max_depth);
            (*wnode)->word[max_depth] = '\0';
        } else {
            ++(*wnode)->num;
        }
    }

    if (root.word != NULL) {
        print_tnode_words(&root);
    }

    return 0;
}

void print_tnode_words(struct tnode *n) {
    if (n == NULL) {
        return;
    }
    print_tnode_words(n->left);
    printf("%s: %d\n", n->word, n->num);
    print_tnode_words(n->right);
}

int skip_quote(void) {
    int c = peekch();
    if (c != '"' && c != '\'') {
        return 0;
    }
    int quote = popch();
    while ((c = popch()) != quote) {
        if (c == '\\') {
            popch();
        }
    }

    return 1;
}

int skip_comment(void) {
    int c = peekch();
    if (c != '/') {
        return 0;
    }

    // single-line comments
    c = popch();
    if (c == '/') {
        while (popch() != '\n')
            ;
        return 1;
    }

    // multi-line comments
    if (c != '*') {
        return 0;
    }
    while (1) {
        c = popch();
        if (c == '*' && peekch() == '/') {
            popch();
            return 1;
        }
    }
}

int skip_whitespace(void) {
    int ret = 0;
    for (int c = peekch(); isspace(c); c = peekch()) {
        popch();
        ret = 1;
    }
    return ret;
}

int getword(char *word) {
    int c;
    while ((c = peekch()) != EOF && !isalpha(c) && c != '_') {
        skip_quote() || skip_comment() || skip_whitespace() || popch();
    }

    if (c == EOF) {
        return c;
    }

    while ((c = peekch()) != EOF && (isalnum(c) || c == '_')) {
        *word++ = popch();
    }

    *word = '\0';
    return word[0];
}

int char_saved = 0;
int ch;

int popch(void) {
    if (char_saved) {
        char_saved = 0;
        return ch;
    } else {
        return getchar();
    }
}

int peekch(void) {
    if (char_saved) {
        return ch;
    } else {
        char_saved = 1;
        return ch = getchar();
    }
}
