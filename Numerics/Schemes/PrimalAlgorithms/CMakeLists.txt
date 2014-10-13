PROJECT(PrimalAlgorithms)

ADD_SUBDIRECTORY(ProjectionAlgorithms)
ADD_SUBDIRECTORY(DiffusionAlgorithms)
ADD_SUBDIRECTORY(ClimateAlgorithms)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../..
	${CMAKE_CURRENT_BINARY_DIR}/../../..
	${XSD_INCLUDE_DIRS}
	${XERCES_INCLUDE_DIRS}
)

FILE(GLOB src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp" "*.hpp")

ADD_LIBRARY(PrimalAlgorithms ${src})

TARGET_LINK_LIBRARIES(PrimalAlgorithms
	ProjectionAlgorithms
	ClimateAlgorithms
	DiffusionAlgorithms
)
