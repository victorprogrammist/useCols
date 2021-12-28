/*
 * Author Telnov Victor, v-telnov@yandex.ru
 * This code under licence GPL3
 *
 * https://habr.com/ru/post/584392/
 */

#ifndef __USE_COLS_H__
#define __USE_COLS_H__

namespace UseCols {

// создает лямбду для доступа к полям элемента
//  для передачи в параметр getFields,
//  пример использования: membersAccessor(&Row::field1, &Row::field2)
template<typename... Ts>
auto membersAccessor(Ts... members);

// Сортирует список по указанным колонкам по возрастанию значений.
template <class T, class F>
void sort(T& collection, const F& getFields);

// Так же сортирует, но по убыванию значений.
template <class T, class F>
void sortDesc(T& collection, const F& getFields);

//Рассчитывает сумму по каждой колонке из getFields в отдельности.
template <class T, class F>
auto sum(const T& collection, const F& getFields);

// Возвращает итератор указывающий на элемент с максимальным значением.
// Максимальное значение по всему компаунду от getFields.
// В случае пустой collection возвращает итератор end().

template <class T, class F>
auto maxItem(T& collection, const F& getFields);

template <class T, class F>
auto minItem(T& collection, const F& getFields);

// Возвращает максимальные/минимальные значения по указанным колонкам.
// Возвращаемый тип std::pair<auto,bool>,
// где second bool равен ложь, если пустая коллекция.
// (хотя если будете смотреть в коде, то там просто auto, но он pair)

template <class T, class F>
auto minValue(T& collection, const F& getFields);

template <class T, class F>
auto maxValue(T& collection, const F& getFields);

// В случае, если заведомо известно, что коллекция
// не пустая, можно использовать maxValue2/minValue2,
// которая возвращает непосредственно максимальные/минимальные
// значения без std::pair

template <class T, class F>
auto minValue2(T& collection, const F& getFields);

template <class T, class F>
auto maxValue2(T& collection, const F& getFields);

// Находит элемент по значению колонок,
// и возвращает на него итератор, из предположения
// что список отсортирован по этим колонкам по возрастанию.
template <class T, class F, class ...V>
auto findSorted(const T& collection, const F& getFields, const V&... value);

// Находит элемент по значению колонок простым перебором,
// и возвращает на него итератор,
// находит первый элемент соответствующий отбору.
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

