#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <ctime>

bool readBit(int flags, int num);

int readFlags(int argc, char *argv[], unsigned int &arraySize);

unsigned int decimalBuffer[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
                                  1000000000}; // Чтобы не высчитывать каждый раз степень десятки
int tmpChar[16] = {0};

void inline printVar(int var) {
    int pos = 0;
    while (var != 0) {
        tmpChar[pos++] = var % 10 + '0';
        var /= 10;
    }
    for (; pos != 0;)
        putchar_unlocked(tmpChar[--pos]);
    putchar_unlocked(' ');
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    unsigned int maxValue = (unsigned int) std::pow((long double) 10, 9); // Максимальное значение элемента
    unsigned int maxSizeDataset = (unsigned int) (std::pow((long double) 10, 7) * 2.5); // Максимальный размер массива
    unsigned int arraySize = 0;
    int flags = readFlags(argc, argv, arraySize);
    if (arraySize == 0)
        if (!readBit(flags, 0))
            arraySize = (unsigned int) abs(rand() % maxSizeDataset);
        else arraySize = maxSizeDataset;
    arraySize = arraySize - arraySize % 10; // Размер массива должен быть кратен 10

    if (readBit(flags, 2)) {
        int randVar = abs(rand() % maxValue);
        for (unsigned int i = 0; i < arraySize; i++) {
            printVar(randVar);
        }
    } else if (readBit(flags, 1)) {
        double chanceForVar = 0.9;
        unsigned int maxCountVar = (unsigned int) (arraySize * chanceForVar);
        int randVar = abs(rand() % maxValue);
        int startPos = 0;

        if (!readBit(flags, 3)) {
            startPos = abs(rand() % (arraySize - maxCountVar));
            chanceForVar = 1;
        }

        for (unsigned int i = 0; i < arraySize; i++) {
            if (i != startPos)
                printVar(abs(rand() % maxValue));
            else
                for (unsigned int j = 0; j < maxCountVar && i < arraySize; i++) {
                    if (abs(rand() % 100) < chanceForVar * 100) {
                        j++;
                        printVar(randVar);
                    } else printVar(abs(rand() % maxValue));
                }
        }
    } else {
        for (unsigned int i = 0; i < arraySize; i++) {
            printVar(abs(rand() % maxValue));
        }
    }

    return 0;
}

void writeBit(int &flags, bool bit, int num) {
    char tmpval = 1;
    tmpval = (tmpval << num); // устанавливаем нужный бит в единицу
    flags = (flags & (~1)); // сбрасываем в 0 нужный бит

    if (bit) { // если бит требуется установить в 1
        flags = (flags | (tmpval)); // то устанавливаем нужный бит в 1
    }
}


int readFlags(int argc, char *argv[], unsigned int &arraySize) {
    int flags = 0;
    //Дефолтные значения
    writeBit(flags, true, 3);
    arraySize = 0;

    if (argc > 1) {
        for (int argNumber = 1; argNumber < argc; argNumber++) {
            if (argv[argNumber][0] == '-') {
                for (int i = 0; argv[argNumber][i] != '\0'; i++) {
                    int numBit = -1;
                    switch (argv[argNumber][i]) {
                        case 'm': // Выходной массив максимально возможной длинны
                            numBit = 0;
                            break;
                        case 'e': // С вероятностью 90% в ячейке будет определенное значение
                            numBit = 1;
                            break;
                        case 'E': // Все значения одинаковые
                            numBit = 2;
                            break;
                        case 'r': // Одинаковые значения идут подряд или нет
                            numBit = 3;
                            break;
                        default:
                            printf("Флаг %c не найден", argv[argNumber][i]);
                            //Nothing
                    }
                    if (numBit > -1) {
                        if (i > 0 && argv[argNumber][i - 1] == 'n') // Флаг n перед нужным флагом инвертирует его
                            writeBit(flags, false, numBit);
                        else
                            writeBit(flags, true, numBit);
                    }
                }
            } else {
                long long tmp = atoll(argv[argNumber]);
                arraySize = (unsigned int) tmp;
            }
        }
    }
    return flags;
}

bool readBit(int flags, int num) {
    return ((flags >> num) & 1) > 0;
}