#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <clocale>
using namespace std;

int main() {

    setlocale(LC_ALL, "Russian"); 

    printf("Введите номер теста (1–4): ");
    int test_number;
    if (scanf("%d", &test_number) != 1) {
        printf("Ошибка: некорректный ввод.\n");
        return 1;
    }
    if (test_number < 1 || test_number > 4) {
        printf("Ошибка: номер должен быть от 1 до 4.\n");
        return 1;
    }

   
    char filename[50];
    sprintf(filename, "test_%d.txt", test_number);

    const int MAX_WORDS = 50;
    const int MAX_LEN = 25;
    char words[MAX_WORDS][MAX_LEN + 1];
    int n = 0;

    FILE* fin = fopen(filename, "r");
    if (!fin) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 1;
    }

    // Чтение слов из файла
    while (fscanf(fin, "%25s", words[n]) == 1) {
        n++;
        if (n >= MAX_WORDS) {
            printf("Предупреждение: превышено максимальное количество слов (50).\n");
            break;
        }
    }
    fclose(fin);

    // количество коренных слов
    int count[MAX_WORDS] = { 0 };
    int important_idx = -1;
    int max_cnt = 0;
    int longest_idx = -1;
    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        int len_i = strlen(words[i]);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (strncmp(words[j], words[i], len_i) == 0) {
                count[i]++;
            }
        }
        if (count[i] > max_cnt) {
            max_cnt = count[i];
            important_idx = i;
        }
        if (count[i] > 0) {
            int len = strlen(words[i]);
            if (len > max_len) {
                max_len = len;
                longest_idx = i;
            }
        }

    }

   
    FILE* fout1 = fopen("longest.txt", "w");
    if (fout1) {
        if (longest_idx != -1) {
            fprintf(fout1, "%s\n", words[longest_idx]);
            int len_long = strlen(words[longest_idx]);
            for (int j = 0; j < n; ++j) {
                if (j == longest_idx) continue;
                if (strncmp(words[j], words[longest_idx], len_long) == 0) {
                    fprintf(fout1, "%s\n", words[j]);
                }
            }
        }
        else {
            fprintf(fout1, "NO\n");
        }
        fclose(fout1);
    }

    
    FILE* fout2 = fopen("most_important.txt", "w");
    if (fout2) {
        if (important_idx != -1 && max_cnt > 0) {
            fprintf(fout2, "%s %d\n", words[important_idx], max_cnt);
        }
        else {
            fprintf(fout2, "NO\n");
        }
        fclose(fout2);
    }

    return 0;
}