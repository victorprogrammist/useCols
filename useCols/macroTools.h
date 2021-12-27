
#ifndef __MACRO_TOOLS_H__
#define __MACRO_TOOLS_H__

#define COMMA ,

#define XSTR(...) STR(__VA_ARGS__)
#define STR(...) #__VA_ARGS__

#define REPACK(...) __VA_ARGS__

#define FIXWRAP(...) (__VA_ARGS__)

#define UNWRAP_HELPER(...) __VA_ARGS__

#define UNWRAP(X) REPACK(REPACK(UNWRAP_HELPER)X)

#define CAT(A,B) A##B

#define CNT_ARGS_HELPER_2( \
    _1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19, n, ...) n

#define CNT_ARGS_HELPER_1(...) REPACK(CNT_ARGS_HELPER_2(__VA_ARGS__))

#define CNT_ARGS(...) \
    CNT_ARGS_HELPER_1(__VA_ARGS__, \
    19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)

#define ONLY_ONE_ARG(...) \
    CNT_ARGS_HELPER_1(__VA_ARGS__, \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)

#endif


