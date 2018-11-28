#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>

#include "../ArtificialEye.hpp"
#include "../Utility.hpp"
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

		// Generates a shell of the mesh for rendering and what not
		void genShellMesh()
		{
			// The shell of a tetrahedron (which only needs to be computed once, mind you)
			// Is the collection of faces such that only one tetrahedron has ownership of it.

			Mesh::m_faces.clear(); // In case you want to redo the shell

			// Doing this requires some helper functions:
			std::unordered_map<HashableFaceIndex, int> faceCounts;
			for (const TetIndex& ti : m_tets)
			{
				// All faces of a tetrahedron:
				std::array<HashableFaceIndex, 4> tetFaces = 
				{
					HashableFaceIndex(ti[0], ti[1], ti[2]),
					HashableFaceIndex(ti[0], ti[1], ti[3]),
					HashableFaceIndex(ti[0], ti[2], ti[3]),
					HashableFaceIndex(ti[1], ti[2], ti[3])
				};

				// Hash and increment them:
				for (HashableFaceIndex in : tetFaces)
				{
					auto it = faceCounts.find(in);
					if (it == faceCounts.end()) { faceCounts.insert(std::make_pair(in, 1)); }
					else { it->second++; }
				}
			}

			// Now we go through and find all faces with a count of 1 (that is, they are only associated with 1 tet)
			// So now the m_faces stores all the shells
			for (const auto& [face, count] : faceCounts)
			{
				if (count == 1) { Mesh::m_faces.push_back(face); }
			}
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