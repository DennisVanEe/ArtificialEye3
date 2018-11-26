#pragma once

#include <vector>

#include "../ArtificialEye.hpp"

namespace ee
{
	struct PosVert { Vec3 pos; };

	template<class _PrimType, class _VertType>
	class Mesh
	{
	public:
		Mesh() {}
		Mesh(std::vector<_VertType> vertices, std::vector<_PrimType> primitives) :
			m_vertices(vertices), m_primitives(primitives) {}

		const _PrimType& primAt(int i) const { return m_primitives[i]; }

		const _VertType& vertAt(int i) const  { return m_vertices[i]; }
		_VertType& vertAt(int i) { return m_vertices[i]; }

		void primVertAt(_VertType* data, int i) const
		{
			const _PrimType& prim = primAt(i);
			for (int i = 0; i < _PrimType::size(); i++) { data[i] = vertAt(prim[i]); }
		}

	private:
		std::vector<_VertType> m_vertices;
		std::vector<_PrimType> m_primitives;
	};
}