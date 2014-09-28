MACRO (XSD2CPPCLASS xsd_file)
	GET_FILENAME_COMPONENT(xsd_base_name "${xsd_file}" NAME_WE)
	SET(xsd_file_path ${CONFIG_PATH}/${xsd_file})
	SET(HPP_SUFFIX "hpp")
	SET(CPP_SUFFIX "cpp")

	INCLUDE_DIRECTORIES(
		${XSD_INCLUDE_DIR}
		${XERCES_INCLUDE_DIRS}
	)
	
	SET(XSD_ARGS "cxx-tree" --std c++11 --hxx-suffix ".${HPP_SUFFIX}"  --cxx-suffix ".${CPP_SUFFIX}" --root-element-last)# --namespace-map ${namespacemap}) #"http://www.ruag.com/PhysicsConfiguration=N_Physics")
	
	FOREACH(arg  ${ARGN})
		LIST(APPEND XSD_ARGS --namespace-map ${arg})
	ENDFOREACH()
	
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${HPP_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${CPP_SUFFIX}
		COMMAND ${XSD_EXECUTABLE} 
		ARGS ${XSD_ARGS} ${xsd_file_path}
		VERBATIM
	)

	SET_PROPERTY(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${HPP_SUFFIX} PROPERTY GENERATED TRUE)
	SET_PROPERTY(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${CPP_SUFFIX} PROPERTY GENERATED TRUE)

	LIST(APPEND src ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${HPP_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/${xsd_base_name}.${CPP_SUFFIX} ${xsd_file_path})
ENDMACRO ()