include (LibAddBinding)

if (DEPENDENCY_PHASE)
	if (APPLE)
		set (CMAKE_FIND_FRAMEWORK "LAST")
	endif ()
	find_package (Ruby)
	find_swig ()
	check_binding_included ("swig_ruby" BINDING_WAS_ADDED SUBDIRECTORY "swig/ruby" SILENT)

	# Disable on GCC 4 and earlier:
	# - https://build.libelektra.org/jenkins/job/elektra-gcc47-all
	# - https://build.libelektra.org/jenkins/job/elektra-gcc-configure-debian-wheezy
	set (SUPPORTED_COMPILER (NOT ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 5)))

	if (RUBY_FOUND AND SWIG_FOUND AND BINDING_WAS_ADDED AND ${SUPPORTED_COMPILER})
		include (LibAddMacros)

		add_custom_command (OUTPUT runtime.h COMMAND ${SWIG_EXECUTABLE} -c++ -ruby -external-runtime runtime.h)

		# we call this SWIG_COMPILE_FLAGS because we have the same variable in our swig bindings
		set (SWIG_COMPILE_FLAGS
		     "-Wno-shadow -Wno-old-style-cast -Wno-unused-variable -Wno-unused-parameter -Wno-reserved-user-defined-literal")

		# Disable warnings produced by generated code
		if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
			set (SWIG_COMPILE_FLAGS "${SWIG_COMPILE_FLAGS} -Wno-deprecated-register")
			set (SWIG_COMPILE_FLAGS "${SWIG_COMPILE_FLAGS} -Wno-macro-redefined")
		elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
			set (SWIG_COMPILE_FLAGS "${SWIG_COMPILE_FLAGS} -Wno-literal-suffix")
		endif ()

		set_source_files_properties ("ruby.cpp" PROPERTIES COMPILE_FLAGS "${SWIG_COMPILE_FLAGS}")
	elseif (NOT RUBY_FOUND)
		remove_plugin (ruby "ruby not found")
	elseif (NOT ${SUPPORTED_COMPILER})
		remove_plugin (ruby "gcc version too old (gcc -dumpversion < 5.0)")
	elseif (NOT SWIG_FOUND)
		remove_plugin (ruby "swig not found")
	elseif (NOT BINDING_WAS_ADDED)
		remove_plugin (ruby "swig_ruby binding is required")
	endif ()
endif ()

add_plugin (ruby
	    CPP
	    SOURCES ruby.hpp
		    ruby.cpp
		    ${CMAKE_CURRENT_BINARY_DIR}/runtime.h
	    INCLUDE_DIRECTORIES ${RUBY_INCLUDE_DIRS}
	    LINK_LIBRARIES ${RUBY_LIBRARY}
	    COMPILE_DEFINITIONS SWIG_TYPE_TABLE=kdb
				SWIG_RUNTIME=\"runtime.h\")

# ~~~
# if (ADDTESTING_PHASE)
#    	# bindings are required for tests
#    	check_binding_was_added ("swig_python" BINDING_WAS_ADDED)
#    	if (NOT BUILD_SHARED AND BUILD_TESTING AND BINDING_WAS_ADDED)
#    		# test environment clears env so setting PYTHONPATH is no option
#    		# we workaround this by changing the current directory to our bindings
#    		# output directory + our test adds the current directory to pythons sys.path
#    		add_plugintest (python
#    			MEMLEAK
#    			WORKING_DIRECTORY
#    				${CMAKE_CURRENT_BINARY_DIR}/../../bindings/swig/python/
#    		)
#
#    		if (INSTALL_TESTING)
#    			install (DIRECTORY python DESTINATION ${TARGET_TEST_DATA_FOLDER})
#    		endif ()
#    	else ()
#    		message (WARNING "swig_python bindings are required for testing, test deactivated")
#    	endif ()
# endif ()
# ~~~
