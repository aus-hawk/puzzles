#include <stdio.h>

// This program checks only for the most basic syntax errors, and expects the
// lines to be standard Unix lines ending with a newline character.

#define NORMAL 0     /* Text is normal with no indication of a comment. */
#define SLASH 1      /* The previous character was a slash, so an asterisk may follow. */
#define IN_COMMENT 2 /* The current character is within a comment. */

int main(void) {
    int paren_depth = 0;
    int bracket_depth = 0;
    int brace_depth = 0;
    int comment_state = NORMAL;

    int c;
    while ((c = getchar()) != EOF) {
        // Handle comments.
        if (comment_state == SLASH && c == '*') {
            comment_state = IN_COMMENT;
            while ((c = getchar()) != EOF && comment_state == IN_COMMENT) {
                if (c == '*' && getchar() == '/') {
                    comment_state = NORMAL;
                }
            }
            if (c == EOF) {
                printf("Unclosed comment\n");
            }
        }
        comment_state = NORMAL;

        if (c == '(') {
            ++paren_depth;
        } else if (c == ')') {
            --paren_depth;
        } else if (c == '[') {
            ++bracket_depth;
        } else if (c == ']') {
            --bracket_depth;
        } else if (c == '{') {
            ++brace_depth;
        } else if (c == '}') {
            --brace_depth;
        } else if (c == '\'') {
            if (getchar() == '\\') {
                getchar(); // The escaped character should be skipped.
            }
            // If the character is not a backslash, then the character is skipped.
            if (getchar() != '\'') {
                printf("Bad character constant\n");
            }
        } else if (c == '"') {
            while ((c = getchar()) != '"') {
                if (c == '\\') {
                    getchar(); // The escaped character should be skipped.
                }
            }
        } else if (c == '/') {
            comment_state = SLASH;
        }

        if (paren_depth < 0 || bracket_depth < 0 || brace_depth < 0) {
            printf("Unmatched '%c' found\n", c);
        }
    }

    if (paren_depth > 0) {
        printf("Open '(' not closed\n");
    }
    if (bracket_depth > 0) {
        printf("Open '[' not closed\n");
    }
    if (brace_depth > 0) {
        printf("Open '{' not closed\n");
    }

    return 0;
}
