add_library(glad STATIC
	"src/glad.c"
	"include/glad/glad.h"
	"include/KHR/khrplatform.h"
)

set_target_properties(glad PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME glad
)

target_include_directories(glad 
	PRIVATE
		
	PUBLIC
		${PROJECT_SOURCE_DIR}/vendor/glad/include
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(glad
		PUBLIC
			
		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
	)
	if (MSVC)
		target_compile_options(glad 
			PRIVATE
				"/MT$<$<CONFIG:Debug>:d>"
		)
	elseif (MINGW)
		target_link_libraries(glad 
			PUBLIC
				
			PRIVATE
				m
		)
		target_link_options(glad 
			PUBLIC
				
			PRIVATE
				-static
				-static-libgcc
				-static-libstdc++
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(glad 
			PUBLIC
				
			PRIVATE
				
		)
		target_link_options(glad 
			PUBLIC
				
			PRIVATE
				-static
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(glad
			PUBLIC
				
			PRIVATE
				dl
				m
  				pthread
		)
		target_link_options(glad
			PUBLIC
				
			PRIVATE
				
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(glad
			PUBLIC
				
			PRIVATE
				
		)
		target_link_options(glad
			PUBLIC
				
			PRIVATE
				
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	# osx stuff idk
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(glad
		PUBLIC
				
		PRIVATE
			DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(glad
		PUBLIC
				
		PRIVATE
			NDEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Dist)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	remove_definitions(-DAPP_RELEASE)
	target_compile_definitions(glad
		PUBLIC
				
		PRIVATE
			NDEBUG
	)
endif()