#ifndef GLACIER_H_
#define GLACIER_H_

#include <memory>

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

	class Glacier
	{
	public:
		~Glacier(); // for shared_ptr to be able to destroy the instance

		//static Glacier& getInstance();
		static std::shared_ptr<Glacier>& getInstance();
		// implement the construction of the physics components with the various factories
		void init(const std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysCoreConf);

		// Getters
		std::shared_ptr<MassBalance> B();
		std::shared_ptr<Rheology>    Rh();
		std::shared_ptr<SlidingLaw>  Sl();
		std::shared_ptr<Geometry>    G();
		std::shared_ptr<Grid>        b();
		std::shared_ptr<Grid>        H();

	private:
		Glacier();

		//Glacier(const Glacier& rhs); // TODO: that must be defined because we must not be able to copy a Singleton?
		//Glacier& operator=(const Glacier& rhs);
		
	private:
		//static Glacier* _instance;
	
		// Physics
		std::shared_ptr<MassBalance> _MassBalance;
		std::shared_ptr<Rheology>    _Rheology;
		std::shared_ptr<SlidingLaw>  _SlidingLaw;

		// Geometry
		std::shared_ptr<Geometry>    _Geometry;
	};

	inline std::shared_ptr<MassBalance> Glacier::B()
	{
		return _MassBalance;
	}

	inline std::shared_ptr<Rheology>    Glacier::Rh()
	{
		return _Rheology;
	}

	inline std::shared_ptr<SlidingLaw>  Glacier::Sl()
	{
		return _SlidingLaw;
	}

	inline std::shared_ptr<Geometry>  Glacier::G()
	{
		return _Geometry;
	}

}

#endif