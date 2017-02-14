cmake_minimum_required(VERSION 2.8)
# find Qt
find_package( Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED )
include( ${QT_USE_FILE} )
include_directories( ${QT_INCLUDES} )

# find VTK for visualisation in the main program
#SET( VTK_DIR "~/vtk6_build/" CACHE PATH "VTK directory override" FORCE )
find_package( VTK REQUIRED NO_MODULE )
include( ${VTK_USE_FILE} )
include_directories( ${VTK_INCLUDE_DIRS} )

# common header
set( common_hdr
	${CMAKE_SOURCE_DIR}/../common/include
)

# common src
file(GLOB common_src ${CMAKE_SOURCE_DIR}/../common/src/*.cpp)


# header files
set( header
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR} # for moc'ed uis!
)

file(GLOB src ${CMAKE_SOURCE_DIR}/src/*.cpp)


include_directories( ${header} )
include_directories( ${common_hdr} )

# Visualizer library: Visualize points, voxels, scanners/scan poses
QT4_WRAP_UI(UISrcs ./ui/viewer.ui)
QT4_WRAP_CPP(MOCSrcs ./include/viewer.hpp ./include/ledwidget.hpp)

add_executable( viewer ${src} ${common_src} ${UISrcs} ${MOCSrcs} )
#target_link_libraries( viewer QVTK ${VTK_LIBRARIES} ${QT_LIBRARIES} )
target_link_libraries( viewer ${VTK_LIBRARIES} ${QT_LIBRARIES} )

