include_directories(${PROJECT_SOURCE_DIR}/src/include)
link_directories(${PROJECT_SOURCE_DIR}/src/lib)


add_executable( showip showip.cpp)



target_link_libraries(showip cpr)


install(FILES key.json DESTINATION ${PROJECT_SOURCE_DIR}/build/srcBin PERMISSIONS OWNER_READ )

