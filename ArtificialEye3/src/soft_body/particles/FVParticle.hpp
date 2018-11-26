#pragma once

#include "Particle.hpp"

namespace ee
{
	class FVParticle : public Particle
	{
	public:
		FVParticle(Float mass) :
			Particle(mass, ParticleType::ACTIVE) {}

		void update(Float time) override;
		Particle* getCopy() const override;

	private:

	};
}