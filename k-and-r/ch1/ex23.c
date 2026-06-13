#include <stdio.h>

/* context types */
#define NORMAL 0     /* not within a quoted literal or comment */
#define CHAR_LIT 1   /* within a quoted character literal */
#define STRING_LIT 2 /* within a quoted string literal */
#define COMMENT 3    /* within a comment */

/* previous character types, NORMAL is reused to be none of these */
#define BACKSLASH 1 /* the last character was a quoted backslash */
#define SLASH 2     /* the last character was a normal forward slash */
#define ASTERISK 3  /* the last character was a commented asterisk */

int main(void) {
    int context = NORMAL;   /* the context of the current character */
    int prev_char = NORMAL; /* type of previous character */

    int c;
    while ((c = getchar()) != EOF) {
        if (prev_char == SLASH) {
            /* check for comment or print delayed slash */
            if (c == '*') {
                context = COMMENT;
            } else {
                putchar('/');
            }
            prev_char = NORMAL;
        }

        if (context == COMMENT) {
            if (c == '*') {
                prev_char = ASTERISK;
            } else if (prev_char == ASTERISK && c == '/') {
                /* comment ended */
                context = NORMAL;
                prev_char = NORMAL;
            } else {
                prev_char = NORMAL;
            }
        } else if (prev_char == BACKSLASH) {
            prev_char = NORMAL;
            putchar(c);
        } else if (c == '"') {
            if (context == NORMAL) {
                context = STRING_LIT;
            } else if (context == STRING_LIT) {
                context = NORMAL;
            }
            putchar(c);
        } else if (c == '\'') {
            if (context == NORMAL) {
                context = CHAR_LIT;
            } else if (context == CHAR_LIT) {
                context = NORMAL;
            }
            putchar(c);
        } else if (c == '\\' && context != NORMAL) {
            /* context not being NORMAL is equivalent to quoted */
            prev_char = BACKSLASH;
            putchar(c);
        } else if (c == '/' && context == NORMAL) {
            prev_char = SLASH;
        } else {
            putchar(c);
        }
    }

    return 0;
}
