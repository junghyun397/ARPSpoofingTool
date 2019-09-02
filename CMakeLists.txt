cmake_minimum_required(VERSION 3.14)
project(ARPSpoofingTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ARPSpoofingTool
        src/main.cpp
        src/util/NetworkHeader.h
        src/spoof/session/ARPSession.cpp
        src/spoof/session/ARPSessionAdaptor.cpp
        src/util/NetTools.cpp
        src/spoof/SessionARPSpoofing.cpp
        src/spoof/BroadcastARPSpoofing.cpp
        src/spoof/IBaseARPSpoofing.cpp
        src/spoof/trigger/IBaseTrigger.cpp src/spoof/trigger/DNSSpoofingTrigger.cpp)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PCAP REQUIRED)

target_link_libraries(ARPSpoofingTool ${PCAP_LIBRARY})