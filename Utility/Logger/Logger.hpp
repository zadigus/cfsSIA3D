#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "Utility/Singleton.hpp"
#include "Log.hpp"

#define LOG_INF(msg) \
	{ \
	std::stringstream tmp; \
	tmp << msg; \
	Logger::getInstance().info(tmp, __FUNCTION__); \
	}
#define LOG_WRN(msg) \
	{ \
	std::stringstream tmp; \
	tmp << msg; \
	Logger::getInstance().warning(tmp, __FUNCTION__); \
	}
#define LOG_ERR(msg) \
	{ \
	std::stringstream tmp; \
	tmp << msg; \
	Logger::getInstance().error(tmp, __FUNCSIG__, __FILE__, __LINE__); \
	}

namespace N_Configuration {
	class AppConfiguration;
}

class Log;

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

	public:
		void init(const std::unique_ptr<N_Configuration::AppConfiguration>& aLoggerConf); 

		void info(std::stringstream& aMessage, const std::string& aFctSig = std::string(), const std::string& aFileName = std::string(), int aLineNb = 0); // more efficient to pass const string& as only string because no copy ctor is called 
		void warning(std::stringstream& aMessage, const std::string& aFctSig = std::string(), const std::string& aFileName = std::string(), int aLineNb = 0);
		void error(std::stringstream& aMessage, const std::string& aFctSig = std::string(), const std::string& aFileName = std::string(), int aLineNb = 0);

	private:
		Logger();
		~Logger();
	
		std::string coreMessage(const std::string& aFctSig = std::string(), const std::string& aFileName = std::string(), int aLineNb = 0) const;
		std::string getDate() const;

	private:
		std::map<std::string, unsigned int> m_VerboseLevels;
		std::ofstream m_Stream; // TODO: allow for log output to the console too

		// Strategy pattern for the Logs
		std::unique_ptr<Log> m_INFLog;
		std::unique_ptr<Log> m_WRNLog;
		std::unique_ptr<Log> m_ERRLog;
};

inline void Logger::info(std::stringstream& aMessage, const std::string& aFctSig, const std::string& aFileName, int aLineNb) 
{
	m_Stream << m_INFLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage.str() + "\n") << std::flush;
}

inline void Logger::warning(std::stringstream& aMessage, const std::string& aFctSig, const std::string& aFileName, int aLineNb) 
{
	m_Stream << m_WRNLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage.str() + "\n") << std::flush;
}

inline void Logger::error(std::stringstream& aMessage, const std::string& aFctSig, const std::string& aFileName, int aLineNb) 
{
	m_Stream << m_ERRLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage.str() + "\n") << std::flush;
}

#endif
