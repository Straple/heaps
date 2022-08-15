#pragma once

#include <set>

template<typename T>
struct setheap {
	std::multiset<T> data;

	bool empty() {
		return data.empty();
	}

	int size() {
		return data.size();
	}

	T top() {
		return *data.begin();
	}

	void pop() {
		data.erase(data.begin());
	}

	void push(const T& value) {
		data.insert(value);
	}

	double calc_mem() const {
		// тестовым путем получили, что std::_Tree_node<T, T*> меньше чем то что там на самом деле
		return 1.0 * data.size() * sizeof(std::_Tree_node<T, T*>) * 1.8 / 1024 / 1024 / 1024;
	}
};