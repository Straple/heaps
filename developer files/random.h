#pragma once

#include <random>

std::mt19937_64 rnd(42);

// returns random range [0, 1]
double get_urnd() {
	return (double)rnd() / ULLONG_MAX;
}

// returns random range [-1, 1]
double get_rnd() {
	return ((double)rnd() - LLONG_MAX) / ULLONG_MAX * 2;
}
