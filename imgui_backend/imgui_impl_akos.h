#ifndef IMGUI_IMPL_AKOS_H
#define IMGUI_IMPL_AKOS_H

#include <imgui.h>
#include <ak_os.h>

bool ImGui_ImplAKOS_Init(akos_handle Window);
void ImGui_ImplAKOS_Shutdown();
void ImGui_ImplAKOS_NewFrame();
void ImGui_ImplAKOS_ProcessEvents(akos_event_list* Events);
void ImGui_ImplAKOS_ProcessEvent(const akos_event* Event);

#endif //IMGUI_IMPL_AKOS_H