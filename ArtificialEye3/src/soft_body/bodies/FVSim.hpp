#pragma once

#include <vector>
#include <array>

#include "../particles/Particle.hpp"
#include "../../shared/modeling/TetMesh.hpp"

namespace ee
{
	// Holds extra info (like momentum)
	class FVParticle : public MeshParticle
	{
	public:

	private:

	};

	// A TetCell is a collection of 5 tetrahedron as described in the paper.
	class TetCell
	{
	public:
		

	private:
		std::array<int, 16> m_springIndicies;
		std::array<int, 8>  m_particleIndices;
	};

	template<class _VertType>
	class FVSim
	{
	public:
		FVSim();

	private:
		TetMesh<_VertType>*     m_mesh;
		std::vector<FVParticle> m_particles;
	};
}