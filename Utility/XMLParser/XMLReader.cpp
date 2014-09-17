#include "XMLReader.hpp"
#include <iostream>

#include <xercesc/parsers/XercesDOMParser.hpp>

XMLReader::XMLReader()
{
	xercesc::XMLPlatformUtils::Initialize();

	_parser.reset(new xercesc::XercesDOMParser); // this MUST come after xerces initialization
}

void XMLReader::Read(std::string fileName)
{
	_parser->setValidationScheme(xercesc::XercesDOMParser::Val_Auto);
	_parser->setDoNamespaces(true);
	_parser->setDoSchema(true);

	_parser->parse(fileName.c_str());
	// no need to free this pointer - owned by the parent parser object
	xercesc::DOMDocument* xmlDoc = _parser->getDocument();
	
	// Get the top-level element: Name is "root". No attributes for "root"
	xercesc::DOMElement* elementRoot = xmlDoc->getDocumentElement();
	if (!elementRoot) throw(std::runtime_error("empty XML document"));
	std::cout << "XML Read" << std::endl;
}

XMLReader::~XMLReader()
{
	xercesc::XMLPlatformUtils::Terminate();
}