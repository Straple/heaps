# heaps

# setheap
надстройка над std::multiset

# biheap
бинарная куча с минимумом
* empty O(1)
* top  O(1)
* pop O(log2 n)
* push O(log2 n)

ТЕСТИРОВАНИЕ

Далее\
biheap слева\
setheap справа\
n = 10^8\
1 step = 1000 добавлений/удалений (это для более формативного графика и нормального его веса). Время суммируется в это "шаге"

testA\
В кучу будут последовательно добавлены числа 1, 2, 3, ..., n\
Затем все они будут вытащены

[time]\
![biheap - testA - time](https://user-images.githubusercontent.com/54230867/184666048-ffdac925-0a32-4de9-bbfa-fdcf00cd7e41.png) ![setheap - testA - time](https://user-images.githubusercontent.com/54230867/184666095-1b40970a-32a2-411a-81bd-51461a438d45.png)


[time with semilogy]\
![biheap - testA - time - semilogy](https://user-images.githubusercontent.com/54230867/184666165-d7c89a43-42dc-4942-a89a-5945030b25df.png) !![setheap - testA - time - semilogy](https://user-images.githubusercontent.com/54230867/184666198-ec627d1b-ce79-48fb-afa9-a99e6060f4a1.png)


[memory]\
![biheap - testA - mem](https://user-images.githubusercontent.com/54230867/184666249-2706b644-49e2-4d43-a4a7-2d47b79a94f2.png) ![setheap - testA - mem](https://user-images.githubusercontent.com/54230867/184666259-f51d59ab-8045-48ed-a9c2-6b6352f5ec73.png)


testB\
агалогичен testA, только тут числа будут добавлены в обратном порядке: n, n - 1, ..., 2, 1

[time]\
![biheap - testB - time](https://user-images.githubusercontent.com/54230867/184666331-f48c51ab-c635-4e30-bdfa-c3a59db4d5de.png) ![setheap - testB - time](https://user-images.githubusercontent.com/54230867/184666343-fb108370-3010-40db-8102-ab1d8eff04fb.png)

[time with semilogy]\
![biheap - testB - time - semilogy](https://user-images.githubusercontent.com/54230867/184666915-a26da449-a77b-4347-a4c4-dcd5d17516b2.png) ![setheap - testB - time - semilogy](https://user-images.githubusercontent.com/54230867/184666924-24a3c4db-e853-430e-8f02-9467210ecc40.png)





testC\
будут рандомно сгенерированы 100 массивов длины 10^6\
затем все эти массивы будут отсортированы с помощью кучи

[biheap time]\
![biheap - testC - time](https://user-images.githubusercontent.com/54230867/184666450-056c0838-8f32-4fc7-972b-39516e609fa9.png)

[setheap time]\
![setheap - testC - time](https://user-images.githubusercontent.com/54230867/184666482-00ef1d3b-d778-40e5-bd45-7b07ccfef1d8.png)

[std::sort time]\
![std_sort - testC - time](https://user-images.githubusercontent.com/54230867/184666507-a501f2ad-f369-41de-90d9-f93922f4f6e3.png)

[total time]\
![testC](https://user-images.githubusercontent.com/54230867/184666520-99646121-4b14-4080-a4c5-47f55be21507.png)

testA\
setheap:  22s 5.3Gb\
biheap:   16s 1.2Gb

testB\
setheap:  24s 5.3Gb\
biheap:   17s 1.2Gb

testC\
setheap:  100s 60mb\
biheap:   20s  18mb\
std_sort: 6.4s
