#ifndef PHYSICALMODEL_H_
#define PHYSICALMODEL_H_

#include <memory>

class PhysicsConfiguration;
class PhysicsCoreConfiguration;
class MassBalance;
class Rheology;
class SlidingLaw;

class PhysicalModel 
{
	public: 
		// implement the construction of the physics components with the various factories
		PhysicalModel(std::unique_ptr<PhysicsConfiguration>& aPhysConf, std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf);
		~PhysicalModel();
	private:
		std::shared_ptr<MassBalance> _MassBalance;
		std::shared_ptr<Rheology>    _Rheology;
		std::shared_ptr<SlidingLaw>  _SlidingLaw;
};

#endif