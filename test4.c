#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(const char *str, int n) {
    char **list = malloc(2 * sizeof(char *));
    if (list == NULL) {
        return NULL; // メモリ割り当てエラー
    }

    // 上位 n 文字を格納するために必要なメモリを割り当て
    list[0] = malloc((n + 1) * sizeof(char));
    if (list[0] == NULL) {
        free(list);
        return NULL; // メモリ割り当てエラー
    }

    // 残りの文字列を格納するために必要なメモリを割り当て
    list[1] = malloc((strlen(str) - n + 1) * sizeof(char));
    if (list[1] == NULL) {
        free(list[0]);
        free(list);
        return NULL; // メモリ割り当てエラー
    }

    // 上位 n 文字をコピー
    strncpy(list[0], str, n);
    list[0][n] = '\0'; // null-terminator を追加

    // 残りの文字列をコピー
    strcpy(list[1], str + n);

    return list;
}

int main() {
    const char *str = "11100011101011100001010";
    int split_pos = 4;

    char **result = split_string(str, split_pos);
    if (result == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    printf("First part: %s\n", result[0]);
    printf("Second part: %s\n", result[1]);

    // メモリの解放
    free(result[0]);
    free(result[1]);
    free(result);

    return 0;
}
