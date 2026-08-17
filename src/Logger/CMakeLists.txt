add_library(Logger STATIC
    Logger.cpp
)

# PUBLIC em src/ para quem usa a lib incluir como <Logger/Logger.hpp>.
target_include_directories(Logger PUBLIC ${CMAKE_SOURCE_DIR}/src)
