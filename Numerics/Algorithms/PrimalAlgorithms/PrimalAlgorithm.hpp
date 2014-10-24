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

	class PrimalAlgorithm
	{
		public:
			PrimalAlgorithm(N_Configuration::Component* aComponent);
			virtual ~PrimalAlgorithm();

			virtual void Run() = 0; 
      
		protected:
			std::shared_ptr<N_Glacier::Glacier> _glacier;
			std::map<std::string, std::string> _parameters;
	};

}

#endif