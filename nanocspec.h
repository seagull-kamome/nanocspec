/** @file nanospec.h 
 * Header file of nanospec.
 * \copyright BSD3
 * \author Hattori, Hiroki
 *
 * Copyright (c) 2018, Hattori, Hiroki all rights reserved
 * This softiware is licensed under BSD3.
 * 
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#if defined(NANOCSPEC_CUSTOM_STDIO)
#  if !defined(nanospec_printf)
#    include "nanospec_user_stdio.h"
#  endif
#else
#  include <stdio.h>
#  define nanospec_printf         printf
#endif



#define describe(name, title) \
  void nanospec_describe_##name##_run(void) { \
    ++nanospec_num_describe; \
    unsigned int nanospec_tmp_failed_tests = nanospec_num_failed_tests; \
    nanospec_printf("\n## %u.%s\n\n", nanospec_num_describe, title); \
    do { \
      __label__ __nanospec_end_it; \
      int const nanospec_it_fail_count = -1;


#define end_it          \
    if (nanospec_it_fail_count == 0) { nanospec_printf(" ... [success]\n"); } \
    __nanospec_end_it: __attribute__((unused)); \
    if (nanospec_it_fail_count > 0) { ++nanospec_num_failed_tests; nanospec_printf("\n\n    %u assertions are failed\n\n", nanospec_it_fail_count); } \
  } while (0);


#define it(title)       \
  end_it \
  do { \
    __label__ __nanospec_end_it; \
    int nanospec_it_fail_count = 0; \
    ++nanospec_num_tests; \
    nanospec_printf("- it %s", title);


#define end_describe    \
    end_it \
    if (nanospec_tmp_failed_tests != nanospec_num_failed_tests) \
      ++nanospec_num_failed_describe; \
  }


#define skip_it(reason) \
  do { \
    nanospec_printf(" ... [skipped because %s]\n", reason); \
    goto __nanospec_end_it; \
  } while(0)


#define run_spec(name) \
  do { \
    extern void nanospec_describe_##name##_run(void); \
    nanospec_describe_##name##_run(); \
  } while(0)
#define print_test_report() ({ \
    nanospec_printf("\n\ntotal: %d/%d test suites failed, %d/%d tests failed. %d/%d assersions failed.\n", \
        nanospec_num_failed_describe, nanospec_num_describe, \
        nanospec_num_failed_tests, nanospec_num_tests, \
        nanospec_num_failed_assertions, nanospec_num_assertions );\
    (nanospec_num_failed_assertions == 0)? 0 : 1; \
    })




#if defined(NANOCSPEC_MAIN)

unsigned int nanospec_num_describe = 0;
unsigned int nanospec_num_failed_describe = 0;
unsigned int nanospec_num_tests = 0;
unsigned int nanospec_num_failed_tests = 0;
unsigned int nanospec_num_assertions = 0;
unsigned int nanospec_num_failed_assertions = 0;

#  define nanospec_make_failure_handler(typ, name, fmt, afmt) \
  void nanospec_failure_##name( \
      char const* const lvl, \
      char const* const file, unsigned int const lineno, \
      char const* const op, typ const expect, typ const actual) { \
  ++nanospec_num_failed_assertions; \
    nanospec_printf("\n    - %s. expected " fmt "(" afmt ") with '%s', but actual is " fmt "(" afmt "). in file %s line %d.", \
      lvl, expect, expect, op, actual, actual, file, lineno); \
  }

void nanospec_failure_bool(
    char const* const lvl,
    char const* const file, unsigned int const lineno,
    bool const expect) {
  ++nanospec_num_failed_assertions;
  nanospec_printf("\n    - %s. expected %s, but actual is not. in file %s line %d.",
      lvl, expect?"true":"false", file, lineno);
}

#else

extern unsigned int nanospec_num_describe;
extern unsigned int nanospec_num_failed_describe;
extern unsigned int nanospec_num_tests;
extern unsigned int nanospec_num_failed_tests;
extern unsigned int nanospec_num_assertions;
extern unsigned int nanospec_num_failed_assertions;


#  define nanospec_make_failure_handler(typ, name, fmt, afmt) \
  extern void nanospec_failure_##name( \
      char const* lvl, \
      char const* file, unsigned int lineno, \
      char const* op, typ expect, typ actual);

void nanospec_failure_bool(
    char const* const lvl,
    char const* const file, unsigned int const lineno,
    bool const expect);

#endif


nanospec_make_failure_handler(char, char, "%d", "0x%x")
nanospec_make_failure_handler(unsigned char, uchar, "%u", "0x%x")
nanospec_make_failure_handler(short, short, "%d", "0x%x")
nanospec_make_failure_handler(unsigned short, ushort, "%u", "0x%x")
nanospec_make_failure_handler(int, int, "%d", "0x%x")
nanospec_make_failure_handler(unsigned int, uint, "%u", "0x%x")
nanospec_make_failure_handler(long int, lint, "%ld", "0x%lx")
nanospec_make_failure_handler(unsigned long, ulint, "%lu", "0x%lx")
nanospec_make_failure_handler(long long int, llint, "%lld", "0x%llx")
nanospec_make_failure_handler(unsigned long long, ullint, "%llu", "0x%llx")
nanospec_make_failure_handler(void*, ptr, "%p", "0x%p")


#define nanospec_fail(lvl, name, typ, op, expect, actual) \
  nanospec_failure_##name(lvl, __FILE__, __LINE__, #op, (typ)(uintptr_t)(expect), (typ)(uintptr_t)(actual))


#define nanospec_compare(lvl, op, expect, actual, onfail) \
  do { typeof(expect) const __expect = (expect); \
       typeof(actual) const __actual = (actual); \
     /* _Static_assert(_Generic((__actual), typeof(__expect):1), "actual value has no same type with expected value."); */ \
     ++nanospec_num_assertions; \
     if (! (__expect op __actual)) { \
       ++nanospec_it_fail_count; \
       _Generic((__actual) \
           , char: nanospec_fail(lvl, char, char, op, __expect, __actual) \
           , unsigned char: nanospec_fail(lvl, uchar, unsigned char, op, __expect, __actual) \
           , short: nanospec_fail(lvl, short, short, op, __expect, __actual) \
           , unsigned short: nanospec_fail(lvl, ushort, unsigned short, op, __expect, __actual) \
           , int: nanospec_fail(lvl, int, int, op, __expect, __actual) \
           , unsigned int: nanospec_fail(lvl, uint, unsigned int, op, __expect, __actual) \
           , long int: nanospec_fail(lvl, lint, long int, op, __expect, __actual) \
           , unsigned long int: nanospec_fail(lvl, ulint, unsigned long int, op, __expect, __actual) \
           , long long int: nanospec_fail(lvl, llint, long long int, op, __expect, __actual) \
           , unsigned long long int: nanospec_fail(lvl, ullint, unsigned long long int, op, __expect, __actual) \
           /* , long int: nanospec_failure_int32_t(lvl, __FILE__, __LINE__, #op, __expect, __actual) \
           , unsigned long int: nanospec_failure_uint32_t(lvl, __FILE__, __LINE__, #op, __expect, __actual) */ \
           , bool: nanospec_failure_bool(lvl, __FILE__, __LINE__, (((bool)__expect op true)?true:false)) \
           , default: nanospec_fail(lvl, ptr, void*, op, __expect, __actual) \
           ); \
       onfail; \
     } \
  } while (0)

