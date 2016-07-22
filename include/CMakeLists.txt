file(GLOB LOCAL_SOURCES
	"*.cpp"
	"*.hpp"
	)

set(PROJECT_SOURCES
    ${PROJECT_SOURCES}
	${LOCAL_SOURCES}
    PARENT_SCOPE
    )

configure_file(
    "${PROJECT_SOURCE_DIR}/include/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
    )