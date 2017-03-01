#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>

#define BUFFERSIZE 32

bool has_error = false;

char parseToNextValue(double *value);

double calculateAndReturn(char operationCode, double var);

double minus(double var);

double devided(double var);

int main() {
    char tmpCh, lastChar = '+';
    double tmpVar;
    double result = 0;
    while ((tmpCh = parseToNextValue(&tmpVar)) != '\0') {
        switch (tmpCh) {
            case '+':
            case '-':

        }
        lastChar = tmpCh;
    }
    return 0;
}

double plus(double var) {
    double tmpVar = 0;
    char tmpChar = parseToNextValue(&tmpVar);
    switch (tmpChar) {
        case '+':
            return plus(var + tmpVar);
        case '-':
            return minus(var + tmpVar);
        default:
            return var + calculateAndReturn(tmpChar, tmpVar);
    }
}

double minus(double var) {
    double tmpVar = 0;
    char tmpChar = parseToNextValue(&tmpVar);
    switch (tmpChar) {
        case '+':
            return plus(var - tmpVar);
        case '-':
            return minus(var - tmpVar);
        default:
            return var - calculateAndReturn(tmpChar, tmpVar);
    }
}

double multiple(double var) {
    double tmpVar = 0;
    char tmpChar = parseToNextValue(&tmpVar);
    switch (tmpChar) {
        case '+':
            return plus(var * tmpVar);
        case '-':
            return minus(var * tmpVar);
        case '*':
            return multiple(var * tmpVar);
        case '/':
        case '\\':
            return devided(var * tmpVar);
        default:
            return var * calculateAndReturn(tmpChar, tmpVar);
    }
}

double devided(double var) {
    double tmpVar = 0;
    char tmpChar = parseToNextValue(&tmpVar);
    switch (tmpChar) {
        case '+':
            return plus(var / tmpVar);
        case '-':
            return minus(var / tmpVar);
        case '*':
            return multiple(var / tmpVar);
        case '/':
        case '\\':
            return devided(var / tmpVar);
        default:
            return var / calculateAndReturn(tmpChar, tmpVar);
    }
}

double highPrior(double var) {
    double tmpVar = 0, tmpVar2 = 0;
    char tmpCh = parseToNextValue(&tmpVar);
    tmpVar = calculateAndReturn(parseToNextValue(&tmpVar2), calculateAndReturn(tmpCh, tmpVar));
    if (tmpVar2 != 0)
        has_error = true;
    return tmpVar;
}

double calculateAndReturn(char operationCode, double result, double var) {
    switch (operationCode) {
        case '+':
            return var + resultc;
        case '-':
            return minus(var);
        case '*':
            return multiple(var);
        case '\\':
        case '/':
            return devided(var);
        case '(':
            return highPrior(var);
        case ')':
            return var;
        default:
            return var;
    }
}

char parseToNextValue(double *value) {
    char wordBuffer[BUFFERSIZE], tmpChar;
    int thisPos = 0;
    bool pointExist = false;

    while (read(STDIN_FILENO, &tmpChar, 1) > 0) {
        if (tmpChar >= '0' && tmpChar <= '9')
            wordBuffer[thisPos++] = tmpChar;
        else if (tmpChar == '.') {
            if (pointExist) {
                has_error = true; //Возможна только одна точка
                return 0;
            }
            wordBuffer[thisPos++] = tmpChar;
            pointExist = true;
        } else {
            wordBuffer[thisPos] = '\0';
            sscanf(wordBuffer, "%lf", value);
            return tmpChar;
        }
    }
    return 0;
}

