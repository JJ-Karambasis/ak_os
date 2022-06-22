struct ImGui_ImplAKOS_Data
{
    akos_handle Window;
    akos_u64 Time;
    int MouseButtonsDown;
    akos_handle MouseCursors[ImGuiMouseCursor_COUNT];
};

static ImGui_ImplAKOS_Data* ImGui_ImplAKOS_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplAKOS_Data*)ImGui::GetIO().BackendPlatformUserData : NULL;
}

static const char* ImGui_ImplAKOS_GetClipboardText(void* UserData)
{
    return AKOS_Get_Clipboard_Text();
}

static void ImGui_ImplAKOS_SetClipboardText(void* UserData, const char* Text)
{
    AKOS_Set_Clipboard_Text(Text);
}

static ImGuiKey ImGui_ImplAKOS_KeyToImGuiKey(akos_keycode key)
{
    switch (key)
    {
        case AKOS_KEYCODE_TAB: return ImGuiKey_Tab;
        case AKOS_KEYCODE_LEFT: return ImGuiKey_LeftArrow;
        case AKOS_KEYCODE_RIGHT: return ImGuiKey_RightArrow;
        case AKOS_KEYCODE_UP: return ImGuiKey_UpArrow;
        case AKOS_KEYCODE_DOWN: return ImGuiKey_DownArrow;
        case AKOS_KEYCODE_PAGEUP: return ImGuiKey_PageUp;
        case AKOS_KEYCODE_PAGEDOWN: return ImGuiKey_PageDown;
        case AKOS_KEYCODE_HOME: return ImGuiKey_Home;
        case AKOS_KEYCODE_END: return ImGuiKey_End;
        case AKOS_KEYCODE_INSERT: return ImGuiKey_Insert;
        case AKOS_KEYCODE_DELETE: return ImGuiKey_Delete;
        case AKOS_KEYCODE_BACKSPACE: return ImGuiKey_Backspace;
        case AKOS_KEYCODE_SPACE: return ImGuiKey_Space;
        case AKOS_KEYCODE_RETURN: return ImGuiKey_Enter;
        case AKOS_KEYCODE_ESCAPE: return ImGuiKey_Escape;
        case AKOS_KEYCODE_QUOTE: return ImGuiKey_Apostrophe;
        case AKOS_KEYCODE_COMMA: return ImGuiKey_Comma;
        case AKOS_KEYCODE_MINUS: return ImGuiKey_Minus;
        case AKOS_KEYCODE_PERIOD: return ImGuiKey_Period;
        case AKOS_KEYCODE_FORWARDSLASH: return ImGuiKey_Slash;
        case AKOS_KEYCODE_SEMICOLON: return ImGuiKey_Semicolon;
        case AKOS_KEYCODE_EQUAL: return ImGuiKey_Equal;
        case AKOS_KEYCODE_LEFTBRACKET: return ImGuiKey_LeftBracket;
        case AKOS_KEYCODE_BACKSLASH: return ImGuiKey_Backslash;
        case AKOS_KEYCODE_RIGHTBRACKET: return ImGuiKey_RightBracket;
        case AKOS_KEYCODE_TICK: return ImGuiKey_GraveAccent;
        case AKOS_KEYCODE_CAPSLOCK: return ImGuiKey_CapsLock;
        case AKOS_KEYCODE_SCROLLLOCK: return ImGuiKey_ScrollLock;
        case AKOS_KEYCODE_NUMLOCK: return ImGuiKey_NumLock;
        case AKOS_KEYCODE_PRINTSCREEN: return ImGuiKey_PrintScreen;
        case AKOS_KEYCODE_PAUSE: return ImGuiKey_Pause;
        case AKOS_KEYCODE_NUMPAD0: return ImGuiKey_Keypad0;
        case AKOS_KEYCODE_NUMPAD1: return ImGuiKey_Keypad1;
        case AKOS_KEYCODE_NUMPAD2: return ImGuiKey_Keypad2;
        case AKOS_KEYCODE_NUMPAD3: return ImGuiKey_Keypad3;
        case AKOS_KEYCODE_NUMPAD4: return ImGuiKey_Keypad4;
        case AKOS_KEYCODE_NUMPAD5: return ImGuiKey_Keypad5;
        case AKOS_KEYCODE_NUMPAD6: return ImGuiKey_Keypad6;
        case AKOS_KEYCODE_NUMPAD7: return ImGuiKey_Keypad7;
        case AKOS_KEYCODE_NUMPAD8: return ImGuiKey_Keypad8;
        case AKOS_KEYCODE_NUMPAD9: return ImGuiKey_Keypad9;
        case AKOS_KEYCODE_NUMPADDOT: return ImGuiKey_KeypadDecimal;
        case AKOS_KEYCODE_NUMPADSLASH: return ImGuiKey_KeypadDivide;
        case AKOS_KEYCODE_NUMPADSTAR: return ImGuiKey_KeypadMultiply;
        case AKOS_KEYCODE_NUMPADMINUS: return ImGuiKey_KeypadSubtract;
        case AKOS_KEYCODE_NUMPADPLUS: return ImGuiKey_KeypadAdd;
        case AKOS_KEYCODE_LSHIFT: return ImGuiKey_LeftShift;
        case AKOS_KEYCODE_LCONTROL: return ImGuiKey_LeftCtrl;
        case AKOS_KEYCODE_LALT: return ImGuiKey_LeftAlt;
        case AKOS_KEYCODE_LSUPER: return ImGuiKey_LeftSuper;
        case AKOS_KEYCODE_RSHIFT: return ImGuiKey_RightShift;
        case AKOS_KEYCODE_RCONTROL: return ImGuiKey_RightCtrl;
        case AKOS_KEYCODE_RALT: return ImGuiKey_RightAlt;
        case AKOS_KEYCODE_RSUPER: return ImGuiKey_RightSuper;
        case AKOS_KEYCODE_MENU: return ImGuiKey_Menu;
        case AKOS_KEYCODE_0: return ImGuiKey_0;
        case AKOS_KEYCODE_1: return ImGuiKey_1;
        case AKOS_KEYCODE_2: return ImGuiKey_2;
        case AKOS_KEYCODE_3: return ImGuiKey_3;
        case AKOS_KEYCODE_4: return ImGuiKey_4;
        case AKOS_KEYCODE_5: return ImGuiKey_5;
        case AKOS_KEYCODE_6: return ImGuiKey_6;
        case AKOS_KEYCODE_7: return ImGuiKey_7;
        case AKOS_KEYCODE_8: return ImGuiKey_8;
        case AKOS_KEYCODE_9: return ImGuiKey_9;
        case AKOS_KEYCODE_A: return ImGuiKey_A;
        case AKOS_KEYCODE_B: return ImGuiKey_B;
        case AKOS_KEYCODE_C: return ImGuiKey_C;
        case AKOS_KEYCODE_D: return ImGuiKey_D;
        case AKOS_KEYCODE_E: return ImGuiKey_E;
        case AKOS_KEYCODE_F: return ImGuiKey_F;
        case AKOS_KEYCODE_G: return ImGuiKey_G;
        case AKOS_KEYCODE_H: return ImGuiKey_H;
        case AKOS_KEYCODE_I: return ImGuiKey_I;
        case AKOS_KEYCODE_J: return ImGuiKey_J;
        case AKOS_KEYCODE_K: return ImGuiKey_K;
        case AKOS_KEYCODE_L: return ImGuiKey_L;
        case AKOS_KEYCODE_M: return ImGuiKey_M;
        case AKOS_KEYCODE_N: return ImGuiKey_N;
        case AKOS_KEYCODE_O: return ImGuiKey_O;
        case AKOS_KEYCODE_P: return ImGuiKey_P;
        case AKOS_KEYCODE_Q: return ImGuiKey_Q;
        case AKOS_KEYCODE_R: return ImGuiKey_R;
        case AKOS_KEYCODE_S: return ImGuiKey_S;
        case AKOS_KEYCODE_T: return ImGuiKey_T;
        case AKOS_KEYCODE_U: return ImGuiKey_U;
        case AKOS_KEYCODE_V: return ImGuiKey_V;
        case AKOS_KEYCODE_W: return ImGuiKey_W;
        case AKOS_KEYCODE_X: return ImGuiKey_X;
        case AKOS_KEYCODE_Y: return ImGuiKey_Y;
        case AKOS_KEYCODE_Z: return ImGuiKey_Z;
        case AKOS_KEYCODE_F1: return ImGuiKey_F1;
        case AKOS_KEYCODE_F2: return ImGuiKey_F2;
        case AKOS_KEYCODE_F3: return ImGuiKey_F3;
        case AKOS_KEYCODE_F4: return ImGuiKey_F4;
        case AKOS_KEYCODE_F5: return ImGuiKey_F5;
        case AKOS_KEYCODE_F6: return ImGuiKey_F6;
        case AKOS_KEYCODE_F7: return ImGuiKey_F7;
        case AKOS_KEYCODE_F8: return ImGuiKey_F8;
        case AKOS_KEYCODE_F9: return ImGuiKey_F9;
        case AKOS_KEYCODE_F10: return ImGuiKey_F10;
        case AKOS_KEYCODE_F11: return ImGuiKey_F11;
        case AKOS_KEYCODE_F12: return ImGuiKey_F12;
        default: return ImGuiKey_None;
    }
}

