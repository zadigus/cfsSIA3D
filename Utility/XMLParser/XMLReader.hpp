#ifndef SIA3D_XMLREADER_H_
#define SIA3D_XMLREADER_H_

#include <xercesc/util/XercesDefs.hpp>
#include <memory>
#include <string>

XERCES_CPP_NAMESPACE_BEGIN
	class XercesDOMParser;
XERCES_CPP_NAMESPACE_END

class XMLReader
{
public:
	XMLReader();
	~XMLReader();

	void Read(std::string);

private:
	std::unique_ptr<xercesc::XercesDOMParser> _parser;

};

#endif