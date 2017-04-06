#include <iostream>
#include <assert.h>
#include <climits>

#define BUFFER_SIZE 16

/**
 * Дана последовательность ​ N прямоугольников различной ширины и высоты (w ​ i​ ,h ​ i​ ). Прямоугольники
 * расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). Требуется найти ​ M -
 * площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой
 * фигуры.
 * Пример 1:
 * 4
 * 30 30
 * 10 40
 * 20 10
 * 10 40
 * Вывод:
 * 1200
 *
 * Пример 2:
 * 1
 * 1 3000
 * Вывод:
 * 3000
 *
 * Пример 3:
 * 3
 * 1 1
 * 1 3
 * 3 2
 * Вывод:
 * 8
 *
**/

struct Rectangle {
    int x;
    int y;

    Rectangle() : x(-1), y(-1) {};
} typedef Rectangle;

class Stack {
public:
    Stack() : bufferSize(BUFFER_SIZE), curIndex(0), count(0) {
        buffer = (Rectangle *) malloc(sizeof(Rectangle) * bufferSize);
    };

    bool IsEmpty() const { return count == 0; }

    void Push(Rectangle value) {
        if (count == bufferSize) {
            bufferSize += BUFFER_SIZE;
            realloc(buffer, sizeof(Rectangle) * bufferSize);
        }

        count++;
        buffer[curIndex++] = value;
    }

    Rectangle Pop() {
        assert(!IsEmpty());

        count--;
        return buffer[--curIndex];
    }

private:
    int curIndex = 0;
    int count = 0;
    int bufferSize = 0;

    Rectangle *buffer;
};

int getMaxArea(int size, Rectangle *array);

int main() {
    int sizeOne = -1;
    std::cin >> sizeOne;
    assert(sizeOne != -1);

    Rectangle *array = new Rectangle[sizeOne];
    for (int i = 0; i < sizeOne; i++) {
        std::cin >> array[i].x;
        std::cin >> array[i].y;
    }

    int result = getMaxArea(sizeOne, array);
    printf("%d", result);

    delete[] array;
    return 0;
}

int getMaxFromStack(Stack &stack, int level) {
    Rectangle tmpRectangle;
    int maxArea = 0;
    int height = INT_MAX;
    int width = 0;

    while (!stack.IsEmpty() && height >= level) {
        tmpRectangle = stack.Pop();
        if (height >= level) {
            if (tmpRectangle.y < height) {
                if (height * width > maxArea) {
                    maxArea = height * width;
                }
                height = tmpRectangle.y;
            }
            width += tmpRectangle.x;
        }
    }

    if (height < level)
        stack.Push(tmpRectangle);

    if (height * width > maxArea) {
        maxArea = height * width;
    }

    return maxArea;
}

int getMaxArea(int size, Rectangle *array) {
    Stack stack;
    int maxArea = 0;
    int tmp = 0;
    int lastHeight = 0;

    for (int i = 0; i < size; i++) {
        if (array[i].y < lastHeight) {
            tmp = getMaxFromStack(stack, array[i].y);
            maxArea = maxArea > tmp ? maxArea : tmp;
        }
        lastHeight = array[i].y;
        stack.Push(array[i]);
    }

    tmp = getMaxFromStack(stack, 0);
    maxArea = maxArea > tmp ? maxArea : tmp;

    return maxArea;
}