# Sources
file(GLOB SRCS_G "src//RCF/RCF.cpp")
CXKJ_SOURCES_AUTO( SRCS ${SRCS_G})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/CXKJ)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/boost19/include)

add_library(Rcff ${SRCS} )
add_library(CXKJ::Rcff ALIAS Rcff)

target_include_directories(Rcff
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/boost19/lib)
IF(MSVC)
if (CXKJ_ENABLE_RCFF_OPENSSL)
   ADD_DEFINITIONS( -DRCF_USE_OPENSSL)
   include_directories(${OPENSSL_INCLUDE_DIR})
   if(BUILD_SHARED_LIBS)#动态库
		target_link_libraries(Rcff debug ${LIB_EAY_DEBUG})
		target_link_libraries(Rcff optimized ${LIB_EAY_RELEASE})
		target_link_libraries(Rcff debug ${SSL_EAY_DEBUG})
		target_link_libraries(Rcff optimized ${SSL_EAY_RELEASE})
   else(NOT BUILD_SHARED_LIBS)#静态库
		
   endif()
endif ()
if (CXKJ_ENABLE_RCFF_ZLIB)
    ADD_DEFINITIONS(-DRCF_USE_ZLIB)
	include_directories(${CMAKE_INSTALL_PREFIX}/include/CXKJ)
	if(MSVC)
		target_link_libraries(Rcff debug ${CMAKE_INSTALL_PREFIX}/lib/CXKJZLIBd.lib)
		target_link_libraries(Rcff optimized ${CMAKE_INSTALL_PREFIX}/lib/CXKJZLIB.lib)
	else()
	endif()	
endif ()
	ADD_DEFINITIONS( -D_WIN32_WINNT=0x601 -DWIN32_LEAN_AND_MEAN )
    target_link_libraries(Rcff debug "ws2_32")
	target_link_libraries(Rcff optimized "ws2_32")
	IF(CMAKE_CL_64)
		set_target_properties(Rcff
			PROPERTIES
			VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
			OUTPUT_NAME Rcff
			COMPILE_FLAGS "${CMAKE_CXX_FLAGS} /bigobj" 
		)
	ENDIF()
ELSE()
    target_link_libraries(Rcff DEBUG "pthread" "dl" "stdc++fs" "uuid")
	target_link_libraries(Rcff optimized "pthread" "dl" "stdc++fs" "uuid")	
ENDIF()

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(Rcff
        PUBLIC
            CXKJ_STATIC
    )
elseif(MINGW)
	target_compile_definitions(Rcff
		PUBLIC
			_DLL)
endif()

CXKJ_INSTALL(Rcff)
CXKJ_GENERATE_PACKAGE(Rcff)

configure_file(CXKJRcff.pc.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJRcff.pc @ONLY)
list(APPEND CXKJ_PKG_CONFIG_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJRcff.pc)
set(CXKJ_PKG_CONFIG_FILES ${CXKJ_PKG_CONFIG_FILES} PARENT_SCOPE)