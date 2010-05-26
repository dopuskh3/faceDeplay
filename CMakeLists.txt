cmake_minimum_required(VERSION 2.6)

project(deplay)

# add ofx includes directories for dependencies 
file ( GLOB_RECURSE app_sources_files src/*)
# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
include_directories ( ../../addons/ofxVectorMath/src/ ) 

# ofxGui
file ( GLOB_RECURSE ofxMSAInteractiveObject ../../addons/ofxMSAInteractiveObject/src/* ) 
include_directories ( ../../addons/ofxMSAInteractiveObject/src/ )

# ofx
file ( GLOB_RECURSE ofxSimpleGuiToo ../../addons/ofxSimpleGuiToo/src/* ../../addons/ofxSimpleGuiToo/src/ofxSimpleGuiToo.h ../../addons/ofxSimpleGuiToo/src/Controls ) 
include_directories ( ../../addons/ofxSimpleGuiToo/src/ ../../addons/ofxSimpleGuiToo/src/Controls)

file ( GLOB_RECURSE ofxXmlSettings ../../addons/ofxXmlSettings/libs/* ../../addons/ofxXmlSettings/src/* ) 
include_directories ( ../../addons/ofxXmlSettings/libs/ ../../addons/ofxXmlSettings/src/ )

file ( GLOB_RECURSE ofxOpenCv ../../addons/ofxOpenCv/src/* )
include_directories ( ../../addons/ofxOpenCv/src/ ) 


# OpenCv addon ##################################
if ( CMAKE_SYSTEM_NAME MATCHES "Linux" ) 
    #include(FindPkgConfig)
    #pkg_search_module(CV opencv)
    #include_directories ( ${CV_INCLUDE_DIRS} )
    set ( CV_LIBRARIES "-L/usr/local/lib -lcxcore -lcv -lcvaux -lml")
    include_directories (/usr/local/include/opencv)
    # message ( " ${CV_LIBRARIES} - ${CV_INCLUDE_DIRS} ") 
endif()
if ( APPLE )
   include_directories(../../libs/OpenCV/include/opencv)
   find_library(cv cv PATHS ../../libs/OpenCV/lib)
   find_library(highgui highgui PATHS ../../libs/OpenCV/lib)
   find_library(cvaux cvaux PATHS ../../libs/OpenCV/lib)
   find_library(cvcore cxcore PATHS ../../libs/OpenCV/lib)
   find_library(opencv_lapack opencv_lapack PATHS ../../libs/OpenCV/3rdparty/lib/ )
   find_library(zlib zlib PATHS ../../libs/OpenCV/3rdparty/lib/ )
   message("${cv} ${cvaux}")
   set (CV_LIBRARIES ${cv} ${cvaux} ${cvcore} ${highgui} ${opencv_lapack} ${zlib})
endif( APPLE )


if (APPLE)
add_executable( deplay
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxOpenCv}
#    ${ofxCvHaarFinder}
    #${ofxMSAInteractiveObject}
    #${ofxXmlSettings}
    #${ofxSimpleGuiToo})
    )
else (APPLE)
add_executable( deplay
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxOpenCv}
#    ${ofxCvHaarFinder}
    #${ofxMSAInteractiveObject}
    #${ofxXmlSettings}
    #${ofxSimpleGuiToo})
    )
endif (APPLE)

if ( APPLE ) 
    include(FindPkgConfig)
    pkg_check_modules(OF openFrameworks)
    message( " LIBS : ${OF_LIBRARIES} INCLUDES ${OF_INCLUDE_DIRS}" )
    set (CMAKE_CXX_FLAGS ${OF_CFLAGS_OTHER} )
    set ( OF_LIBRARIES ${OF_LIBRARIES} "-framework OpenGL" "-framework QuickTime") # ${ofx_libs} ${cv_LIBRARIES}) 
    include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})
    #find_library(openFrameworks OF_LIBRARIES /usr/local/lib)
    set_target_properties(deplay
        PROPERTIES BUILD_WITH_INSTALL_RPATH ON
         INSTALL_NAME_DIR "@executable_path"
        )

else ( APPLE ) 
    include(FindPkgConfig)
    pkg_check_modules(OF openFrameworks)
    set (CMAKE_CXX_FLAGS ${OF_CFLAGS_OTHER} )
    include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})
endif ( APPLE )

set ( libs ${OF_LIBRARIES} ${CV_LIBRARIES} ${freeimage} ${poco} ${lapack} ${cv} ${cvaux} ${cxcore} ${ml}) # ${CV_LIBRARIES} )
target_link_libraries(deplay ${libs})


