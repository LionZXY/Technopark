#include <stdio.h>
#include <malloc.h>

#define BUFFERSIZE 64

int main() {
    char **strs;

    readAllString(strs);
    printAllString(strs);

    return 0;
}

int readAllString(char **strs) {
    int ch = -1;
    int indexCurChar = 0;
    int indexRows = 0;
    size_t curRowsArraySize = BUFFERSIZE;
    size_t curRowSize = BUFFERSIZE;

    strs = malloc(curRowsArraySize);
    if (strs == NULL)
        return -1;

    strs[indexRows] = malloc(curRowSize);
    if (strs[indexRows] == NULL)
        return -1;

    while (!feof(stdin)) {
        ch = getchar();

        if (indexCurChar < curRowSize) {
            if (ch == '\n' || ch == '\0') {
                strs[indexRows][indexCurChar] = 0;
                indexRows++;
                if (indexRows >= curRowsArraySize) {
                    curRowsArraySize += BUFFERSIZE;
                    if (realloc(strs, curRowsArraySize) == NULL)
                        return -1;
                }
                curRowSize = BUFFERSIZE;
                strs[indexRows] = malloc(curRowSize);
                if (strs[indexRows] == NULL)
                    return -1;

                indexCurChar = 0;
                continue;
            }
        } else {
            curRowSize += BUFFERSIZE;
            if (realloc(strs[indexRows], curRowSize) == NULL)
                return -1;
        }

        strs[indexRows][indexCurChar++] = (char) ch;
    }

    strs[indexRows][indexCurChar++] = 0;
    indexRows++;
    if (indexRows >= curRowsArraySize) {
        curRowsArraySize += BUFFERSIZE;
        if (realloc(strs, curRowsArraySize) == NULL)
            return -1;
    }
    strs[indexRows] = NULL;
    return 0;
}

void printAllString(char **strs) {
    int index = 0;
    char *str = strs[index++];
    while (str != NULL) {
        str = strs[index++];
        printf("%s", str);
    }
}
