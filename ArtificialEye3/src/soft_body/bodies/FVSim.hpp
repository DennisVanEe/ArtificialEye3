#pragma once

#include <vector>
#include <array>

#include "../particles/Particle.hpp"
#include "../../shared/modeling/TetMesh.hpp"
#include "../spring/spring.hpp"

namespace ee
{
	// A TetCell is a collection of 5 tetrahedron as described in the paper.
	template<class _VertType>
	class TetCell
	{
	public:
		
		Float lambda(const TetMesh<_VertType>* mesh) const
		{

		}

		Float volume(const TetMesh<_VertType>* mesh) const
		{
			std::array<Vec3, 8> pos;
			for (int i = 0; i < 8; i++) { pos[i] = mesh->getPosAt(m_particleIndices[i]); }

			Float v0 = volumeTet(pos[0], pos[1], pos[2], pos[3]);
			Float v2 = volumeTet(pos)
		}

	private:
		std::array<int, 16> m_springIndicies;
		std::array<int, 8>  m_particleIndices;
		Float m_initVolume;
	};

	// Right now only supports a single mesh.
	// In the future, will support numerous meshes.
	template<class _VertType>
	class FVSim
	{
	public:
		FVSim();

		void step(Float time)
		{
			// begin by updating all the spring forces:
			for (const Spring& s : m_springs) { s.applyForce(); }



			// update the object positions and reset forces:
			for (const MeshParticle* p : m_particles) 
			{ 
				m_mesh->setPosAt(p->vertIndex, p->cPos); 
				p->resetForces();
			}
		}

	private:
		TetMesh<_VertType>*       m_mesh;
		std::vector<MeshParticle> m_particles;
		std::vector<Spring>       m_springs;
	};
}