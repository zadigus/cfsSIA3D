#include "Logger.hpp"

#include "Configuration/AppConfiguration.hpp"

#include <iostream>

Logger::Logger()
: m_INFLog(new OFFLog)
, m_WRNLog(new OFFLog)
, m_ERRLog(new OFFLog)
{
	m_VerboseLevels.emplace("INF", 1);
	m_VerboseLevels.emplace("WRN", 2);
	m_VerboseLevels.emplace("ERR", 3);
}

Logger::~Logger()
{
	m_Stream.close();
}

void Logger::init(const std::unique_ptr<N_Configuration::AppConfiguration>& aLoggerConf)
{ 
	N_Configuration::AppConfiguration::Parameter_sequence params(aLoggerConf->Parameter());
	for (N_Configuration::AppConfiguration::Parameter_const_iterator it(params.begin()); it != params.end(); ++it)
	{
		if (!strcmp(it->name().c_str(), "FileName"))
		{
			m_Stream.open(*it, std::ios::out); // TODO: see if that's cool; it may be better to close the file and use an append mode
		}

		if (!strcmp(it->name().c_str(), "Mode"))
		{
			std::string mode(*it);

			switch (m_VerboseLevels[mode])
			{
				case 1:
					m_INFLog.reset(new INFLog);
				case 2:
					m_WRNLog.reset(new WRNLog);
				case 3:
					m_ERRLog.reset(new ERRLog);
					break;
				default:
					std::cerr << "Unknown Logger mode" << std::endl;
					exit(EXIT_FAILURE);
			}
		}
	}
}

std::string Logger::coreMessage(const std::string& aFctSig, const std::string& aFileName, int aLineNb) const
{
	std::string tmp("[" + getDate() + "]");
	if (!aFctSig.empty())
		tmp += "[" + aFctSig + "]";
	if (!aFileName.empty())
		tmp += "[" + aFileName + "]";
	if (aLineNb)
		tmp += "[" + std::to_string(aLineNb) + "]";
	return tmp;
}

std::string Logger::getDate() const
{
	time_t rawtime;
	unsigned int dateSize(80);

	time(&rawtime);
	struct tm* timeinfo = localtime(&rawtime);
	char* tmp = new char[dateSize];
	strftime(tmp, dateSize, "%d/%m/%Y %H:%M:%S", timeinfo);
	std::string theDate(tmp);
	delete[] tmp;

	return theDate;
}