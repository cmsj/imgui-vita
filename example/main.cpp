// ImGui - standalone example application for SDL2 + OpenGL
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the sdl_opengl3_example/ folder**
// See imgui_impl_sdl.cpp for details.

#include <imgui_vita.h>
#include <stdio.h>
#include <vitaGL.h>

enum BT_WIN {
    BT_WIN_MAIN,
    BT_WIN_SEARCH,
    BT_WIN_BROWSE,
    BT_WIN_UPDATE,
    BT_WIN_DEMO
};

int main(int, char**)
{
	
	vglInit(0x100000);

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplVitaGL_Init();

	// Setup style
	ImGui::StyleColorsDark();

    enum BT_WIN current_window = BT_WIN_MAIN;
    ImGuiWindowFlags fullscreenFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

const char* categories[] = {
    "All",
    "Ports",
    "Games",
    "Emulators",
    "Utilities"
};
static int current_category = 0;


	// Main loop
	bool done = false;
	while (!done)
	{
		vglStartRendering();
		ImGui_ImplVitaGL_NewFrame();
		
        switch (current_window) {
            case BT_WIN_MAIN:
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y)); 
                ImGui::Begin("Main Window", NULL, fullscreenFlags);
                ImGui::Text("BrewThing");
                if (ImGui::Button("Browse")) {
                    current_window = BT_WIN_BROWSE;
                }
                if (ImGui::Button("Search")) {
                    current_window = BT_WIN_SEARCH;
                }
                if (ImGui::Button("Update")) {
                    current_window = BT_WIN_UPDATE;
                }
                if (ImGui::Button("Demo")) {
                    current_window = BT_WIN_DEMO;
                }
    			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            break;
            case BT_WIN_SEARCH:
            break;
            case BT_WIN_BROWSE:
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y)); 
                ImGui::Begin("Browse Window", NULL, fullscreenFlags);
                ImGui::Combo("Category", &current_category, categories, IM_ARRAYSIZE(categories)); 
            break;
            case BT_WIN_UPDATE:
            break;
            case BT_WIN_DEMO:
                ImGui::ShowDemoWindow();
            break;
            default:
                // Something has gone wrong
                current_window = BT_WIN_MAIN;
                break;
        }


		// Rendering
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui::Render();
		ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
		vglStopRendering();
	}

	// Cleanup
	ImGui_ImplVitaGL_Shutdown();
	ImGui::DestroyContext();
	
	vglEnd();

	return 0;
}
