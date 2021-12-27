/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 *
 * https://habr.com/ru/post/584392/
 */

#ifndef __USE_COLS_RANGES_H__
#define __USE_COLS_RANGES_H__

#include <cassert>
#include <utility>
#include <cstddef>

namespace UseCols {

template <class Itr>
class Range {
public:

    using iterator = Itr;
    using value_type = typename iterator::value_type;
    using const_value_type = const typename std::remove_const<value_type>::type;

    Range() {}
    Range(const Itr& be, const Itr& en) : m_begin(be), m_end(en) {}

    template <class T>
    Range(T& list) : m_begin(list.begin()), m_end(list.end()) {}

    bool operator==(const Range& o) const { return m_begin == o.m_begin && m_end == o.m_end; }
    bool operator!=(const Range& o) const { return !(*this == o); }

    bool empty() const { return begin() == end(); }
    size_t size() const { return end() - begin(); }

    iterator begin() const { return m_begin; }
    iterator end() const { return m_end; }

    iterator begin() { return m_begin; }
    iterator end() { return m_end; }

    value_type& first() { assert(!empty()); return *begin(); }
    value_type& last() { assert(!empty()); return *--end(); }
    value_type* operator->() { return &first(); }

    const_value_type& first() const { assert(!empty()); return *begin(); }
    const_value_type& last() const { assert(!empty()); return *--end(); }
    const_value_type* operator->() const { return &first(); }

private:
    Itr m_begin = {};
    Itr m_end = {};
};

template <class Itr, class F>
class Groups {
public:

    using Rng = Range<Itr>;
    using value_type = Rng;

    template <class T>
    Groups(T& list, const F& fn) : range(list), getFields(fn) {}

    struct iterator {
        using value_type = typename Rng::value_type;

        iterator(const Groups &ow, const Rng &rg)
            : owner(&ow), range(rg) {}

        bool operator==(const iterator&o) const { return range == o.range; }
        bool operator!=(const iterator&o) const { return range != o.range; }
        const Rng &operator*() const { return range; }
        void operator++() { range = owner->rangeNext(range); }

    private:
        const Groups *owner = nullptr;
        Rng range;
    };

    iterator begin() const { return iterator(*this, rangeBegin()); }
    iterator end() const { return iterator(*this, rangeEnd()); }

    size_t countGroups() const {

        size_t r = 0;

        Itr itr = range.begin();
        for (; itr != range.end(); itr = findNextGroup(itr))
            ++r;

        return r;
    }

private:

    const Rng range;
    const F getFields;

    Rng rangeEnd() const { return Rng(range.end(), range.end()); }

    Rng rangeBegin() const {
        if (range.empty()) return rangeEnd();
        return Rng(range.begin(), findNextGroup(range.begin()));
    }

    Rng rangeNext(const Rng &rg) const {
        if (rg.empty()) return rangeEnd();
        return Rng(rg.end(), findNextGroup(rg.end()));
    }

    Itr findNextGroup(const Itr& itr) const {

        if (itr == range.end())
            return itr;

        Itr res = itr;
        do {
            ++res;
        } while (res != range.end() && getFields(*itr) == getFields(*res) );

        return res;
    }
};

}

#endif // ALG_RANGES_H


