include_directories(/usr/local/Cellar/poco/1.9.4/include/)
link_directories(/usr/local/Cellar/poco/1.9.4/lib)

add_executable(make_bill make_bill_task.h test_task_makefile.cpp ../log/log.h)
target_link_libraries(make_bill PocoUtil PocoJSON PocoXML PocoFoundation)


install(TARGETS make_bill
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
