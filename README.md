# heaps
 
# biheap
бинарная куча с минимумом
* empty O(1)
* top  O(1)
* pop O(log2 n)
* push O(log2 n)

ТЕСТИРОВАНИЕ

testA\
В кучу будут последовательно добавлены числа 1, 2, 3, ..., n\
Затем все они будут вытащены с помощью\
\
testB\
агалогичен testA, только тут числа будут добавлены в обратном порядке: n, n - 1, ..., 2, 1\
\
testC\
будут рандомно сгенерированы 100 массивов длины 10^6\
затем все эти массивы будут отсортированы с помощью кучи

biheap - testA - time\
![biheap - testA - time](https://user-images.githubusercontent.com/54230867/184658295-210b8c8f-4477-4e41-b9eb-839f30b8069e.png)

biheap - testA - time - semilogy\
![biheap - testA - time - semilogy](https://user-images.githubusercontent.com/54230867/184658468-f784c5ae-0af1-4086-8468-22c8233c6fbb.png)