static void ImGui_ImplAKOS_UpdateMousePos()
{
    ImGui_ImplAKOS_Data* bd = ImGui_ImplAKOS_GetBackendData();
    ImGuiIO& io = ImGui::GetIO();
    
    akos_handle Window = AKOS_Get_Focused_Window();
    if(Window)
    {
        if(io.WantSetMousePos) 
            AKOS_Set_Window_Cursor_Pos(Window, (akos_i32)io.MousePos.x, (akos_i32)io.MousePos.y);
        
        if(bd->MouseButtonsDown == 0)
        {
            akos_i32 x, y;
            AKOS_Get_Window_Cursor_Pos(Window, &x, &y);
            io.MousePos = ImVec2((float)x, (float)y);
        }
    }
}

static void ImGui_ImplAKOS_UpdateMouseCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    if(io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return;
    
    ImGui_ImplAKOS_Data* bd = ImGui_ImplAKOS_GetBackendData();
    
    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if(io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
    {
        AKOS_Show_Cursor(false);
    }
    else
    {
        AKOS_Set_Cursor(bd->MouseCursors[imgui_cursor] ? bd->MouseCursors[imgui_cursor] : bd->MouseCursors[ImGuiMouseCursor_Arrow]);
        AKOS_Show_Cursor(true);
    }
    
}

bool ImGui_ImplAKOS_Init(akos_handle Window)
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == NULL && "Already initialized a platform backend!");
    
    ImGui_ImplAKOS_Data* bd = IM_NEW(ImGui_ImplAKOS_Data)();
    io.BackendPlatformUserData = (void*)bd;
    io.BackendPlatformName = "imgui_impl_akos";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    bd->Window = Window;
    bd->Time = AKOS_Performance_Counter();
    
    io.SetClipboardTextFn = ImGui_ImplAKOS_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplAKOS_GetClipboardText;
    io.ClipboardUserData  = NULL;
    
    bd->MouseCursors[ImGuiMouseCursor_Arrow] = AKOS_Create_Cursor(AKOS_CURSOR_ARROW);
    bd->MouseCursors[ImGuiMouseCursor_TextInput] = AKOS_Create_Cursor(AKOS_CURSOR_IBEAM);
    bd->MouseCursors[ImGuiMouseCursor_ResizeAll] = AKOS_Create_Cursor(AKOS_CURSOR_SIZEALL);
    bd->MouseCursors[ImGuiMouseCursor_ResizeNS] = AKOS_Create_Cursor(AKOS_CURSOR_SIZENS);
    bd->MouseCursors[ImGuiMouseCursor_ResizeEW] = AKOS_Create_Cursor(AKOS_CURSOR_SIZEEW);
    bd->MouseCursors[ImGuiMouseCursor_ResizeNESW] = AKOS_Create_Cursor(AKOS_CURSOR_SIZENESW);
    bd->MouseCursors[ImGuiMouseCursor_ResizeNWSE] = AKOS_Create_Cursor(AKOS_CURSOR_SIZENWSE);
    bd->MouseCursors[ImGuiMouseCursor_Hand] = AKOS_Create_Cursor(AKOS_CURSOR_HAND);
    bd->MouseCursors[ImGuiMouseCursor_NotAllowed] = AKOS_Create_Cursor(AKOS_CURSOR_NO);
    
    
    //Set platform dependent data in viewport
    ImGui::GetMainViewport()->PlatformHandleRaw = AKOS_Window_Get_Platform_Data(Window);
    
    return true;
}

