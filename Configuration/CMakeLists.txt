PROJECT(Configuration) 

INCLUDE_DIRECTORIES(
	${XSD_INCLUDE_DIRS}
	${XERCES_INCLUDE_DIRS}
)

FILE(GLOB src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.hpp")

XSD2CPPCLASS(ModelCoreConfiguration.xsd "http://www.cjcaesar.ch/ModelCoreConfiguration=N_Configuration" "http://www.cjcaesar.ch/Parameter=N_Configuration" "http://www.cjcaesar.ch/SubComponent=N_Configuration")
XSD2CPPCLASS(ModelConfiguration.xsd "http://www.cjcaesar.ch/ModelConfiguration=N_Configuration" "http://www.cjcaesar.ch/Parameter=N_Configuration" "http://www.cjcaesar.ch/SubComponent=N_Configuration")
XSD2CPPCLASS(Parameter.xsd "http://www.cjcaesar.ch/Parameter=N_Configuration")
XSD2CPPCLASS(SubComponent.xsd "http://www.cjcaesar.ch/SubComponent=N_Configuration" "http://www.cjcaesar.ch/Parameter=N_Configuration")
XSD2CPPCLASS(AppConfiguration.xsd "http://www.cjcaesar.ch/AppConfiguration=N_Configuration" "http://www.cjcaesar.ch/Parameter=N_Configuration" "http://www.cjcaesar.ch/SubComponent=N_Configuration")

ADD_LIBRARY(${PROJECT_NAME} ${src})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${XERCES_LIBRARIES})

FILE(GLOB includes RELATIVE "${PROJECT_SOURCE_DIR}" "*.xsd")
INSTALL(FILES ${includes}	DESTINATION ${CMAKE_INSTALL_PREFIX}/Configuration/)

FILE(GLOB includes RELATIVE "${PROJECT_SOURCE_DIR}" "../Config/*.xml")
INSTALL(FILES ${includes}	DESTINATION ${CMAKE_INSTALL_PREFIX}/Config/)
