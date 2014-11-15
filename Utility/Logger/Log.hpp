#ifndef LOG_HPP
#define LOG_HPP

#include <string>

class Log
{
	public:
		Log(std::string aTag) : m_Tag(aTag) { };
		virtual ~Log() { };

		virtual std::string message(std::string aMessage)
		{
			return m_Tag + " : " + aMessage;
		}
	
	protected:
		std::string m_Tag;
};

class TRCLog : public Log
{
public:
	TRCLog() : Log("TRC") { }
	virtual ~TRCLog() { };
};

class INFLog : public Log
{
	public:
		INFLog() : Log("INF") { }
		virtual ~INFLog() { };
};

class WRNLog : public Log
{
public:
	WRNLog() : Log("WRN") { }
	virtual ~WRNLog() { };
};

class ERRLog : public Log
{
public:
	ERRLog() : Log("ERR") { }
	virtual ~ERRLog() { };
};

class OFFLog : public Log
{
public:
	OFFLog() : Log("") { }
	virtual ~OFFLog() { };

	virtual std::string message(std::string aMessage)
	{
		return "";
	}

};

#endif