
#ifndef __MACRO_FOREACH_H__
#define __MACRO_FOREACH_H__

#include "macroTools.h"

#define APPLY_SPL(FN, NAME, P0, SPL) APPLY(FN, NAME, P0) UNWRAP(SPL)

#define SEQ_1(SPL, FN, P0, NAME, ...) APPLY(FN, NAME, P0)
#define SEQ_2(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_1(SPL, FN, P0, __VA_ARGS__))
#define SEQ_3(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_2(SPL, FN, P0, __VA_ARGS__))
#define SEQ_4(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_3(SPL, FN, P0, __VA_ARGS__))
#define SEQ_5(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_4(SPL, FN, P0, __VA_ARGS__))
#define SEQ_6(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_5(SPL, FN, P0, __VA_ARGS__))
#define SEQ_7(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_6(SPL, FN, P0, __VA_ARGS__))
#define SEQ_8(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_7(SPL, FN, P0, __VA_ARGS__))
#define SEQ_9(SPL, FN, P0, NAME, ...) APPLY_SPL(FN, NAME, P0, SPL) REPACK(SEQ_8(SPL, FN, P0, __VA_ARGS__))

#define SEQ_NUM(N, SPL, FN, P0, ...) REPACK(CAT(SEQ_,N)(SPL, FN, P0, __VA_ARGS__))

#define APPLY(FN, NAME, P0) FN(NAME, UNWRAP(P0))

#define SEQ_HELPER(SPL, FN, P0, ...) \
    SEQ_NUM(CNT_ARGS(__VA_ARGS__), SPL, FN, P0, __VA_ARGS__)

//*************************************************************

#define JOIN(SPL, FN, P0, ...) SEQ_HELPER(FIXWRAP(SPL), FN, FIXWRAP(P0), __VA_ARGS__)
#define FOREACH(FN, P0, ...)   SEQ_HELPER(FIXWRAP(), FN, FIXWRAP(P0), __VA_ARGS__)

//*************************************************************
#define MULTI_HELPER(NAME,FN,...) FN(NAME, __VA_ARGS__)
#define MULTI(NAME,P0) MULTI_HELPER(NAME, P0)

// sample of using
// #define USE(NAME,OP,B) int NAME OP B
// JOIN(;, MULTI, REPACK(USE,=,5), A, B, C);

//*************************************************************

#endif
