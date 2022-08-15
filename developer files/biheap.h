#pragma once

#include <vector>
#include <iostream>

#define VERIFY(condition, message)\
if(!(condition)){\
	std::cerr << "error:" << "\nmessage: " << (message) << "\nline: " << __LINE__ << "\nfile: " << __FILE__ << std::endl;\
	exit(EXIT_FAILURE);\
}

// бинарная куча с минимумом
// empty O(1)
// top O(1)
// pop O(log2 n)
// push O(log2 n)
template<typename T>
class biheap {

	// бинарное дерево представлено в виде массива
	// нумерация с 1
	// предок: v / 2
	// левый сын: 2 * v
	// правый сын: 2 * v + 1

	int tree_size;

	T* data;

	bool* used;

	// для каждого слоя храниться множество индексов вершин, которые не используются

	int* layers;

	int* layer_size;

	/*
	* БАЗОВЫЕ ФУНКЦИИ
	*/

	// безопасная проверка на используемость вершины v
	bool is_used(int v) {
		return v < tree_size && used[v];
	}

	// возвращает номер слоя вершины v
	int get_layer_id(int v) {
		int cnt = 0;
		// 30s
		/*for (int k = 4; k >= 0; k--) {
			while ((v >> (1 << k)) != 0) {
				v >>= (1 << k);
				cnt += (1 << k);
			}
		}*/

		// 17s
		{
			if (v >> 16) {
				v >>= 16;
				cnt += 16;
			}
			if (v >> 8) {
				v >>= 8;
				cnt += 8;
			}

			while (v) {
				v >>= 1;
				cnt++;
			}
			cnt -= 1;
		}

		// 38s
		/*while (v) {
			v >>= 1;
			cnt++;
		}
		cnt -= 1*/
		return cnt;
	}

	/*
	* Фукнции для layers
	*/

	void push_in_layer(int v) {
		int k = get_layer_id(v);
		layers[(1 << k) + layer_size[k]] = v;
		layer_size[k]++;
	}

	void pop_in_layer(int k) {
		layer_size[k]--;
	}

	int get_back_in_layer(int k) {
		return layers[(1 << k) + layer_size[k] - 1];
	}

	/*
	* СТРУКТУРНЫЕ ФУНКЦИИ
	*/

	// перестраивает структуру, уменьшая высоту
	/*void rebuild() {
		// переберем самые глубокие вершины и постараемся закинуть их ближе к корню

		for (int v = data.size() - 1; v > 1; v--) {
			if (used[v]) {
				int layer_v = mylog2(v) - 1; // получим номер слоя текущей вершины

				// найдем лучшее для нее место
				int i = find_free_layer();

				if (i != -1 && i < layer_v) {
					// нашли место ближе к корню

					// удалим вершину v
					T val = std::move(data[v]);
					used[v] = false;
					layers[layer_v].push_back(v);

					// закинем значение val в структуру
					{
						// добавим вершину v
						int v = layers[i].back();
						layers[i].pop_back();
						used[v] = true;
						data[v] = val;

						bubble(v); // всплывем
					}
				}
				else {
					break; // уже максимально сжали
				}
			}
		}
	}*/

	// добавляет еще один слой в структуру
	void add_layer() {
		// update data and used
		{
			T* new_data = new T[tree_size * 2];
			bool* new_used = new bool[tree_size * 2];

			// заполнить new_used
			for (int i = tree_size; i < 2 * tree_size; i++) {
				new_used[i] = false;
			}

			// скопировать старые значения
			for (int i = 0; i < tree_size; i++) {
				if (used[i]) {
					std::swap(new_data[i], data[i]);
				}
				new_used[i] = used[i];
			}

			delete[] data;
			delete[] used;

			data = new_data;
			used = new_used;
		}

		tree_size *= 2;

		// update layers
		{
			delete[] layers;
			delete[] layer_size;
			
			// количество слоев
			int k = get_layer_id(tree_size);

			layers = new int[tree_size];
			layer_size = new int[k];
			
			for (int i = 0; i < k; i++) {
				layer_size[i] = 0;
			}

			//for (int layer = 0; layer < k; layer++) {
			//	int i = (1 << layer);
			//	for (int j = i; j < i + i; j++) {
			//		if (!used[j]) {
			//			//push_in_layer(j);
			//			layers[i + layer_size[layer]] = j;
			//			layer_size[layer]++;
			//		}
			//	}
			//}

			int layer = 0;

			for (int i = 1; i < tree_size; i++) {
				if (i == (1 << layer + 1)) {
					layer++;
				}
				if (!used[i]) {
					layers[(1 << layer) + layer_size[layer]] = i;
					layer_size[layer]++;
				}
			}
		}
	}

