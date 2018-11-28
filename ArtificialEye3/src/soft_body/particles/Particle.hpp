#pragma once

#include <memory>
#include "../../shared/ArtificialEye.hpp"

namespace ee
{
	class Particle
	{
	public:
		// free refers to whether or not a particle can move:
		Particle() {}
		Particle(Float mass, bool free) : mass(mass), free(free) {}

		void resetForces() { rForce = Vec3(0); }

	public:
		Vec3  cPos;   // current position
		Vec3  pPos;   // previous position

		Vec3  cVel;   // current velocity
		Vec3  rForce; // all forces on the object
		Float mass;

		bool  free;
	};

	// A particle associated with a vertex in a mesh
	class MeshParticle : public Particle
	{
	public:
		MeshParticle(Float mass, bool free, int index, Vec3 pos) :
			Particle(mass, free), vertIndex(index) {
			cPos = pPos = pos;
		}

	public:
		const int vertIndex;
	};
}