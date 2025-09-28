#include "example.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_add) {
    ck_assert_int_eq(add(2, 3), 5);
    ck_assert_int_eq(add(-1, 1), 0);
    ck_assert_int_eq(add(0, 0), 0);
}
END_TEST

START_TEST(test_multiply) {
    ck_assert_int_eq(multiply(2, 3), 6);
    ck_assert_int_eq(multiply(-1, 1), -1);
    ck_assert_int_eq(multiply(0, 5), 0);
}
END_TEST

START_TEST(test_get_greeting) {
    const char *greeting = get_greeting();
    ck_assert_ptr_nonnull(greeting);
    ck_assert_str_eq(greeting, "Hello from C project template!");
}
END_TEST

Suite *example_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Example");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_multiply);
    tcase_add_test(tc_core, test_get_greeting);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = example_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}