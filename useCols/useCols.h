
#ifndef __USE_COLS_H__
#define __USE_COLS_H__

namespace UseCols {

template <class T, class F>
void sort(T& collection, const F& getFields);

template <class T, class F>
void sortDesc(T& collection, const F& getFields);

template <class T, class F>
auto sum(const T& collection, const F& getFields);

template <class T, class F>
auto maxItem(T& collection, const F& getFields);

template <class T, class F>
auto minItem(T& collection, const F& getFields);

template <class T, class F>
auto minValue(T& collection, const F& getFields);

template <class T, class F>
auto maxValue(T& collection, const F& getFields);

template <class T, class F>
auto minValue2(T& collection, const F& getFields);

template <class T, class F>
auto maxValue2(T& collection, const F& getFields);

template <class T, class F, class ...V>
auto findSorted(const T& collection, const F& getFields, const V&... value);

template <class T, class F, class ...V>
auto findFirst(const T& collection, const F& getFields, const V&... value);

template <class T, class F>
auto groups(T& list, const F& getFields);

template <class Itr>
class Range;

template <class Itr, class F>
class Groups;

}

#include "ranges.h"
#include "useCols_impl.h"
#include "macroColumns.h"

#endif

