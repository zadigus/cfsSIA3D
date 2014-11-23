#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <string>
#include "Utility/Singleton.hpp"

class Backend : public Singleton<Backend>
{
	friend class Singleton<Backend>;

	public:
		void init(const std::string& aAppConfFileName);
		void run();
};

#endif