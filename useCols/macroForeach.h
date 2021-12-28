/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 *
 * https://habr.com/ru/post/584392/
 */

#ifndef __MACRO_FOREACH_H__
#define __MACRO_FOREACH_H__

#include "macroTools.h"

// SQ - Sequence
// IUC21 - inner using cols 2021
// UC - using cols

#define IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_APPLY(FN, NAME, P0) IUC21_UNWRAP(SPL)

#define IUC21_SQ_1(SPL, FN, P0, NAME, ...) IUC21_APPLY(FN, NAME, P0)

#define IUC21_SQ_2(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_1(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_3(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_2(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_4(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_3(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_5(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_4(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_6(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_5(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_7(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_6(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_8(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_7(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_9(SPL, FN, P0, NAME, ...) \
    IUC21_APPLY_SPL(FN, NAME, P0, SPL) IUC21_REPACK(IUC21_SQ_8(SPL, FN, P0, __VA_ARGS__))

#define IUC21_SQ_NUM(N, SPL, FN, P0, ...) \
    IUC21_REPACK(IUC21_CAT(IUC21_SQ_,N)(SPL, FN, P0, __VA_ARGS__))

#define IUC21_APPLY(FN, NAME, P0) FN(NAME, IUC21_UNWRAP(P0))

#define IUC21_SQ_HELPER(SPL, FN, P0, ...) \
    IUC21_SQ_NUM(IUC21_CNT_ARGS(__VA_ARGS__), SPL, FN, P0, __VA_ARGS__)

//*************************************************************

#define UC_JOIN(SPL, FN, P0, ...) \
    IUC21_SQ_HELPER(IUC21_FIXWRAP(SPL), FN, IUC21_FIXWRAP(P0), __VA_ARGS__)

#define UC_FOREACH(FN, P0, ...) \
    IUC21_SQ_HELPER(IUC21_FIXWRAP(), FN, IUC21_FIXWRAP(P0), __VA_ARGS__)


#endif
