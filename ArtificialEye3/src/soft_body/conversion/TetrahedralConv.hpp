#pragma once

#include "../bodies/SimTetMesh.hpp"
#include "../bodies/SimTetCellMesh.hpp"

namespace ee
{
	namespace sb
	{
		template<class _VertType>
		SimTetCellMesh<_VertType> convertToCells(SimTetMesh<_VertType>& tmesh)
		{
			// First we need to figure out who is who's neighbor
			int n
		}
	}
}