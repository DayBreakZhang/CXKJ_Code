# Sources
CXKJ_HEADERS( SRCS g3log
		include/CXKJ/g3log/active.hpp
        include/CXKJ/g3log/atomicbool.hpp
        include/CXKJ/g3log/crashhandler.hpp
        include/CXKJ/g3log/filesink.hpp
        include/CXKJ/g3log/future.hpp
        include/CXKJ/g3log/g3log.hpp
        include/CXKJ/g3log/logcapture.hpp
        include/CXKJ/g3log/loglevels.hpp
        include/CXKJ/g3log/logmessage.hpp
        include/CXKJ/g3log/logworker.hpp
        include/CXKJ/g3log/moveoncopy.hpp
        include/CXKJ/g3log/shared_queue.hpp
        include/CXKJ/g3log/sink.hpp
        include/CXKJ/g3log/sinkhandle.hpp
        include/CXKJ/g3log/sinkwrapper.hpp
        include/CXKJ/g3log/stlpatch_future.hpp
        include/CXKJ/g3log/time.hpp
        )
CXKJ_SOURCES( SRCS g3log
		src/filesink.cpp
		src/filesinkhelper.ipp
		src/g3log.cpp
		src/logcapture.cpp
		src/loglevels.cpp
		src/logmessage.cpp
		src/logworker.cpp
		src/time.cpp
	)
if(WIN32)
        CXKJ_SOURCES( SRCS g3log
            src/crashhandler_windows.cpp
            src/stacktrace_windows.cpp
            )
        CXKJ_HEADERS( SRCS g3log
		    include/CXKJ/g3log/stacktrace_windows.hpp)
else()
        CXKJ_SOURCES( SRCS g3log
            src/crashhandler_unix.cpp
            )
endif()

#设置g3log G3_DEFINITIONS generated_definitions.hpp
SET(G3_DEFINITIONS "")
#设置G3LOG编译选项

# -DUSE_DYNAMIC_LOGGING_LEVELS=ON   : run-type turn on/off levels
option (USE_DYNAMIC_LOGGING_LEVELS
       "Turn ON/OFF log levels. An disabled level will not push logs of that level to the sink. By default dynamic logging is disabled" OFF)
IF(USE_DYNAMIC_LOGGING_LEVELS)
   LIST(APPEND G3_DEFINITIONS G3_DYNAMIC_LOGGING)
   message( STATUS "-DUSE_DYNAMIC_LOGGING_LEVELS=ON" )
   message( STATUS "\tDynamic logging levels is used" )
   message( STATUS "\tUse  [g3::addLogLevel(LEVEL boolean)] to enable/disable logging on specified levels\n\n" )
ELSE() 
   message( STATUS "-DUSE_DYNAMIC_LOGGING_LEVELS=OFF" ) 
ENDIF(USE_DYNAMIC_LOGGING_LEVELS)

# -DCHANGE_G3LOG_DEBUG_TO_DBUG=ON   : change the DEBUG logging level to be DBUG to avoid clash with other libraries that might have
# predefined DEBUG for their own purposes
option (CHANGE_G3LOG_DEBUG_TO_DBUG
       "Use DBUG logging level instead of DEBUG. By default DEBUG is the debugging level" OFF)
IF(CHANGE_G3LOG_DEBUG_TO_DBUG)
   LIST(APPEND G3_DEFINITIONS CHANGE_G3LOG_DEBUG_TO_DBUG)
   LIST(APPEND G3_DEFINITIONS "G3LOG_DEBUG DBUG")
   message( STATUS "-DCHANGE_G3LOG_DEBUG_TO_DBUG=ON                 DBUG instead of DEBUG logging level is used" )
ELSE() 
   LIST(APPEND G3_DEFINITIONS "G3LOG_DEBUG DEBUG")
   message( STATUS "-DCHANGE_G3LOG_DEBUG_TO_DBUG=OFF \t(Debuggin logging level is 'DEBUG')" ) 
ENDIF(CHANGE_G3LOG_DEBUG_TO_DBUG)

# -DG3_DYNAMIC_MAX_MESSAGE_SIZE   : use dynamic memory for final_message in logcapture.cpp
option (USE_G3_DYNAMIC_MAX_MESSAGE_SIZE
       "Use dynamic memory for message buffer during log capturing" OFF)
IF(USE_G3_DYNAMIC_MAX_MESSAGE_SIZE)
   LIST(APPEND G3_DEFINITIONS G3_DYNAMIC_MAX_MESSAGE_SIZE)
   message( STATUS "-DUSE_G3_DYNAMIC_MAX_MESSAGE_SIZE=ON\t\tDynamic memory used during log capture" )
ELSE()
   message( STATUS "-DUSE_G3_DYNAMIC_MAX_MESSAGE_SIZE=OFF" )
