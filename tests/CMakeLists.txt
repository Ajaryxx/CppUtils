add_executable(EXE "main.cpp")

set_target_properties(EXE PROPERTIES
CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON
CXX_EXTENSIONS OFF
)

target_link_libraries(EXE PRIVATE ${LIB})
target_compile_definitions(EXE PRIVATE LOG_MESSAGES)