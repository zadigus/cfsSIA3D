#ifndef PHYSICALMODEL_H_
#define PHYSICALMODEL_H_

#include <memory>

namespace N_Configuration {
	class ModelConfiguration;
	class PhysicsCoreConfiguration;
}

namespace N_Physics {

	class MassBalance;
	class Rheology;
	class SlidingLaw;

	class PhysicsModel
	{
	public:
		static PhysicsModel& getInstance();
		// implement the construction of the physics components with the various factories
		void init(std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, std::unique_ptr<N_Configuration::PhysicsCoreConfiguration>& aPhysCoreConf);

	private:
		PhysicsModel();
		~PhysicsModel();

	private:
		std::shared_ptr<MassBalance> _MassBalance;
		std::shared_ptr<Rheology>    _Rheology;
		std::shared_ptr<SlidingLaw>  _SlidingLaw;
	};

}

#endif