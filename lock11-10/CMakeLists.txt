PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(LIBPATH /home/houjinliang/WorkSpace/apue/Ourhdr)
link_directories(${LIBPATH})
INCLUDE_DIRECTORIES(${LIBPATH})
SET(DIR_SRCS main.c)
ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES( main Ourhdr)
