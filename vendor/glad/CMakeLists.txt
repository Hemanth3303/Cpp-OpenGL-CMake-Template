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
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE

)

target_compile_definitions(glad
	PUBLIC

	PRIVATE
		GLAD
)

# PLATFORM AND COMPILER SPECIFIC

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	target_compile_definitions(glad
		PUBLIC

		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
			GLAD_PLATFORM_WINDOWS
	)

	if(MSVC)
		target_compile_options(glad
			PUBLIC

			PRIVATE
				/Zc:__cplusplus
		)
	elseif(MINGW)
		target_link_libraries(glad
			PUBLIC
				m
			PRIVATE

		)
		target_link_options(glad
			PUBLIC

			PRIVATE
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
		)
	endif()

endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

	target_compile_definitions(glad
		PUBLIC

		PRIVATE
			GLAD_PLATFORM_LINUX
	)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(glad
			PUBLIC
				dl
				m
				pthread
			PRIVATE

		)
		target_link_options(glad
			PUBLIC

			PRIVATE
				-static-libgcc
				-static-libstdc++
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

	target_compile_definitions(glad
		PUBLIC

		PRIVATE
			GLAD_PLATFORM_OSX
	)

endif()

# CONFIGURATION SPECIFIC

target_compile_definitions(glad
	PUBLIC

	PRIVATE
		$<$<CONFIG:Debug>:GLAD_DEBUG_BUILD>
		$<$<CONFIG:Debug>:DEBUG>

		$<$<CONFIG:Profile>:GLAD_PROFILE_BUILD>
		$<$<CONFIG:Profile>:NDEBUG>

		$<$<CONFIG:Release>:GLAD_RELEASE_BUILD>
		$<$<CONFIG:Release>:NDEBUG>
)
