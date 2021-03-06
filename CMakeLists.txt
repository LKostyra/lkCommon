CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(lkCommon)

INCLUDE(FindPkgConfig)


# assume Release build
IF(NOT DEFINED BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
ELSE(NOT DEFINED BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${BUILD_TYPE})
ENDIF(NOT DEFINED BUILD_TYPE)

MESSAGE(STATUS "lkCommon build type: ${CMAKE_BUILD_TYPE}")


IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    ADD_DEFINITIONS(-O0 -ggdb -D_DEBUG)
ELSE("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    ADD_DEFINITIONS(-O2)
ENDIF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")


SET(LKCOMMON_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
SET(LKCOMMON_OUTPUT_DIRECTORY ${LKCOMMON_ROOT_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})
SET(LKCOMMON_DIRECTORY ${LKCOMMON_ROOT_DIRECTORY}/lkCommon)
SET(LKCOMMON_DEPS_DIRECTORY ${LKCOMMON_ROOT_DIRECTORY}/Deps)

SET(LKCOMMON_TARGET lkCommon)
SET(LKCOMMON_TEST_TARGET lkCommonTest)


MACRO(LKCOMMON_COPY_RESULT TARGET)
    ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD COMMAND
                       ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> ${LKCOMMON_OUTPUT_DIRECTORY})
ENDMACRO(LKCOMMON_COPY_RESULT)


ADD_SUBDIRECTORY(Deps)
ADD_SUBDIRECTORY(lkCommon)

IF(DEFINED LKCOMMON_BUILD_TEST)
    MESSAGE(STATUS "lkCommonTest will be included in build")
    ADD_SUBDIRECTORY(lkCommonTest)
ELSE(DEFINED LKCOMMON_BUILD_TEST)
    MESSAGE(STATUS "lkCommonTest excluded from build")
ENDIF(DEFINED LKCOMMON_BUILD_TEST)


FILE(MAKE_DIRECTORY ${LKCOMMON_OUTPUT_DIRECTORY})
