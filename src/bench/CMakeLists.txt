add_library(Benchmark
        BenchParser.cpp
        BenchmarkLib.cpp
        CircuitToBDD.cpp
        bench_grammar.hpp
        skip_parser.hpp)

#Boost
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Boost/boost_1_78_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Boost/boost_1_78_0/libs")


#Executable
add_executable(VDSProject_bench main_bench.cpp)
target_link_libraries(VDSProject_bench Manager)
target_link_libraries(VDSProject_bench Benchmark)
target_link_libraries(VDSProject_bench ${Boost_LIBRARIES})


