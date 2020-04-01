include_directories(
    /usr/local/include/
    /usr/hdp/2.6.5.0-292/usr
)

ADD_EXECUTABLE(indbtohive
		main.cpp
    IndbToHive.cpp
		OffSetMgr.cpp
		FileHandle.cpp
		HiveApi.cpp
    ../common/KafkaEventCb.cpp
    ../common/KafkaConfig.cpp
    ../common/KafkaProducer.cpp
    ../common/KafkaConsumer.cpp
    ../common/CResMgr.cpp
    ../proto/DistributeMessage.pb.cc
    ../proto/LogAlertMessage.pb.cc
    ../proto/DispatchAudit.pb.cc
    )

add_definitions(-DWITH_BOL) #-DWITH_HIVE)

TARGET_LINK_LIBRARIES(
    indbtohive
    PocoUtil 
    PocoFoundation 
    BolServiceAPI 
    rdkafka++ 
    protobuf
    hiredis_vip
    credis
    hdfs 
    thrift
    gtest
    sasl2
		thrift-sasl    
    arrow
    arrow_hiveserver2 
    arrow_hiveserver2_thrift   
    PocoXML 
    )



install(TARGETS indbtohive 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
