#ifndef PRIMALALGORITHM_HPP_
#define PRIMALALGORITHM_HPP_

#include <memory>
#include <map>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	class Glacier;
}

namespace N_Mathematics {

	// TODO: every output to the console (or the GUI) should be performed by means of the Observer Pattern

	class PrimalAlgorithm
	{
		public:
			PrimalAlgorithm(N_Configuration::Component* aComponent);
			virtual ~PrimalAlgorithm();

			virtual void Run() = 0; 
      
		protected:
			std::shared_ptr<N_Glacier::Glacier> m_glacier;
			std::map<std::string, std::string> m_parameters;
	};

}

#endif