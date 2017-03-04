#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFERSIZE 32

double calculateAndReturn(char operationCode, double result, double var);
int parseToNextValue(double *value, char *nextOperation);
int highPrior(double *result);
int multiple(char *tmpCh, double tmpVar, double *result);
int start(double *result);

int main() {
    double result = 0;
    if (start(&result) < 0)
        printf("[error]");
    else printf("%0.2lf", result);
    return 0;
}

int start(double *result) {
    char tmpCh = '+', lastChar = ' ';
    double tmpVar = 0;
    bool expectOperation = false;
    do {
        double tmpReturnVar = 0;
        lastChar = tmpCh;
        tmpReturnVar = parseToNextValue(&tmpVar, &tmpCh);
        if (tmpReturnVar > 0)
            expectOperation = true;
        else if (tmpReturnVar < 0)
            return -1;
        else expectOperation = false;
        switch (tmpCh) {
            case '+':
            case '-':
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                break;
            case '*':
            case '/':
                if (multiple(&tmpCh, tmpVar, &tmpReturnVar) < 0)
                    return -1;
                *result = calculateAndReturn(lastChar, *result, tmpReturnVar);
                break;
            case '(':
                if (expectOperation)
                    return -1;
                if (highPrior(&tmpReturnVar) < 0)
                    return -1;
                tmpVar = tmpReturnVar;
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                expectOperation = true;
                break;
            case ')':
                return -1;
            default:
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                break;
        }
    } while (tmpCh != 0);
    return 0;
}


int multiple(char *tmpCh, double tmpVar, double *result) {
    char lastChar = ' ';
    *result = tmpVar;
    bool expectOperation = false;
    double tmpReturningVar = 0;
    do {
        lastChar = *tmpCh;
        tmpReturningVar = parseToNextValue(&tmpVar, tmpCh);
        if (tmpReturningVar > 0)
            expectOperation = true;
        else if (tmpReturningVar < 0)
            return -1;
        else expectOperation = false;
        switch (*tmpCh) {
            default:
            case '+':
            case '-':
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                return 0;
            case '*':
            case '/':
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                return 0;
            case '(':
                if (expectOperation)
                    return -1;
                if (highPrior(&tmpReturningVar))
                    return -1;
                *result = calculateAndReturn(lastChar, *result, tmpReturningVar);
                tmpVar = *result;
                break;
        }
    } while (tmpCh > 0);
    return -1;
}

int highPrior(double *result) {
    char lastChar = ' ', tmpCh = '+';
    double tmpVar = 0;
    double tmpReturningVar = 0;
    *result = 0;
    bool expectOperation = false;
    do {
        lastChar = tmpCh;
        tmpReturningVar = parseToNextValue(&tmpVar, &tmpCh);
        if (tmpReturningVar > 0)
            expectOperation = true;
        else if (tmpReturningVar < 0)
            return -1;
        else expectOperation = false;

        switch (tmpCh) {
            default:
            case '+':
            case '-':
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                break;
            case '*':
            case '/':
                if (multiple(&tmpCh, tmpVar, &tmpReturningVar) < 0)
                    return -1;
                *result = calculateAndReturn(lastChar, *result, tmpReturningVar);
                break;
            case '(':
                if (expectOperation)
                    return -1;
                if (highPrior(&tmpReturningVar) < 0)
                    return -1;
                *result = calculateAndReturn(lastChar, *result, tmpReturningVar);
                tmpVar = *result;
                break;
            case ')':
                *result = calculateAndReturn(lastChar, *result, tmpVar);
                return 0;
        }
        if (tmpCh == ')') {
            return 0;
        }
    } while (tmpCh > 0);
    return -1;
}

double calculateAndReturn(char operationCode, double result, double var) {
    switch (operationCode) {
        case '+':
            return result + var;
        case '-':
            return result - var;
        case '*':
            return result * var;
        case '/':
            return result / var;
        default:
            return var;
    }
}

int parseToNextValue(double *value, char *nextOperation) {
    char wordBuffer[BUFFERSIZE] = {0};
    int thisPos = 0;
    int ch = 0;
    bool pointExist = false;
    while ((ch = getchar()) != EOF && ch != EOF) {
        if (ch >= '0' && ch <= '9')
            wordBuffer[thisPos++] = (char) ch;
        else if (ch == '.') {
            if (pointExist) {
                return -1; //Возможна только одна точка
            }
            wordBuffer[thisPos++] = (char) ch;
            pointExist = true;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '\n') {
            if (thisPos > 0) {
                wordBuffer[thisPos] = '\0';
                if (sscanf(wordBuffer, "%lf", value) < 0)
                    return -1;
            }
            *nextOperation = (char) (ch == '\n' ? 0 : ch);
            return thisPos;
        } else if (ch != ' ')
            return -1;
    }
    if (thisPos > 0) {
        wordBuffer[thisPos] = '\0';
        sscanf(wordBuffer, "%lf", value);
    }
    *nextOperation = 0;
    return 0;
}