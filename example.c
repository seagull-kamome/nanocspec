
#define NANOCSPEC_MAIN
#include "./nanocspec.h"

describe(basic, "basic functions")

  it("success with integer.")
    should_eq(1, 1);
    should_eq(-1, -1);

    should_eq(10l, 10l);
    should_eq(-10l, -10l);

    should_eq(100ll, 100ll);
    should_eq(-100ll, -100ll);

    should_gt(1, 2);
    should_ge(1, 2);
    should_lt(2, 1);
    should_le(2, 2);

    assert_eq(1, 1);
    assert_eq(-1, -1);

    assert_eq(10l, 10l);
    assert_eq(-10l, -10l);

    assert_eq(100ll, 100ll);
    assert_eq(-100ll, -100ll);

    assert_gt(1, 2);
    assert_ge(1, 2);
    assert_lt(2, 1);
    assert_le(2, 2);


  it("fail with integer.")
    should_eq(1, 2);
    should_eq(-1, 3);

    should_eq(10l, 19l);
    should_eq(-10l, -12l);

    should_eq(100ll, 101ll);
    should_eq(-100ll, -109ll);

    assert_eq(1, 2);
    assert_eq(2, 3); // never reachs here

  it("success with boolean")
    should_eq(true, true);
    should_eq(false, false);
    should_ne(false, true);
    should_ne(true, false);

    should_true(true);
    should_false(false);

  it("fail with boolean")
    should_ne(true, true);
    should_ne(false, false);
    should_eq(false, true);
    should_eq(true, false);

    should_true(false);
    should_false(true);

  it("one liner") should_eq(1, 1);
  it("able to skip")
    skip_it("God helps me");
  it("one line skip") skip_it("I'm feeling lucky");
end_describe


int main(int argc, char* argv[]) {
  run_spec(basic);
  run_spec(basic);
  return print_test_report();
}

