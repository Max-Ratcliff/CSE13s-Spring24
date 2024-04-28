#include "hangman_helpers.h"

int main(void) {
    printf("testing helper functions\n");
    printf("testing read letter expect the letter you enter\n");
    char test1 = read_letter();
    printf("%c\n", test1);

    printf("testing string contains, expect: 1 and 0\n");
    bool test2 = string_contains_character("I am lolol", 'a');
    bool test3 = string_contains_character("I am lolol", 'b');
    printf("%d\n", test2);
    printf("%d\n", test3);

    printf("testing is lowercase expect: 0 and 1\n");
    bool test4 = is_lowercase_letter('A');
    bool test5 = is_lowercase_letter('a');
    printf("%d\n", test4);
    printf("%d\n", test5);

    printf("testing is valid secret, expect: 1 and 0\n");
    bool test6 = is_valid_secret("the quick brown fox's jump over the lazy-dogs");
    bool test7 = is_valid_secret("the*quick$brow# fox's jump over the lazy-dogs");
    printf("%d\n", test6);
    printf("%d\n", test7);

    return 0;
}
