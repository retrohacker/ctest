#include "test.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int equal(test *t, char* type, char *msg, ...) {
  // Log message
  va_list args;
  va_start(args, msg);
  int pass;
  if(strcmp(type, "%d") == 0) {
    pass = va_arg(args, int) == va_arg(args, int);
  } else if(strcmp(type, "%zd") == 0) {
    pass = va_arg(args, int) == va_arg(args, size_t);
  } else if(strcmp(type, "%s") == 0) {
    pass = strcmp(va_arg(args, char *), va_arg(args, char *)) == 0;
  } else {
    printf("Unsupported type %s for \"%s\"\n", type, msg);
    return 0;
  }
  va_end(args);
  if(pass) {
    printf("  [ OK ] - ");
  } else {
    printf("  [FAIL] - ");
    (*t).state = FAIL;
  }
  va_start(args, msg);
  vprintf(msg, args);
  va_end(args);
  printf("\n");
  return pass;
}

int ok(test *t, char*type, char *msg, ...) {
  va_list args;
  va_start(args, msg);
  int pass;
  if(strcmp(type, "%d") == 0) {
    pass = va_arg(args, int);
  } else {
    printf("Unsupported type %s for \"%s\"\n", type, msg);
    return 0;
  }
  va_end(args);
  if(pass) {
    printf("  [ OK ] - ");
  } else {
    printf("  [FAIL] - ");
    (*t).state = FAIL;
  }
  va_start(args, msg);
  vprintf(msg, args);
  va_end(args);
  printf("\n");
  return pass;
}

// Get the process exit status based on this test's status
int done(test *t) {
  test_state state = (*t).state;
  free(t);
  if(state == PASS) {
    return 0;
  } else {
    return 1;
  }
}

test* new_test(char *name) {
  printf("# %s\n", name);
  test *t = malloc(sizeof(test));
  (*t).state = PASS;
  return t;
}
