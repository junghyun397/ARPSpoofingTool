cmake_minimum_required(VERSION 3.14)
project(ARPSpoofingTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ARPSpoofingTool
        src/main.cpp
        src/util/NetworkHeader.h
        src/spoof/session/ARPSession.cpp
        src/spoof/session/ARPSessionAdaptor.cpp
        src/util/NetFuncs.cpp
        src/spoof/SessionARPSpoofing.cpp
        src/spoof/BroadcastARPSpoofing.cpp
        src/spoof/BaseARPSpoofing.cpp
        src/spoof/trigger/BaseTrigger.cpp)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PCAP REQUIRED)

target_link_libraries(ARPSpoofingTool ${PCAP_LIBRARY})