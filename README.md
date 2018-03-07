# nanospec
xSpec style simple test tool for C. (single header, embedded system)


## How to install

Copy nanospec.h into your test code.

## How to run example

    $ ${CC} -Wall example.c && ./a.out
    
    ## 1.basic functions

    - it success with integer. ... [success]
    - it fail with integer.
        - fail. expected 1(0x1) with '==', but actual is 2(0x2). in file example.c line 39.
        - fail. expected -1(0xffffffff) with '==', but actual is 3(0x3). in file example.c line 40.
        - fail. expected 10(0xa) with '==', but actual is 19(0x13). in file example.c line 42.
        - fail. expected -10(0xfffffffffffffff6) with '==', but actual is -12(0xfffffffffffffff4). in file example.c line 43.
        - fail. expected 100(0x64) with '==', but actual is 101(0x65). in file example.c line 45.
        - fail. expected -100(0xffffffffffffff9c) with '==', but actual is -109(0xffffffffffffff93). in file example.c line 46.
        - fatal. expected 1(0x1) with '==', but actual is 2(0x2). in file example.c line 48.
    
        7 assertions are failed
    
    - it success with boolean ... [success]
    - it fail with boolean
        - fail. expected 1(0x1) with '!=', but actual is 1(0x1). in file example.c line 63.
        - fail. expected 0(0x0) with '!=', but actual is 0(0x0). in file example.c line 64.
        - fail. expected 0(0x0) with '==', but actual is 1(0x1). in file example.c line 65.
        - fail. expected 1(0x1) with '==', but actual is 0(0x0). in file example.c line 66.
        - fail. expected true, but actual is not. in file example.c line 68.
        - fail. expected false, but actual is not. in file example.c line 69.
    
        6 assertions are failed
    
    - it one liner ... [success]
    - it able to skip ... [skipped because God helps me]
    - it one line skip ... [skipped because I'm feeling lucky]
    
    ## 2.basic functions
    
    - it success with integer. ... [success]
    - it fail with integer.
        - fail. expected 1(0x1) with '==', but actual is 2(0x2). in file example.c line 39.
        - fail. expected -1(0xffffffff) with '==', but actual is 3(0x3). in file example.c line 40.
        - fail. expected 10(0xa) with '==', but actual is 19(0x13). in file example.c line 42.
        - fail. expected -10(0xfffffffffffffff6) with '==', but actual is -12(0xfffffffffffffff4). in file example.c line 43.
        - fail. expected 100(0x64) with '==', but actual is 101(0x65). in file example.c line 45.
        - fail. expected -100(0xffffffffffffff9c) with '==', but actual is -109(0xffffffffffffff93). in file example.c line 46.
        - fatal. expected 1(0x1) with '==', but actual is 2(0x2). in file example.c line 48.
    
        7 assertions are failed
    
    - it success with boolean ... [success]
    - it fail with boolean
        - fail. expected 1(0x1) with '!=', but actual is 1(0x1). in file example.c line 63.
        - fail. expected 0(0x0) with '!=', but actual is 0(0x0). in file example.c line 64.
        - fail. expected 0(0x0) with '==', but actual is 1(0x1). in file example.c line 65.
        - fail. expected 1(0x1) with '==', but actual is 0(0x0). in file example.c line 66.
        - fail. expected true, but actual is not. in file example.c line 68.
        - fail. expected false, but actual is not. in file example.c line 69.
    
        6 assertions are failed
    
    - it one liner ... [success]
    - it able to skip ... [skipped because God helps me]
    - it one line skip ... [skipped because I'm feeling lucky]



