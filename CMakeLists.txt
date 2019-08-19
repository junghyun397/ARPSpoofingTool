cmake_minimum_required(VERSION 3.14)
project(ARPSpoofingTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ARPSpoofingTool
        main.cpp
        network/NetworkHeader.h
        network/arp/ARPSession.cpp
        network/arp/ARPSessionAdaptor.cpp
        network/NetFuncs.cpp
        network/arp/SessionARPSpoofing.cpp
        network/arp/BroadcastARPSpoofing.cpp
        network/arp/BaseARPSpoofing.cpp
        network/arp/trigger/BaseTrigger.cpp)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PCAP REQUIRED)

target_link_libraries(ARPSpoofingTool ${PCAP_LIBRARY})