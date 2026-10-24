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

cmake_base_configure_target(glad)
cmake_base_apply_target_definitions(glad GLAD)
cmake_base_apply_os_definitions_to_target(glad GLAD)
cmake_base_apply_architecture_definitions_to_target(glad GLAD)
cmake_base_apply_compiler_definitions_to_target(glad GLAD)

# Note to future self:
# include/ means copy contents of src to include/
# if just include, then it will copy to include/include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	FILES_MATCHING
		PATTERN "*.h"
)
