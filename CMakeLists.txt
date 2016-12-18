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
#link_directories(${SDL2_LIBRARY_DIRS})
#add_definitions(${SDL2_DEFINITIONS})

# SDL_mixer and SDL_ttf
#find_package(SDL_mixer REQUIRED)
#find_package(SDL_ttf REQUIRED)

# hardcoded - finding results to SDL1.0 lib!
set(SDL_MIXER_LIBRARIES /Library/Frameworks/SDL2_mixer.framework)
set(SDL_TTF_LIBRARIES /Library/Frameworks/SDL2_ttf.framework)
message(SDL Mixer Library : ${SDL_MIXER_LIBRARIES})
message(SDL TTF Library : ${SDL_TTF_LIBRARIES})
message(TTF library found : ${SDL_TTF_FOUND})
include_directories(SDL_MIXER_INCLUDE_DIRS)
include_directories(SDL_TTF_INCLUDE_DIRS)
message(SDL Mixer Includes :  ${SDL_MIXER_INCLUDE_DIRS})
message(SDL TTF Includes : ${SDL_TTF_INCLUDE_DIRS})
# load Box2d
#set(BOX2D_LIB_PATH ~/Dropbox/dev)
#FIND_LIBRARY(BOX2D_LIB
#        NAMES Box2D
#        PATHS ${BOX2D_LIB_PATH}
#        )

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

target_link_libraries(JN ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL_MIXER_LIBRARIES} ${SDL_TTF_LIBRARIES})


