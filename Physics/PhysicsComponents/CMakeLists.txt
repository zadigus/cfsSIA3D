PROJECT(PhysicsComponents) 

ADD_SUBDIRECTORY(SlidingLaw)
ADD_SUBDIRECTORY(Rheology)
ADD_SUBDIRECTORY(MassBalance)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${XSD_INCLUDE_DIRS}
	${XERCES_INCLUDE_DIRS}
)

FILE(GLOB src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.hpp")

XSD2CPPCLASS(PhysicsCoreConfiguration.xsd "http://www.ruag.com/PhysicsCoreConfiguration=N_Physics" "http://www.ruag.com/Parameter=N_Physics")
XSD2CPPCLASS(PhysicsConfiguration.xsd "http://www.ruag.com/PhysicsConfiguration=N_Physics" "http://www.ruag.com/Parameter=N_Physics")
XSD2CPPCLASS(Parameter.xsd "http://www.ruag.com/Parameter=N_Physics")

ADD_LIBRARY(PhysicsComponents ${src})
TARGET_LINK_LIBRARIES(PhysicsComponents
	${XERCES_LIBRARIES}
#	MassBalance
#	Rheology
#	SlidingLaw
)
