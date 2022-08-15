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

	std::vector<T> data;

	std::vector<bool> used;

	// для каждого слоя храниться множество индексов вершин, которые не используются
	std::vector<std::vector<int>> layers;

	int get_layer_id(int v) {
		int cnt = 0;
		if ((v >> 16)) {
			cnt += 16;
			v >>= 16;
		}
		if ((v >> 8)) {
			cnt += 8;
			v >>= 8;
		}
		while (v) {
			v >>= 1;
			cnt++;
		}
		return cnt - 1;
	}

	// добавляет еще один слой в структуру
	void add_layer() {
		int v = (1 << layers.size());
		int end = v * 2;
		layers.push_back({});

		data.resize(end);
		used.resize(end);

		while (v != end) {
			layers.back().push_back(v);
			v++;
		}
	}

	// перестраивает структуру, уменьшая высоту
	void rebuild() {
		// переберем самые глубокие вершины и постараемся закинуть их ближе к корню

		int free_layer = 0;

		auto move_free_layer = [&]() {
			while (free_layer < layers.size() && layers[free_layer].empty()) {
				free_layer++;
			}
		};

		move_free_layer();

		for (int layer = (int)layers.size() - 1; layer > 0; layer--) {

			int v = (1 << layer);

			for (; v < (1 << layer + 1) && free_layer < layer; v++) {
				if (used[v]) {

					// удалим вершину v
					T val = std::move(data[v]);
					used[v] = false;
					layers[layer].push_back(v);

					// закинем значение val в структуру
					{
						// добавим вершину v
						int v = layers[free_layer].back();
						layers[free_layer].pop_back();
						used[v] = true;
						data[v] = val;

						bubble(v); // всплывем
					}

					move_free_layer();
				}
			}
		}
	}

	// удаляет лишние слои
	void cut() {
		while (!layers.empty() && layers.back().size() == (1 << layers.size() - 1)) {
			data.resize(data.size() - (1 << layers.size() - 1));
			data.shrink_to_fit();

			used.resize(used.size() - (1 << layers.size() - 1));
			used.shrink_to_fit();

			layers.pop_back();
		}
	}

	// всплывает пузырь v на подходящее ему место
	void bubble(int v) {
		// значение у ребенка меньше чем у родителя
		if (v != 1 && data[v] < data[v / 2]) {
			std::swap(data[v], data[v / 2]); // поменяем значения
			bubble(v / 2);
		}
	}

	bool is_used(int v) {
		return v < used.size() && used[v];
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
			layers[get_layer_id(v)].push_back(v);
		}
	}

	// вернет -1, если такого слоя нет
	int find_free_layer() {
		for (int i = 0; i < layers.size(); i++) {
			if (!layers[i].empty()) {
				return i;
			}
		}
		return -1;
	}

public:

	int size() {
		if (data.empty()) {
			return 0;
		}
		int sz = 0;
		for (int i = 0; i < layers.size(); i++) {
			sz += layers[i].size();
		}
		return data.size() - 1 - sz;
	}

	// пытается перестроить структуру, чтобы уменьшить высоту и занимаемую память
	void resize() {
		cut();

		if (size() * 3 < data.size()) {
			rebuild();
		}

		cut();
	}

	bool empty() {
		return !is_used(1);
	}

	void push(const T& val) {
		// находим минимальный свободный слой
		int i = find_free_layer();
		if (i == -1) { // если такого нет
			i = layers.size();
			add_layer(); // добавим его
		}

		// добавим вершину v
		int v = layers[i].back();
		layers[i].pop_back();
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
};
