#pragma once

#include "../particles/Particle.hpp"

namespace ee
{
	// A very basic spring structure

	class Spring
	{
	public:
		Spring(Float stiff, Float damp, Particle* p0, Particle* p1) :
			stiffness(stiff), dampening(damp), m_p0(p0), m_p1(p1) { restLength = glm::length(p1->cPos - p0->cPos); }
		Spring(Float stiff, Float damp, Float len, Particle* p0, Particle* p1) :
			stiffness(stiff), dampening(damp), restLength(len), m_p0(p0), m_p1(p1) {}

		void applyForce() const
		{
			const Vec3 dir = m_p0->cPos - m_p1->cPos;
			const Float currLength = glm::length(dir);
			const Vec3 normDir = glm::normalize(dir);
			Vec3 force = -stiffness * ((currLength - restLength) * dir);
			force += -dampening * glm::dot(m_p0->cVel - m_p1->cVel, dir) * normDir;
			m_p0->rForce += force;
			m_p1->rForce -= force;
		}

	public:
		Float stiffness;
		Float dampening;
		Float restLength;

	private:
		Particle* m_p0;
		Particle* m_p1;
	};
}