	// удаляет последний слой
	void remove_layer() {
		// update data and used
		{
			T* new_data = new T[tree_size / 2];
			bool* new_used = new bool[tree_size / 2];

			// скопировать старые значения
			for (int i = 0; i < tree_size / 2; i++) {
				if (used[i]) {
					std::swap(new_data[i], data[i]);
				}
				new_used[i] = used[i];
			}

			delete[] data;
			delete[] used;

			data = new_data;
			used = new_used;
		}

		tree_size /= 2;

		// update layers
		{
			delete[] layers;
			delete[] layer_size;

			// количество слоев
			int k = get_layer_id(tree_size);

			layers = new int[tree_size];
			layer_size = new int[k];

			for (int i = 0; i < k; i++) {
				layer_size[i] = 0;
			}

			for (int i = 1; i < tree_size; i++) {
				if (!used[i]) {
					push_in_layer(i);
				}
			}
		}
	}

	// удаляет лишние слои
	void cut() {
		while (tree_size > 2 && layer_size[get_layer_id(tree_size - 1)] == (1 << get_layer_id(tree_size - 1))) {
			remove_layer();
		}
		/*while (!layers.empty() && layers.back().size() == (1 << layers.size() - 1)) {
			data.resize(data.size() - (1 << layers.size() - 1));
			used.resize(used.size() - (1 << layers.size() - 1));
			layers.pop_back();
		}*/
	}

	// всплывает пузырь v на подходящее ему место
	void bubble(int v) {
		// значение у ребенка меньше чем у родителя
		if (v != 1 && data[v] < data[v / 2]) {
			std::swap(data[v], data[v / 2]); // поменяем значения
			bubble(v / 2);
		}
	}

	// потопляет вершину v
	// удаляет значение в вершине v
	void drown(int v) {
		// поменяем местами v с самым наименьшим по значению ребенком
		// затем запустимся рекурсивно от этого реберка
		if (is_used(2 * v) && is_used(2 * v + 1)) {
			if (data[2 * v] < data[2 * v + 1]) {
				std::swap(data[v], data[2 * v]);
				drown(2 * v);
			}
			else {
				std::swap(data[v], data[2 * v + 1]);
				drown(2 * v + 1);
			}
		}
		else if (is_used(2 * v)) {
			std::swap(data[v], data[2 * v]);
			drown(2 * v);
		}
		else if (is_used(2 * v + 1)) {
			std::swap(data[v], data[2 * v + 1]);
			drown(2 * v + 1);
		}
		else { // пришли в конечную вершину
			// удалим ее
			used[v] = false;
			T tmp;
			std::swap(tmp, data[v]);
			push_in_layer(v);
		}
	}

	// находит слой, в котором есть свободная вершина
	// вернет -1, если такого слоя нет
	int find_free_layer() {
		for (int i = 0; i < get_layer_id(tree_size); i++) {
			if (layer_size[i] != 0) {
				return i;
			}
		}
		return -1;
	}

public:

	biheap() {
		tree_size = 2;
		data = new T[2];
		used = new bool[2];
		layers = new int[2];
		layer_size = new int[1];
		
		layers[1] = 1;
		layer_size[0] = 1;

		used[0] = used[1] = false;
	}

	bool empty() {
		return !is_used(1);
	}

	int size() {
		int sz = 0;
		for (int i = 0; i < get_layer_id(tree_size); i++) {
			sz += (1 << i) - layer_size[i];
		}
		return sz;
	}

	void push(const T& val) {
		// находим минимальный свободный слой
		int i = find_free_layer();
		if (i == -1) { // если такого нет
			i = get_layer_id(tree_size);
			add_layer(); // добавим его
		}

		// добавим вершину v
		int v = get_back_in_layer(i);
		pop_in_layer(i);
		used[v] = true;
		data[v] = val;

		bubble(v); // всплывем
	}

	T top() {
		VERIFY(!empty(), "biheap is empty, but you want to check something from it");
		return data[1];
	}

	void pop() {
		VERIFY(!empty(), "biheap is empty, but you want to remove something from it");
		drown(1);
		resize();
	}

	// по возможности уменьшает размер структуры
	void resize() {
		cut(); // постараемся обрезать неиспользуемые слои

		// структура слишком большая, а объектов мало
		/*if (2 * size() < data.size()) {
			rebuild();
		}

		cut();*/
	}

	double calc_mem() {
		return 1.0 *
			(
				tree_size * (sizeof(T) + sizeof(bool) + sizeof(int)) +
				get_layer_id(tree_size) * sizeof(int)
			) / 1024 / 1024 / 1024;
	}
};
