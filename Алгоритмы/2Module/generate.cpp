#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <ctime>

bool readBit(int flags, int num);

int readFlags(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    int flags = readFlags(argc, argv);

    srand(time(NULL));
    unsigned int maxValue = (unsigned int) std::pow((long double) 10, 9); // Максимальное значение элемента
    unsigned int maxSizeDataset = (unsigned int) (std::pow((long double) 10, 7) * 2.5); // Максимальный размер массива
    unsigned int arraySize = maxSizeDataset;
    if (!readBit(flags, 0))
        arraySize = (unsigned int) abs(rand() % maxSizeDataset);
    arraySize = arraySize - arraySize % 10; // Размер массива должен быть кратен 10

    if (readBit(flags, 2)) {
        int randVar = abs(rand() % maxValue);
        for (unsigned int i = 0; i < arraySize; i++) {
            printf("%d ", randVar);
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
                printf("%d ", abs(rand() % maxValue));
            else
                for (unsigned int j = 0; j < maxCountVar && i < arraySize; i++) {
                    if (abs(rand() % 100) < chanceForVar * 100) {
                        j++;
                        printf("%d ", randVar);
                    } else printf("%d ", abs(rand() % maxValue));
                }
        }
    } else {
        for (unsigned int i = 0; i < arraySize; i++) {
            printf("%d ", abs(rand() % maxValue));
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


int readFlags(int argc, char *argv[]) {
    int flags = 0;
    //Дефолтные значения
    writeBit(flags, true, 3);

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
            }
        }
    }
    return flags;
}

bool readBit(int flags, int num) {
    return ((flags >> num) & 1) > 0;
}