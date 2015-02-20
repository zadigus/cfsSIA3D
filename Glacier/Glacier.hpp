#ifndef GLACIER_H_
#define GLACIER_H_

#include <memory>

#include "Utility/Singleton.hpp"


class Grid;

namespace N_Configuration {
	class ModelConfiguration;
	class ModelCoreConfiguration;
	class Component;
}

namespace N_Glacier {

	class MassBalance;
	class Rheology;
	class SlidingLaw;
	class Geometry;
	class PhysicsCoreParams;

	class Glacier : public Singleton<Glacier>
	{
		friend class Singleton<Glacier>;

		public:
			// implement the construction of the physics components with the various factories
      void init(std::unique_ptr<N_Configuration::ModelConfiguration> a_PhysConf, std::unique_ptr<N_Configuration::ModelCoreConfiguration> a_PhysCoreConf);

			// Getters
			std::shared_ptr<MassBalance> B();
			std::shared_ptr<Rheology>    Rh();
			std::shared_ptr<SlidingLaw>  Sl();
			std::shared_ptr<Geometry>    G();

		private:
			Glacier();
			~Glacier();
			Glacier(const Glacier&); // not implemented
			Glacier& operator=(const Glacier&); // not implemented

			// Configuration setup
			void setComponent(const N_Configuration::Component& a_Comp, const PhysicsCoreParams& a_Core);

		private:
			// Physics
			std::shared_ptr<MassBalance> m_MassBalance;
			std::shared_ptr<Rheology>    m_Rheology;
			std::shared_ptr<SlidingLaw>  m_SlidingLaw;

			// Geometry
			std::shared_ptr<Geometry>    m_Geometry;
	};

	inline std::shared_ptr<MassBalance> Glacier::B()
	{
		return m_MassBalance;
	}

	inline std::shared_ptr<Rheology>    Glacier::Rh()
	{
		return m_Rheology;
	}

	inline std::shared_ptr<SlidingLaw>  Glacier::Sl()
	{
		return m_SlidingLaw;
	}

	inline std::shared_ptr<Geometry>  Glacier::G()
	{
		return m_Geometry;
	}

}

#endif
