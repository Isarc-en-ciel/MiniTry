#include "unity.h"
#include "../inc/minishell.h"

t_shell *sh;

void setUp(void) {
    // Initialize shell structure before each test
    sh = (t_shell *)malloc(sizeof(t_shell));
    sh->exit_status = 0;
    sh->env = NULL;  // You'll need to set up environment variables as needed
}

void tearDown(void) {
    // Clean up after each test
    if (sh) {
        // Clean up environment if necessary
        free(sh);
    }
}

// Test basic word without expansion
void test_NoExpansion(void) {
    char *input = strdup("hello world");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("hello world", input);
    free(input);
}

// Test single dollar sign at end
void test_SingleDollarAtEnd(void) {
    char *input = strdup("hello$");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("hello$", input);
    free(input);
}

// Test double dollar signs
void test_DoubleDollar(void) {
    char *input = strdup("hello$$world");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("helloworld", input);  // $$ should be removed
    free(input);
}

// Test environment variable expansion
void test_EnvVarExpansion(void) {
    // Set up test environment
    char *env[] = {"USER=testuser", NULL};
    sh->env = env;
    
    char *input = strdup("Hello $USER!");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("Hello testuser!", input);
    free(input);
}

// Test exit status expansion
void test_ExitStatusExpansion(void) {
    sh->exit_status = 42;
    char *input = strdup("Exit status: $?");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("Exit status: 42", input);
    free(input);
}

// Test multiple expansions in one string
void test_MultipleExpansions(void) {
    sh->exit_status = 1;
    char *env[] = {"USER=testuser", "HOME=/home/testuser", NULL};
    sh->env = env;
    
    char *input = strdup("$USER's exit status was $? at $HOME");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("testuser's exit status was 1 at /home/testuser", input);
    free(input);
}

// Test undefined variable expansion
void test_UndefinedVariable(void) {
    char *input = strdup("$UNDEFINED_VAR");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("", input);  // Undefined variables should expand to empty string
    free(input);
}

// Test dollar sign with space
void test_DollarWithSpace(void) {
    char *input = strdup("hello $ world");
    int result = expand_var(sh, &input);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("hello $ world", input);
    free(input);
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_NoExpansion);
    RUN_TEST(test_SingleDollarAtEnd);
    RUN_TEST(test_DoubleDollar);
    RUN_TEST(test_EnvVarExpansion);
    RUN_TEST(test_ExitStatusExpansion);
    RUN_TEST(test_MultipleExpansions);
    RUN_TEST(test_UndefinedVariable);
    RUN_TEST(test_DollarWithSpace);
    
    return UNITY_END();
}
