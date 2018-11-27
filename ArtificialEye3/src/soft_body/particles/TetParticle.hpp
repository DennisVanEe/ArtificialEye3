#pragma once

#include "Particle.hpp"
#include "../../shared/modeling/TetMesh.hpp"

namespace ee
{
	namespace sb
	{
		// This is a particle designed to work with tetrahedral meshes
		// for tetrahedral mesh soft body simulation.
		template<class _VertType>
		class TetParticle : public Particle
		{
		public:
			TetParticle(Float mass, TetMesh<_VertType>* mesh, int vertIndex) :
				Particle(mass, ParticleType::ACTIVE), m_mesh(mesh), m_vertIndex(vertIndex)
			{
				m_cPos = m_pPos = m_mesh->vertAt(vertIndex).pos;
			}

			void update(Float time) override { m_mesh->vertAt(m_vertIndex).pos = m_cPos; }
			std::unique_ptr<Particle> getCopy() const override { return std::make_unique<FVParticle>(*this); }

		private:
			TetMesh<_VertType>* m_mesh;
			int m_vertIndex;
		};
	}
}