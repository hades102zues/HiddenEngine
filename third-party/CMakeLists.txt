

# Create a base library 
add_library(third_party_deps)

# Add source files
target_sources(third_party_deps PRIVATE glad/glad.c)

# Add the include paths
target_include_directories(third_party_deps PUBLIC
    glad/include
    sdl2_core/include
)

# Third Party Libraries
target_link_libraries(third_party_deps PRIVATE 
    sdl2_core/lib/libSDL2.a
)