#define nanospec_compare_bool(lvl, expect, actual, onfail) \
  do { \
    bool const __actual = (actual); \
    bool const __expect = (expect); \
    ++nanospec_num_assertions; \
    if (__expect != __actual) { \
      ++nanospec_it_fail_count; \
      nanospec_failure_bool(lvl, __FILE__, __LINE__, __expect); \
      onfail; \
    } \
  } while(0)


#define should_eq(expect, actual)       nanospec_compare("fail", ==, expect, actual, )
#define should_ne(expect, actual)       nanospec_compare("fail", !=, expect, actual, )
#define should_gt(expect, actual)       nanospec_compare("fail", <, expect, actual, )
#define should_ge(expect, actual)       nanospec_compare("fail", <=, expect, actual, )
#define should_lt(expect, actual)       nanospec_compare("fail", >, expect, actual, )
#define should_le(expect, actual)       nanospec_compare("fail", >=, expect, actual, )

#define should_true(actual)             nanospec_compare_bool("fail", true, actual,)
#define should_false(actual)            nanospec_compare_bool("fail", false, actual,)


#define assert_eq(expect, actual)       nanospec_compare("fatal", ==, expect, actual, goto __nanospec_end_it)
#define assert_ne(expect, actual)       nanospec_compare("fatal", !=, expect, actual, goto __nanospec_end_it)
#define assert_gt(expect, actual)       nanospec_compare("fatal", <, expect, actual, goto __nanospec_end_it)
#define assert_ge(expect, actual)       nanospec_compare("fatal", <=, expect, actual, goto __nanospec_end_it)
#define assert_lt(expect, actual)       nanospec_compare("fatal", >, expect, actual, goto __nanospec_end_it)
#define assert_le(expect, actual)       nanospec_compare("fatal", >=, expect, actual, goto __nanospec_end_it)

#define assert_true(actual)             nanospec_comapre_bool("fatal", true, goto __nanospec_end_it)
#define assert_false(actual)            nanospec_compare_bool("fatal", false, goto __nanospec_end_it)



