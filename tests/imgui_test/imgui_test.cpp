#include <stdint.h>
#include <imgui_backend/imgui_impl_akos.h>
#include <windows.h>
#include <gl/gl.h>
#undef GL_VERSION_1_1
#include <backends/imgui_impl_opengl3.h>
#include <stdio.h>

int main()
{
    akos_context_create_info ContextCreateInfo = {};
    ContextCreateInfo.GLInfo.MajorVersion = 3;
    ContextCreateInfo.GLInfo.MinorVersion = 2;
    ContextCreateInfo.GLInfo.ProfileMask = AKOS_GL_CONTEXT_PROFILE_MASK_CORE_BIT;
    ContextCreateInfo.GLInfo.ContextFlags = AKOS_GL_CONTEXT_DEBUG_BIT;
    
    if(!AKOS_Create_Context(&ContextCreateInfo)) return 1;
    
    akos_window_create_info WindowCreateInfo = {};
    WindowCreateInfo.Width = 1920;
    WindowCreateInfo.Height = 1080;
    WindowCreateInfo.Title = "Dear Imgui AKOS test";
    akos_handle Window = AKOS_Create_Window(&WindowCreateInfo);
    if(!Window) return 1;
    
    AKOS_GL_Make_Current(Window);
    AKOS_GL_Set_Swap_Interval(1);
    
    ImGui::CreateContext();
    ImGuiIO& IO = ImGui::GetIO();
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplAKOS_Init(Window);
    ImGui_ImplOpenGL3_Init("#version 130");
    
    bool ShowDemoWindow = true;
    bool Running = true;
    while(Running)
    {
        akos_event_list Events = AKOS_Poll_Events();
        ImGui_ImplAKOS_ProcessEvents(&Events);
        
        for(uint64_t EventIndex = 0; EventIndex < Events.Count; EventIndex++)
        {
            const akos_event* Event = Events.Events + EventIndex;
            switch(Event->Type)
            {
                case AKOS_EVENT_TYPE_WINDOW_CLOSED:
                {
                    if(Event->Window == Window)
                        Running = false;
                    AKOS_Delete_Window(Window);
                } break;
            }
        }   
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAKOS_NewFrame();
        ImGui::NewFrame();
        
        ImGui::ShowDemoWindow(&ShowDemoWindow);
        
        ImGui::Render();
        glViewport(0, 0, (int)IO.DisplaySize.x, (int)IO.DisplaySize.y);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        AKOS_GL_Swap_Buffers(Window);
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAKOS_Shutdown();
    ImGui::DestroyContext();
    AKOS_Delete_Context(AKOS_Get_Context());
    return 0;
}

#define AK_OS_IMPLEMENTATION
#include <ak_os.h>
#include <imgui_backend/imgui_impl_akos.cpp>
#include <backends/imgui_impl_opengl3.cpp>

#include <imgui.cpp>
#include <imgui_widgets.cpp>
#include <imgui_draw.cpp>
#include <imgui_tables.cpp>
#include <imgui_demo.cpp>