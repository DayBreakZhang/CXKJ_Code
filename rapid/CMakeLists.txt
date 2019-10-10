# Sources
file(GLOB SRCS_G "src/*.cpp")
CXKJ_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
CXKJ_HEADERS_AUTO( SRCS ${HDRS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.hpp" )
CXKJ_HEADERS_AUTO( SRCS ${HDRS_G})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/CXKJ)

add_library(Rapid ${SRCS} )
add_library(CXKJ::Rapid ALIAS Rapid)
set_target_properties(Rapid
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
	OUTPUT_NAME CXKJRapid
    DEFINE_SYMBOL Rapid_EXPORTS
    )
target_include_directories(Rapid
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(Rapid
        PUBLIC
            CXKJ_STATIC
    )
elseif(MINGW)
	target_compile_definitions(Rapid
		PUBLIC
			_DLL)
endif()

CXKJ_INSTALL(Rapid)
CXKJ_GENERATE_PACKAGE(Rapid)

configure_file(CXKJRapid.pc.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJRapid.pc @ONLY)
list(APPEND CXKJ_PKG_CONFIG_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJRapid.pc)
set(CXKJ_PKG_CONFIG_FILES ${CXKJ_PKG_CONFIG_FILES} PARENT_SCOPE)