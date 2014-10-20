PROJECT(Configuration) 

INCLUDE_DIRECTORIES(
	${XSD_INCLUDE_DIRS}
	${XERCES_INCLUDE_DIRS}
)

FILE(GLOB src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.hpp")

XSD2CPPCLASS(ModelCoreConfiguration.xsd "http://www.ruag.com/ModelCoreConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(ModelConfiguration.xsd "http://www.ruag.com/ModelConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(Parameter.xsd "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(AppConfiguration.xsd "http://www.ruag.com/AppConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")

ADD_LIBRARY(Configuration ${src})