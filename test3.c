#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint32_t sign;      // 符号
    uint32_t exponent;  // 指数
    uint32_t fraction;  // 仮数
    char fraction_b[25]; // 仮数部を2進数表現の文字列にして格納
    char **split_list; // 整数部分と小数部分で分割したリストを格納
    int  intpart;
    int  decpart;
} FloatParts;

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


void extract_float_parts(float num, FloatParts *parts) {
    uint32_t mem;
    memcpy(&mem, &num, sizeof(float));

    // 符号（1ビット）
    parts->sign = (mem >> 31) & 0x1;

    // 指数（8ビット）
    parts->exponent = (mem >> 23) & 0xFF;

    // 仮数（23ビット）
    parts->fraction = mem & 0x7FFFFF;

    // 仮数部を2進数表現の文字列にして格納
    parts->fraction_b[0] = '1'; // 先頭に1を追加

    for (int i = 0; i < 23; i++) {
        parts->fraction_b[i + 1] = ((parts->fraction >> (22 - i)) & 0x1) + '0';
    }
    parts->fraction_b[24] = '\0'; // null-terminator を追加

    int exponent = parts->exponent - 126;

    // 仮数部の分割
    parts->split_list = split_string(parts->fraction_b, exponent);
    printf("1: %s\n", parts->split_list[0]);
    printf("2: %s\n", parts->split_list[1]);

    // 整数部分と小数部分の計算
    parts->intpart = strtol(parts->split_list[0], NULL, 2);
    parts->decpart = strtol(parts->split_list[1], NULL, 2);
}

void put_float(FloatParts parts)
{
    printf("%d.%d", parts.intpart, parts.decpart);
}

int main() {
    float num = 30.23f;
    FloatParts parts;
    extract_float_parts(num, &parts);

    printf("Sign: %u\n", parts.sign);
    printf("Exponent: %u\n", parts.exponent);
    printf("Fraction: %u\n", parts.fraction);
    printf("Binary Fraction: %s\n", parts.fraction_b);
    printf("Integer Part: %d\n", parts.intpart);
    printf("Decimal Part: %d\n", parts.decpart);

    printf("Restored value: ");
    put_float(parts);
    printf("\n");

    return 0;
}
