/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 */

#ifndef __MACRO_FLD_H__
#define __MACRO_FLD_H__

#include "macroTools.h"
#include "macroForeach.h"

namespace UseCols {
namespace Helpers {

template <class T>
const T& asReference(const T* p) { return *p; }

template <class T>
const T& asReference(T* p) { return *p; }

template <class T>
const T& asReference(const T& p) { return p; }

template <class T>
const T& asReference(T& p) { return p; }

}}

#define FIELD(X) [](const auto& it) -> const auto& { \
    return UseCols::Helpers::asReference(it).X; }

#define COLS_HELPER_1(X) FIELD(X)

#define COLS_HELPER_0__FIELD(X,DUMMY) UseCols::Helpers::asReference(it).X

#define COLS_HELPER_0__DECLTYPE_REMOVE_CVREF(X) \
    typename std::remove_cv< \
    typename std::remove_reference< \
        decltype(UseCols::Helpers::asReference(it).X)>::type>::type

#define COLS_HELPER_0__DECLTYPE_WITH_REFERENCE(X,DUMMY) \
    const COLS_HELPER_0__DECLTYPE_REMOVE_CVREF(X)&

#define COLS_HELPER_0__TYPE_WITH_REFERENCE(...) \
        std::tuple<JOIN(COMMA, COLS_HELPER_0__DECLTYPE_WITH_REFERENCE, ~, __VA_ARGS__)>

#define COLS_HELPER_0(...) \
        [](const auto& it) -> COLS_HELPER_0__TYPE_WITH_REFERENCE(__VA_ARGS__) { \
            return COLS_HELPER_0__TYPE_WITH_REFERENCE(__VA_ARGS__)( \
                JOIN(COMMA, COLS_HELPER_0__FIELD, ~, __VA_ARGS__) \
            ); \
        }

#define COLS_HELPER_BOOL(ONLY_ONE, ...) \
        CAT(COLS_HELPER_,ONLY_ONE)(__VA_ARGS__)

#define COLUMNS(...) COLS_HELPER_BOOL( \
        ONLY_ONE_ARG(__VA_ARGS__), __VA_ARGS__)

#endif // __MACRO_FLD_H__

