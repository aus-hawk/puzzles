#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 100


int get_word(char *word);

int popch(void);
int peekch(void);

int main(void) {
    char word[MAX_WORD_LEN];
    struct word_occurrence {
        char word[MAX_WORD_LEN];
        int num_occ;
    } words[MAX_WORDS];
    int num_words = 0;

    while (get_word(word) != -1) {
        int i;
        for (i = 0; words[i].num_occ != 0 && strcmp(words[i].word, word) != 0; ++i)
            ;

        if (words[i].num_occ++ == 0) {
            strcpy(words[i].word, word);
            ++num_words;
        }
    }

    // Yes, it's bubble sort. I don't care.
    for (int i = 0; i < num_words - 1; ++i) {
        for (int j = i; j < num_words - 1; ++j) {
            if (words[j].num_occ > words[j + 1].num_occ) {
                struct word_occurrence temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }

    for (int i = num_words; --i > 0;) {
        printf("%4d %s\n", words[i].num_occ, words[i].word);
    }

    return 0;
}

int get_word(char *word) {
    int c;
    while ((c = peekch()) != EOF && !isalpha(c)) {
        popch();
    }

    if (c == EOF) {
        return EOF;
    }

    while ((c = peekch()) != EOF && isalpha(c)) {
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
