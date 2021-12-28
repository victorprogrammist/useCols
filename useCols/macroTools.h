/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 *
 * https://habr.com/ru/post/584392/
 */

#ifndef __MACRO_TOOLS_H__
#define __MACRO_TOOLS_H__

#define IUC21_COMMA ,

// IUC21 - inner using cols, 2021

#define IUC21_REPACK(...) __VA_ARGS__

#define IUC21_FIXWRAP(...) (__VA_ARGS__)

#define IUC21_UNWRAP_HELPER(...) __VA_ARGS__

#define IUC21_UNWRAP(X) IUC21_REPACK(IUC21_REPACK(IUC21_UNWRAP_HELPER)X)

#define IUC21_CAT(A,B) A##B

#define IUC21_CNT_ARGS_HELPER_2( \
    _1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19, n, ...) n

#define IUC21_CNT_ARGS_HELPER_1(...) IUC21_REPACK(IUC21_CNT_ARGS_HELPER_2(__VA_ARGS__))

#define IUC21_CNT_ARGS(...) \
    IUC21_CNT_ARGS_HELPER_1(__VA_ARGS__, \
    19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)

#define IUC21_ONLY_ONE_ARG(...) \
    IUC21_CNT_ARGS_HELPER_1(__VA_ARGS__, \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)

#endif


