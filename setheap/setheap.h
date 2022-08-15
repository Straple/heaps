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
};