void ImGui_ImplAKOS_Shutdown()
{
    ImGui_ImplAKOS_Data* bd = ImGui_ImplAKOS_GetBackendData();
    IM_ASSERT(bd != NULL && "No platform backend to shutdown, or already shutdown?");
    ImGuiIO& io = ImGui::GetIO();
    
    for(ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
        AKOS_Delete_Cursor(bd->MouseCursors[cursor_n]);
    
    io.BackendPlatformName = NULL;
    io.BackendPlatformUserData = NULL;
    IM_DELETE(bd);
}

void ImGui_ImplAKOS_NewFrame()
{
    ImGui_ImplAKOS_Data* bd = ImGui_ImplAKOS_GetBackendData();
    IM_ASSERT(bd != NULL && "Did you call ImGui_ImplAKOS_Init()?");
    
    ImGuiIO& io = ImGui::GetIO();
    
    akos_i32 w, h;
    AKOS_Get_Window_Dim(bd->Window, &w, &h);
    
    io.DisplaySize = ImVec2((float)w, (float)h);
    io.DisplayFramebufferScale = ImVec2(1, 1);
    
    akos_u64 current_time = AKOS_Performance_Counter();
    io.DeltaTime = (float)(current_time-bd->Time)/(float)AKOS_Performance_Frequency();
    bd->Time = current_time;
    
    ImGui_ImplAKOS_UpdateMousePos();
    ImGui_ImplAKOS_UpdateMouseCursor();
}

void ImGui_ImplAKOS_ProcessEvents(akos_event_list* Events)
{
    for(akos_u64 EventIndex = 0; EventIndex < Events->Count; EventIndex++)
    {
        const akos_event* Event = Events->Events + EventIndex;
        ImGui_ImplAKOS_ProcessEvent(Event);
    }
}

void ImGui_ImplAKOS_ProcessEvent(const akos_event* event)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplAKOS_Data* bd = ImGui_ImplAKOS_GetBackendData();
    
    switch(event->Type)
    {
        case AKOS_EVENT_TYPE_MOUSE_MOVED:
        {
            io.MousePos = ImVec2((float)event->MouseMoved.MouseX, (float)event->MouseMoved.MouseY);
        } break;
        
        case AKOS_EVENT_TYPE_KEY_PRESSED:
        {
            ImGuiKeyModFlags key_mods = 
            (((event->KeyPressed.Modifiers & AKOS_MODIFIER_CONTROL) ? ImGuiKeyModFlags_Ctrl : 0) |
             ((event->KeyPressed.Modifiers & AKOS_MODIFIER_SHIFT) ? ImGuiKeyModFlags_Shift : 0) |
             ((event->KeyPressed.Modifiers & AKOS_MODIFIER_ALT) ? ImGuiKeyModFlags_Alt : 0));
            
            ImGuiKey imgui_key = ImGui_ImplAKOS_KeyToImGuiKey(event->KeyPressed.KeyCode);
            io.AddKeyEvent(imgui_key, true);
            io.SetKeyEventNativeData(imgui_key, event->KeyPressed.KeyCode, event->KeyPressed.ScanCode);
            
            io.AddKeyEvent(ImGuiKey_ModCtrl, (event->KeyPressed.Modifiers & AKOS_MODIFIER_CONTROL) != 0);
            io.AddKeyEvent(ImGuiKey_ModShift, (event->KeyPressed.Modifiers & AKOS_MODIFIER_SHIFT) != 0);
            io.AddKeyEvent(ImGuiKey_ModAlt, (event->KeyPressed.Modifiers & AKOS_MODIFIER_ALT) != 0);
            
            printf("Out\n");
        } break;
        
        case AKOS_EVENT_TYPE_KEY_RELEASED:
        {
            ImGuiKeyModFlags key_mods = 
            (((event->KeyReleased.Modifiers & AKOS_MODIFIER_CONTROL) ? ImGuiKeyModFlags_Ctrl : 0) |
             ((event->KeyReleased.Modifiers & AKOS_MODIFIER_SHIFT) ? ImGuiKeyModFlags_Shift : 0) |
             ((event->KeyReleased.Modifiers & AKOS_MODIFIER_ALT) ? ImGuiKeyModFlags_Alt : 0));
            
            ImGuiKey imgui_key = ImGui_ImplAKOS_KeyToImGuiKey(event->KeyPressed.KeyCode);
            io.AddKeyEvent(imgui_key, false);
            io.SetKeyEventNativeData(imgui_key, event->KeyPressed.KeyCode, event->KeyPressed.ScanCode);
            
            io.AddKeyEvent(ImGuiKey_ModCtrl, (event->KeyReleased.Modifiers & AKOS_MODIFIER_CONTROL) != 0);
            io.AddKeyEvent(ImGuiKey_ModShift, (event->KeyReleased.Modifiers & AKOS_MODIFIER_SHIFT) != 0);
            io.AddKeyEvent(ImGuiKey_ModAlt, (event->KeyReleased.Modifiers & AKOS_MODIFIER_ALT) != 0);
        } break;
        
        case AKOS_EVENT_TYPE_MOUSE_PRESSED:
        {
            int button = -1;
            if(event->MousePressed.MouseCode == AKOS_MOUSECODE_LEFT) { button = 0;}
            if(event->MousePressed.MouseCode == AKOS_MOUSECODE_RIGHT) { button = 1; }
            if(event->MousePressed.MouseCode == AKOS_MOUSECODE_MIDDLE) { button = 2; }
            if(button == -1)
                break;
            
            if(bd->MouseButtonsDown == 0 && AKOS_Get_Mouse_Capture() == NULL)
                AKOS_Set_Mouse_Capture(event->Window);
            
            bd->MouseButtonsDown |= 1 << button;
            io.MouseDown[button] = true;
        } break;
        
        case AKOS_EVENT_TYPE_MOUSE_RELEASED:
        {
            int button = -1;
            if(event->MouseReleased.MouseCode == AKOS_MOUSECODE_LEFT) { button = 0;}
            if(event->MouseReleased.MouseCode == AKOS_MOUSECODE_RIGHT) { button = 1; }
            if(event->MouseReleased.MouseCode == AKOS_MOUSECODE_MIDDLE) { button = 2; }
            if(button == -1)
                break;
            
            bd->MouseButtonsDown &= ~(1 << button);
            if(bd->MouseButtonsDown == 0 && AKOS_Get_Mouse_Capture() == event->Window)
                AKOS_Set_Mouse_Capture(0);
            io.MouseDown[button] = false;
        } break;
        
        case AKOS_EVENT_TYPE_MOUSE_SCROLLED:
        {
            float wheel_y = (event->MouseScroll.Scroll > 0) ? 1.0f : (event->MouseScroll.Scroll < 0) ? -1.0f : 0.0f;
            io.AddMouseWheelEvent(0, wheel_y);
        } break;
        
        case AKOS_EVENT_TYPE_CHAR_INPUT:
        {
            io.AddInputCharacterUTF16(event->CharInput.Code);
        } break;
        
        case AKOS_EVENT_TYPE_WINDOW_FOCUSED:
        {
            io.AddFocusEvent(event->Focused.IsFocused);
        } break;
        
        case AKOS_EVENT_TYPE_MOUSE_LEFT:
        {
            io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
        } break;
    }
}