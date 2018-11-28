#pragma once

#include <vector>
#include <array>
#include <functional>

#include "../ArtificialEye.hpp"

namespace ee
{
	struct Vertex { Vec3 pos; };
	struct TexVert : public Vertex { Vec3 tex; };

	// Generic face type:
	template<class _T>
	class tFace
	{
	public:
		tFace() {}
		tFace(_T v0, _T v1, _T v2) : m_data({ v0, v1, v2 }) {}

		const _T operator[](int i) const { return m_data[i]; }
		// Not sure if this is how you do it but this should work:
		std::remove_reference<_T>::type& operator[](int i) { return m_data[i]; }

	protected:
		std::array<_T, 3> m_data;
	};

	// A mesh face is always a triangle. This way ray intersection and rendering works as normal.
    // A face declared here is used for indexing.
	using FaceIndex = tFace<int>;
	// Stores references so that modifying values here modifies the actual values
	// that belong to the mesh.
	using FaceRef = tFace<Vec3&>;
	// Stores the vertices themselves if no reference is needed (not planning on modifying anything).
	using Face = tFace<Vec3>;

	// A special face designed for use with hashing.
	// It makes sure that the elements are of a certain order.
	// This way faces with different ordering will still equal each other
	class HashableFaceIndex : public FaceIndex
	{
	public:
		HashableFaceIndex() : FaceIndex() {}
		HashableFaceIndex(int v0, int v1, int v2) : FaceIndex(v0, v1, v2) { sort3(m_data[0], m_data[1], m_data[2]); }
	};

	class FaceIndexHash
	{
	public:
		size_t operator()(const HashableFaceIndex& index) const
		{
			static std::hash<int> hasher;
			return hashCombine(hashCombine(hasher(index[0]), hasher(index[1])), hasher(index[2]));
		}
	};

	// The same as the above, but this includes the entire vertex if required:
	template<class _VertType> using FaceRefVert = tFace<_VertType&>;
	template<class _VertType> using FaceVert = tFace<_VertType>;

	template<class _VertType>
	class Mesh
	{
		static_assert(std::is_base_of_v<Vertex, _VertType>, "_VertType must inherit from Vertex");

	public:
		Mesh() {}
		Mesh(std::vector<_VertType> vertices, std::vector<FaceIndex> faces) :
			m_verts(vertices), m_faces(faces) {}

		void setVertices(std::vector<_VertType> vertices) { m_verts = vertices; }
		void setFaceIndices(std::vector<FaceIndex> faces) { m_faces = faces; }

		int numVert() const { return m_verts.size(); }
		int numFace() const { return m_faces.size(); }

		_VertType getVertAt(int i) const { return m_verts[i]; }
		FaceIndex getFaceIndexAt(int i) const { return m_faces[i]; }

		FaceRef getFaceRefAt(int i)
		{
			const FaceIndex in = m_faces[i];
			return FaceRef(m_verts[in[0]].pos, m_verts[in[1]].pos, m_verts[in[2]].pos);
		}

		Face getFaceAt(int i) const
		{
			const FaceIndex in = m_faces[i];
			return Face(m_verts[in[0]].pos, m_verts[in[1]].pos, m_verts[in[2]].pos);
		}

		FaceRefVert<_VertType> getFaceRefVertAt(int i)
		{
			const FaceIndex in = m_faces[i];
			return FaceRefVert<_VertType>(m_verts[in[0]], m_verts[in[1]], m_verts[in[2]]);
		}

		FaceVert<_VertType> getFaceVertAt(int i)
		{
			const FaceIndex in = m_faces[i];
			return FaceVert<_VertType>(m_verts[in[0]], m_verts[in[1]], m_verts[in[2]]);
		}

		void setVertAt(int i, _VertType v) { m_verts[i] = v; }
		void setFaceIndexAt(int i, FaceIndex f) { m_faces[i] = f; }

	protected:
		std::vector<_VertType> m_verts;
		std::vector<FaceIndex> m_faces;
	};
}