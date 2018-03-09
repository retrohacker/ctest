# Installation

```sh
git submodule git@github.com:retrohacker/ctest deps/ctest
```

This should automatically work with the following SConstruct setup:

```sh
env = Environment()
deps = Glob("./deps/*")
SConscript(dirs=deps)

env.Append(CPPPATH=deps)
env.Append(LIBPATH=deps)
env.Append(LIBS=[
  "ctest"
])
```

# Quick Start

```c
#include <ctest.h>

int test1() {
  test *t = new_test("Foobar: should do a thing");
  equal(t, "%s", "Expect to log '%s' and saw '%s'", "c", "c");
  equal(t, "%s", "Expected to log '%s' and saw '%s'", "c", "d");
  return done(t);
}

int test2() {
  test *t = new_test("Foobar: should do a different thing");
  equal(t, "%d", "Expect '%d' === '%d'", 5, 5);
  equal(t, "%d", "Expect '%d' === '%d'", 5, 6);
  return done(t);
}

int main() {
  return test1() | test2();
}
```

Output:

```
# Foobar: should do a thing
  [ OK ] - Expected to see 'c' and saw 'c'
  [FAIL] - Expected to see 'c' and saw 'd'
# Foobar: should do a different thing
  [ OK ] - Expected to see 5 and saw 5
  [FAIL] - Expected to see 5 and saw 6
```

The status of the process will be non-zero if anything fails.

# Usage

### `new_test(char *name)`

Create a new test, will print `name` to stdout as a title.

### `equal(test *t, char* type, char *msg, arg1, arg2)`

Assert that `arg1` is equal to `arg2`

* `test *t` - The test that this assertion belongs to
* `char* type` - The printf type belonging to the data passed in
* `char* msg` - Printed to stdout with the test
* `arg1` and `arg2` - The values to compare

Supported types: `%d`, `%zd`, `%s`

### `ok(test *t, char* type, char *msg, arg1)`

Assert that `arg1` is "truthy" (not equal to 0)

* `test *t` - The test that this assertion belongs to
* `char* type` - The printf type belonging to the data passed in
* `char* msg` - Printed to stdout with the test
* `arg1` - The value to compare against

Supported types: `%d`
