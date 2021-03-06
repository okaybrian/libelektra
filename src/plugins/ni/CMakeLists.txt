include (LibAddMacros)

set (NI ${CMAKE_CURRENT_SOURCE_DIR}/nickel-1.1.0)

file (GLOB NI_FILES ${NI}/src/*.c ${NI}/src/*.h)

if (DEPENDENCY_PHASE AND ENABLE_ASAN)
	remove_plugin (ni "ni reports runtime errors about unsigned integer overflows if you compile it using AddressSanitizer")
endif (DEPENDENCY_PHASE AND ENABLE_ASAN)

add_plugin (ni SOURCES ni.h ni.c ${NI_FILES} INCLUDE_DIRECTORIES ${NI}/include ${NI}/src/include LINK_ELEKTRA elektra-ease ADD_TEST)

if (ADDTESTING_PHASE)
	file (GLOB NI_INI_FILES ${NI}/src/tests/*.ini)
	foreach (NI_INI_FILE ${NI_INI_FILES})
		copy_file (${NI_INI_FILE} "${CMAKE_CURRENT_BINARY_DIR}")
	endforeach ()
endif ()
