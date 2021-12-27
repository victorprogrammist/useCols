
#ifndef __USE_COLS_IMPL_H__
#define __USE_COLS_IMPL_H__

#include <utility>
#include <algorithm>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace UseCols {

namespace Helper_remove_cvref {

    template <class T>
    using my_remove_cvref = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

    template <typename ...T>
    constexpr auto decay_types_helper(std::tuple<T...>)
        -> std::tuple<my_remove_cvref<T>...>;

    template <typename T>
    constexpr auto decay_types_helper(T)
        -> my_remove_cvref<T>;

    template <typename T>
    using decay_types = decltype(decay_types_helper(std::declval<T>()));
}

namespace Helper_append {

    template <typename T1, typename T2>
    const T1& append(T1& res, const T2& other) {
        res += other;
        return res;
    }

    template<typename T1, typename T2, size_t... Is>
    const auto& append_seq(T1& res, const T2& other, const std::integer_sequence<size_t, Is...>&) {
        auto l = { (std::get<Is>(res) += std::get<Is>(other), 0)... };
        (void)l;
        return res;
    }

    template <typename ...T1, typename ...T2>
    void append(std::tuple<T1...>& res, const std::tuple<T2...>& other) {
        append_seq(res, other, std::index_sequence_for<T1...>());
    }
}

namespace Helper_setMinMax {

    template <typename T1, typename T2>
    const T1& setMinMax(T1& res, bool asMax, const T2& other) {
        if (asMax && res < other) res = other;
        else
            if (!asMax && other < res) res = other;
        return res;
    }

    template<typename T1, typename T2, size_t... Is>
    void setMinMax_seq(T1& res, bool asMax, const T2& other, std::integer_sequence<size_t, Is...>) {

        auto l = { (setMinMax(std::get<Is>(res), asMax, std::get<Is>(other)), 0)... };
        (void)l;
    }

    template <typename ...T1, typename ...T2>
    const auto& setMinMax(std::tuple<T1...>& res, bool asMax, const std::tuple<T2...>& other) {
        setMinMax_seq(res, asMax, other, std::index_sequence_for<T1...>());
        return res;
    }
}


template <class T, class F>
void sort(T& collection, const F& getFields) {

    auto compare =
        [&getFields](const auto& r1, const auto& r2) -> bool {
            return getFields(r1) < getFields(r2);
    };

    std::sort(collection.begin(), collection.end(), compare);
}

template <class T, class F>
void sortDesc(T& collection, const F& getFields) {

    auto compare =
        [&getFields](const auto& r1, const auto& r2) -> bool {
            return getFields(r2) < getFields(r1);
    };

    std::sort(collection.begin(), collection.end(), compare);
}

template <class T, class F>
auto sum(const T& collection, const F& getFields) {

    Helper_remove_cvref::decay_types<decltype(getFields(*collection.begin()))>
        res = {};

    for (const auto& v: collection)
        Helper_append::append(res, getFields(v));

    return res;
}

template <class T, class F>
auto minMaxItem(T& collection, bool asMax, const F& getFields) {

    auto itr = collection.begin();
    auto en = collection.end();
    auto result = itr;

    if (itr == en)
        return result;

    Helper_remove_cvref::decay_types<decltype(getFields(*collection.begin()))>
        maxValue = getFields(*itr);

    ++itr;

    for (; itr != en; ++itr) {
        auto v = getFields(*itr);

        if (asMax && !(maxValue < v)) continue;
        else
            if (!asMax && !(v < maxValue)) continue;

        maxValue = v;
        result = itr;
    }

    return result;
}

template <class T, class F>
auto maxItem(T& collection, const F& getFields) {
    return minMaxItem(collection, true, getFields);
}

template <class T, class F>
auto minItem(T& collection, const F& getFields) {
    return minMaxItem(collection, false, getFields);
}

template <class T, class F>
auto minMaxValue(T& collection, bool asMax, const F& getFields) {

    auto itr = collection.begin();
    auto en = collection.end();

    std::pair<
        Helper_remove_cvref::decay_types<decltype(getFields(*collection.begin()))>,
        bool>
            resultValue = {{},false};

    if (itr == en)
        return resultValue;

    resultValue.second = true;
    resultValue.first = getFields(*itr);
    ++itr;

    for (; itr != en; ++itr)
        Helper_setMinMax::setMinMax(resultValue.first, asMax, getFields(*itr));

    return resultValue;
}

template <class T, class F>
auto minValue(T& collection, const F& getFields) {
    return minMaxValue(collection, false, getFields);
}

template <class T, class F>
auto maxValue(T& collection, const F& getFields) {
    return minMaxValue(collection, true, getFields);
}

template <class T, class F>
auto minValue2(T& collection, const F& getFields) {
    return minValue(collection, getFields).first;
}

template <class T, class F>
auto maxValue2(T& collection, const F& getFields) {
    return maxValue(collection, getFields).first;
}

template <class T, class F, class ...V>
auto findSorted(const T& collection, const F& getFields, const V&... value) {

    Helper_remove_cvref::decay_types<decltype(getFields(*collection.begin()))>
        compareValue = {value...};

    auto res =
    std::lower_bound(
        collection.begin(), collection.end(),
        compareValue, [&](const auto& it, const auto& val) -> bool {
            return getFields(it) < val; });

    if (res == collection.end() || getFields(*res) != compareValue)
        return collection.end();

    return res;
}

template <class T, class F, class ...V>
auto findFirst(const T& collection, const F& getFields, const V&... value) {

    Helper_remove_cvref::decay_types<decltype(getFields(*collection.begin()))>
        compareValue = {value...};

    auto itr = collection.begin();
    auto en = collection.end();

    for (; itr != en; ++itr)
        if (getFields(*itr) == compareValue)
            break;

    return itr;
}

template <class Itr, class F>
class Groups;

template <class T, class F>
auto groups(T& list, const F& getFields) {
    using Itr = decltype(list.begin());
    return Groups<Itr,F>(list, getFields);
}

}

#endif

