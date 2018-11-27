#pragma once

#include <array>
#include <vector>
#include "SimTetMesh.hpp"

namespace ee
{
	namespace sb
	{
		template<class _VertType>
		class SimTetCell
		{
		private:
			using SimTetMesh = SimTetMesh<_VertType>;

		public:
			SimTetCell(SimTetMesh* mesh, std::array<int, 5> tets) :
				m_mesh(mesh), m_tets(tets) {}
			SimTetCell(SimTetMesh* mesh, int* tets) :
				m_mesh(mesh) { std::copy(tets, tets + 5, m_tets.begin()); }

		private:
			SimTetMesh* m_mesh;
			std::array<int, 5> m_tets;
		};

		template<class _VertType>
		class SimTetCellMesh
		{
		private:
			using SimTetCell = SimTetCell<_VertType>;

		public:
			SimTetCellMesh(std::vector<SimTetCell> cells) :
				m_cells(cells) {}

		private:
			std::vector<SimTetCell> m_cells;
		};
	}
}