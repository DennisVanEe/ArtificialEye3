#pragma once

#include <bitset>

namespace ee
{
	// Hashes 3 integers such that we can always extract the result.
	// Also note that it's order independent. So 3, 4, 5, and 5, 3, 4
	// hash to the same value.

	template<class _T>
	void sort3(_T& a, _T& b, _T& c)
	{
		if (a > b) { std::swap(a, b); }
		if (b > c) { std::swap(b, c); }
		if (a > b) { std::swap(a, b); }
	}

	size_t hashCombine(size_t h0, size_t h1)
	{
		size_t seed = 0;
		seed ^= h0 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}

	std::bitset<128> hash3(int a, int b, int c)
	{
		using bs128 = std::bitset<128>;

		// First we sort it:
		if (a > b) { std::swap(a, b); }
		if (b > c) { std::swap(b, c); }
		if (a > b) { std::swap(a, b); }

		bs128 result;
		result.reset();
		result |= bs128(a) | (bs128(b) << (sizeof(int) * 8)) | (bs128(c) << (sizeof(int) * 8 * 2));
		return result;
	}
}