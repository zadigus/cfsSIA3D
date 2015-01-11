#include "Logger.hpp"

#include <algorithm>
#include <functional>

#include "Configuration/AppConfiguration.hpp"

#include <iostream>

using namespace std::placeholders;

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

void Logger::applyParameter(const N_Configuration::Parameter& aParam)
{
	if (!strcmp(aParam.name().c_str(), "FileName"))
	{
		m_Stream.open(aParam.data(), std::ios::out); // TODO: see if that's cool; it may be better to close the file and use an append mode
	}

	if (!strcmp(aParam.name().c_str(), "Mode"))
	{
		std::string mode(aParam.data());

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

void Logger::init(const std::unique_ptr<N_Configuration::AppConfiguration>& aLoggerConf)
{ 
	if (!aLoggerConf)
	{
		std::cerr << "Logger configuration not specified." << std::endl;
		exit(EXIT_FAILURE);
	}

	N_Configuration::AppConfiguration::Parameter_sequence params(aLoggerConf->Parameter());
	std::for_each(params.begin(), params.end(), std::bind(&Logger::applyParameter, this, _1));
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