# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
POCO_HEADERS_AUTO( SRCS ${HDRS_G})

include_directories(${OPENSSL_INCLUDE_DIR})

add_library(NetSSL ${SRCS} )
add_library(Poco::NetSSL ALIAS NetSSL)
set_target_properties( NetSSL
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
	OUTPUT_NAME PocoNetSSL
    DEFINE_SYMBOL NetSSL_EXPORTS
    )

target_link_libraries(NetSSL Poco::Crypto Poco::Util Poco::Net)

		target_link_libraries(NetSSL debug ${LIB_EAY_DEBUG})
		target_link_libraries(NetSSL optimized ${LIB_EAY_RELEASE})
		target_link_libraries(NetSSL debug ${SSL_EAY_DEBUG})
		target_link_libraries(NetSSL optimized ${SSL_EAY_RELEASE})
target_include_directories(NetSSL
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

POCO_INSTALL(NetSSL)
POCO_GENERATE_PACKAGE(NetSSL)

if (POCO_ENABLE_TESTS)
    add_subdirectory(testsuite)
endif ()
if (POCO_ENABLE_SAMPLES)
    add_subdirectory(samples)
endif ()

configure_file(PocoNetSSL.pc.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/PocoNetSSL.pc @ONLY)
list(APPEND POCO_PKG_CONFIG_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/PocoNetSSL.pc)
set(POCO_PKG_CONFIG_FILES ${POCO_PKG_CONFIG_FILES} PARENT_SCOPE)
