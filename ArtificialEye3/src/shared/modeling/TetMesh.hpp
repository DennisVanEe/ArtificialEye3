#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "../ArtificialEye.hpp"
#include "Mesh.hpp"

namespace ee
{

	// A basic tetrahedron structure
	class Tet
	{
	public:
		Tet() {}
		Tet(Float v0, Float v1, Float v2, Float v3) :
			m_data({ v0, v1, v2, v3 }) {}
		Tet(std::array<Float, 4> data) :
			m_data(data) {}
		Tet(const Float* data) { std::copy(data, data + 4, m_data); }

		static constexpr int size() { return 4; }

		Float operator[](int i) const { return m_data[i]; }

	private:
		std::array<Float, 4> m_data;
	};

	template<class _VertType>
	using TetMesh = Mesh<Tet, _VertType>;
}