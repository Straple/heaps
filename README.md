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
n = 10^8

testA\
В кучу будут последовательно добавлены числа 1, 2, 3, ..., n\
Затем все они будут вытащены

[time]\
![biheap - testA - time](https://user-images.githubusercontent.com/54230867/184658295-210b8c8f-4477-4e41-b9eb-839f30b8069e.png) ![setheap - testA - time](https://user-images.githubusercontent.com/54230867/184659085-1a10bc09-a166-4f5c-8406-cb4190392dfd.png)


[time with semilogy]\
![biheap - testA - time - semilogy](https://user-images.githubusercontent.com/54230867/184658468-f784c5ae-0af1-4086-8468-22c8233c6fbb.png) ![setheap - testA - time - semilogy](https://user-images.githubusercontent.com/54230867/184659151-e565046c-0772-40db-9cb1-1c1454e2de4f.png)


[memory]\
![biheap - testA - mem](https://user-images.githubusercontent.com/54230867/184658751-0ed9bfaa-2c59-43f6-a025-65f53fc318ca.png) ![setheap - testA - mem](https://user-images.githubusercontent.com/54230867/184658826-83e444ed-eeb1-4308-939c-abbec2dba746.png)


testB\
агалогичен testA, только тут числа будут добавлены в обратном порядке: n, n - 1, ..., 2, 1

[time]\
![biheap - testB - time](https://user-images.githubusercontent.com/54230867/184659613-d0b0687f-fb3c-49dc-8527-b9610d34efd8.png) ![setheap - testB - time](https://user-images.githubusercontent.com/54230867/184659640-99166cfe-52b0-4326-9610-9653f5f119c5.png)

[time with semilogy]\
![biheap - testB - time - semilogy](https://user-images.githubusercontent.com/54230867/184659812-0e2a1ea3-4230-405f-86ea-9513b6b7fc7f.png) ![setheap - testB - time - semilogy](https://user-images.githubusercontent.com/54230867/184659823-15b8cf9f-62e1-4aab-937f-5962dcfcc3d2.png)



testC\
будут рандомно сгенерированы 100 массивов длины 10^6\
затем все эти массивы будут отсортированы с помощью кучи

[biheap time]\
![biheap - testC - time](https://user-images.githubusercontent.com/54230867/184660097-f9df7a7f-abb7-4772-bf56-54b1783241d1.png)

[setheap time]\
![setheap - testC - time](https://user-images.githubusercontent.com/54230867/184659980-433632a6-5aca-40b3-aac1-1788418814fc.png)

[std::sort time]\
![std_sort - testC - time](https://user-images.githubusercontent.com/54230867/184660145-e43d22fc-e895-4c22-886e-baf2fa2874f8.png)

[total time]\
![testC](https://user-images.githubusercontent.com/54230867/184660173-30f4be35-f74e-48da-9d3d-4aa4c28ab474.png)

