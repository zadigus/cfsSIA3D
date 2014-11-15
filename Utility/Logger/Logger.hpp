#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <string>
#include <map>
#include <fstream>

#include "Log.hpp"

#define LOG_TRC(msg) Logger::getInstance().trace(msg, __FUNCSIG__, __FILE__, __LINE__) 
// TODO: that mode must write "ENTERING function ..." / "LEAVING fucntion"
/*#define LOG_TRC tracer_t _token(__func__)
struct tracer_t {
    char const* fname;
    tracer_t(char const* fname_): fname(fname_) { printin(fname); }
    ~tracer_t() { printout(fname); }
}*/
#define LOG_INF(msg) Logger::getInstance().info(msg, __FUNCSIG__, __FILE__, __LINE__)
#define LOG_WRN(msg) Logger::getInstance().warning(msg, __FUNCSIG__, __FILE__, __LINE__)
#define LOG_ERR(msg) Logger::getInstance().error(msg, __FUNCSIG__, __FILE__, __LINE__)

namespace N_Configuration {
	class AppConfiguration;
}

class Log;

class Logger
{
	public:
		static Logger& getInstance();
		void init(const std::unique_ptr<N_Configuration::AppConfiguration>& aLoggerConf); 

		void trace(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb);
		void info(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb);
		void warning(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb);
		void error(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb);

	private:
		Logger();
		~Logger();
	
		std::string coreMessage(std::string aFctSig, std::string aFileName, int aLineNb);
		std::string getDate();

	private:
		std::map<std::string, unsigned int> m_VerboseLevels;
		std::ofstream m_Stream; // TODO: allow for log output in the console too

		// Strategy pattern for the Logs
		std::unique_ptr<Log> m_TRCLog;
		std::unique_ptr<Log> m_INFLog;
		std::unique_ptr<Log> m_WRNLog;
		std::unique_ptr<Log> m_ERRLog;
};

inline void Logger::trace(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb)
{
	m_Stream << m_TRCLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage) << std::endl;
}

inline void Logger::info(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb)
{
	m_Stream << m_INFLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage) << std::endl;
}

inline void Logger::warning(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb)
{
	m_Stream << m_WRNLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage) << std::endl;
}

inline void Logger::error(std::string aMessage, std::string aFctSig, std::string aFileName, int aLineNb)
{
	m_Stream << m_ERRLog->message(coreMessage(aFctSig, aFileName, aLineNb) + " : " + aMessage) << std::endl;
}

#endif
