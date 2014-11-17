#ifndef GLACIER_H_
#define GLACIER_H_

#include <memory>

#include "Utility/Singleton.hpp"

class Grid;

namespace N_Configuration {
	class ModelConfiguration;
	class ModelCoreConfiguration;
}

namespace N_Glacier {

	class MassBalance;
	class Rheology;
	class SlidingLaw;
	class Geometry;

	class Glacier : public Singleton<Glacier>
	{
		friend class Singleton<Glacier>;

		public:
			// implement the construction of the physics components with the various factories
			void init(const std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysCoreConf);

			// Getters
			std::shared_ptr<MassBalance> B();
			std::shared_ptr<Rheology>    Rh();
			std::shared_ptr<SlidingLaw>  Sl();
			std::shared_ptr<Geometry>    G();
			std::shared_ptr<Grid>        b();
			std::shared_ptr<Grid>        H();
			std::shared_ptr<Grid>        gradbx();
			std::shared_ptr<Grid>        gradby();

		private:
			Glacier();
			~Glacier(); 

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