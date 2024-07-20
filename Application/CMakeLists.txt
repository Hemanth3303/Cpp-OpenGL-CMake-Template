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
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME Application
)

target_include_directories(Application
	PUBLIC
		
	PRIVATE
		${PROJECT_SOURCE_DIR}/vendor/glad/include
		${PROJECT_SOURCE_DIR}/vendor/glfw/include
		${PROJECT_SOURCE_DIR}/Application/src
)

target_compile_definitions(Application
	PUBLIC
		
	PRIVATE
		APPLICATION
)

target_link_libraries(Application
	PUBLIC
		
	PRIVATE
		glad
		glfw
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(Application
		PUBLIC
			
		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
			APP_WINDOWS
	)
	if (MSVC)
		target_compile_options(Application
			PUBLIC
				
			PRIVATE
				/Zc:__cplusplus
		)
	elseif (MINGW)
		target_link_libraries(Application
			PUBLIC
				
			PRIVATE
				m
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
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(Application
		PRIVATE
		APP_LINUX
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Application
			PUBLIC
				
			PRIVATE
				dl
				m
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
			APP_OSX
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Application
		PUBLIC
				
		PRIVATE
			APP_DEBUG
			DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Application
		PUBLIC
				
		PRIVATE
			APP_RELEASE
			NDEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Dist)
	remove_definitions(-DAPP_RELEASE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)

	target_compile_definitions(Application
		PUBLIC
				
		PRIVATE
			APP_DIST
			NDEBUG
	)

	if(MSVC)
		target_link_options(Application PRIVATE
			/SUBSYSTEM:WINDOWS
			/ENTRY:mainCRTStartup
		)
	endif()
endif()