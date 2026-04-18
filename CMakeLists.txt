cmake_minimum_required(VERSION 3.16)

project(ProxyInterceptor)

add_executable(Interceptor "app/src/App.cpp")

add_subdirectory(Proxy)
