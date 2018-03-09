#ifndef TEST_HEADER
#define TEST_HEADER
enum test_state_t { PASS, FAIL };
typedef enum test_state_t test_state;
typedef struct {
  test_state state;
} test;
test* new_test(char *name);
int equal(test *t, char *type, char *msg, ...);
int ok(test *t, char*type, char *msg, ...);
int done(test *t);
#endif
