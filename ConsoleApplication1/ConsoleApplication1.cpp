#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define MAX_SIZE 100
void initialize_matrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols, int random) {
    srand(time(0));
    int kuzma;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (random) {
                matrix[i][j] = rand() % 100 - 20;
            }
            else {
                do {
                    printf("Введите элемент [%d][%d]: ", i, j);
                    kuzma = scanf_s("%d", &matrix[i][j]);
                    if (kuzma != 1) {
                        printf("Введите правельное заначение");
                        while (getchar() != '\n');
                    }
                } while (kuzma != 1);
            }
        }
    }
}
void print_matrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int count_duplicates(const int* row, int length) {
    int counts[201] = { 0 };
    for (int i = 0; i < length; i++) {
        if (row[i] >= -100 && row[i] <= 100) {
            counts[row[i] + 100]++;
        }
    }
    int duplicates = 0;
    for (int i = 0; i < 201; i++) {
        if (counts[i] > 1) {
            duplicates += counts[i] - 1;
        }
    }
    return duplicates;
}
void swap_rows(int matrix[MAX_SIZE][MAX_SIZE], int row1, int row2, int cols) {
    for (int i = 0; i < cols; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}
void bubble_sort_rows(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (count_duplicates(matrix[j], cols) > count_duplicates(matrix[j + 1], cols)) {
                swap_rows(matrix, j, j + 1, cols);
            }
        }
    }
}

int find_first_non_negative_column(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int col = 0; col < cols; col++) {
        int has_negative = 0;
        for (int row = 0; row < rows; row++) {
            if (matrix[row][col] < 0) {
                has_negative = 1;
                break;
            }
        }
        if (!has_negative) {
            return col;
        }
    }
    return -1;
}

int has_zero(int* row, int length) {
    for (int i = 0; i < length; i++) {
        if (row[i] == 0) {
            return 1;
        }
    }
    return 0;

}
void task3(int matrix[MAX_SIZE][MAX_SIZE], int n, int m) {
    int random, pop;
    do {
        printf("Инициализировать матрицу случайными значениями? (1 - Да, 0 - Нет): ");
        pop = scanf_s("%d", &random);
        if (pop != 1 || (random != 1 && random != 0)) {
            printf("Неправильно введено значение. Введите 1 или 0.\n");
            while (getchar() != '\n');
        }
        else {
            initialize_matrix(matrix, n, m, random);
        }
    } while (pop != 1 || (random != 1 && random != 0));

    printf("Матрица до обработки:\n");
    print_matrix(matrix, n, m);

    int sum = 0;
    for (int i = n / 2; i < n; i++) {
        for (int j = n / 2; j < n; j++) {
            sum += matrix[i][j];
        }
    }
    printf("Сумма в 4 блоке равна %d\n", sum);
}
void replace_negative(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < 0) {
                matrix[i][j] = 0;
            }
        }
    }
}

