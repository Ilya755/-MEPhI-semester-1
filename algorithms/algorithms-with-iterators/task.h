#include <cstdlib>
#include <iterator>
#include <vector>

using namespace std;

/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    for (; firstIn != lastIn; ++firstIn) {
        *firstOut = op(*firstIn);
        firstOut++;
    }
}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    BidirIt begin = first;
    for (; first != last; ++first) {
        if (p(*first)) {
            std::iter_swap(begin, first);
            begin++;
        }
    }
}

/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *firstOut = *first1;
            first1++;
            firstOut++;
        } else {
            *firstOut = *first2;
            first2++;
            firstOut++;
        }
    }
    while (first1 != last1) {
        *firstOut = *first1;
        first1++;
        firstOut++;
    }
    while (first2 != last2) {
        *firstOut = *first2;
        first2++;
        firstOut++;
    }
}

/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
private:
    vector<uint64_t> vec;

public:
    class Iterator {
        private:
            size_t pos;
            vector<uint64_t> vec;

        public:
            friend class FibonacciRange;
            using iterator_category = std::input_iterator_tag;
            using value_type = uint64_t;
            using difference_type = ptrdiff_t;
            using pointer = value_type*;
            using reference = value_type&;

            Iterator(size_t pos_, vector<uint64_t> vec_)
                : pos(pos_)
                , vec(vec_)
                {}

            value_type operator*() const {
                return vec[pos];
            }

            Iterator& operator++() {
                ++pos;
                return *this;
            }

            Iterator operator++(int) {
                Iterator cur = *this;
                ++(*this);
                return cur;
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

            bool operator==(const Iterator& other) const {
                return pos == other.pos;

            }

            bool operator<(const Iterator& rhs) const {
                if (this->pos >= rhs.pos) {
                    return false;
                } else {
                    return true;
                }
            }

            Iterator& operator=(const Iterator& rhs){
                pos = rhs.pos;
                return *this;
            }
        };

        FibonacciRange(vector<uint64_t> vec_)
            : vec(vec_)
            {}

        FibonacciRange(size_t amount) {
            if (amount == 0) {
                return;
            } else if (amount == 1) {
                vec.push_back(1);
            } else if (amount >= 2) {
                vec.push_back(1);
                vec.push_back(2);
                for (size_t i = 2; i < amount; ++i) {
                    vec.push_back(vec[i - 1] + vec[i - 2]);
                }
            }
    }

    Iterator begin() const {
        return Iterator(0, vec);
    }

    Iterator end() const {
        return Iterator((int) vec.size(), vec);
    }

    size_t size() const {
        return vec.size();
    }
};