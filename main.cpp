
#include "useCols/useCols.h"

#include <vector>
#include <iostream>

template <class T>
void operator += (std::vector<T>& list, const T& value) {
    list.push_back(value);
}

int main(int argc, char *argv[])
{

    struct Row {
      int field1 = 0;
      int field2 = 0;
      double qty = 0;
      double sum = 0;
    };

    std::vector<Row> table1;

    table1 += Row{2,3,1,10};
    table1 += Row{2,3,2,11};
    table1 += Row{1,1,2,2};
    table1 += Row{1,1,3,4};
    table1 += Row{4,5,3,9};
    table1 += Row{1,0,9,8};
    table1 += Row{1,6,9,3};

    auto funcOut = [&](const std::string& msg) {
        std::cout << "====================================" << std::endl;
        std::cout << "vector<Row> " << msg << std::endl;
        std::cout << "field1, field2, qty, sum" << std::endl;
        for (const Row& row: table1)
            std::cout << row.field1 << ", " << row.field2 << ", "
            << row.qty << ", " << row.sum << std::endl;
    };

    //******************************************************
    UseCols::sort(table1, FIELD(sum));
    funcOut("sort by: Row::sum");

    UseCols::sort(table1, COLUMNS(field1,field2));
    funcOut("sort by: Row::field1,Row::field2");

    std::cout << "====================================" << std::endl;
    auto itr1 = UseCols::findSorted(table1, COLUMNS(field1,field2), 2, 3);
    std::cout << "vector<Row>, findSorted: field1, field2 == {2,3}" << std::endl;
    std::cout << "qty, sum => [" << itr1->qty << ", " << itr1->sum << "]" << std::endl;

    auto itr2 = UseCols::findSorted(table1, COLUMNS(field1), 4);
    std::cout << "vector<Row>, findSorted: field1 == 4" << std::endl;
    std::cout << "qty, sum => [" << itr2->qty << ", " << itr2->sum << "]" << std::endl;

    //******************************************************
    std::vector<const Row*> table2;
    for (const Row& row: table1)
        table2 += &row;

    UseCols::sort(table2, COLUMNS(field2,field1));

    std::cout << "====================================" << std::endl;
    std::cout << "vector<const Row*>, sort: field2, field1" << std::endl;
    std::cout << "field1, field2, qty, sum" << std::endl;
    for (const Row* row: table2)
        std::cout << row->field1 << ", " << row->field2 << ", "
        << row->qty << ", " << row->sum << std::endl;

    //******************************************************

    std::cout << "====================================" << std::endl;
    std::cout << "sum by column sum: " << UseCols::sum(table2, FIELD(sum)) << std::endl;

    auto [suQty, suSum] = UseCols::sum(table2, COLUMNS(qty,sum));
    std::cout << "simultaneously sums of [qty, sum]: " << suQty << ", " << suSum << std::endl;

    std::cout << "====================================" << std::endl;

    auto maxRow = UseCols::maxItem(table1, COLUMNS(qty,sum));

    std::cout << "row with max qty & sum: " << maxRow->qty << ", " << maxRow->sum << std::endl;

    std::cout << "====================================" << std::endl;

    auto [maQty, maSum] = UseCols::maxValue2(table2, COLUMNS(qty,sum));
    std::cout << "maximum values qty & sum: " << maQty << ", " << maSum << std::endl;

    auto [miQty, miSum] = UseCols::minValue2(table2, COLUMNS(qty,sum));
    std::cout << "minimum values qty & sum: " << miQty << ", " << miSum << std::endl;

    //******************************************************
    std::cout << "====================================" << std::endl;
    std::cout << "GROUPS by field1" << std::endl;

    UseCols::sort(table1, FIELD(field1));
    for (auto& range: UseCols::groups(table1, FIELD(field1))) {

        auto [suQty,suSum] = UseCols::sum(range, COLUMNS(qty,sum));

        std::cout
        << "value of group's field: " << range->field1
        << ", count rows: " << range.size()
        << ", sum of qty & sum: " << suQty << ", " << suSum
        << std::endl;

        UseCols::sort(range, COLUMNS(qty,sum));

        for (const Row& row: range)
            std::cout << " == row: field2, qty, sum: "
            << row.field2 << ", " << row.qty << ", " << row.sum << std::endl;

        UseCols::sort(range, FIELD(field2));
        for (auto& r2: UseCols::groups(range, FIELD(field2)))
            std::cout << " ==== group lev2: field2, sum(qty), sum(sum): "
            << r2->field2
            << ", " << UseCols::sum(r2, FIELD(qty))
            << ", " << UseCols::sum(r2, FIELD(sum))
            << std::endl;
    }

    std::cout << "====================================" << std::endl;
    std::cout << "GROUPS by field1, field2" << std::endl;

    auto g12 = COLUMNS(field1,field2);
    UseCols::sort(table1, g12);

    for (const auto& range: UseCols::groups(table1, g12)) {

        auto [suQty,suSum] = UseCols::sum(range, COLUMNS(qty,sum));

        std::cout
        << "value of group's fields: " << range->field1 << ", " << range->field2
        << ", count rows: " << range.size()
        << ", sum of qty & sum: " << suQty << ", " << suSum
        << std::endl;

        for (const auto& row: range)
            std::cout
            << " == qty, sum: "
            << row.qty << ", " << row.sum
            << std::endl;
    }

    return 0;
}

