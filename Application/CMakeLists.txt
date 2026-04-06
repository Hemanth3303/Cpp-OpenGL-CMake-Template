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

	PRIVATE
		APPLICATION
)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(Application
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
			APPLICATION_PLATFORM_WINDOWS
	)

	if(MSVC)
		target_compile_options(Application
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
		)
	elseif(MINGW)
		target_link_libraries(Application
			PUBLIC
				m
			PRIVATE
				OpenGL::GL
		)
		target_link_options(Application
			PUBLIC

			PRIVATE
				-static
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Application
			PUBLIC

			PRIVATE
				OpenGL::GL
		)
		target_link_options(Application
			PUBLIC

			PRIVATE
				-static
				-static-libstdc++
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	target_compile_definitions(Application
		PUBLIC

		PRIVATE
			APPLICATION_PLATFORM_LINUX
	)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Application
			PUBLIC
				dl
				m
				pthread
			PRIVATE
				OpenGL::OpenGL
				X11
		)
		target_link_options(Application
			PUBLIC

			PRIVATE
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Application
			PUBLIC

			PRIVATE
				OpenGL::OpenGL
				X11
		)
		target_link_options(Application
			PUBLIC

			PRIVATE
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

	target_compile_definitions(Application
		PUBLIC

		PRIVATE
			APPLICATION_PLATFORM_OSX
	)

endif()

if(MSVC)
	target_link_options(Application PRIVATE
		"$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
		"$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
	)
endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(Application
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:APPLICATION_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:APPLICATION_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:APPLICATION_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)

# POST-BUILD RESOURCE COPY

add_custom_command(
	TARGET Application POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/res"
		"$<TARGET_FILE_DIR:Application>/res"
	COMMENT "Copying resource folder to binary directory"
)
