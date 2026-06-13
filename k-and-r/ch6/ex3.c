#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100
#define MAX_LINES 100

// This list is stolen from the C Answers Book.
const char *noise_words[] = {"a", "an", "and", "are", "in", "is", "of", "or", "that", "the", "this", "to"};

#define NOISE_WORDS_LENGTH (sizeof(noise_words) / sizeof(noise_words[0]))

struct tnode {
    struct tnode *left;
    struct tnode *right;
    char word[MAX_WORD];
    int num_lines;
    int lines[MAX_LINES];
};

void print_tree(struct tnode *t);

int is_noise_word(char *word);

int get_word(char *word);

int popch(void);
int peekch(void);

int main(void) {
    char word[MAX_WORD];
    int line;
    struct tnode root = {NULL, NULL, "", 0, {0}};

    while ((line = get_word(word)) != -1) {
        // Do not include noise words.
        if (is_noise_word(word)) {
            continue;
        }

        // Set root if not already set.
        if (root.num_lines == 0) {
            strcpy(root.word, word);
        }

        // Have wnode point to the variable pointing to the correct node.
        struct tnode *w_ptr = &root;
        struct tnode **wnode = &w_ptr;
        while (*wnode != NULL) {
            int cmp = strcmp(word, (*wnode)->word);
            if (cmp < 0) {
                wnode = &(*wnode)->left;
            } else if (cmp > 0) {
                wnode = &(*wnode)->right;
            } else {
                break;
            }
        }

        if (*wnode == NULL) {
            // wnode points to new word location.
            *wnode = malloc(sizeof(**wnode));
            **wnode = (struct tnode){NULL, NULL, "", 0, {0}};
            strcpy((*wnode)->word, word);
        }

        // Add the new line if it isn't already on it.
        w_ptr = *wnode;
        if (w_ptr->num_lines == 0 || w_ptr->lines[w_ptr->num_lines - 1] != line) {
            w_ptr->lines[w_ptr->num_lines++] = line;
        }
    }

    print_tree(&root);

    return 0;
}

void print_tree(struct tnode *t) {
    if (t == NULL) {
        return;
    }

    print_tree(t->left);
    printf("%s: ", t->word);
    for (int i = 0; i < t->num_lines; ++i) {
        printf("%d%c", t->lines[i], (i == t->num_lines - 1) ? '\n' : ' ');
    }
    print_tree(t->right);
}

int is_noise_word(char *word) {
    for (int i = 0; i < NOISE_WORDS_LENGTH; ++i) {
        if (strcmp(word, noise_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int line = 1;

int get_word(char *word) {
    int c;
    while ((c = peekch()) != EOF && !isalpha(c)) {
        if (c == '\n') {
            ++line;
        }
        popch();
    }

    if (c == EOF) {
        return -1;
    }

    while ((c = peekch()) != EOF && isalpha(c)) {
        *word++ = popch();
    }

    *word = '\0';
    return line;
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