ENDIF(USE_G3_DYNAMIC_MAX_MESSAGE_SIZE)

# G3LOG_FULL_FILENAME logs full file name instead of short filename.  This makes it
# easier to copy filenames to open them without needing to search.
option (G3_LOG_FULL_FILENAME "Log full filename" OFF)
IF(G3_LOG_FULL_FILENAME)
   LIST(APPEND G3_DEFINITIONS G3_LOG_FULL_FILENAME)
   message( STATUS "-DG3_LOG_FULL_FILENAME=ON\t\tShowing full filenames with logs")
ELSE()
   message( STATUS "-DG3_LOG_FULL_FILENAME=OFF")
ENDIF(G3_LOG_FULL_FILENAME)

# -DENABLE_FATAL_SIGNALHANDLING=ON   : defualt change the
# By default fatal signal handling is enabled. You can disable it with this option
# enumerated in src/stacktrace_windows.cpp 
option (ENABLE_FATAL_SIGNALHANDLING
    "Vectored exception / crash handling with improved stack trace" ON)

IF(NOT ENABLE_FATAL_SIGNALHANDLING)
   LIST(APPEND G3_DEFINITIONS DISABLE_FATAL_SIGNALHANDLING)

   message( STATUS "-DENABLE_FATAL_SIGNALHANDLING=OFF               Fatal signal handler is disabled" )
ELSE() 
   message( STATUS "-DENABLE_FATAL_SIGNALHANDLING=ON\tFatal signal handler is enabled" )
ENDIF(NOT ENABLE_FATAL_SIGNALHANDLING)

# WINDOWS OPTIONS
IF (MSVC OR MINGW) 
# -DENABLE_VECTORED_EXCEPTIONHANDLING=ON   : defualt change the
# By default vectored exception handling is enabled, you can disable it with this option. 
# Please know that only known fatal exceptions will be caught, these exceptions are the ones
# enumerated in src/stacktrace_windows.cpp 
   option (ENABLE_VECTORED_EXCEPTIONHANDLING
       "Vectored exception / crash handling with improved stack trace" ON)

   IF(NOT ENABLE_VECTORED_EXCEPTIONHANDLING)
      LIST(APPEND G3_DEFINITIONS DISABLE_VECTORED_EXCEPTIONHANDLING)
      message( STATUS "-DENABLE_VECTORED_EXCEPTIONHANDLING=OFF           Vectored exception handling is disabled" ) 
   ELSE() 
      message( STATUS "-DENABLE_VECTORED_EXCEPTIONHANDLING=ON\t\t\tVectored exception handling is enabled" ) 
   ENDIF(NOT ENABLE_VECTORED_EXCEPTIONHANDLING)




# Default ON. Will trigger a break point in DEBUG builds if the signal handler 
#  receives a fatal signal.
#
   option (DEBUG_BREAK_AT_FATAL_SIGNAL
       "Enable Visual Studio break point when receiving a fatal exception. In __DEBUG mode only" OFF)
   IF(DEBUG_BREAK_AT_FATAL_SIGNAL)
     LIST(APPEND G3_DEFINITIONS DEBUG_BREAK_AT_FATAL_SIGNAL)
     message( STATUS "-DDEBUG_BREAK_AT_FATAL_SIGNAL=ON                  Break point for fatal signal is enabled for __DEBUG." ) 
   ELSE() 
      message( STATUS "-DDEBUG_BREAK_AT_FATAL_SIGNAL=OFF\t\t\tBreak point for fatal signal is disabled" ) 
   ENDIF(DEBUG_BREAK_AT_FATAL_SIGNAL)

ENDIF (MSVC OR MINGW)
#设置输出lib文件
if(BUILD_SHARED_LIBS)
    IF(MSVC)  
        ADD_DEFINITIONS (/D_VARIADIC_MAX=10)     
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    ENDIF()
endif()
include(GenerateMacroDefinitionsFile.cmake)
#添加generated_definitions.hpp到项目
include_directories(${PROJECT_SOURCE_DIR}/g3log/include/CXKJ)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)


add_library(G3Log ${SRCS} )
add_library(CXKJ::G3Log ALIAS G3Log)
set_target_properties(G3Log
    PROPERTIES
    LINKER_LANGUAGE CXX
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
	OUTPUT_NAME CXKJG3Log
    DEFINE_SYMBOL g3logger_EXPORTS
    CLEAN_DIRECT_OUTPUT 1
    )
target_include_directories(G3Log
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

CXKJ_INSTALL(G3Log)
CXKJ_GENERATE_PACKAGE(G3Log)

configure_file(CXKJG3Log.pc.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJG3Log.pc @ONLY)
list(APPEND CXKJ_PKG_CONFIG_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/CXKJG3Log.pc)
set(CXKJ_PKG_CONFIG_FILES ${CXKJ_PKG_CONFIG_FILES} PARENT_SCOPE)