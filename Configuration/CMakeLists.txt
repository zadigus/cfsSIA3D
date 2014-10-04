PROJECT(Configuration) 

FILE(GLOB src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.hpp")

XSD2CPPCLASS(PhysicsCoreConfiguration.xsd "http://www.ruag.com/PhysicsCoreConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(ModelConfiguration.xsd "http://www.ruag.com/ModelConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(Parameter.xsd "http://www.ruag.com/Parameter=N_Configuration")
XSD2CPPCLASS(AppConfiguration.xsd "http://www.ruag.com/AppConfiguration=N_Configuration" "http://www.ruag.com/Parameter=N_Configuration")

ADD_LIBRARY(Configuration ${src})