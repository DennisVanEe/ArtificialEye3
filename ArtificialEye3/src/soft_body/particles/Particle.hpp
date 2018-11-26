#pragma once

#include "../../shared/ArtificialEye.hpp"

namespace ee
{
	// passive objects will act like the muscle in this case
	enum class ParticleType { PASSIVE, ACTIVE };

	class Particle
	{
	public:
		Particle(Float mass, ParticleType type) :
			m_type(type),
			m_mass(mass) {}

		void resetForces() { m_rForce = Vec3(0); }

		virtual void update(Float time) = 0;
		virtual Particle* getCopy() const = 0;

	public:
		Vec3  m_cPos;
		Vec3  m_pPos;
		Vec3  m_cVel;
		Vec3  m_rForce;
		Float m_mass;

		ParticleType m_type;
	};
}