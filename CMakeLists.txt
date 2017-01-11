cmake_minimum_required(VERSION 3.6)
project(JN)

set(CMAKE_CXX_STANDARD 11)

# ***** DEPENDENCIES *****

# directories with header files
include_directories(
        ~/Dropbox/dev/headers)

# directories with libraries
link_directories(
        ~/Dropbox/dev)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# OPENGL load
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# SDL2 load
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# hardcoded - finding results to SDL1.0 lib!
set(SDL_MIXER_LIBRARIES /Library/Frameworks/SDL2_mixer.framework)
set(SDL_TTF_LIBRARIES /Library/Frameworks/SDL2_ttf.framework)

include_directories(SDL_MIXER_INCLUDE_DIRS)
include_directories(SDL_TTF_INCLUDE_DIRS)


# load ROCKET framework
set(ROCKET_LIB_PATH ~/Dropbox/dev/libs)
set(JN_INC_PATH ~/Dropbox/dev/libs/Rocket.framework)

FIND_LIBRARY(ROCKET_LIB
        NAMES Rocket
        PATHS ${ROCKET_LIB_PATH}
        )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Rocket REQUIRED_VARS ROCKET_LIB ROCKET_LIB_PATH)

# ***** DEPENDENCIES ******


FILE(GLOB FrameworkSources *.cpp)
FILE(GLOB FrameworkHeaders *.h*)

set(SOURCE_FILES
        ${FrameworkSources}
        ${FrameworkHeaders}
        )



add_library(JN SHARED ${SOURCE_FILES})
set_target_properties(JN PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION A
        MACOSX_FRAMEWORK_IDENTIFIER com.jannovak.JN
        MACOSX_FRAMEWORK_INFO_PLIST Info.plist
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Jan Novak"
        )


file(MAKE_DIRECTORY ~/Dropbox/dev/JN.framework/Headers)

MACRO(COPY_FILE_INTO_DIRECTORY_IF_CHANGED in_file out_dir)
    file(COPY ${in_file} DESTINATION ${out_dir})
ENDMACRO(COPY_FILE_INTO_DIRECTORY_IF_CHANGED)

MACRO(COPY_FILES_INTO_DIRECTORY_IF_CHANGED in_file_list out_dir)
    FOREACH(in_file ${in_file_list})
        COPY_FILE_INTO_DIRECTORY_IF_CHANGED(${in_file}
                ${out_dir})
    ENDFOREACH(in_file)
ENDMACRO()

COPY_FILES_INTO_DIRECTORY_IF_CHANGED("${FrameworkHeaders}" "/Users/cablegibbon443/Dropbox/dev/JN.framework/Headers")

target_link_libraries(JN ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL_MIXER_LIBRARIES} ${SDL_TTF_LIBRARIES} ${ROCKET_LIB})


