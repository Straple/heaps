#define VIS_VERIFY_HEAP_COMMENT false

#include "setheap.h"
//#include "biheap.h"
#include "git_biheap.h"

#include "random.h"

#include "time.h"

#undef min
#undef max

#include <bits/stdc++.h>

using value_t = int;

value_t get_rnd_val() {
	return rnd() % 1000;
}

template<typename my_heap_t>
bool verify_heap() {
	my_heap_t my_heap;
	setheap<value_t > set_heap;

	const int n = 1e7;
	for (int i = 0; i < n; i++) {
		if (set_heap.empty() != my_heap.empty()) {
			return false;
		}

		if (!set_heap.empty() && set_heap.top() != my_heap.top()) {
			return false;
		}

		if (set_heap.size() != my_heap.size()) {
			return false;
		}

		if (set_heap.empty() || get_urnd() < 0.7) {
			auto x = get_rnd_val();
#if VIS_VERIFY_HEAP_COMMENT
			cout << "push: " << x << "\n";
#endif
			set_heap.push(x);
			my_heap.push(x);
		}
		else {
#if VIS_VERIFY_HEAP_COMMENT
			cout << "pop: " << set_heap.top() << "\n";
#endif
			set_heap.pop();
			my_heap.pop();
		}
#if VIS_VERIFY_HEAP_COMMENT
		cout << "size: " << set_heap.data.size() << "\n";
#endif
	}

#if VIS_VERIFY_HEAP_COMMENT
	cout << "popping...\n";
#endif

	while (!set_heap.empty()) {
		if (set_heap.empty() != my_heap.empty()) {
			return false;
		}

		if (set_heap.top() != my_heap.top()) {
			return false;
		}

		if (set_heap.size() != my_heap.size()) {
			return false;
		}

#if VIS_VERIFY_HEAP_COMMENT
		cout << "pop: " << set_heap.top() << "\n";
#endif
		set_heap.pop();
		my_heap.pop();
	}

	return true;
}

template<typename my_heap_t>
void explore_time_heap() {

	const int n = 1e8;

	my_heap_t heap;

	double max_time = 0;
	double max_mem = 0;
	double all_time = 0;

	ofstream output("test.csv");

	output << fixed << setprecision(10);
	output << "time memory size\n";

	/* test A
	* в этом тесте в кучу будут последовательно добавлены числа 1, 2, 3, ..., n
	* а затем достать все значения
	*/
	/*{
		for (int i = 1; i <= n; i += 1000) {
			Timer t;
			for (int j = i; j < i + 1000; j++) {
				heap.push(j);
			}

			double time = t.time();
			double memory = heap.calc_mem();

			max_time = max(max_time, time);
			all_time += time;

			max_mem = max(max_mem, memory);

			output << time << " " << memory << "\n";
		}

		for (int i = 1; i <= n; i += 1000) {
			Timer t;
			for (int j = i; j < i + 1000; j++) {
				heap.pop();
			}

			double time = t.time();
			double memory = heap.calc_mem();

			max_time = max(max_time, time);
			all_time += time;

			max_mem = max(max_mem, memory);

			output << time << " " << memory << "\n";
		}

		cout << "A: " << max_time << "s " << max_mem << "Gb " << all_time << "s\n";
	}*/

	/* test B
	* в этом тесте в кучу будут последовательно добавлены числа n, n-1, n-2, ..., 1
	* а затем достать все значения
	*/
	/*{
		for (int i = n; i >= 1; i -= 1000) {

			Timer t;
			for (int j = i; j > i - 1000; j--) {
				heap.push(j);
			}
			double time = t.time();

			double memory = heap.calc_mem();

			max_time = max(max_time, time);
			all_time += time;

			max_mem = max(max_mem, memory);

			output << time << " " << memory << "\n";
		}
		for (int i = 1; i <= n; i += 1000) {
			Timer t;
			for (int j = i; j < i + 1000; j++) {
				heap.pop();
			}

			double time = t.time();
			double memory = heap.calc_mem();

			max_time = max(max_time, time);
			all_time += time;

			max_mem = max(max_mem, memory);

			output << time << " " << memory << "\n";
		}

		cout << "B: " << max_time << "s " << max_mem << "Gb " << all_time << "s\n";
	}*/

	/* testC
	*  в этом тесте будут рандомно сгенированы 100 массивов длины 10^6
	*  а затем отсортированы с помощью кучи
	*/
	/*{
		output << "time\n";
		int len = 1e6;
		for (int i = 0; i < 100; i++) {
			std::cout << i << "\n";
			vector<int> a(len);

			for (int i = 0; i < len; i++) {
				a[i] = rnd() % (int)1e5;
			}

			shuffle(a.begin(), a.end(), rnd);
			shuffle(a.begin(), a.end(), rnd);
			shuffle(a.begin(), a.end(), rnd);

			auto sort_a = a;
			{
				Timer t;
				std::sort(sort_a.begin(), sort_a.end());
				double time = t.time();

				output << time << "\n";
			}

			Timer t;

			for (int i = 0; i < len; i++) {
				heap.push(a[i]);
			}
			for (int i = 0; i < len; i++) {
				a[i] = heap.top();
				heap.pop();
			}

			double time = t.time();

			if (a != sort_a) {
				std::cout << "error!\n";
				exit(-1);
			}

			max_time = max(max_time, time);
			all_time += time;

			output << time << " setheap\n";
		}

		cout << "C: " << max_time << "s " << all_time << "s\n";
	}*/

	/* testD
	*  stresstest
	*/
	{
		int n = 1e8;
		for (int step = 0; step < 100; step++) {
			int to_size = (rnd() % 100) * (n / 100);

			int old_heap_size = heap.size();

			Timer t;

			auto relax = [&]() {
				if (abs((int)heap.size() - old_heap_size) == 10000) {
					old_heap_size = heap.size();
					double time = t.time();

					output << time << " " << heap.calc_mem() << " " << heap.size() << "\n";

					t.reset();
				}
			};

			while (heap.size() < to_size) {
				heap.push(rnd());

				relax();
			}
			while (heap.size() > to_size) {
				heap.pop();

				relax();
			}

			std::cout << "hi: " << step << "\n";
		}
	}
}

int main() {

	/*cout << "verification...";
	{
		if (!verify_heap<biheap<value_t>>()) {
			cout << "error\n";
			return 0;
		}
	}
	cout << "\b\b\b [successful]\n";*/

	explore_time_heap<biheap<value_t>>();

	return 0;
}
