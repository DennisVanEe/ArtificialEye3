#pragma once

#include <vector>

#include "../bodies/SimTetMesh.hpp"
#include "../bodies/SimTetCellMesh.hpp"
#include "../../shared/modeling/TetMesh.hpp"

namespace ee
{
	namespace sb
	{
		// TODO: Right now the cells can overlap each other.
		// If this causes issues I'll have to address this.
		// Also, I am not checking if a tet doesn't belong to any cell, so let's hope
		// the shapes I'm dealing with here don't have that issue.

		// This converts the regular tet meshes to cell based meshes for actual simulation:
		template<class _VertType>
		SimTetCellMesh<_VertType> convertToCells(SimTetMesh<_VertType>& tmesh)
		{
			const TetMesh<_VertType>* mesh = tmesh.rawMesh();

			// First we need to figure out who is who's neighbor
			// Indexing into this vector results in a specific vertex
			std::vector<std::vector<int>> counts(mesh->numVert());
			for (int i = 0; i < mesh->numPrim(); i++)
			{
				const Tet& tet = mesh->primAt(i);
				for (int j = 0; j < 4; j++) { counts[tet[j]].push_back(i); }
			}

			// Now we need to go through and form the cells
			std::vector<SimTetCell<_VertType>> cells;
			for (int i = 0; i < mesh->numPrim(); i++)
			{
				std::vector<int> vertexCounts;
				const Tet& tet = mesh->primAt(i);

				// Collect all the vertices of the tet:
				bool invalid = false;
				for (int j = 0; j < 4; j++)
				{
					// This can't possibly be a mesh
					if (counts[tet[j]].size() < 4) { invalid = true; break; }
					vertexCounts.insert(vertexCounts.end(), counts[tet[j]].begin(), counts[tet[j]].end());
				}

				if (invalid) { continue; }

				// Because there can't be duplicates PER  each vertex this should work:
				std::sort(vertexCounts.begin(), vertexCounts.end());

				// Now we perform our check:
				std::vector<int> cellIndices;
				int currChecked = vertexCounts[0], count = 1;
				for (int j = 1; j < vertexCounts.size(); j++)
				{
					if (vertexCounts[j] == currChecked) { count++; }
					else
					{
						// Two tet can touch at most 3 points
						// The only one with 4 points will the main one were looking at
						if (count >= 3) { cellIndices.push_back(currChecked); }
						currChecked = vertexCounts[j];
						count = 1;
					}
				}

				// Make sure there are 5 tets in a cell:
				if (cellIndices.size() != 5) { continue; }
			    // We finally have a cell! We append it and keep looking:
				cells.push_back(SimTetCell<_VertType>(&tmesh, cellIndices.data()));
			}

			return SimTetCellMesh<_VertType>(std::move(cells));
		}
	}
}