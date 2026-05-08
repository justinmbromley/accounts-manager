find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(accounts_manager
    main.cpp
)

target_link_libraries(accounts_manager
    PRIVATE accounts_core
    PRIVATE Qt6::Core
    PRIVATE Qt6::Widgets
)
