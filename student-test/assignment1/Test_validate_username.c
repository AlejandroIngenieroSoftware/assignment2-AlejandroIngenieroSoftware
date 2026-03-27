#include <stdio.h>
#include <string.h>
#include "unity.h"

extern int validate_username(const char *username);

void test_valid_username(void)

void test_validate_my_username()
{
    TEST_ASSERT_EQUAL(1, validate_username("AlejandroIngenieroSoftware"));
}

void test_invalid_username_empty(void)
{
    TEST_ASSERT_EQUAL(0, validate_username(""));
}

void test_invalid_username_spaces(void)
{
    TEST_ASSERT_EQUAL(0, validate_username("juan 123"));
}

void test_invalid_username_special_chars(void)
{
    TEST_ASSERT_EQUAL(0, validate_username("juan@123"));
}


