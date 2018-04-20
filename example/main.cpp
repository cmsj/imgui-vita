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
    BT_WIN_SEARCH,
    BT_WIN_BROWSE,
    BT_WIN_UPDATE
};

int main(int, char**)
{
	sceClibPrintf("starting up\n");
	vglInit(0x100000);

	// Setup ImGui binding
    sceClibPrintf("creating context\n");
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplVitaGL_Init();

	// Setup style
    sceClibPrintf("setting style\n");
	ImGui::StyleColorsDark();
    sceClibPrintf("getting style\n");
    ImGuiStyle &style = ImGui::GetStyle();

    // Window styling
    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 0.0f;
    style.WindowPadding = ImVec2(10.0f, 10.0f);

    // General styling
    style.FrameBorderSize = 0.0f;
    style.FrameRounding = 5.0f;
    style.FramePadding = ImVec2(5.0f, 5.0f);

    // Load font
    io.Fonts->AddFontFromFileTTF("ux0:app/IMGUI0001/font.ttf", 30.0f);

    enum BT_WIN current_window = BT_WIN_BROWSE;
    ImGuiWindowFlags fullscreenFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
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

        // BEGIN: Header
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y)); 
        ImGui::Begin("Main Window", NULL, fullscreenFlags);

        ImVec2 headerButtonSize = ImVec2(200.0f, 75.0f);
        // This is effectively a poor man's tab bar, but ImGui doesn't have native tabs yet
        ImGui::Columns(3, "tabbar", false);
        if (ImGui::Button("Browse", headerButtonSize)) current_window = BT_WIN_BROWSE;
        ImGui::NextColumn();
        if (ImGui::Button("Search", headerButtonSize)) current_window = BT_WIN_SEARCH;
        ImGui::NextColumn();
        if (ImGui::Button("Updates", headerButtonSize)) current_window = BT_WIN_UPDATE;
        ImGui::Columns(1);
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        // BEGIN: Contents
        switch (current_window) {
            case BT_WIN_SEARCH:
                break;
            default: // This is here so if something goes wrong, we default to showing the Browse page
                current_window = BT_WIN_BROWSE;
            case BT_WIN_BROWSE:
                ImGui::Columns(2, "category", false);
                ImGui::SetColumnWidth(-1, 200.0f);
                ImGui::PushItemWidth(-1.0f);
                ImGui::Text("Category:");
                ImGui::PopItemWidth();
                ImGui::NextColumn();
                ImGui::PushItemWidth(-1.0f);
                ImGui::Combo("", &current_category, categories, IM_ARRAYSIZE(categories)); 
                ImGui::PopItemWidth();
                ImGui::Columns(1);
                break;
            case BT_WIN_UPDATE:
                break;
        }

        // BEGIN: Footer
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();


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
