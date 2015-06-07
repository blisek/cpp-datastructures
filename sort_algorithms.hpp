#ifndef SORT_ALGORITHMS
#define SORT_ALGORITHMS

#include <type_traits>
#include <memory>
#include <cstring>

/*
 * Sortowanie kubełkowe
 * Dopuszczalne tylko typy całkowitoliczbowe bool, char, short, int, long, long long w wersji
 * ze znakiem i bez znaku.
 * 
 * Argumenty:
 * first - iterator do 1. elementu
 * last - iterator do następnego za ostatnim elementu
 * min - minimalna wartość całkowita
 * max - maksymalna wartość całkowita
 * 
 * Zwraca dynamicznie alokowaną tablicę typu Result[] opakowaną
 * w std::unique_ptr<Result[]>.
 * 
 * Przykład:
 * vector<int> v { 1,1,1,1, 4,4,4,4, 3,3,3,3,3,3,3,3,3, 2,2, 6,6,6,6 };
 * unique_ptr<int[]> p = bucket_sort<int>(v.begin(), v.end(), 1, 6);
 * for(int i = 0; i < v.size(); ++i)
 *   std::cout << p[i] << ',';
 * 
 * Output:
 * 1,1,1,1,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,6,6,6,6,
*/
template<typename Result, typename InputIterator>
std::unique_ptr<typename std::enable_if<std::is_integral<Result>::value, Result>::type[]>
    bucket_sort(InputIterator first, InputIterator last, Result min, Result max)
{
        Result *arr = new Result[max-min+1];
        Result length {};
        memset(arr, 0, sizeof(Result) * (max-min+1));
        
        for(; first != last; ++first) {
            arr[*first - min] += 1;
            ++length;
        }
            
        Result *retArr = new Result[length];
        for(Result i = 0, shift = 0; i < max-min+1; ++i)
            for(Result j = 0; j < arr[i]; ++j, ++shift)
                retArr[shift] = static_cast<Result>(i + min);
                
        return std::unique_ptr<Result[]>(std::move(retArr));
}

#endif // SORT_ALGORITHMS