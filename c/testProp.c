/*************************************************************************
	> File Name: testProp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 26 Mar 2015 03:48:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define PROPERTY_VALUE_MAX  32

char model[PROPERTY_VALUE_MAX];

static void get_customized_exif_info(const int info_type, char prop_value[]) {
    const char *ret = "wangsijie";

    switch(info_type) {
        case 0:
             
            memcpy(prop_value, "wangsijie", sizeof("wangsijie"));
            break;
        case 1:

            break;
        default:
            break;
    }
}

static int test_static() {
    printf("%s\n",  "invoke test_static");
    return 1;
}

static char get_a_char() {
    printf("%s\n",  "invoke get_a_char");
    static int test;
    test = test_static();

    return 'a';
}

static void get_a_string(char a_string[]) {
    a_string[0] = 'a';
    a_string[1] = 'b';
    a_string[2] = 'c';
}

typedef struct test_struct_t {
    int int_value;
    char char_value;
    union {
        char *string;
        char c;
        float f;
    } data;
} test_struct;

test_struct ts = {
    10,
    'b',
    "big",
};

test_struct ts2;
//ts2.int_value = 1;
//ts2.char_value = get_a_char();

int main(int argc, char **argv) {
    char prop_value[PROPERTY_VALUE_MAX] = {0};
    printf("len = %d\n", strlen(model));
    printf("sizeof = %d\n", sizeof(model));

    get_customized_exif_info(0, model);
    printf("model = %s, len = %d\n", model, strlen(model));

    ts.char_value = get_a_char();

    char a_string[PROPERTY_VALUE_MAX] = {0};
    get_a_string(a_string);
    ts.data.string = a_string;
    //strcpy(ts.data.string, a_string);
    printf("%d : %c : %s\n", ts.int_value, ts.char_value, ts.data.string);

    get_a_char();
    get_a_char();
    get_a_char();
    get_a_char();
    get_a_char();
    get_a_char();

    return 0;
}
