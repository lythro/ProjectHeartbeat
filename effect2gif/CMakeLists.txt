cmake_minimum_required(VERSION 2.8)

find_package( PkgConfig )
pkg_check_modules( Magick REQUIRED Magick++ )
include_directories( ${Magick_INCLUDE_DIRS} )


# common header
set( common_hdr
	${CMAKE_SOURCE_DIR}/..
)

# common src
file(GLOB common_src ${CMAKE_SOURCE_DIR}/../*.cpp)


# header files
set( header
	${CMAKE_SOURCE_DIR}/include
)

file(GLOB src ${CMAKE_SOURCE_DIR}/src/*.cpp)


include_directories( ${header} )
include_directories( ${common_hdr} )


add_executable( effect2gif ${src} ${common_src} )
target_link_libraries( effect2gif ${Magick_LIBRARIES} )
