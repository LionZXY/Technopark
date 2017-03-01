#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>

#define BUFFERSIZE 32

char parseToNextValue(double *value);

double calculateAndReturn(char operationCode, double result, double var);

double multiple(char *lastChar, double tmpVar);

double highPrior();

void error();

int main() {
    char tmpCh = '+', lastChar;
    double tmpVar = 0, result = 0;
    do {
        lastChar = tmpCh;
        tmpCh = parseToNextValue(&tmpVar);
        if (lastChar != '(')
            switch (tmpCh) {
                default:
                case '+':
                case '-':
                    result = calculateAndReturn(lastChar, result, tmpVar);
                    break;
                case '*':
                case '/':
                    result = calculateAndReturn(lastChar, result, multiple(&tmpCh, tmpVar));
                    break;
                case '(':
                    tmpVar = highPrior();
                    result = calculateAndReturn(lastChar, result, tmpVar);
                    break;
            }
    } while (tmpCh > 0);

    printf("%0.2lf", result);
    return 0;
}


double multiple(char *tmpCh, double tmpVar) {
    char lastChar;
    double result = tmpVar;
    do {
        lastChar = *tmpCh;
        *tmpCh = parseToNextValue(&tmpVar);
        switch (*tmpCh) {
            default:
            case '+':
            case '-':
                result = calculateAndReturn(lastChar, result, tmpVar);
                return result;
            case '*':
            case '/':
                result = calculateAndReturn(lastChar, result, tmpVar);
                break;
            case '(':
                tmpVar = highPrior();
                result = calculateAndReturn(lastChar, result, tmpVar);
                break;
        }
    } while (tmpCh > 0);
    return result;
}

double highPrior() {
    char lastChar, tmpCh = '+';
    double tmpVar;
    double result = 0;
    do {
        lastChar = tmpCh;
        tmpCh = parseToNextValue(&tmpVar);
        switch (tmpCh) {
            default:
            case '+':
            case '-':
                result = calculateAndReturn(lastChar, result, tmpVar);
                break;
            case '*':
            case '/':
                result = calculateAndReturn(lastChar, result, multiple(&tmpCh, tmpVar));
                break;
            case '(':
                tmpVar = highPrior();
                result = calculateAndReturn(lastChar, result, tmpVar);
                break;
            case ')':
                result = calculateAndReturn(lastChar, result, tmpVar);
                return result;
        }
        if (tmpCh == ')') {
            return result;
        }
    } while (tmpCh > 0);
    return result;
}

double calculateAndReturn(char operationCode, double result, double var) {
    switch (operationCode) {
        case '+':
            return result + var;
        case '-':
            return result + var;
        case '*':
            return result * var;
        case '\\':
        case '/':
            return result / var;
        default:
            return result;
    }
}

char parseToNextValue(double *value) {
    char wordBuffer[BUFFERSIZE];
    int thisPos = 0;
    int ch;
    bool pointExist = false;
    while ((ch = getchar()) != EOF && ch != EOF) {
        if (ch >= '0' && ch <= '9')
            wordBuffer[thisPos++] = (char) ch;
        else if (ch == '.') {
            if (pointExist) {
                error(); //Возможна только одна точка
                return 0;
            }
            wordBuffer[thisPos++] = (char) ch;
            pointExist = true;
        } else {
            if (thisPos > 0) {
                wordBuffer[thisPos] = '\0';
                sscanf(wordBuffer, "%lf", value);
            }
            return (char) (ch == '\n' ? 0 : ch);
        }
    }

    return 0;
}

void error() {
    printf("[error]");
    exit(0);
}