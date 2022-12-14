#include "TestMacros.h"

const char *tuuvm_test_currentTestSuiteName;
const char *tuuvm_test_currentTestCaseName;
int tuuvm_test_currentHasError;
int tuuvm_test_runCount;
int tuuvm_test_errorCount;

tuuvm_context_t *tuuvm_test_context;

TEST_SUITE_FIXTURE_INITIALIZE(TuuvmCore)
{
    tuuvm_test_context = tuuvm_context_create();
}

TEST_SUITE_FIXTURE_SHUTDOWN(TuuvmCore)
{
    tuuvm_context_destroy(tuuvm_test_context);
}

#define TEST_SUITE_NAME(name) DECLARE_TEST_SUITE(name);
#include "TestSuites.inc"
#undef TEST_SUITE_NAME


int main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

#define TEST_SUITE_NAME(name) RUN_TEST_SUITE(name);
#include "TestSuites.inc"
#undef TEST_SUITE_NAME

    if(tuuvm_test_errorCount)
        printf("Run %d tests. Errors: %d\n", tuuvm_test_runCount, tuuvm_test_errorCount);
    else
        printf("Run %d tests. All tests passed.\n", tuuvm_test_runCount);

    return tuuvm_test_errorCount > 0 ? 1 : 0;
}
