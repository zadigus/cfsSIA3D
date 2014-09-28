#ifndef PHYSICALMODEL_H_
#define PHYSICALMODEL_H_

#include <memory>

namespace N_Physics {

	class PhysicsConfiguration;
	class PhysicsCoreConfiguration;

	class MassBalance;
	class Rheology;
	class SlidingLaw;

	class PhysicsModel
	{
	public:
		static PhysicsModel& getInstance();
		// implement the construction of the physics components with the various factories
		void init(std::unique_ptr<PhysicsConfiguration>& aPhysConf, std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf);

	private:
		//PhysicsModel(std::unique_ptr<PhysicsConfiguration>& aPhysConf, std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf);
		PhysicsModel();
		~PhysicsModel();

	private:
		std::shared_ptr<MassBalance> _MassBalance;
		std::shared_ptr<Rheology>    _Rheology;
		std::shared_ptr<SlidingLaw>  _SlidingLaw;
	};

}

#endif