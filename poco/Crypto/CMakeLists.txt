# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO( SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h" )
POCO_HEADERS_AUTO( SRCS ${HDRS_G})

include_directories(${OPENSSL_INCLUDE_DIR})

add_library(Crypto ${SRCS} )
add_library(Poco::Crypto ALIAS Crypto)
set_target_properties(Crypto
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME PocoCrypto
    DEFINE_SYMBOL Crypto_EXPORTS
    )

target_link_libraries(Crypto Poco::Foundation)
		target_link_libraries(Crypto debug ${LIB_EAY_DEBUG})
		target_link_libraries(Crypto optimized ${LIB_EAY_RELEASE})
		target_link_libraries(Crypto debug ${SSL_EAY_DEBUG})
		target_link_libraries(Crypto optimized ${SSL_EAY_RELEASE})
target_include_directories(Crypto
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

if(MSVC AND POCO_DISABLE_INTERNAL_OPENSSL)
    target_compile_definitions(Crypto PUBLIC POCO_EXTERNAL_OPENSSL)	
endif()

POCO_INSTALL(Crypto)
POCO_GENERATE_PACKAGE(Crypto)

if (POCO_ENABLE_TESTS)
    add_subdirectory(testsuite)
endif ()
if (POCO_ENABLE_SAMPLES)
    add_subdirectory(samples)
endif ()

configure_file(PocoCrypto.pc.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/PocoCrypto.pc @ONLY)
list(APPEND POCO_PKG_CONFIG_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/PocoCrypto.pc)
set(POCO_PKG_CONFIG_FILES ${POCO_PKG_CONFIG_FILES} PARENT_SCOPE)
