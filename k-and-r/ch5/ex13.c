#include <stdio.h>
#include <stdlib.h>

#define LINE_DATA_SIZE 1000

static char line_data[LINE_DATA_SIZE];

int main(int argc, char *argv[]) {
    const int MAX_LINES = (argc > 1 && **++argv == '-') ? atoi(++*argv) : 10;
    int num_lines = 0;
    char *line_data_ptr = line_data;

    int c;
    while ((c = getchar()) != EOF) {
        *line_data_ptr++ = c;

        if (c == '\n' && ++num_lines > MAX_LINES) {
            char *write_ptr = line_data;
            char *read_ptr = line_data;

            while (*read_ptr++ != '\n')
                ;

            int lines_copied = 0;
            while (lines_copied < MAX_LINES) {
                if (*read_ptr == '\n') {
                    ++lines_copied;
                }
                *write_ptr++ = *read_ptr++;
            }
            line_data_ptr = write_ptr;
        }
    }

    *line_data_ptr = '\0';

    printf("%s", line_data);

    return 0;
}
