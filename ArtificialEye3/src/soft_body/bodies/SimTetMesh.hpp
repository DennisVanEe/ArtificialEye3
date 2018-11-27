#pragma once

#include <array>
#include <vector>

#include "../particles/TetParticle.hpp"
#include "../../shared/modeling/TetMesh.hpp"

namespace ee
{
	namespace sb
	{
		// An individual tetrahedron designed for simulating:
		template<class _VertType>
		class SimTet
		{
		private:
			using TetPart = TetParticle<_VertType>;

		public:
			SimTet(Float mass, TetMesh<_VertType>* mesh, Tet tet) :
				m_parts({ TetPart(mass, mesh, tet[0]), TetPart(mass, mesh, tet[1]), TetPart(mass, mesh, tet[2]), TetPart(mass, mesh, tet[3]) })
			{
				m_v0 = volume();
			}

			Float volume() const
			{
				Vec3 ab = m_parts[1].currParticle() - m_parts[0].currParticle();
				Vec3 ac = m_parts[2].currParticle() - m_parts[0].currParticle();
				Vec3 bc = m_parts[3].currParticle() - m_parts[0].currParticle();
				Float vp = glm::dot(ab, glm::cross(ac, bc));
				return vp / 6;
			}

		private:
			std::array<TetPart, 4> m_parts;
			Float m_v0; // initial volume
		};

		template<class _VertType>
		class SimTetMesh
		{
		private:
			using SimTet = SimTet<_VertType>;
			using TetMesh = TetMesh<_VertType>;

		public:
			SimTetMesh(Float partMass, TetMesh* mesh) :
				m_mesh(mesh)
			{
				loadTetMesh(partMass);
			}

			const TetMesh* rawMesh() const { return m_mesh; }

		private:
			void loadTetMesh(Float mass)
			{
				for (int i = 0; i < m_mesh->numPrim(); i++)
				{
					SimTet tet = SimTet(mass, m_mesh, m_mesh->primAt(i));
					m_tets.push_back(tet);
				}
			}

			std::vector<SimTet> m_tets;
			TetMesh* m_mesh;
		};
	}
}