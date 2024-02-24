#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

void append(ListNode **listp, int value) {
    ListNode *current = *listp;
    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;
    if (current == NULL) {
        *listp = new_node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

typedef struct s_arginf {
    ListNode *flag;
    char format;
    int wid;
    int prec;
} s_arginf;

int is_legal(char *arg) {
    size_t i = 0;
    while (arg[i] == '-' || arg[i] == '0' || arg[i] == '#' || arg[i] == '+') {
        i++;
    }
    while (isdigit(arg[i])) {
        i++;
    }
    if (arg[i] == '.') {
        i++;
        while (isdigit(arg[i])) {
            i++;
        }
    }
    if (strchr("diouxXfFeEgGaAcspn", arg[i]) == NULL) {
        return FALSE;
    }
    return TRUE;
}

void parse_option(char *arg, s_arginf *s_arg) {
    size_t i = 0;
    while (arg[i] == '-' || arg[i] == '0' || arg[i] == '#' || arg[i] == '+') {
        append(&(s_arg->flag), arg[i]);
        i++;
    }
    s_arg->format = arg[i];
    s_arg->wid = 0; // 初期化
    s_arg->prec = 0; // 初期化
    while (isdigit(arg[i])) {
        s_arg->wid = s_arg->wid * 10 + (arg[i] - '0');
        i++;
    }
    if (arg[i] == '.') {
        i++;
        while (isdigit(arg[i])) {
            s_arg->prec = s_arg->prec * 10 + (arg[i] - '0');
            i++;
        }
    }
	if (strchr("diouxXfFeEgGaAcspn", arg[i]))
		s_arg->format = arg[i];
}

s_arginf parse_arg(char *arg) {
    s_arginf s_arg;
    s_arg.flag = NULL; // 初期化
    size_t i = 0;
    while (arg[i]) {
        if (arg[i] == '%') {
            i++;
            if (is_legal(&arg[i])) {
                parse_option(&arg[i], &s_arg);
            }
        }
        i++;
    }

    return s_arg;
}

int main(void) {
    char *format_string = "%-10.5d";
    s_arginf parsed_arg = parse_arg(format_string);
    printf("Format: %c, Width: %d, Precision: %d\n", parsed_arg.format, parsed_arg.wid, parsed_arg.prec);

    // フラグの出力
    ListNode *current_flag = parsed_arg.flag;
    printf("Flags: ");
    while (current_flag != NULL) {
        printf("%c ", current_flag->value);
        current_flag = current_flag->next;
    }
    printf("\n");

    // 解放
    while (parsed_arg.flag != NULL) {
        ListNode *temp = parsed_arg.flag;
        parsed_arg.flag = parsed_arg.flag->next;
        free(temp);
    }

    return 0;
}
