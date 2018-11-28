#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "../ArtificialEye.hpp"
#include "Mesh.hpp"

namespace ee
{
	// A generic tetrahedron (as done with faces):
	template<class _T>
	class tTet
	{
	public:
		tTet() {}
		tTet(_T v0, _T v1, _T v2, _T v3) :
			m_data({v0, v1, v2, v3}) {}

		const _T operator[](int i) const { return m_data[i]; }
		std::remove_reference<_T>::type& operator[](int i) { return m_data[i]; }

	private:
		std::array<_T, 4> m_data;
	};

	// See Face for details:
	using TetIndex = tTet<int>;
	using TetRef = tTet<Vec3&>;
	using Tet = tTet<Vec3>;

	// A TetMesh also has a triangular mesh that represents the shell.
	// This shell is what is used when rendering in 3D and when intersection
	// with a ray tracer.
	template<class _VertType>
	class TetMesh : public Mesh<_VertType>
	{
		using Mesh = Mesh<_VertType>;

	public:
		TetMesh() : Mesh() {}
		TetMesh(std::vector<_VertType> vertices, std::vector<TetIndex> tets) :
			Mesh(vertices, std::move(std::vector<FaceIndex>())), m_tets(tets) {}

		void genShellMesh()
		{
			// The shell of a tetrahedron (which only needs to be computed once, mind you)
			// Is the collection of faces such that only one tetrahedron has ownership of it.

			// Doing this requires some helper functions:

		}

		int numTet() const { return m_tets.size(); }

		TetIndex getTetIndexAt(int i) const { return m_tets[i]; }
		void setTetAt(int i, TetIndex tet) { m_tets[i] = tet; }

		TetRef getTetRefAt(int i)
		{
			const TetIndex in = m_tets[i];
			return TetRef(Mesh::m_verts[in[0]].pos, Mesh::m_verts[in[1]].pos, Mesh::m_verts[in[2]].pos, Mesh::m_verts[in[3]].pos);
		}

		Tet getTetAt(int i)
		{
			const TetIndex in = m_tets[i];
			return Tet(Mesh::m_verts[in[0]].pos, Mesh::m_verts[in[1]].pos, Mesh::m_verts[in[2]].pos, Mesh::m_verts[in[3]].pos);
		}

	private:
		std::vector<TetIndex> m_tets;
	};
}