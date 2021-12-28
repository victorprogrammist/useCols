/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 *
 * https://habr.com/ru/post/584392/
 */

#ifndef __MACRO_FLD_H__
#define __MACRO_FLD_H__

#include "macroTools.h"
#include "macroForeach.h"

#define IUC21_CLM_HELPER_1(X) UC_FIELD(X)

#define IUC21_CLM_HELPER_0__FIELD(X,DUMMY) UseCols::Helpers::asReference(it).X

#define IUC21_CLM_HELPER_0__DECLTYPE_REMOVE_CVREF(X) \
    typename std::remove_cv< \
    typename std::remove_reference< \
        decltype(UseCols::Helpers::asReference(it).X)>::type>::type

#define IUC21_CLM_HELPER_0__DECLTYPE_WITH_REFERENCE(X,DUMMY) \
    const IUC21_CLM_HELPER_0__DECLTYPE_REMOVE_CVREF(X)&

#define IUC21_CLM_HELPER_0__TYPE_WITH_REFERENCE(...) \
        std::tuple<UC_JOIN(IUC21_COMMA, IUC21_CLM_HELPER_0__DECLTYPE_WITH_REFERENCE, ~, __VA_ARGS__)>

#define IUC21_CLM_HELPER_0(...) \
        [](const auto& it) -> IUC21_CLM_HELPER_0__TYPE_WITH_REFERENCE(__VA_ARGS__) { \
            return IUC21_CLM_HELPER_0__TYPE_WITH_REFERENCE(__VA_ARGS__)( \
                UC_JOIN(IUC21_COMMA, IUC21_CLM_HELPER_0__FIELD, ~, __VA_ARGS__) \
            ); \
        }

#define IUC21_CLM_HELPER_BOOL(ONLY_ONE, ...) \
        IUC21_CAT(IUC21_CLM_HELPER_,ONLY_ONE)(__VA_ARGS__)


#define UC_FIELD(X) [](const auto& it) -> const auto& { \
    return UseCols::Helpers::asReference(it).X; }

#define UC_COLUMNS(...) IUC21_CLM_HELPER_BOOL( \
        IUC21_ONLY_ONE_ARG(__VA_ARGS__), __VA_ARGS__)


#endif // __MACRO_FLD_H__

