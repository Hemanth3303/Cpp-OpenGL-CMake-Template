file(GLOB_RECURSE APPLICATION_SRC CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_executable(Application
	${APPLICATION_SRC}
)

set_target_properties(Application PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	OUTPUT_NAME Application
)

target_include_directories(Application
	PUBLIC

	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_SOURCE_DIR}/vendor/glad/include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
)

target_link_libraries(Application
	PUBLIC

	PRIVATE
		glad
		glfw
)

target_compile_definitions(Application
	PUBLIC
		# this allows to use include glad and glfw in any order.
		# without this, glad must always be included before glfw
		GLFW_INCLUDE_NONE
)

cmake_base_configure_target(Application)
cmake_base_apply_target_definitions(Application APPLICATION)
cmake_base_apply_os_definitions_to_target(Application APPLICATION)
cmake_base_apply_architecture_definitions_to_target(Application APPLICATION)
cmake_base_apply_compiler_definitions_to_target(Application APPLICATION)
cmake_base_apply_sanitizers(Application SANITIZERS ASAN UBSAN CONFIGS Debug)

# PLATFORM AND COMPILER SPECIFIC
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(MINGW)
		target_link_libraries(Application
			PRIVATE
				OpenGL::GL
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Application
			PRIVATE
				OpenGL::GL
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	if (TARGET OpenGL::OpenGL)
        target_link_libraries(Application
			PUBLIC
				OpenGL::OpenGL
		)
    else()
        target_link_libraries(Application
			PUBLIC
				OpenGL::GL
		)
    endif()
endif()

if(MSVC)
	target_link_options(Application PRIVATE
		"$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
		"$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
	)
endif()

# POST-BUILD RESOURCE COPY
add_custom_command(
	TARGET Application POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:Application>/res"
	COMMENT "Copying resource folder to binary directory"
)

# adding res to install
# cmake-base already handles bin, lib and include
# Note to future self:
# res/ means copy contents of res to bin/res
# if just res, then it will copy to bin/res/res
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res/"
    DESTINATION bin/res
)