void task2(int n, int m, int matrix[MAX_SIZE][MAX_SIZE])
{
    int random, pop; do {
        printf("Инициализировать матрицу случайными значениями? (1 - Да, 0 - Нет): ");
        pop = scanf_s("%d", &random);
        if (pop != 1 || (random != 1 && random != 0)) {
            printf("Неправильно введено значение. Введите 1 или 0.\n");
            while (getchar() != '\n');
        }
        else { initialize_matrix(matrix, n, m, random); }
    } while (pop != 1 || (random != 1 && random != 0));
    printf("Матрица до обработки:\n");
    print_matrix(matrix, n, m); int all_rows_have_zero = 1;
    for (int i = 0; i < n; i++)
    {
        if (!has_zero(matrix[i], m)) { all_rows_have_zero = 0; break; }
    } if (!all_rows_have_zero) {
        replace_negative(matrix, n, m);
    }
    printf("Матрица после обработки:\n");
    print_matrix(matrix, n, m);
}
void zadanie1(int n, int m, int matrix[MAX_SIZE][MAX_SIZE]) {
    int random;
    printf("Инициализировать матрицу случайными значениями? (1 - Да, 0 - Нет): ");
    scanf_s("%d", &random);
    initialize_matrix(matrix, n, m, random);
    printf("Матрица до сортировки:\n");
    print_matrix(matrix, n, m);
    bubble_sort_rows(matrix, n, m);
    printf("Матрица после сортировки:\n");
    print_matrix(matrix, n, m);
    int first_non_negative_column = find_first_non_negative_column(matrix, n, m);
    if (first_non_negative_column != -1) {
        printf("Первый столбец без отрицательных элементов: %d\n", first_non_negative_column);
    }
    else {
        printf("Все столбцы содержат отрицательные элементы.\n");
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    int number_the_task, task_support;
    int choice_exit, exit;
    int matrix[MAX_SIZE][MAX_SIZE];
    int task3_size;
    int n, m;
    printf(" Лабораторную выполнил ЕФлаков Д.Д: \n");

    do {
        do {
            printf("Выберите номер задания (всего 3 задания) ");
            task_support = scanf_s("%d", &number_the_task);
            if (task_support != 1 || number_the_task > 3 || number_the_task < 1) {
                printf("Неправильно введено значение. Введите значение из 1, 2, 3\n");
                while (getchar() != '\n');
            }
        } while (task_support != 1 || number_the_task > 3 || number_the_task < 1);

        if (number_the_task == 3) {
            do {
                printf("Введите размер квадратной матрицы (только 1 значение): ");
                task3_size = scanf_s("%d", &n);
                if (task3_size != 1 || n <= 0 || n > 100) {
                    printf("Неправильно введено значение. Введите значение от 1 до 100\n");
                    while (getchar() != '\n');
                }
            } while (task3_size != 1 || n <= 0 || n > 100);
            m = n;
            task3(matrix, n, m);
        }

        if (number_the_task == 2) {
            int ohol;
            do {
                printf("Проверить, все ли строки матрицы содержат хотя бы один нулевой элемент.\n Если нет, то заменить значения всех отрицательных элементов матрицы на нулевые.\n");
                printf("Введите количество строк (не более 100) и количество столбцов: ");
                ohol = scanf_s("%d%d", &n, &m);
                if (ohol != 2 || n > 100 || n <= 0 || m > 100 || m <= 0) {
                    printf("Неправильно введено значение. Введите значение от 1 до 100\n");
                    while (getchar() != '\n');
                }
            } while (ohol != 2 || n > 100 || n <= 0 || m > 100 || m <= 0);
            initialize_matrix(matrix, n, m, 1);
            task2(n, m, matrix);
        }

        if (number_the_task == 1) {
            int hoh;
            do {
                printf("Упорядочить строки целочисленной прямоугольной матрицы по возрастанию количества \n одинаковых элементов в каждой строке. Найти номер первого из столбцов,\n несодержащих ни одного отрицательного элемента.\n");
                printf("Введите количество строк (не более 100) и количество столбцов: ");
                hoh = scanf_s("%d%d", &n, &m);
                if (hoh != 2 || n > 100 || n <= 0 || m > 100 || m <= 0) {
                    printf("Неправильно введено значение. Введите значение от 1 до 100\n");
                    while (getchar() != '\n');
                }
            } while (hoh != 2 || n > 100 || n <= 0 || m > 100 || m <= 0);
            zadanie1(n, m, matrix);
        }

        do {
            printf("Хотите продолжить?\n");
            printf("Нажмите 1 чтобы продолжить\n");
            printf("Нажмите 0 чтобы выйти\n");
            exit = scanf("%d", &choice_exit);
            if (exit != 1) {
                while (getchar() != '\n');
                printf("Неправильно введен элемент массива\n");
            }
        } while (choice_exit != 1 && choice_exit != 0);

        if (choice_exit == 0) {
            printf("Конец\n");
            return 0;
        }
    } while (choice_exit == 1);

    return 0;
}