#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "imgui/imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

// GLFW error callback
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int argc, char* argv[]) {
    // Initialize GLFW
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return 1;

    // Create window with OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    if (gl3wInit() != GL3W_OK) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variables for refreshing the window
    bool refreshWholeWindow = false;
    bool refreshSubset = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example: Add radio buttons for refreshing options
        ImGui::Text("Refresh Options:");
        ImGui::RadioButton("Entire Window", &refreshWholeWindow, true); ImGui::SameLine();
        ImGui::RadioButton("Subset", &refreshSubset, true);

        // Example: Add sliders
        static float sliderValue = 0.5f;
        ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 1.0f);

        // Example: Add a menu bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) { /* Handle new file */ }
                if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Handle open file */ }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Handle save file */ }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Rendering
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Example: Refresh the entire window
        if (refreshWholeWindow) {
            ImGui::SetNextWindowSize(io.DisplaySize);
            ImGui::Begin("Entire Window", &refreshWholeWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("This is the entire window refreshed.");
            ImGui::End();
        }

        // Example: Refresh a subset of the window
        if (refreshSubset) {
            ImGui::SetNextWindowPos(ImVec2(50, 50));
            ImGui::Begin("Subset", &refreshSubset, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("This is a subset of the window refreshed.");
            ImGui::End();
        }

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
