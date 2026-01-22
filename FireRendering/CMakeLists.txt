project (FireRendering)

add_subdirectory (Libs)

add_executable(${PROJECT_NAME} 
    "Source/main.cpp"
    
    "Source/Core/App.cpp"
    
    "Source/Core/Window.cpp"

    "Source/Engine/Camera.cpp"
    "Source/Engine/IndexBuffer.cpp"
    "Source/Engine/Shader.cpp"
    "Source/Engine/ShaderBuilder.cpp"
    "Source/Engine/VertexArray.cpp"
    "Source/Engine/VertexBuffer.cpp"
    "Source/Engine/VertexLayout.cpp"

    "Source/Managers/ShaderManager.cpp"

    "Source/Objects/Components/TranslationComponent.cpp"
    "Source/Objects/Components/ScalingComponent.cpp"
    "Source/Objects/Components/RotationComponent.cpp"

    "Source/Objects/Shape.cpp"
    "Source/Objects/Cube.cpp"
    "Source/Objects/Spring.cpp"
    "Source/Objects/Plane.cpp"
    "Source/Objects/Trace.cpp" 
    "Source/Objects/Line.cpp"
    "Source/Objects/Arrow.cpp"

    "Source/Utils/ColorPalette.cpp"
    "Source/Utils/Init.cpp"
    "Source/Utils/Logger.cpp"
 "Source/Scenes/IScene.h" "Source/Scenes/FireScene.h" "Source/Scenes/FireScene.cpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/Source
)

target_include_directories (${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}/Dependencies/glfw/include
	${CMAKE_SOURCE_DIR}/Dependencies/glew/include
	${CMAKE_SOURCE_DIR}/Dependencies/glm
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(${PROJECT_NAME} 
	glfw 
	libglew_static
	imgui
)

add_custom_target(copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/Resources
	${PROJECT_BINARY_DIR}/Resources
	COMMENT "Copying resources into binary directory")

add_dependencies(${PROJECT_NAME} copy_resources)