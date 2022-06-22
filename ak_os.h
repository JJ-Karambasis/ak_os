#ifndef AK_OS_H
#define AK_OS_H

#ifdef AK_OS_STATIC
#define AK_OS_DEF static
#else
#ifdef __cplusplus
#define AK_OS_DEF extern "C"
#else
#define AK_OS_DEF extern
#endif // __cplusplus
#endif //AK_OS_STATIC

#ifndef __cplusplus
#include <stdalign.h>
#endif

#include <stdarg.h>
#include <stddef.h>

//TODO(JJ): Proper character code support for files and window displays?

typedef unsigned char      akos_u8;
typedef   signed char      akos_i8;
typedef unsigned short     akos_u16;
typedef   signed short     akos_i16;
typedef unsigned int       akos_u32;
typedef   signed int       akos_i32;
typedef unsigned long long akos_u64;
typedef   signed long long akos_i64;

typedef akos_i32 akos_b32;

#define akos_true  1
#define akos_false 0

#define AKOS_INVALID_FILE_SIZE ((akos_u64)-1)

enum 
{
    AKOS_EVENT_TYPE_NONE,
    AKOS_EVENT_TYPE_WINDOW_CLOSED,
    AKOS_EVENT_TYPE_MOUSE_MOVED,
    AKOS_EVENT_TYPE_KEY_PRESSED, 
    AKOS_EVENT_TYPE_KEY_RELEASED,
    AKOS_EVENT_TYPE_MOUSE_PRESSED,
    AKOS_EVENT_TYPE_MOUSE_RELEASED,
    AKOS_EVENT_TYPE_MOUSE_SCROLLED, 
    AKOS_EVENT_TYPE_CHAR_INPUT, 
    AKOS_EVENT_TYPE_WINDOW_FOCUSED,
    AKOS_EVENT_TYPE_MOUSE_LEFT
};

enum 
{
    AKOS_FILE_FLAG_READ  = (1 << 0),
    AKOS_FILE_FLAG_WRITE = (1 << 1)
};

enum 
{
    AKOS_GL_CONTEXT_PROFILE_MASK_CORE_BIT = (1 << 0),
    AKOS_GL_CONTEXT_PROFILE_MASK_COMPATABILITY_BIT = (1 << 1)
};

enum
{
    AKOS_GL_CONTEXT_FORWARD_COMPATABILITY_BIT = (1 << 0), 
    AKOS_GL_CONTEXT_DEBUG_BIT = (1 << 1)
};

enum
{
    AKOS_CURSOR_ARROW,
    AKOS_CURSOR_IBEAM,
    AKOS_CURSOR_SIZEALL,
    AKOS_CURSOR_SIZENS,
    AKOS_CURSOR_SIZEEW,
    AKOS_CURSOR_SIZENESW,
    AKOS_CURSOR_SIZENWSE,
    AKOS_CURSOR_HAND,
    AKOS_CURSOR_NO,
    AKOS_CURSOR_COUNT
};

typedef enum akos_keycode
{
    AKOS_KEYCODE_UNKNOWN,
    AKOS_KEYCODE_A,
    AKOS_KEYCODE_B,
    AKOS_KEYCODE_C,
    AKOS_KEYCODE_D,
    AKOS_KEYCODE_E,
    AKOS_KEYCODE_F,
    AKOS_KEYCODE_G,
    AKOS_KEYCODE_H,
    AKOS_KEYCODE_I,
    AKOS_KEYCODE_J,
    AKOS_KEYCODE_K,
    AKOS_KEYCODE_L,
    AKOS_KEYCODE_M,
    AKOS_KEYCODE_N,
    AKOS_KEYCODE_O,
    AKOS_KEYCODE_P,
    AKOS_KEYCODE_Q,
    AKOS_KEYCODE_R,
    AKOS_KEYCODE_S,
    AKOS_KEYCODE_T,
    AKOS_KEYCODE_U,
    AKOS_KEYCODE_V,
    AKOS_KEYCODE_W,
    AKOS_KEYCODE_X,
    AKOS_KEYCODE_Y,
    AKOS_KEYCODE_Z,
    AKOS_KEYCODE_0,
    AKOS_KEYCODE_1,
    AKOS_KEYCODE_2,
    AKOS_KEYCODE_3,
    AKOS_KEYCODE_4,
    AKOS_KEYCODE_5,
    AKOS_KEYCODE_6,
    AKOS_KEYCODE_7,
    AKOS_KEYCODE_8,
    AKOS_KEYCODE_9,
    AKOS_KEYCODE_SPACE,
    AKOS_KEYCODE_TICK,
    AKOS_KEYCODE_MINUS,
    AKOS_KEYCODE_EQUAL,
    AKOS_KEYCODE_LEFTBRACKET,
    AKOS_KEYCODE_RIGHTBRACKET,
    AKOS_KEYCODE_SEMICOLON,
    AKOS_KEYCODE_QUOTE,
    AKOS_KEYCODE_COMMA,
    AKOS_KEYCODE_PERIOD,
    AKOS_KEYCODE_FORWARDSLASH,
    AKOS_KEYCODE_BACKSLASH,
    AKOS_KEYCODE_TAB,
    AKOS_KEYCODE_ESCAPE,
    AKOS_KEYCODE_PAUSE,
    AKOS_KEYCODE_UP,
    AKOS_KEYCODE_DOWN,
    AKOS_KEYCODE_LEFT,
    AKOS_KEYCODE_RIGHT,
    AKOS_KEYCODE_BACKSPACE,
    AKOS_KEYCODE_RETURN,
    AKOS_KEYCODE_DELETE,
    AKOS_KEYCODE_INSERT,
    AKOS_KEYCODE_HOME,
    AKOS_KEYCODE_END,
    AKOS_KEYCODE_PAGEUP,
    AKOS_KEYCODE_PAGEDOWN,
    AKOS_KEYCODE_CAPSLOCK,
    AKOS_KEYCODE_NUMLOCK,
    AKOS_KEYCODE_SCROLLLOCK,
    AKOS_KEYCODE_SHIFT,
    AKOS_KEYCODE_CONTROL,
    AKOS_KEYCODE_ALT,
    AKOS_KEYCODE_LSHIFT,
    AKOS_KEYCODE_RSHIFT,
    AKOS_KEYCODE_LCONTROL,
    AKOS_KEYCODE_RCONTROL,
    AKOS_KEYCODE_LALT,
    AKOS_KEYCODE_RALT,
    AKOS_KEYCODE_LSUPER,
    AKOS_KEYCODE_RSUPER,
    AKOS_KEYCODE_PRINTSCREEN,
    AKOS_KEYCODE_MENU,
    AKOS_KEYCODE_COMMAND,
    AKOS_KEYCODE_F1,
    AKOS_KEYCODE_F2,
    AKOS_KEYCODE_F3,
    AKOS_KEYCODE_F4,
    AKOS_KEYCODE_F5,
    AKOS_KEYCODE_F6,
    AKOS_KEYCODE_F7,
    AKOS_KEYCODE_F8,
    AKOS_KEYCODE_F9,
    AKOS_KEYCODE_F10,
    AKOS_KEYCODE_F11,
    AKOS_KEYCODE_F12,
    AKOS_KEYCODE_F13,
    AKOS_KEYCODE_F14,
    AKOS_KEYCODE_F15,
    AKOS_KEYCODE_F16,
    AKOS_KEYCODE_F17,
    AKOS_KEYCODE_F18,
    AKOS_KEYCODE_F19,
    AKOS_KEYCODE_F20,
    AKOS_KEYCODE_F21,
    AKOS_KEYCODE_F22,
    AKOS_KEYCODE_F23,
    AKOS_KEYCODE_F24,
    AKOS_KEYCODE_NUMPAD0,
    AKOS_KEYCODE_NUMPAD1,
    AKOS_KEYCODE_NUMPAD2,
    AKOS_KEYCODE_NUMPAD3,
    AKOS_KEYCODE_NUMPAD4,
    AKOS_KEYCODE_NUMPAD5,
    AKOS_KEYCODE_NUMPAD6,
    AKOS_KEYCODE_NUMPAD7,
    AKOS_KEYCODE_NUMPAD8,
    AKOS_KEYCODE_NUMPAD9,
    AKOS_KEYCODE_NUMPADSTAR,
    AKOS_KEYCODE_NUMPADPLUS,
    AKOS_KEYCODE_NUMPADMINUS,
    AKOS_KEYCODE_NUMPADDOT,
    AKOS_KEYCODE_NUMPADSLASH
} akos_keycode;

typedef enum akos_mousecode
{
    AKOS_MOUSECODE_UNKNOWN,
    AKOS_MOUSECODE_LEFT, 
    AKOS_MOUSECODE_MIDDLE, 
    AKOS_MOUSECODE_RIGHT
} akos_mousecode;

#define AKOS_MODIFIER_ALT 1
#define AKOS_MODIFIER_SHIFT 2
#define AKOS_MODIFIER_CONTROL 4

typedef struct akos_context akos_context;
typedef akos_u64 akos_handle;
typedef akos_i32 akos_thread_callback(void* UserData);
typedef void akos_timer_callback(void* UserData);

typedef struct akos_window_create_info
{
    akos_u32    Width;
    akos_u32    Height;
    const char* Title;
} akos_window_create_info;

typedef struct akos_event
{
    akos_u64    Type;
    akos_handle Window;
    
    union
    {
        struct
        {
            akos_i32 MouseX;
            akos_i32 MouseY;
        } MouseMoved;
        
        struct
        {
            akos_keycode KeyCode;
            akos_u32     Modifiers;
            akos_u32     ScanCode;
        } KeyPressed, KeyReleased;
        
        struct 
        {
            akos_mousecode MouseCode;
            akos_u32       Modifiers;
        } MousePressed, MouseReleased;
        
        struct
        {
            float Scroll;
        } MouseScroll;
        
        struct
        {
            akos_i32 IsFocused;
        } Focused;
        
        struct
        {
            akos_u16 Code;
        } CharInput;
    };
} akos_event;

typedef struct akos_event_list
{
    akos_u64          Count;
    const akos_event* Events;
}  akos_event_list;

typedef struct akos_clipboard_text
{
    akos_u64    Length;
    const char* Str;
} akos_clipboard_text;

typedef struct akos_gl_context_create_info
{
    akos_u16 MajorVersion;
    akos_u16 MinorVersion;
    akos_u32 ProfileMask;
    akos_u32 ContextFlags;
} akos_gl_context_create_info;

typedef struct akos_context_create_info
{
    akos_gl_context_create_info GLInfo;
} akos_context_create_info;

AK_OS_DEF void* AKOS_Reserve(size_t Size);
AK_OS_DEF int   AKOS_Commit(void* Memory, size_t Size);
AK_OS_DEF void  AKOS_Decommit(void* Memory, size_t Size);
AK_OS_DEF void  AKOS_Release(void* Memory);

AK_OS_DEF void* AKOS_Allocate(size_t Size);
AK_OS_DEF void  AKOS_Free(void* Memory);

AK_OS_DEF akos_u32 AKOS_Get_Current_Thread_ID();

AK_OS_DEF int AKOS_Directory_Exists(const char* Directory);
AK_OS_DEF int AKOS_Create_Directory(const char* Directory);

AK_OS_DEF akos_context* AKOS_Create_Context(const akos_context_create_info* ContextCreateInfo);
AK_OS_DEF void          AKOS_Delete_Context(akos_context* Context);
AK_OS_DEF akos_context* AKOS_Get_Context();
AK_OS_DEF void          AKOS_Set_Context(akos_context* Context);

AK_OS_DEF akos_u64 AKOS_Performance_Counter();
AK_OS_DEF akos_u64 AKOS_Performance_Frequency();

AK_OS_DEF akos_handle AKOS_Create_Thread(akos_thread_callback* ThreadCallback, void* UserData);
AK_OS_DEF void AKOS_Delete_Thread(akos_handle Handle);
AK_OS_DEF void AKOS_Thread_Wait(akos_handle Handle);

AK_OS_DEF akos_handle AKOS_Create_Mutex();
AK_OS_DEF void AKOS_Delete_Mutex(akos_handle Handle);
AK_OS_DEF void AKOS_Mutex_Lock(akos_handle Handle);
AK_OS_DEF void AKOS_Mutex_Unlock(akos_handle Handle);

AK_OS_DEF akos_handle AKOS_Create_Event();
AK_OS_DEF void AKOS_Delete_Event(akos_handle Handle);
AK_OS_DEF void AKOS_Event_Signal(akos_handle Handle);
AK_OS_DEF void AKOS_Event_Wait(akos_handle Handle);

AK_OS_DEF akos_handle AKOS_Create_Timer();
AK_OS_DEF void AKOS_Delete_Timer(akos_handle Handle);
AK_OS_DEF void AKOS_Timer_Set(akos_handle Handle, akos_u64 Ticks, akos_timer_callback* TimerCallback, void* UserData);
AK_OS_DEF void AKOS_Timer_Wait(akos_handle Handle);

AK_OS_DEF akos_handle AKOS_Create_File(const char* Filepath, akos_u64 Flags);
AK_OS_DEF akos_u64 AKOS_Get_File_Size(akos_handle Handle);
AK_OS_DEF int AKOS_Read_File( akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset);
AK_OS_DEF int AKOS_Write_File(akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset);
AK_OS_DEF void AKOS_Delete_File(akos_handle Handle);

AK_OS_DEF int AKOS_Write_Entire_File(const char* Filepath, void* Data, akos_u32 WriteSize);

AK_OS_DEF akos_event_list AKOS_Poll_Events();

AK_OS_DEF const char* AKOS_Get_Clipboard_Text();
AK_OS_DEF void AKOS_Set_Clipboard_Text(const char* Text);

AK_OS_DEF akos_handle AKOS_Create_Window(const akos_window_create_info* WindowCreateInfo);
AK_OS_DEF void AKOS_Delete_Window(akos_handle WindowHandle);
AK_OS_DEF void* AKOS_Window_Get_Platform_Data(akos_handle WindowHandle);

AK_OS_DEF void AKOS_Show_Window(akos_handle WindowHandle, int IsFocused);
AK_OS_DEF void AKOS_Set_Window_Pos(akos_handle WindowHandle, akos_i32 PosX, akos_i32 PosY);
AK_OS_DEF void AKOS_Get_Window_Pos(akos_handle WindowHandle, akos_i32* PosX, akos_i32* PosY);
AK_OS_DEF void AKOS_Set_Window_Dim(akos_handle WindowHandle, akos_i32 Width, akos_i32 Height);
AK_OS_DEF void AKOS_Get_Window_Dim(akos_handle WindowHandle, akos_i32* Width, akos_i32* Height);
AK_OS_DEF void AKOS_Set_Window_User_Data(akos_handle WindowHandle, akos_u64 UserData);
AK_OS_DEF akos_u64 AKOS_Get_Window_User_Data(akos_handle WindowHandle);

AK_OS_DEF int AKOS_Is_Window_Focused(akos_handle WindowHandle);
AK_OS_DEF void AKOS_Focus_Window(akos_handle WindowHandle);
AK_OS_DEF int AKOS_Is_Window_Minimized(akos_handle WindowHandle);
AK_OS_DEF akos_handle AKOS_Get_Focused_Window();
AK_OS_DEF void AKOS_Get_Cursor_Pos(akos_i32* PosX, akos_i32* PosY);
AK_OS_DEF void AKOS_Get_Window_Cursor_Pos(akos_handle WindowHandle, akos_i32* PosX, akos_i32* PosY);
AK_OS_DEF void AKOS_Set_Cursor_Pos(akos_i32 PosX, akos_i32 PosY);
AK_OS_DEF void AKOS_Set_Window_Cursor_Pos(akos_handle WindowHandle, akos_i32 PosX, akos_i32 PosY);
AK_OS_DEF void AKOS_Set_Mouse_Capture(akos_handle WindowHandle);
AK_OS_DEF akos_handle AKOS_Get_Mouse_Capture();

AK_OS_DEF int AKOS_GL_Make_Current(akos_handle WindowHandle);
AK_OS_DEF void AKOS_GL_Set_Swap_Interval(int SwapInterval);
AK_OS_DEF void AKOS_GL_Swap_Buffers(akos_handle WindowHandle);

AK_OS_DEF akos_handle AKOS_Create_Cursor(akos_u32 SystemCode);
AK_OS_DEF void  AKOS_Delete_Cursor(akos_handle Cursor);
AK_OS_DEF void AKOS_Set_Cursor(akos_handle Cursor);
AK_OS_DEF akos_handle AKOS_Get_Cursor();
AK_OS_DEF void AKOS_Show_Cursor(int Show);

#ifdef AK_OS_VULKAN_HELPERS

#ifndef AK_OS_VULKAN_INCLUDE

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif //_WIN32

#include <vulkan/vulkan.h>

#endif //AK_OS_VULKAN_INCLUDE

AK_OS_DEF VkSurfaceKHR AKOS_Create_Vulkan_Surface(akos_handle WindowHandle, VkInstance Instance, PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr, 
                                                  VkAllocationCallbacks* Callbacks);

#endif //AK_OS_VULKAN_HELPERS

#endif //AK_OS_H

#ifdef AK_OS_IMPLEMENTATION

#define AKOS__HANDLE_TYPE_WINDOW 1
#define AKOS__HANDLE_TYPE_THREAD 2
#define AKOS__HANDLE_TYPE_MUTEX  3
#define AKOS__HANDLE_TYPE_FILE   4
#define AKOS__HANDLE_TYPE_EVENT  5
#define AKOS__HANDLE_TYPE_TIMER  6
#define AKOS__HANDLE_TYPE_CURSOR 7

#ifndef AK_OS_MALLOC
#include <stdlib.h>
#define AK_OS_MALLOC(size) malloc(size)
#define AK_OS_FREE(memory) free(memory)
#endif //AK_OS_MALLOC

#ifndef AK_OS_MEMCPY
#include <string.h>
#define AK_OS_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define AK_OS_MEMSET(ptr, value, n) memset(ptr, value, n)
#endif //AK_OS_MEMCPY

#ifndef AK_OS_ASSERT
#include <assert.h>
#define AK_OS_ASSERT(condition, message) assert(condition)
#endif //AK_OS_ASSERT

//~Internal utility functions and macros

#define AKOS__Max(a, b) ((a) > (b) ? (a) : (b))
#define AKOS__Min(a, b) ((a) < (b) ? (a) : (b))

#define AKOS__DLL_Push_Back_NP(f,l,n,next,prev) ((f)==0?\
((f)=(l)=(n),(n)->next=(n)->prev=0):\
((n)->prev=(l),(l)->next=(n),(l)=(n),(n)->next=0))
#define AKOS__DLL_Push_Back(f,l,n) AKOS__DLL_Push_Back_NP(f,l,n,Next,Prev)

#define AKOS__DLL_Push_Front(f,l,n) AKOS__DLL_Push_Back_NP(l,f,n,Prev,Next)

#define AKOS__DLL_Remove_NP(f,l,n,next,prev) ((f)==(n)?\
((f)==(l)?\
((f)=(l)=(0)):\
((f)=(f)->next,(f)->prev=0)):\
(l)==(n)?\
((l)=(l)->prev,(l)->next=0):\
((n)->next->prev=(n)->prev,\
(n)->prev->next=(n)->next))
#define AKOS__DLL_Remove(f,l,n) AKOS__DLL_Remove_NP(f,l,n,Next,Prev)

#define AKOS__SLL_Queue_Push_N(f,l,n,next) ((f)==0?\
(f)=(l)=(n):\
((l)->next=(n),(l)=(n)),\
(n)->next=0)
#define AKOS__SLL_Queue_Push(f,l,n) AKOS__SLL_Queue_Push_N(f,l,n,Next)

#define AKOS__SLL_Queue_Push_Front_N(f,l,n,next) ((f)==0?\
((f)=(l)=(n),(n)->next=0):\
((n)->next=(f),(f)=(n)))
#define AKOS__SLL_Queue_Push_Front(f,l,n) AKOS__SLL_Queue_Push_Front_N(f,l,n,Next)

#define AKOS__SLL_Queue_Pop_N(f,l,next) ((f)==(l)?\
(f)=(l)=0:\
(f)=(f)->next)
#define AKOS__SLL_Queue_Pop(f,l) AKOS__SLL_Queue_Pop_N(f,l,Next)

#define AKOS__SLL_Stack_Push_N(f,n,next) ((n)->next=(f),(f)=(n))
#define AKOS__SLL_Stack_Push(f,n) AKOS__SLL_Stack_Push_N(f,n,Next)

#define AKOS__SLL_Stack_Pop_N(f,next) ((f)==0?0:\
(f)=(f)->next)
#define AKOS__SLL_Stack_Pop(f) AKOS__SLL_Stack_Pop_N(f,Next)

static void AKOS__Memory_Copy(void* Dest, const void* Src, size_t Size)
{
    AK_OS_MEMCPY(Dest, Src, Size);
}

static void AKOS__Memory_Set(void* Dest, akos_u8 Value, size_t Size)
{
    AK_OS_MEMSET(Dest, Value, Size);
}

static void AKOS__Memory_Clear(void* Dest, size_t Size)
{
    AK_OS_MEMSET(Dest, 0, Size);
}

static void* AKOS__Malloc(size_t Size)
{
    return AK_OS_MALLOC(Size);
}

static void AKOS__Free(void* Memory)
{
    if(Memory) AK_OS_FREE(Memory);
}

static akos_u64 AKOS__Memory_Align(akos_u64 Value, akos_u64 Alignment)
{
    Alignment = Alignment ? Alignment : 1;
    akos_u64 Mod = Value & (Alignment-1);
    return Mod ? Value + (Alignment-Mod) : Value;
}

static akos_u64 AKOS__Ceil_Pow2(akos_u64 V)
{
    --V;
    V |= V >> 1;
    V |= V >> 2;
    V |= V >> 4;
    V |= V >> 8;
    V |= V >> 16;
    V |= V >> 32;
    ++V;
    V += ( V == 0 );    
    return V;
}

static akos_u64 AKOS__String_Length(const char* Str)
{
    akos_u64 Length = 0;
    while(*Str++) Length++;
    return Length;
}

//~Internal pool implementation
#define AKOS__INVALID_POOL_INDEX ((akos_u16)-1)

typedef union akos__pool_id
{
    akos_u64 ID;
    struct
    {
        union
        {
            struct
            {
                akos_u16 PreviousIndex;
                akos_u16 NextIndex;
            };
            struct
            {
                akos_u16 Index;
                akos_u16 Type;
            };
        };
        akos_u32 Key;
    };
} akos__pool_id;


typedef struct akos__pool
{
    akos_u8* Data;
    akos_u16 ItemSize;
    akos_u16 Type;
    akos_u16 Length;
    akos_u16 Capacity;
    akos_u16 FirstAllocatedIndex;
    akos_u16 FirstAvailableIndex;
    akos_u16 MaxUsed;
    akos_u32 NextKey;
} akos__pool;

static akos__pool AKOS__Create_Pool(akos_u16 Capacity, akos_u16 ItemSize, akos_u16 Type)
{
    akos__pool Result;
    Result.Data = (akos_u8*)AKOS__Malloc(Capacity*ItemSize);
    if(!Result.Data) 
    {
        //TODO(JJ): Diagnostic and error logging
        AKOS__Memory_Clear(&Result, sizeof(akos__pool));
        return Result;
    }
    
    Result.ItemSize = ItemSize + sizeof(akos__pool_id);
    Result.Type = Type;
    Result.Length = 0;
    Result.Capacity = Capacity;
    Result.FirstAllocatedIndex = AKOS__INVALID_POOL_INDEX;
    Result.FirstAvailableIndex = AKOS__INVALID_POOL_INDEX;
    Result.NextKey = 1;
    Result.MaxUsed = 0;
    return Result;
}

static void AKOS__Delete_Pool(akos__pool* Pool)
{
    if(Pool->Data) AKOS__Free(Pool->Data);
    AKOS__Memory_Clear(Pool, sizeof(akos__pool));
}

static akos_u64 AKOS__Pool_Allocate(akos__pool* Pool)
{
    akos_u16 Index;
    if(Pool->FirstAvailableIndex != AKOS__INVALID_POOL_INDEX)
    {
        Index = Pool->FirstAvailableIndex;
        akos__pool_id* PoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*Index);
        Pool->FirstAvailableIndex = PoolID->NextIndex;
    }
    else
    {
        if(Pool->MaxUsed == Pool->Capacity)
        {
            akos_u16 NewCapacity = AKOS__Max(Pool->Capacity*2, 0xFFFD);
            AK_OS_ASSERT(NewCapacity != Pool->Capacity, "Pool overflow!");
            
            akos_u8* Data = (akos_u8*)AKOS__Malloc(NewCapacity*Pool->ItemSize);
            if(!Data)
            {
                //TODO(JJ): Diagnostic and error logging
                return 0;
            }
            
            AKOS__Memory_Copy(Data, Pool->Data, Pool->Capacity*Pool->ItemSize);
            AKOS__Free(Pool->Data);
            Pool->Data = Data;
            Pool->Capacity = NewCapacity;
        }
        
        Index = Pool->MaxUsed++;
    }
    
    akos__pool_id* PoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*Index);
    PoolID->Key = Pool->NextKey++;
    PoolID->PreviousIndex = AKOS__INVALID_POOL_INDEX;
    PoolID->NextIndex = Pool->FirstAllocatedIndex;
    
    if(!Pool->NextKey)
    {
        //NOTE(EVERYONE): Our pool has ran out of unique keys. Reset it back to one a start 
        //all over again (old keys are no longer invalid)
        Pool->NextKey = 1;
    }
    
    if(Pool->FirstAllocatedIndex != AKOS__INVALID_POOL_INDEX)
    {
        akos__pool_id* FirstID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*Pool->FirstAllocatedIndex);
        FirstID->PreviousIndex = Index;
    }
    
    void* Data = PoolID+1;
    AKOS__Memory_Clear(Data, Pool->ItemSize);
    
    Pool->FirstAllocatedIndex = Index;
    Pool->Length++;
    
    akos__pool_id ID;
    ID.Key   = PoolID->Key;
    ID.Type  = Pool->Type;
    ID.Index = Index;
    
    return ID.ID;
}

static void* AKOS__Pool_Get(akos__pool* Pool, akos_u64 InputID)
{
    if(InputID)
    {
        akos__pool_id ID = {InputID};
        akos__pool_id* PoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*ID.Index);
        if(PoolID->Key != ID.Key) return NULL;
        if(Pool->Type != ID.Type) return NULL;
        void* Result = PoolID+1;
        return Result;
    }
    return NULL;
}

static void AKOS__Pool_Free(akos__pool* Pool, akos_u64 InputID)
{
    if(InputID)
    {
        akos__pool_id ID = {InputID};
        akos__pool_id* PoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*ID.Index);
        if(PoolID->Key != ID.Key) return;
        if(Pool->Type != ID.Type) return;
        
        akos_b32 IsHead = ID.Index == Pool->FirstAllocatedIndex;
        if(!IsHead)
        {
            AK_OS_ASSERT(PoolID->PreviousIndex != AKOS__INVALID_POOL_INDEX, "Invalid pool head!");
            akos__pool_id* PreviousPoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*PoolID->PreviousIndex);
            PreviousPoolID->NextIndex = PoolID->NextIndex;
        }
        else
            Pool->FirstAllocatedIndex = PoolID->NextIndex;
        
        if(PoolID->NextIndex != AKOS__INVALID_POOL_INDEX)
        {
            akos__pool_id* NextPoolID = (akos__pool_id*)(Pool->Data + Pool->ItemSize*PoolID->NextIndex);
            NextPoolID->PreviousIndex = PoolID->PreviousIndex;
        }
        
        PoolID->ID = 0;
        PoolID->NextIndex = Pool->FirstAvailableIndex;
        
        Pool->FirstAvailableIndex = ID.Index;
        
        Pool->Length--;
    }
}

static akos_u64 AKOS__Pool_Get_ID_From_Index(akos__pool* Pool, akos_u16 Index)
{
    AK_OS_ASSERT(Index < Pool->MaxUsed, "Index out of bounds!");
    akos__pool_id* PoolID = (akos__pool_id*)(Pool->Data + Index*Pool->ItemSize);
    if(!PoolID->Key) return 0;
    
    akos__pool_id ID;
    ID.Key = PoolID->Key;
    ID.Type = Pool->Type;
    ID.Index = Index;
    return ID.ID;
}

//~Internal arena implementation

typedef struct akos__arena akos__arena;

typedef struct akos__arena_block
{
    akos_u8*           Memory;
    akos_u64           Used;
    akos_u64           Size;
    struct akos__arena_block* Next;
} akos__arena_block;

typedef struct akos__arena_marker
{
    akos__arena*       Arena;
    akos__arena_block* Block;
    akos_u64           Marker;
} akos__arena_marker;

struct akos__arena
{
    akos__arena_block* FirstBlock;
    akos__arena_block* CurrentBlock;
    akos__arena_block* LastBlock;
    akos_u64           InitialBlockSize;
};

static akos__arena AKOS__Create_Arena(akos_u64 InitialBlockSize)
{
    akos__arena Result;
    AKOS__Memory_Clear(&Result, sizeof(akos__arena));
    Result.InitialBlockSize = InitialBlockSize;
    return Result;
}

static void AKOS__Delete_Arena(akos__arena* Arena)
{
    if(Arena->FirstBlock)
    {
        akos__arena_block* Block = Arena->FirstBlock;
        while(Block)
        {
            akos__arena_block* BlockToDelete = Block;
            Block = Block->Next;
            AKOS__Free(BlockToDelete);
        }
    }
    AKOS__Memory_Clear(Arena, sizeof(akos__arena));
}

static akos__arena_block* AKOS__Arena_Allocate_Block(akos_u64 BlockSize)
{
    akos__arena_block* Block = (akos__arena_block*)AKOS__Malloc(sizeof(akos__arena_block)+BlockSize);
    if(!Block)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    AKOS__Memory_Clear(Block, sizeof(akos__arena_block));
    Block->Memory = (akos_u8*)(Block+1);
    Block->Size = BlockSize;
    
    return Block;
}

static void AKOS__Arena_Add_Block(akos__arena* Arena, akos__arena_block* Block)
{
    (Arena->FirstBlock == 0) ? 
    (Arena->FirstBlock = Arena->LastBlock = Block) : 
    (Arena->LastBlock->Next = Block, Arena->LastBlock = Block);
}

static akos__arena_block* AKOS__Arena_Get_Block(akos__arena* Arena, akos_u64 Size, akos_u64 Alignment)
{
    akos__arena_block* Block = Arena->CurrentBlock;
    if(!Block) return NULL;
    
    akos_u64 Used = AKOS__Memory_Align(Block->Used, Alignment);
    while(Used+Size > Block->Size)
    {
        Block = Block->Next;
        if(!Block) return NULL;
        Used = AKOS__Memory_Align(Block->Used, Alignment);
    }
    
    return Block;
}

static void* AKOS__Arena_Allocate(akos__arena* Arena, akos_u64 Size, akos_u64 Alignment)
{
    if(!Size) return NULL;
    
    akos__arena_block* Block = AKOS__Arena_Get_Block(Arena, Size, Alignment);
    if(!Block)
    {
        akos_u64 BlockSize = Arena->InitialBlockSize;
        if(Size > BlockSize)
            BlockSize = (Alignment) ? AKOS__Memory_Align(Size, Alignment) : Size;
        
        Block = AKOS__Arena_Allocate_Block(BlockSize);
        if(!Block)
        {
            //TODO(JJ): Diagnostic and error logging
            return NULL;
        }
        
        AKOS__Arena_Add_Block(Arena, Block);
    }
    
    Arena->CurrentBlock = Block;
    if(Alignment) Arena->CurrentBlock->Used = AKOS__Memory_Align(Arena->CurrentBlock->Used, Alignment);
    
    akos_u8* Ptr = Arena->CurrentBlock->Memory + Arena->CurrentBlock->Used;
    Arena->CurrentBlock->Used += Size;
    
    return Ptr;
}

static akos__arena_marker AKOS__Arena_Get_Marker(akos__arena* Arena)
{
    akos__arena_marker Marker;
    Marker.Arena = Arena;
    Marker.Block = Arena->CurrentBlock;
    if(Arena->CurrentBlock) Marker.Marker = Arena->CurrentBlock->Used;
    return Marker;
}

static void AKOS__Arena_Set_Marker(akos__arena* Arena, akos__arena_marker Marker)
{
    AK_OS_ASSERT(Arena == Marker.Arena, "Invalid arena for marker!");
    
    //NOTE(EVERYONE): If the block is null it always signalizes the beginning of the arena
    if(!Marker.Block)
    {
        Arena->CurrentBlock = Arena->FirstBlock;
        if(Arena->CurrentBlock) Arena->CurrentBlock->Used = 0;
    }
    else
    {
        Arena->CurrentBlock = Marker.Block;
        Arena->CurrentBlock->Used = Marker.Marker;
        
        akos__arena_block* ArenaBlock;
        for(ArenaBlock = Arena->CurrentBlock->Next; ArenaBlock; ArenaBlock = ArenaBlock->Next)
            ArenaBlock->Used = 0;
    }
}

#define AKOS__Push_Struct(arena, type) (type*)AKOS__Arena_Allocate(arena, sizeof(type), alignof(type))

//~Internal hashmap implementation

typedef akos_u32 akos__hash_function(void* Key);
typedef akos_b32 akos__hash_comparer(void* KeyA, void* KeyB);

typedef struct akos__hashmap_slot
{
    akos_b32 IsValid;
    akos_u32 ItemIndex;
    akos_u32 BaseCount;
    akos_u32 Hash;
} akos__hashmap_slot;

typedef struct akos__hashmap
{
    akos_u32 Length;
    akos_u32 SlotCapacity;
    akos_u32 ValueCapacity;
    akos_u32 KeySize;
    akos_u32 ValueSize;
    
    akos__hashmap_slot* Slots;
    
    akos_u32* ValueSlots;
    akos_u8* Keys;
    akos_u8* Values;
    
    akos__hash_function* Hash_Function;
    akos__hash_comparer* Hash_Comparer;
} akos__hashmap;

static akos__hashmap AKOS__Create_Hashmap(akos_u32 SlotCapacity, akos_u32 ValueCapacity, akos_u32 KeySize, akos_u32 ValueSize, 
                                          akos__hash_function* Hash_Function, akos__hash_comparer* Hash_Comparer)
{
    akos__hashmap Result;
    
    Result.Length = 0;
    Result.SlotCapacity = (akos_u32)AKOS__Ceil_Pow2(SlotCapacity);
    Result.ValueCapacity = ValueCapacity;
    Result.KeySize  = KeySize;
    Result.ValueSize = ValueSize;
    Result.Slots = NULL;
    Result.ValueSlots = NULL;
    Result.Keys = NULL;
    Result.Values = NULL;
    
    Result.Hash_Function = Hash_Function;
    Result.Hash_Comparer = Hash_Comparer;
    
    return Result;
}

static void AKOS__Delete_Hashmap(akos__hashmap* Hashmap)
{
    if(Hashmap->Slots)
        AKOS__Free(Hashmap->Slots);
    if(Hashmap->ValueSlots)
        AKOS__Free(Hashmap->ValueSlots);
    AKOS__Memory_Clear(Hashmap, sizeof(akos__hashmap));
}

static void AKOS__Hashmap_Realloc_Slots(akos__hashmap* Hashmap, akos_u32 NewCapacity)
{
    akos_u32 SlotMask = NewCapacity-1;
    
    akos_u64 AllocSize = NewCapacity*sizeof(akos__hashmap_slot);
    akos__hashmap_slot* Slots = (akos__hashmap_slot*)AKOS__Malloc(AllocSize);
    AKOS__Memory_Clear(Slots, AllocSize);
    
    if(Hashmap->Slots)
    {
        akos_u32 OldSlotIndex;
        for(OldSlotIndex = 0; OldSlotIndex < Hashmap->SlotCapacity; OldSlotIndex++)
        {
            if(Hashmap->Slots[OldSlotIndex].IsValid)
            {
                akos_u32 Hash = Hashmap->Slots[OldSlotIndex].Hash;
                akos_u32 BaseSlot = Hash & SlotMask;
                akos_u32 Slot = BaseSlot;
                while(Slots[Slot].IsValid)
                    Slot = (Slot+1) & SlotMask;
                Slots[Slot].Hash = Hash;
                akos_u32 ItemIndex = Hashmap->Slots[OldSlotIndex].ItemIndex;
                Slots[Slot].ItemIndex = ItemIndex;
                Hashmap->ValueSlots[ItemIndex] = Slot;            
                Slots[BaseSlot].BaseCount++;
                Slots[Slot].IsValid = akos_true;
            }
        }
        AKOS__Free(Hashmap->Slots);
    }
    
    Hashmap->SlotCapacity = NewCapacity;
    Hashmap->Slots = Slots;
}

static void AKOS__Hashmap_Realloc(akos__hashmap* Hashmap, akos_u32 NewCapacity)
{
    size_t AllocSize = NewCapacity * (sizeof(akos_u32) + Hashmap->KeySize + Hashmap->ValueSize);
    void* MapData = AKOS__Malloc(AllocSize);        
    AKOS__Memory_Clear(MapData, AllocSize);
    
    akos_u32* NewValueSlots = (akos_u32*)MapData;
    akos_u8* NewKeys = (akos_u8*)(NewValueSlots + NewCapacity);
    akos_u8* NewValues = NewKeys + NewCapacity*Hashmap->KeySize;        
    
    if(Hashmap->ValueSlots)
    {
        AKOS__Memory_Copy(NewValueSlots, Hashmap->ValueSlots, Hashmap->Length*sizeof(akos_u32));
        AKOS__Memory_Copy(NewKeys, Hashmap->Keys, Hashmap->Length*Hashmap->KeySize);
        AKOS__Memory_Copy(NewValues, Hashmap->Values, Hashmap->Length*Hashmap->ValueSize);
        AKOS__Free(Hashmap->ValueSlots);
    }
    
    Hashmap->ValueCapacity = NewCapacity;
    Hashmap->ValueSlots = NewValueSlots;
    Hashmap->Keys = NewKeys;
    Hashmap->Values = NewValues;        
}

static akos_i64 AKOS__Hashmap_Find_Slot(akos__hashmap* Hashmap, void* Key)
{
    akos_u32 SlotMask = Hashmap->SlotCapacity - 1;
    akos_u32 Hash = Hashmap->Hash_Function(Key);
    
    akos_u32 BaseSlot = Hash & SlotMask;
    akos_u32 BaseCount = Hashmap->Slots[BaseSlot].BaseCount;
    akos_u32 Slot = BaseSlot;
    
    while(BaseCount > 0)
    {
        if(Hashmap->Slots[Slot].IsValid)
        {
            akos_u32 SlotHash = Hashmap->Slots[Slot].Hash;
            akos_u32 SlotBase = SlotHash & SlotMask;
            if(SlotBase == BaseSlot)
            {
                BaseCount--;
                if(SlotHash == Hash)
                {
                    akos_u8* HashKey = Hashmap->Keys + Hashmap->KeySize*Hashmap->Slots[Slot].ItemIndex;
                    
                    akos_b32 KeysEqual = Hashmap->Hash_Comparer(HashKey, Key);
                    if(KeysEqual) return (akos_i64)Slot;
                }
            }
        }        
        
        Slot = (Slot+1) & SlotMask;
    }
    
    return -1;
}

static void AKOS__Hashmap_Add(akos__hashmap* Hashmap, void* Key, void* Value)
{
    if(!Hashmap->Slots) AKOS__Hashmap_Realloc_Slots(Hashmap, Hashmap->SlotCapacity);
    if(!Hashmap->ValueSlots) AKOS__Hashmap_Realloc(Hashmap, Hashmap->ValueCapacity);
    
    AK_OS_ASSERT(AKOS__Hashmap_Find_Slot(Hashmap, Key) < 0, "Cannot insert duplicate keys into hash map");
    
    if(Hashmap->Length >= (Hashmap->SlotCapacity - Hashmap->SlotCapacity/3))
        AKOS__Hashmap_Realloc_Slots(Hashmap, (akos_u32)AKOS__Ceil_Pow2(Hashmap->SlotCapacity*2));
    
    akos_u32 SlotMask = Hashmap->SlotCapacity-1;
    akos_u32 Hash = Hashmap->Hash_Function(Key);
    
    akos_u32 BaseSlot = Hash & SlotMask;
    akos_u32 BaseCount = Hashmap->Slots[BaseSlot].BaseCount;
    akos_u32 Slot = BaseSlot;
    akos_u32 FirstFree = Slot;
    
    while(BaseCount)
    {
        akos_u32 SlotHash = Hashmap->Slots[Slot].Hash;
        if(!Hashmap->Slots[Slot].IsValid && Hashmap->Slots[FirstFree].IsValid) FirstFree = Slot;
        akos_u32 SlotBase = SlotHash & SlotMask;
        if(SlotBase == BaseSlot)
            BaseCount--;
        Slot = (Slot+1) & SlotMask;
    }
    
    Slot = FirstFree;
    while(Hashmap->Slots[Slot].IsValid)
        Slot = (Slot+1) & SlotMask;
    
    if(Hashmap->Length >= Hashmap->ValueCapacity)
        AKOS__Hashmap_Realloc(Hashmap, Hashmap->ValueCapacity*2);
    
    AK_OS_ASSERT(!Hashmap->Slots[Slot].IsValid && (Hash & SlotMask) == BaseSlot, "");
    AK_OS_ASSERT(Hash, "Invalid hash");
    
    Hashmap->Slots[Slot].Hash = Hash;
    Hashmap->Slots[Slot].ItemIndex = Hashmap->Length;
    Hashmap->Slots[Slot].IsValid = akos_true;
    Hashmap->Slots[BaseSlot].BaseCount++;
    
    Hashmap->ValueSlots[Hashmap->Length] = Slot;
    
    AKOS__Memory_Copy(Hashmap->Keys + Hashmap->Length*Hashmap->KeySize, Key, Hashmap->KeySize);
    AKOS__Memory_Copy(Hashmap->Values + Hashmap->Length*Hashmap->ValueSize, Value, Hashmap->ValueSize);
    
    Hashmap->Length++;
}

static void* AKOS__Hashmap_Find(akos__hashmap* Hashmap, void* Key)
{
    akos_i64 Slot = AKOS__Hashmap_Find_Slot(Hashmap, Key);
    if(Slot < 0) return NULL;
    
    akos_u32 ItemIndex = Hashmap->Slots[Slot].ItemIndex;
    void* Result = Hashmap->Values + ItemIndex*Hashmap->ValueSize;
    return Result;
}

static void AKOS__Hashmap_Remove(akos__hashmap* Hashmap, void* Key)
{
    akos_i64 Slot = AKOS__Hashmap_Find_Slot(Hashmap, Key);
    AK_OS_ASSERT(Slot >= 0, "Cannot find entry with key in hash map");
    AK_OS_ASSERT(Hashmap->Slots[Slot].IsValid, "Hash is invalid");
    
    if(Slot >= 0 && Hashmap->Slots[Slot].IsValid)
    {
        akos_u32 SlotMask = Hashmap->SlotCapacity-1;
        akos_u32 Hash = Hashmap->Slots[Slot].Hash;
        akos_u32 BaseSlot = Hash & SlotMask;
        Hashmap->Slots[BaseSlot].BaseCount--;
        Hashmap->Slots[Slot].Hash = 0;
        Hashmap->Slots[Slot].IsValid = akos_false;
        
        akos_u32 Index = Hashmap->Slots[Slot].ItemIndex;
        akos_u32 LastIndex = Hashmap->Length-1;
        
        if(Index != LastIndex)
        {
            AKOS__Memory_Copy(Hashmap->Keys + Index*Hashmap->KeySize, Hashmap->Keys + LastIndex*Hashmap->KeySize, Hashmap->KeySize);
            AKOS__Memory_Copy(Hashmap->Values + Index*Hashmap->ValueSize, Hashmap->Values + LastIndex*Hashmap->ValueSize, Hashmap->ValueSize);
            Hashmap->ValueSlots[Index] = Hashmap->ValueSlots[LastIndex];
            Hashmap->Slots[Hashmap->ValueSlots[LastIndex]].ItemIndex = Index;
        }
        
        Hashmap->Length--;
    }
}

typedef struct akos__event_buffer
{
    akos_u64    Capacity;
    akos_u64    Length;
    akos_event* Events;
} akos__event_buffer;

akos__event_buffer AKOS__Create_Event_Buffer(akos_u64 InitialCapacity)
{
    akos__event_buffer Result;
    Result.Capacity = InitialCapacity;
    Result.Length = 0;
    Result.Events = (akos_event*)AKOS__Malloc(InitialCapacity*sizeof(akos_event));
    if(!Result.Events)
    {
        //TODO(JJ): Diagnostic and error logging
        AKOS__Memory_Clear(&Result, sizeof(akos__event_buffer));
    }
    return Result;
}

void AKOS__Add_Event_To_Buffer(akos__event_buffer* EventBuffer, akos_event* Event)
{
    if(EventBuffer->Length == EventBuffer->Capacity)
    {
        akos_u64 NewCapacity = EventBuffer->Capacity*2;
        akos_event* Events = (akos_event*)AKOS__Malloc(NewCapacity*sizeof(akos_event));
        if(!Events)
        {
            //TODO(JJ): Diagnostic and error logging
            return;
        }
        
        AKOS__Memory_Copy(Events, EventBuffer->Events, EventBuffer->Capacity*sizeof(akos_event));
        AKOS__Free(EventBuffer->Events);
        EventBuffer->Events = Events;
        EventBuffer->Capacity = NewCapacity;
    }
    
    EventBuffer->Events[EventBuffer->Length++] = *Event;
}

void AKOS__Clear_Events(akos__event_buffer* EventBuffer)
{
    if(EventBuffer->Length) AKOS__Memory_Clear(EventBuffer->Events, sizeof(akos_event)*EventBuffer->Length);
    EventBuffer->Length = 0;
}

typedef struct akos__event_manager
{
    akos_u32           BufferIndex;
    akos__event_buffer EventBuffers[2];
} akos__event_manager;

akos__event_manager AKOS__Create_Event_Manager()
{
    akos__event_manager Result;
    Result.BufferIndex = 0;
    Result.EventBuffers[0] = AKOS__Create_Event_Buffer(1024);
    Result.EventBuffers[1] = AKOS__Create_Event_Buffer(1024);
    return Result;
}

void AKOS__Add_Event(akos__event_manager* EventManager, akos_event* Event)
{
    AKOS__Add_Event_To_Buffer(&EventManager->EventBuffers[EventManager->BufferIndex], Event);
}

akos_event_list AKOS__Get_Event_List(akos__event_manager* EventManager)
{
    akos__event_buffer* Buffer = &EventManager->EventBuffers[EventManager->BufferIndex];
    
    akos_event_list Result;
    Result.Count = Buffer->Length;
    Result.Events = Buffer->Length ? Buffer->Events : NULL;
    
    EventManager->BufferIndex = EventManager->BufferIndex ? 0 : 1;
    AKOS__Clear_Events(&EventManager->EventBuffers[EventManager->BufferIndex]);
    
    return Result;
}

typedef struct akos__clipboard
{
    akos_u64 TextLength;
    char* Str;
} akos__clipboard;

//~Internal win32 implementation
#ifdef _WIN32

#include <windows.h>

#define AKOS__WINDOW_CLASS_NAME "AKOS__Window_Class_Name"

#define AKOS__Win32_LoadProc(library, proc) \
do \
{ \
(library)->proc = (akos__##proc*)GetProcAddress((library)->Library, #proc); \
if(!(library)->proc) \
{ \
/*TODO(JJ): Diagnostic and error logging*/ \
return akos_false; \
} \
} while(0)

#define AKOS__GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define AKOS__GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

#define AKOS__WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define AKOS__WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define AKOS__WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define AKOS__WGL_CONTEXT_FLAGS_ARB                   0x2094
#define AKOS__WGL_CONTEXT_PROFILE_MASK_ARB            0x9126

#define AKOS__WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define AKOS__WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

#define AKOS__WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#define AKOS__WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define AKOS__WGL_DRAW_TO_WINDOW_ARB                  0x2001
#define AKOS__WGL_ACCELERATION_ARB                    0x2003
#define AKOS__WGL_SUPPORT_OPENGL_ARB                  0x2010
#define AKOS__WGL_DOUBLE_BUFFER_ARB                   0x2011
#define AKOS__WGL_PIXEL_TYPE_ARB                      0x2013

#define AKOS__WGL_TYPE_RGBA_ARB                       0x202B
#define AKOS__WGL_FULL_ACCELERATION_ARB               0x2027

#define AKOS__WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB        0x20A9

#define AKOS__WGL_COLOR_BITS_ARB                      0x2014
#define AKOS__WGL_RED_BITS_ARB                        0x2015
#define AKOS__WGL_GREEN_BITS_ARB                      0x2017
#define AKOS__WGL_BLUE_BITS_ARB                       0x2019
#define AKOS__WGL_ALPHA_BITS_ARB                      0x201B
#define AKOS__WGL_DEPTH_BITS_ARB                      0x2022
#define AKOS__WGL_STENCIL_BITS_ARB                    0x2023

//~User32 functions
typedef ATOM akos__RegisterClassExA(WNDCLASSEX* unnamedParam1);
typedef BOOL akos__GetClassInfoExA(HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSEXA lpwcx);
typedef BOOL akos__UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance);
typedef LRESULT akos__DefWindowProcA(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
typedef BOOL akos__AdjustWindowRectEx(LPRECT Rect, DWORD Style, BOOL Menu, DWORD ExStyle);
typedef HWND akos__CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
typedef BOOL akos__DestroyWindow(HWND Window);
typedef LONG_PTR akos__SetWindowLongPtrA(HWND Window, int nIndex, LONG_PTR dwNewLong);
typedef LONG_PTR akos__GetWindowLongPtrA(HWND Window, int nIndex);
typedef void akos__PostQuitMessage(int nExitCode);
typedef BOOL akos__TranslateMessage(const MSG* lpMsg);
typedef LRESULT akos__DispatchMessageA(const MSG* lpMsg);
typedef BOOL akos__PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
typedef BOOL akos__OpenClipboard(HWND hWndNewOwnder);
typedef HANDLE akos__GetClipboardData(UINT uFormat);
typedef HANDLE akos__SetClipboardData(UINT uFormat, HANDLE hMem);
typedef BOOL akos__EmptyClipboard();
typedef BOOL akos__CloseClipboard();
typedef HCURSOR akos__LoadCursorA(HINSTANCE Instance, LPCSTR CursorName);
typedef BOOL akos__DestroyCursor(HCURSOR Cursor);
typedef HCURSOR akos__SetCursor(HCURSOR hCursor);
typedef int akos__ShowCursor(BOOL bShow);
typedef HWND akos__GetForegroundWindow();
typedef BOOL akos__BringWindowToTop(HWND Window);
typedef BOOL akos__SetForegroundWindow(HWND Window);
typedef HWND akos__SetFocus(HWND Window);
typedef BOOL akos__IsIconic(HWND Window);
typedef BOOL akos__SetCursorPos(int x, int y);
typedef BOOL akos__GetCursorPos(LPPOINT Point);
typedef BOOL akos__ScreenToClient(HWND Window, LPPOINT lpPoint);
typedef HWND akos__SetCapture(HWND Window);
typedef BOOL akos__ReleaseCapture();
typedef BOOL akos__ClientToScreen(HWND Window, LPPOINT lpPoint);
typedef HWND akos__GetCapture();
typedef DWORD akos__GetWindowThreadProcessId(HWND Window, LPDWORD lpdwProcessId);
typedef BOOL akos__ShowWindow(HWND Window, int nCmdShow);
typedef BOOL akos__SetWindowPos(HWND Window, HWND InsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
typedef BOOL akos__GetClientRect(HWND Window, LPRECT lpRect);
typedef HDC akos__GetDC(HWND Window);
typedef int akos__ReleaseDC(HWND Window, HDC hDC);
typedef SHORT akos__GetAsyncKeyState(int vKey);

typedef struct akos__user32
{
    HMODULE Library;
    akos__RegisterClassExA* RegisterClassExA;
    akos__GetClassInfoExA* GetClassInfoExA;
    akos__UnregisterClassA* UnregisterClassA;
    akos__DefWindowProcA* DefWindowProcA;
    akos__AdjustWindowRectEx* AdjustWindowRectEx;
    akos__CreateWindowExA* CreateWindowExA;
    akos__DestroyWindow* DestroyWindow;
    akos__SetWindowLongPtrA* SetWindowLongPtrA;
    akos__GetWindowLongPtrA* GetWindowLongPtrA;
    akos__PostQuitMessage* PostQuitMessage;
    akos__PeekMessageA* PeekMessageA;
    akos__TranslateMessage* TranslateMessage;
    akos__DispatchMessageA* DispatchMessageA;
    akos__OpenClipboard* OpenClipboard;
    akos__GetClipboardData* GetClipboardData;
    akos__SetClipboardData* SetClipboardData;
    akos__EmptyClipboard* EmptyClipboard;
    akos__CloseClipboard* CloseClipboard;
    akos__LoadCursorA* LoadCursorA;
    akos__DestroyCursor* DestroyCursor;
    akos__SetCursor* SetCursor;
    akos__ShowCursor* ShowCursor;
    akos__GetForegroundWindow* GetForegroundWindow;
    akos__BringWindowToTop* BringWindowToTop;
    akos__SetForegroundWindow* SetForegroundWindow;
    akos__SetFocus* SetFocus;
    akos__IsIconic* IsIconic;
    akos__SetCursorPos* SetCursorPos;
    akos__GetCursorPos* GetCursorPos;
    akos__ScreenToClient* ScreenToClient;
    akos__SetCapture* SetCapture;
    akos__ReleaseCapture* ReleaseCapture;
    akos__ClientToScreen* ClientToScreen;
    akos__GetCapture* GetCapture;
    akos__GetWindowThreadProcessId* GetWindowThreadProcessId;
    akos__ShowWindow* ShowWindow;
    akos__SetWindowPos* SetWindowPos;
    akos__GetClientRect* GetClientRect;
    akos__GetDC* GetDC;
    akos__ReleaseDC* ReleaseDC;
    akos__GetAsyncKeyState* GetAsyncKeyState;
} akos__user32;

//~GDI32 functions

typedef int akos__ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR* ppfd);
typedef int akos__DescribePixelFormat(HDC hdc, int iPixelFormat, UINT nBytes, PIXELFORMATDESCRIPTOR* ppfd);
typedef BOOL akos__SetPixelFormat(HDC hdc, int iPixelFormat, CONST PIXELFORMATDESCRIPTOR* ppfd);
typedef BOOL akos__SwapBuffers(HDC hdc);

typedef struct akos__gdi32
{
    HMODULE Library;
    akos__ChoosePixelFormat*   ChoosePixelFormat;
    akos__DescribePixelFormat* DescribePixelFormat;
    akos__SetPixelFormat*      SetPixelFormat;
    akos__SwapBuffers*         SwapBuffers;
} akos__gdi32;

typedef HGLRC akos__wglCreateContext(HDC DeviceContext);
typedef PROC akos__wglGetProcAddress(LPCSTR Proc);
typedef BOOL akos__wglMakeCurrent(HDC DeviceContext, HGLRC RenderContext);
typedef BOOL akos__wglDeleteContext(HGLRC RenderContext);

typedef struct akos__opengl32
{
    HMODULE Library;
    akos__wglCreateContext*  wglCreateContext;
    akos__wglGetProcAddress* wglGetProcAddress;
    akos__wglMakeCurrent*    wglMakeCurrent;
    akos__wglDeleteContext*  wglDeleteContext;
} akos__opengl32;

typedef BOOL akos__wglChoosePixelFormatARB(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC akos__wglCreateContextAttribsARB(HDC hdc, HGLRC hShareContext, const int* attribList);
typedef const char* akos__wglGetExtensionsStringARB(HDC hdc);
typedef BOOL akos__wglSwapIntervalEXT(int Interval);

typedef struct akos__wgl
{
    akos__wglChoosePixelFormatARB* wglChoosePixelFormatARB;
    akos__wglCreateContextAttribsARB* wglCreateContextAttribsARB;
    akos__wglGetExtensionsStringARB* wglGetExtensionsStringARB;
    akos__wglSwapIntervalEXT* wglSwapIntervalEXT;
} akos__wgl;

typedef struct akos__window
{
    HWND  HWND;
    DWORD Style;
    DWORD ExStyle;
    akos_u64 UserData;
    HDC   DeviceContext;
    HGLRC RenderContext;
} akos__window;

typedef struct akos__thread
{
    HANDLE Handle;
    DWORD  ThreadID;
} akos__thread;

typedef struct akos__mutex
{
    CRITICAL_SECTION CriticalSection;
} akos__mutex;

typedef struct akos__file
{
    HANDLE Handle;
    akos_u64 Flags;
} akos__file;

typedef struct akos__event
{
    HANDLE Handle;
} akos__event;

typedef struct akos__timer
{
    HANDLE Handle;
    akos_timer_callback* Callback;
    void* UserData;
} akos__timer;

typedef struct akos__cursor
{
    HCURSOR Handle;
} akos__cursor;

typedef struct akos_context
{
    akos__arena PermanentStorage;
    akos__arena TransientStorage;
    akos__user32   User32;
    akos__gdi32    GDI32;
    akos__opengl32 OpenGL32;
    akos__wgl      WGL;
    
    akos__pool Windows;
    akos__pool Threads;
    akos__pool Mutexes;
    akos__pool Files;
    akos__pool Events;
    akos__pool Timers;
    akos__pool Cursors;
    
    akos_handle SetCursorHandle;
    
    int WGLAttributes[9];
    
    akos__event_manager EventManager;
    akos__clipboard Clipboard;
} akos_context;

AK_OS_DEF void* AKOS_Reserve(size_t Size)
{
    void* Result = VirtualAlloc(0, Size, MEM_RESERVE, PAGE_READWRITE);
    return Result;
}

AK_OS_DEF int  AKOS_Commit(void* Memory, size_t Size)
{
    int Result = VirtualAlloc(Memory, Size, MEM_COMMIT, PAGE_READWRITE) != NULL;
    return Result;
}

AK_OS_DEF void  AKOS_Decommit(void* Memory, size_t Size)
{
    VirtualFree(Memory, Size, MEM_DECOMMIT);
}

AK_OS_DEF void  AKOS_Release(void* Memory)
{
    VirtualFree(Memory, 0, MEM_RELEASE);
}

AK_OS_DEF akos_u32 AKOS_Get_Current_Thread_ID()
{
    return GetCurrentThreadId();
}

AK_OS_DEF int AKOS_Directory_Exists(const char* Directory)
{
    DWORD Attrib = GetFileAttributes(Directory);
    return (Attrib != INVALID_FILE_ATTRIBUTES && Attrib & FILE_ATTRIBUTE_DIRECTORY);
}

AK_OS_DEF int AKOS_Create_Directory(const char* Directory)
{
    return CreateDirectoryA(Directory, NULL);
}

static akos_handle AKOS__Win32_Get_Handle_From_HWND(HWND Window)
{
    akos_context* Context = AKOS_Get_Context();
    akos__user32* User32 = &Context->User32;
    akos_u16 WindowIndex = (akos_u16)User32->GetWindowLongPtrA(Window, GWLP_USERDATA);
    if(WindowIndex)
    {
        akos_handle Handle = AKOS__Pool_Get_ID_From_Index(&Context->Windows, WindowIndex-1);
        return Handle;
    }
    return 0;
}

static LRESULT CALLBACK AKOS__Win32_Default_Window_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;
    
    akos_context* Context = AKOS_Get_Context();
    akos__user32* User32 = &Context->User32;
    
    akos_event Event;
    AKOS__Memory_Clear(&Event, sizeof(akos_event));
    
    switch(Message)
    {
        case WM_CREATE:
        {
            //NOTE(EVERYONE): Set the user data to window index plus one because GetWindowLongPtrA returns 0
            //if the user data has not been set. Since the 0 index will conflict with this restriction add 1 to every index
            akos_u16 WindowIndex = (akos_u16)(size_t)((LPCREATESTRUCT)LParam)->lpCreateParams;
            User32->SetWindowLongPtrA(Window, GWLP_USERDATA, (LONG_PTR)(WindowIndex+1));
        } break;
        
        case WM_CLOSE:
        {
            Event.Type = AKOS_EVENT_TYPE_WINDOW_CLOSED;
            Event.Window = AKOS__Win32_Get_Handle_From_HWND(Window);
        } break;
        
        case WM_SETFOCUS:
        {
            Event.Type = AKOS_EVENT_TYPE_WINDOW_FOCUSED;
            Event.Focused.IsFocused = akos_true;
        } break;
        
        case WM_KILLFOCUS:
        {
            Event.Type = AKOS_EVENT_TYPE_WINDOW_FOCUSED;
            Event.Focused.IsFocused = akos_false;
        } break;
        
        case WM_CHAR:
        case WM_SYSCHAR:
        {
            if(WParam > 0 && WParam < 0x10000)
            {
                Event.Type = AKOS_EVENT_TYPE_CHAR_INPUT;
                Event.CharInput.Code = (akos_u16)WParam;
            }
        } break;
        
        default:
        {
            Result = User32->DefWindowProcA(Window, Message, WParam, LParam);
        } break;
    }
    
    if(Event.Type != AKOS_EVENT_TYPE_NONE)
        AKOS__Add_Event(&Context->EventManager, &Event);
    
    return Result;
}

akos_b32 AKOS__Win32_Init_Libraries(akos_context* Context)
{
    akos__user32* User32 = &Context->User32;
    User32->Library = LoadLibrary("User32.dll");
    if(!User32->Library) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    AKOS__Win32_LoadProc(User32, RegisterClassExA);
    AKOS__Win32_LoadProc(User32, GetClassInfoExA);
    AKOS__Win32_LoadProc(User32, UnregisterClassA);
    AKOS__Win32_LoadProc(User32, DefWindowProcA);
    AKOS__Win32_LoadProc(User32, AdjustWindowRectEx);
    AKOS__Win32_LoadProc(User32, CreateWindowExA);
    AKOS__Win32_LoadProc(User32, DestroyWindow);
    AKOS__Win32_LoadProc(User32, SetWindowLongPtrA);
    AKOS__Win32_LoadProc(User32, GetWindowLongPtrA);
    AKOS__Win32_LoadProc(User32, PostQuitMessage);
    AKOS__Win32_LoadProc(User32, PeekMessageA);
    AKOS__Win32_LoadProc(User32, TranslateMessage);
    AKOS__Win32_LoadProc(User32, DispatchMessageA);
    AKOS__Win32_LoadProc(User32, OpenClipboard);
    AKOS__Win32_LoadProc(User32, GetClipboardData);
    AKOS__Win32_LoadProc(User32, SetClipboardData);
    AKOS__Win32_LoadProc(User32, EmptyClipboard);
    AKOS__Win32_LoadProc(User32, CloseClipboard);
    AKOS__Win32_LoadProc(User32, LoadCursorA);
    AKOS__Win32_LoadProc(User32, DestroyCursor);
    AKOS__Win32_LoadProc(User32, SetCursor);
    AKOS__Win32_LoadProc(User32, ShowCursor);
    AKOS__Win32_LoadProc(User32, GetForegroundWindow);
    AKOS__Win32_LoadProc(User32, BringWindowToTop);
    AKOS__Win32_LoadProc(User32, SetForegroundWindow);
    AKOS__Win32_LoadProc(User32, SetFocus);
    AKOS__Win32_LoadProc(User32, IsIconic);
    AKOS__Win32_LoadProc(User32, SetCursorPos);
    AKOS__Win32_LoadProc(User32, GetCursorPos);
    AKOS__Win32_LoadProc(User32, ScreenToClient);
    AKOS__Win32_LoadProc(User32, SetCapture);
    AKOS__Win32_LoadProc(User32, ReleaseCapture);
    AKOS__Win32_LoadProc(User32, ClientToScreen);
    AKOS__Win32_LoadProc(User32, GetCapture);
    AKOS__Win32_LoadProc(User32, GetWindowThreadProcessId);
    AKOS__Win32_LoadProc(User32, ShowWindow);
    AKOS__Win32_LoadProc(User32, SetWindowPos);
    AKOS__Win32_LoadProc(User32, GetClientRect);
    AKOS__Win32_LoadProc(User32, GetDC);
    AKOS__Win32_LoadProc(User32, ReleaseDC);
    AKOS__Win32_LoadProc(User32, GetAsyncKeyState);
    
    akos__gdi32* GDI32 = &Context->GDI32;
    GDI32->Library = LoadLibrary("GDI32.dll");
    if(!GDI32->Library)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    AKOS__Win32_LoadProc(GDI32, ChoosePixelFormat);
    AKOS__Win32_LoadProc(GDI32, DescribePixelFormat);
    AKOS__Win32_LoadProc(GDI32, SetPixelFormat);
    AKOS__Win32_LoadProc(GDI32, SwapBuffers);
    
    akos__opengl32* OpenGL32 = &Context->OpenGL32;
    OpenGL32->Library = LoadLibrary("opengl32.dll");
    if(!OpenGL32->Library)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    AKOS__Win32_LoadProc(OpenGL32, wglCreateContext);
    AKOS__Win32_LoadProc(OpenGL32, wglGetProcAddress);
    AKOS__Win32_LoadProc(OpenGL32, wglMakeCurrent);
    AKOS__Win32_LoadProc(OpenGL32, wglDeleteContext);
    
    return akos_true;
}

akos_b32 AKOS__Register_Window_Classes(akos_context* Context)
{
    akos__user32* User32 = &Context->User32;
    
    WNDCLASSEXA WindowClass = {};
    WindowClass.cbSize = sizeof(WNDCLASSEXA);
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
    WindowClass.lpfnWndProc = AKOS__Win32_Default_Window_Proc;
    WindowClass.lpszClassName = AKOS__WINDOW_CLASS_NAME;
    if(!User32->RegisterClassExA(&WindowClass))
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    return akos_true;
}

akos_b32 AKOS__Init_WGL(akos_context* Context)
{
    akos__user32* User32 = &Context->User32;
    akos__gdi32* GDI32 = &Context->GDI32;
    akos__opengl32* OpenGL32 = &Context->OpenGL32;
    
    HWND DummyWindow = User32->CreateWindowExA(0, AKOS__WINDOW_CLASS_NAME, "Temp", 0, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(0), NULL);
    if(!DummyWindow)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    HDC DeviceContext = User32->GetDC(DummyWindow);
    if(!DeviceContext)
    {
        //TODO(JJ): Diagnostic and error logging
        User32->DestroyWindow(DummyWindow);
        return akos_false;
    }
    
    
    PIXELFORMATDESCRIPTOR TargetPixelFormat = {};
    TargetPixelFormat.nSize = sizeof(TargetPixelFormat);
    TargetPixelFormat.nVersion = 1;
    TargetPixelFormat.iPixelType = PFD_TYPE_RGBA;
    TargetPixelFormat.dwFlags = PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER;
    TargetPixelFormat.cColorBits =  32;
    TargetPixelFormat.iLayerType = PFD_MAIN_PLANE;
    
    int TargetPixelFormatIndex = GDI32->ChoosePixelFormat(DeviceContext, &TargetPixelFormat);
    
    PIXELFORMATDESCRIPTOR PixelFormat;
    if(!GDI32->DescribePixelFormat(DeviceContext, TargetPixelFormatIndex, sizeof(PixelFormat), 
                                   &PixelFormat))
    {
        //TODO(JJ): Diagnostic and error logging
        User32->ReleaseDC(DummyWindow, DeviceContext);
        User32->DestroyWindow(DummyWindow);
        return akos_false;
    }
    
    if(!GDI32->SetPixelFormat(DeviceContext, TargetPixelFormatIndex, &PixelFormat))
    {
        //TODO(JJ): Diagnostic and error logging
        User32->ReleaseDC(DummyWindow, DeviceContext);
        User32->DestroyWindow(DummyWindow);
        return akos_false;
    }
    
    HGLRC RenderContext = OpenGL32->wglCreateContext(DeviceContext);
    if(!RenderContext)
    {
        //TODO(JJ): Diagnostic and error logging
        User32->ReleaseDC(DummyWindow, DeviceContext);
        User32->DestroyWindow(DummyWindow);
        return akos_false;
    }
    
    if(!OpenGL32->wglMakeCurrent(DeviceContext, RenderContext))
    {
        //TODO(JJ): diagnostic and error logging
        OpenGL32->wglDeleteContext(RenderContext);
        User32->ReleaseDC(DummyWindow, DeviceContext);
        User32->DestroyWindow(DummyWindow);
        return akos_false;
    }
    
    akos__wgl* WGL = &Context->WGL;
    WGL->wglChoosePixelFormatARB = (akos__wglChoosePixelFormatARB*)OpenGL32->wglGetProcAddress("wglChoosePixelFormatARB");
    WGL->wglCreateContextAttribsARB = (akos__wglCreateContextAttribsARB*)OpenGL32->wglGetProcAddress("wglCreateContextAttribsARB");
    WGL->wglGetExtensionsStringARB = (akos__wglGetExtensionsStringARB*)OpenGL32->wglGetProcAddress("wglGetExtensionsStringARB");
    WGL->wglSwapIntervalEXT = (akos__wglSwapIntervalEXT*)OpenGL32->wglGetProcAddress("wglSwapIntervalEXT");
    
    int Result = (WGL->wglChoosePixelFormatARB && WGL->wglCreateContextAttribsARB &&
                  WGL->wglGetExtensionsStringARB && WGL->wglSwapIntervalEXT);
    if(!Result)
    {
        //TODO(JJ): Diagnostic and error logging
    }
    
    OpenGL32->wglMakeCurrent(NULL, NULL);
    OpenGL32->wglDeleteContext(RenderContext);
    User32->ReleaseDC(DummyWindow, DeviceContext);
    User32->DestroyWindow(DummyWindow);
    
    return akos_true;
}

AK_OS_DEF akos_context* AKOS_Create_Context(const akos_context_create_info* ContextCreateInfo)
{
    akos__arena ContextArena = AKOS__Create_Arena(1024*1024);
    akos_context* Context = AKOS__Push_Struct(&ContextArena, akos_context);
    if(!Context)
    {
        //TODO(JJ): Diagnostic and error logging
        AKOS__Delete_Arena(&ContextArena);
        return NULL;
    }
    
    AKOS_Set_Context(Context);
    Context->PermanentStorage = ContextArena;
    
    if(!AKOS__Win32_Init_Libraries(Context))
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    if(!AKOS__Register_Window_Classes(Context))
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Windows = AKOS__Create_Pool(64, sizeof(akos__window), AKOS__HANDLE_TYPE_WINDOW);
    if(!Context->Windows.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Threads = AKOS__Create_Pool(64, sizeof(akos__thread), AKOS__HANDLE_TYPE_THREAD);
    if(!Context->Threads.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Mutexes = AKOS__Create_Pool(64, sizeof(akos__mutex), AKOS__HANDLE_TYPE_MUTEX);
    if(!Context->Mutexes.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Files = AKOS__Create_Pool(64, sizeof(akos__file), AKOS__HANDLE_TYPE_FILE);
    if(!Context->Files.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Events = AKOS__Create_Pool(64, sizeof(akos__event), AKOS__HANDLE_TYPE_EVENT);
    if(!Context->Events.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Timers = AKOS__Create_Pool(64, sizeof(akos__timer), AKOS__HANDLE_TYPE_TIMER);
    if(!Context->Timers.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    Context->Cursors = AKOS__Create_Pool(64, sizeof(akos__cursor), AKOS__HANDLE_TYPE_CURSOR);
    if(!Context->Cursors.Data)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    
    if(!AKOS__Init_WGL(Context))
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    if(ContextCreateInfo)
    {
        const akos_gl_context_create_info* GLInfo = &ContextCreateInfo->GLInfo;
        
        int ContextFlags = 0;
        if(GLInfo->ContextFlags & AKOS_GL_CONTEXT_FORWARD_COMPATABILITY_BIT)
            ContextFlags |= AKOS__WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
        
        if(GLInfo->ContextFlags & AKOS_GL_CONTEXT_DEBUG_BIT)
            ContextFlags |= AKOS__WGL_CONTEXT_DEBUG_BIT_ARB;
        
        int ProfileMask = 0;
        if(GLInfo->ProfileMask & AKOS_GL_CONTEXT_PROFILE_MASK_COMPATABILITY_BIT)
            ProfileMask |= AKOS__WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        
        if(GLInfo->ProfileMask & AKOS_GL_CONTEXT_PROFILE_MASK_CORE_BIT)
            ProfileMask |= AKOS__WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
        
        int Attributes[] = 
        {
            AKOS__WGL_CONTEXT_MAJOR_VERSION_ARB, GLInfo->MajorVersion, 
            AKOS__WGL_CONTEXT_MINOR_VERSION_ARB, GLInfo->MinorVersion,
            AKOS__WGL_CONTEXT_FLAGS_ARB, ContextFlags, 
            AKOS__WGL_CONTEXT_PROFILE_MASK_ARB, ProfileMask, 
            0
        };
        
        AKOS__Memory_Copy(Context->WGLAttributes, Attributes, sizeof(Attributes));
    }
    
    Context->EventManager = AKOS__Create_Event_Manager();
    if(!Context->EventManager.EventBuffers[0].Capacity)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    if(!Context->EventManager.EventBuffers[1].Capacity)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    return Context;
    
    error:
    AKOS_Delete_Context(Context);
    AKOS_Set_Context(NULL);
    return NULL;
}

AK_OS_DEF void AKOS_Delete_Context(akos_context* Context)
{
    if(Context)
    {
        akos__user32* User32 = &Context->User32;
        
        User32->PostQuitMessage(0);
        AKOS_Poll_Events();
        //Delete context resources here
    }
}

AK_OS_DEF akos_u64 AKOS_Performance_Counter()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return Result.QuadPart;
}

AK_OS_DEF akos_u64 AKOS_Performance_Frequency()
{
    LARGE_INTEGER Result;
    QueryPerformanceFrequency(&Result);
    return Result.QuadPart;
}

AK_OS_DEF akos_handle AKOS_Create_Thread(akos_thread_callback* ThreadCallback, void* UserData)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Threads);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__thread* Thread = (akos__thread*)AKOS__Pool_Get(&Context->Threads, Handle);
    Thread->Handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadCallback, UserData, 0, &Thread->ThreadID);
    if(Thread->Handle == INVALID_HANDLE_VALUE)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    return Handle;
    
    error:
    AKOS_Delete_Thread(Handle);
    return 0;
}

AK_OS_DEF void AKOS_Delete_Thread(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__thread* Thread = (akos__thread*)AKOS__Pool_Get(&Context->Threads, Handle);
    if(Thread)
    {
        CloseHandle(Thread->Handle);
        AKOS__Pool_Free(&Context->Threads, Handle);
    }
}

AK_OS_DEF void AKOS_Thread_Wait(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__thread* Thread = (akos__thread*)AKOS__Pool_Get(&Context->Threads, Handle);
    if(Thread)
    {
        WaitForSingleObject(Thread->Handle, INFINITE);
    }
}

AK_OS_DEF akos_handle AKOS_Create_Mutex()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Mutexes);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__mutex* Mutex = (akos__mutex*)AKOS__Pool_Get(&Context->Mutexes, Handle);
    InitializeCriticalSection(&Mutex->CriticalSection);
    return Handle;
}

AK_OS_DEF void AKOS_Delete_Mutex(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__mutex* Mutex = (akos__mutex*)AKOS__Pool_Get(&Context->Mutexes, Handle);
    if(Mutex)
    {
        DeleteCriticalSection(&Mutex->CriticalSection);
        AKOS__Pool_Free(&Context->Mutexes, Handle);
    }
}

AK_OS_DEF void AKOS_Mutex_Lock(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__mutex* Mutex = (akos__mutex*)AKOS__Pool_Get(&Context->Mutexes, Handle);
    if(Mutex) EnterCriticalSection(&Mutex->CriticalSection);
}

AK_OS_DEF void AKOS_Mutex_Unlock(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__mutex* Mutex = (akos__mutex*)AKOS__Pool_Get(&Context->Mutexes, Handle);
    if(Mutex) LeaveCriticalSection(&Mutex->CriticalSection);
}

AK_OS_DEF akos_handle AKOS_Create_Event()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Events);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__event* Event = (akos__event*)AKOS__Pool_Get(&Context->Events, Handle);
    Event->Handle = CreateEventA(NULL, FALSE, FALSE, NULL);
    return Handle;
}

AK_OS_DEF void AKOS_Delete_Event(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__event* Event = (akos__event*)AKOS__Pool_Get(&Context->Events, Handle);
    if(Event)
    {
        CloseHandle(Event->Handle);
        AKOS__Pool_Free(&Context->Events, Handle);
    }
}

AK_OS_DEF void AKOS_Event_Signal(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__event* Event = (akos__event*)AKOS__Pool_Get(&Context->Events, Handle);
    if(Event) SetEvent(Event->Handle);
}

AK_OS_DEF void AKOS_Event_Wait(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__event* Event = (akos__event*)AKOS__Pool_Get(&Context->Events, Handle);
    if(Event) WaitForSingleObject(Event->Handle, INFINITE);
}

AK_OS_DEF akos_handle AKOS_Create_Timer()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Timers);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__timer* Timer = (akos__timer*)AKOS__Pool_Get(&Context->Timers, Handle);
    Timer->Handle = CreateWaitableTimerA(NULL, FALSE, NULL);
    return Handle;
}

AK_OS_DEF void AKOS_Delete_Timer(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__timer* Timer = (akos__timer*)AKOS__Pool_Get(&Context->Timers, Handle);
    if(Timer)
    {
        CloseHandle(Timer->Handle);
        AKOS__Pool_Free(&Context->Timers, Handle);
    }
}

void AKOS__Win32_Internal_Timer_Completion_Routine(LPVOID UserData, DWORD Low, DWORD High)
{
    akos_u16 TimerIndex = (akos_u16)(size_t)UserData;
    akos_context* Context = AKOS_Get_Context();
    
    akos_handle TimerHandle = AKOS__Pool_Get_ID_From_Index(&Context->Timers, TimerIndex);
    akos__timer* Timer = (akos__timer*)AKOS__Pool_Get(&Context->Timers, TimerHandle);
    if(Timer && Timer->Callback) Timer->Callback(Timer->UserData);
}

AK_OS_DEF void AKOS_Timer_Set(akos_handle Handle, akos_u64 TicksToWait, akos_timer_callback* TimerCallback, void* UserData)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__timer* Timer = (akos__timer*)AKOS__Pool_Get(&Context->Timers, Handle);
    if(Timer)
    {
        Timer->Callback = TimerCallback;
        Timer->UserData = UserData;
        akos_u64 TicksPerHundredSecond = AKOS_Performance_Frequency()/10000000;
        
        akos_u16 TimerIndex = (akos_u16)Handle;
        
        LARGE_INTEGER TimerValue;
        TimerValue.QuadPart = -((akos_i64)TicksToWait/(akos_i64)TicksPerHundredSecond);
        SetWaitableTimer(Timer->Handle, &TimerValue, 0, AKOS__Win32_Internal_Timer_Completion_Routine, (LPVOID)(size_t)TimerIndex, 0);
    }
}

AK_OS_DEF void AKOS_Timer_Wait(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__timer* Timer = (akos__timer*)AKOS__Pool_Get(&Context->Timers, Handle);
    if(Timer) WaitForSingleObject(Timer->Handle, INFINITE);
}

AK_OS_DEF akos_handle AKOS_Create_File(const char* Filepath, akos_u64 Flags)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    DWORD DesiredAttributes   = 0;
    DWORD CreationDisposition = 0;
    
    akos_i32 ReadAndWrite = Flags == (AKOS_FILE_FLAG_READ|AKOS_FILE_FLAG_WRITE);
    if(ReadAndWrite)
    {
        DesiredAttributes = GENERIC_READ|GENERIC_WRITE;
        CreationDisposition = OPEN_ALWAYS;
    }
    else if(Flags & AKOS_FILE_FLAG_READ)
    {
        DesiredAttributes = GENERIC_READ;
        CreationDisposition = OPEN_EXISTING;
    }
    else if(Flags & AKOS_FILE_FLAG_WRITE)
    {
        DesiredAttributes   = GENERIC_WRITE;
        CreationDisposition = CREATE_ALWAYS;
    }
    else
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Files);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    
    File->Handle = CreateFile(Filepath, DesiredAttributes, 0, NULL, CreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if(File->Handle == INVALID_HANDLE_VALUE)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    File->Flags = Flags;
    
    return Handle;
    
    error:
    AKOS_Delete_File(Handle);
    return 0;
}

AK_OS_DEF akos_u64 AKOS_Get_File_Size(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return AKOS_INVALID_FILE_SIZE;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(!File)
    {
        //TODO(JJ): Diagnostic and error logging
        return AKOS_INVALID_FILE_SIZE;
    }
    
    if(!(File->Flags & AKOS_FILE_FLAG_READ))
    {
        //TODO(JJ): Diagnostic and error logging
        return AKOS_INVALID_FILE_SIZE;
    }
    
    LARGE_INTEGER FileSize;
    GetFileSizeEx(File->Handle, &FileSize);
    return FileSize.QuadPart;
}

AK_OS_DEF int AKOS_Read_File(akos_handle Handle,  void* Data, akos_u32 DataSize, akos_u64 Offset)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(!File)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    if(!(File->Flags & AKOS_FILE_FLAG_READ))
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    
    OVERLAPPED* POverlappedOffset = NULL;
    OVERLAPPED OverlappedOffset = {};
    if(Offset != AKOS_INVALID_FILE_SIZE)
    {
        OverlappedOffset.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        OverlappedOffset.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        POverlappedOffset = &OverlappedOffset;
    }
    
    DWORD BytesRead;
    if(!ReadFile(File->Handle, Data, DataSize, &BytesRead, POverlappedOffset))
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    if(BytesRead != DataSize)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    return akos_true;
}

AK_OS_DEF int AKOS_Write_File(akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(!File)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    if(!(File->Flags & AKOS_FILE_FLAG_WRITE))
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    
    OVERLAPPED* POverlappedOffset = NULL;
    OVERLAPPED OverlappedOffset = {};
    if(Offset != AKOS_INVALID_FILE_SIZE)
    {
        OverlappedOffset.Offset = (DWORD)(Offset & 0xFFFFFFFF);
        OverlappedOffset.OffsetHigh = (DWORD)((Offset >> 32) & 0xFFFFFFFF);
        POverlappedOffset = &OverlappedOffset;
    }
    
    DWORD BytesWritten;
    if(!WriteFile(File->Handle, Data, DataSize, &BytesWritten, POverlappedOffset))
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    if(BytesWritten != DataSize)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    return akos_true;
}

AK_OS_DEF void AKOS_Delete_File(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(File)
    {
        CloseHandle(File->Handle);
        AKOS__Pool_Free(&Context->Files, Handle);
    }
}

static akos_mousecode AKOS__Mouse_Event_To_AKOS(DWORD Event)
{
    akos_mousecode Result = AKOS_MOUSECODE_UNKNOWN;
    
    switch(Event)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        Result = AKOS_MOUSECODE_LEFT;
        break;
        
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        Result = AKOS_MOUSECODE_RIGHT;
        break;
        
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        Result = AKOS_MOUSECODE_MIDDLE;
        break;
    }
    
    return Result;
}

static akos_keycode AKOS__VK_To_AKOS(DWORD KeyCode)
{
    akos_keycode Result = AKOS_KEYCODE_UNKNOWN;
    switch(KeyCode)
    {
        case 'A':
        Result = AKOS_KEYCODE_A;
        break;
        
        case 'B':
        Result = AKOS_KEYCODE_B;
        break;
        
        case 'C':
        Result = AKOS_KEYCODE_C;
        break;
        
        case 'D':
        Result = AKOS_KEYCODE_D;
        break;
        
        case 'E':
        Result = AKOS_KEYCODE_E;
        break;
        
        case 'F':
        Result = AKOS_KEYCODE_F;
        break;
        
        case 'G':
        Result = AKOS_KEYCODE_G;
        break;
        
        case 'H':
        Result = AKOS_KEYCODE_H;
        break;
        
        case 'I':
        Result = AKOS_KEYCODE_I;
        break;
        
        case 'J':
        Result = AKOS_KEYCODE_J;
        break;
        
        case 'K':
        Result = AKOS_KEYCODE_K;
        break;
        
        case 'L':
        Result = AKOS_KEYCODE_L;
        break;
        
        case 'M':
        Result = AKOS_KEYCODE_M;
        break;
        
        case 'N':
        Result = AKOS_KEYCODE_N;
        break;
        
        case 'O':
        Result = AKOS_KEYCODE_O;
        break;
        
        case 'P':
        Result = AKOS_KEYCODE_P;
        break;
        
        case 'Q':
        Result = AKOS_KEYCODE_Q;
        break;
        
        case 'R':
        Result = AKOS_KEYCODE_R;
        break;
        
        case 'S':
        Result = AKOS_KEYCODE_S;
        break;
        
        case 'T':
        Result = AKOS_KEYCODE_T;
        break;
        
        case 'U':
        Result = AKOS_KEYCODE_U;
        break;
        
        case 'V':
        Result = AKOS_KEYCODE_V;
        break;
        
        case 'W':
        Result = AKOS_KEYCODE_W;
        break;
        
        case 'X':
        Result = AKOS_KEYCODE_X;
        break;
        
        case 'Y':
        Result = AKOS_KEYCODE_Y;
        break;
        
        case 'Z':
        Result = AKOS_KEYCODE_Z;
        break;
        
        case '0':
        Result = AKOS_KEYCODE_0;
        break;
        
        case '1':
        Result = AKOS_KEYCODE_1;
        break;
        
        case '2':
        Result = AKOS_KEYCODE_2;
        break;
        
        case '3':
        Result = AKOS_KEYCODE_3;
        break;
        
        case '4':
        Result = AKOS_KEYCODE_4;
        break;
        
        case '5':
        Result = AKOS_KEYCODE_5;
        break;
        
        case '6':
        Result = AKOS_KEYCODE_6;
        break;
        
        case '7':
        Result = AKOS_KEYCODE_7;
        break;
        
        case '8':
        Result = AKOS_KEYCODE_8;
        break;
        
        case '9':
        Result = AKOS_KEYCODE_9;
        break;
        
        case VK_SPACE:
        Result = AKOS_KEYCODE_SPACE;
        break;
        
        case VK_OEM_3:
        Result = AKOS_KEYCODE_TICK;
        break;
        
        case VK_OEM_MINUS:
        Result = AKOS_KEYCODE_MINUS;
        break;
        
        case VK_OEM_PLUS:
        Result = AKOS_KEYCODE_EQUAL;
        break;
        
        case VK_OEM_4:
        Result = AKOS_KEYCODE_LEFTBRACKET;
        break;
        
        case VK_OEM_6:
        Result = AKOS_KEYCODE_RIGHTBRACKET;
        break;
        
        case VK_OEM_1:
        Result = AKOS_KEYCODE_SEMICOLON;
        break;
        
        case VK_OEM_7:
        Result = AKOS_KEYCODE_QUOTE;
        break;
        
        case VK_OEM_COMMA:
        Result = AKOS_KEYCODE_COMMA;
        break;
        
        case VK_OEM_PERIOD:
        Result = AKOS_KEYCODE_PERIOD;
        break;
        
        case VK_OEM_2:
        Result = AKOS_KEYCODE_FORWARDSLASH;
        break;
        
        case VK_OEM_5:
        Result = AKOS_KEYCODE_BACKSLASH;
        break;
        
        case VK_TAB:
        Result = AKOS_KEYCODE_TAB;
        break;
        
        case VK_ESCAPE:
        Result = AKOS_KEYCODE_ESCAPE;
        break;
        
        case VK_PAUSE:
        Result = AKOS_KEYCODE_PAUSE;
        break;
        
        case VK_UP:
        Result = AKOS_KEYCODE_UP;
        break;
        
        case VK_DOWN:
        Result = AKOS_KEYCODE_DOWN;
        break;
        
        case VK_LEFT:
        Result = AKOS_KEYCODE_LEFT;
        break;
        
        case VK_RIGHT:
        Result = AKOS_KEYCODE_RIGHT;
        break;
        
        case VK_BACK:
        Result = AKOS_KEYCODE_BACKSPACE;
        break;
        
        case VK_RETURN:
        Result = AKOS_KEYCODE_RETURN;
        break;
        
        case VK_DELETE:
        Result = AKOS_KEYCODE_DELETE;
        break;
        
        case VK_INSERT:
        Result = AKOS_KEYCODE_INSERT;
        break;
        
        case VK_HOME:
        Result = AKOS_KEYCODE_HOME;
        break;
        
        case VK_END:
        Result = AKOS_KEYCODE_END;
        break;
        
        case VK_PRIOR:
        Result = AKOS_KEYCODE_PAGEUP;
        break;
        
        case VK_NEXT:
        Result = AKOS_KEYCODE_PAGEDOWN;
        break;
        
        case VK_CAPITAL:
        Result = AKOS_KEYCODE_CAPSLOCK;
        break;
        
        case VK_NUMLOCK:
        Result = AKOS_KEYCODE_NUMLOCK;
        break;
        
        case VK_SCROLL:
        Result = AKOS_KEYCODE_SCROLLLOCK;
        break;
        
        case VK_SHIFT:
        Result = AKOS_KEYCODE_SHIFT;
        break;
        
        case VK_CONTROL:
        Result = AKOS_KEYCODE_CONTROL;
        break;
        
        case VK_MENU:
        Result = AKOS_KEYCODE_ALT;
        break;
        
        case VK_LSHIFT:
        Result = AKOS_KEYCODE_LSHIFT;
        break;
        
        case VK_LCONTROL:
        Result = AKOS_KEYCODE_LCONTROL;
        break;
        
        case VK_LMENU:
        Result = AKOS_KEYCODE_LALT;
        break;
        
        case VK_LWIN:
        Result = AKOS_KEYCODE_LSUPER;
        break;
        
        case VK_RSHIFT:
        Result = AKOS_KEYCODE_RSHIFT;
        break;
        
        case VK_RCONTROL:
        Result = AKOS_KEYCODE_RCONTROL;
        break;
        
        case VK_RMENU:
        Result = AKOS_KEYCODE_RALT;
        break;
        
        case VK_RWIN:
        Result = AKOS_KEYCODE_RSUPER;
        break;
        
        case VK_SNAPSHOT:
        Result = AKOS_KEYCODE_PRINTSCREEN;
        break;
        
        case VK_APPS:
        Result = AKOS_KEYCODE_MENU;
        break;
        
        //NOTE(EVERYONE): We skip AKOS_KEYCODE_COMMAND
        
        case VK_F1:
        Result = AKOS_KEYCODE_F1;
        break;
        
        case VK_F2:
        Result = AKOS_KEYCODE_F2;
        break;
        
        case VK_F3:
        Result = AKOS_KEYCODE_F3;
        break;
        
        case VK_F4:
        Result = AKOS_KEYCODE_F4;
        break;
        
        case VK_F5:
        Result = AKOS_KEYCODE_F5;
        break;
        
        case VK_F6:
        Result = AKOS_KEYCODE_F6;
        break;
        
        case VK_F7:
        Result = AKOS_KEYCODE_F7;
        break;
        
        case VK_F8:
        Result = AKOS_KEYCODE_F8;
        break;
        
        case VK_F9:
        Result = AKOS_KEYCODE_F9;
        break;
        
        case VK_F10:
        Result = AKOS_KEYCODE_F10;
        break;
        
        case VK_F11:
        Result = AKOS_KEYCODE_F11;
        break;
        
        case VK_F12:
        Result = AKOS_KEYCODE_F12;
        break;
        
        case VK_F13:
        Result = AKOS_KEYCODE_F13;
        break;
        
        case VK_F14:
        Result = AKOS_KEYCODE_F14;
        break;
        
        case VK_F15:
        Result = AKOS_KEYCODE_F15;
        break;
        
        case VK_F16:
        Result = AKOS_KEYCODE_F16;
        break;
        
        case VK_F17:
        Result = AKOS_KEYCODE_F17;
        break;
        
        case VK_F18:
        Result = AKOS_KEYCODE_F18;
        break;
        
        case VK_F19:
        Result = AKOS_KEYCODE_F19;
        break;
        
        case VK_F20:
        Result = AKOS_KEYCODE_F20;
        break;
        
        case VK_F21:
        Result = AKOS_KEYCODE_F21;
        break;
        
        case VK_F22:
        Result = AKOS_KEYCODE_F22;
        break;
        
        case VK_F23:
        Result = AKOS_KEYCODE_F23;
        break;
        
        case VK_F24:
        Result = AKOS_KEYCODE_F24;
        break;
        
        case VK_NUMPAD0:
        Result = AKOS_KEYCODE_NUMPAD0;
        break;
        
        case VK_NUMPAD1:
        Result = AKOS_KEYCODE_NUMPAD1;
        break;
        
        case VK_NUMPAD2:
        Result = AKOS_KEYCODE_NUMPAD2;
        break;
        
        case VK_NUMPAD3:
        Result = AKOS_KEYCODE_NUMPAD3;
        break;
        
        case VK_NUMPAD4:
        Result = AKOS_KEYCODE_NUMPAD4;
        break;
        
        case VK_NUMPAD5:
        Result = AKOS_KEYCODE_NUMPAD5;
        break;
        
        case VK_NUMPAD6:
        Result = AKOS_KEYCODE_NUMPAD6;
        break;
        
        case VK_NUMPAD7:
        Result = AKOS_KEYCODE_NUMPAD7;
        break;
        
        case VK_NUMPAD8:
        Result = AKOS_KEYCODE_NUMPAD8;
        break;
        
        case VK_NUMPAD9:
        Result = AKOS_KEYCODE_NUMPAD9;
        break;
        
        case VK_MULTIPLY:
        Result = AKOS_KEYCODE_NUMPADSTAR;
        break;
        
        case VK_ADD:
        Result = AKOS_KEYCODE_NUMPADPLUS;
        break;
        
        case VK_SUBTRACT:
        Result = AKOS_KEYCODE_NUMPADMINUS;
        break;
        
        case VK_DECIMAL:
        Result = AKOS_KEYCODE_NUMPADDOT;
        break;
        
        case VK_DIVIDE:
        Result = AKOS_KEYCODE_NUMPADSLASH;
        break;
    }
    
    return Result;
}

static akos_u32 AKOS__Win32_Get_Modifiers()
{
    akos_u32 Result = 0;
    akos__user32* User32 = &AKOS_Get_Context()->User32;
    
    if(User32->GetAsyncKeyState(VK_MENU) & 0x8000)
        Result |= AKOS_MODIFIER_ALT;
    
    if(User32->GetAsyncKeyState(VK_SHIFT) & 0x8000)
        Result |= AKOS_MODIFIER_SHIFT;
    
    if(User32->GetAsyncKeyState(VK_CONTROL) & 0x8000)
        Result |= AKOS_MODIFIER_CONTROL;
    
    return Result;
}

AK_OS_DEF akos_event_list AKOS_Poll_Events()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context)
    {
        //TODO(JJ): Diagnostic and error logging
        akos_event_list Empty;
        AKOS__Memory_Clear(&Empty, sizeof(akos_event_list));
        return Empty;
    }
    
    akos__user32* User32 = &Context->User32;
    
    MSG Message;
    while(User32->PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
    {
        akos_b32 Translate = akos_false;
        
        switch(Message.message)
        {
            case WM_QUIT:
            {
                //TODO(JJ): Delete context resources here
            } break;
            
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            {
                if((Message.lParam & (1 << 30)) == 0)
                {
                    akos_event Event = {};
                    Event.Type = AKOS_EVENT_TYPE_KEY_PRESSED;
                    Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                    Event.KeyPressed.KeyCode = AKOS__VK_To_AKOS((DWORD)Message.wParam);
                    Event.KeyPressed.Modifiers = AKOS__Win32_Get_Modifiers();
                    Event.KeyPressed.ScanCode = (akos_u32)LOBYTE(HIWORD(Message.lParam));
                    
                    AKOS__Add_Event(&Context->EventManager, &Event);
                }
                Translate = akos_true;
            } break;
            
            case WM_KEYUP:
            case WM_SYSKEYUP:
            {
                akos_event Event = {};
                Event.Type = AKOS_EVENT_TYPE_KEY_RELEASED;
                Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                Event.KeyReleased.KeyCode = AKOS__VK_To_AKOS((DWORD)Message.wParam);
                Event.KeyReleased.Modifiers = AKOS__Win32_Get_Modifiers();
                Event.KeyReleased.ScanCode = (akos_u32)LOBYTE(HIWORD(Message.lParam));
                AKOS__Add_Event(&Context->EventManager, &Event);
                
                Translate = akos_true;
            } break;
            
            case WM_MOUSEMOVE:
            {
                akos_event Event = {};
                Event.Type = AKOS_EVENT_TYPE_MOUSE_MOVED;
                Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                Event.MouseMoved.MouseX = AKOS__GET_X_LPARAM(Message.lParam);
                Event.MouseMoved.MouseY = AKOS__GET_Y_LPARAM(Message.lParam);
                AKOS__Add_Event(&Context->EventManager, &Event);
            } break;
            
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            {
                akos_event Event = {};
                Event.Type = AKOS_EVENT_TYPE_MOUSE_PRESSED;
                Event.MousePressed.MouseCode = AKOS__Mouse_Event_To_AKOS(Message.message);
                Event.MousePressed.Modifiers = AKOS__Win32_Get_Modifiers();
                Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                AKOS__Add_Event(&Context->EventManager, &Event);
            } break;
            
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            {
                akos_event Event = {};
                Event.Type = AKOS_EVENT_TYPE_MOUSE_RELEASED;
                Event.MousePressed.MouseCode = AKOS__Mouse_Event_To_AKOS(Message.message);
                Event.MousePressed.Modifiers = AKOS__Win32_Get_Modifiers();
                Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                AKOS__Add_Event(&Context->EventManager, &Event);
            } break;
            
            case WM_MOUSEWHEEL:
            {
                akos_event Event = {};
                Event.Type = AKOS_EVENT_TYPE_MOUSE_SCROLLED;
                Event.MouseScroll.Scroll = (float)GET_WHEEL_DELTA_WPARAM(Message.wParam) / (float)WHEEL_DELTA;
                Event.Window = AKOS__Win32_Get_Handle_From_HWND(Message.hwnd);
                AKOS__Add_Event(&Context->EventManager, &Event);
            } break;
            
            default:
            {
                Translate = akos_true;
            } break;
        }
        
        if(Translate)
        {
            User32->TranslateMessage(&Message);
            User32->DispatchMessage(&Message);
        }
    }
    akos_event_list EventList = AKOS__Get_Event_List(&Context->EventManager);
    return EventList;
}

AK_OS_DEF const char* AKOS_Get_Clipboard_Text()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    akos__user32* User32 = &Context->User32;
    if(!User32->OpenClipboard(NULL))
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    HANDLE Handle = User32->GetClipboardData(CF_TEXT);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        User32->CloseClipboard();
        return NULL;
    }
    
    char* Text = (char*)GlobalLock(Handle);
    if(!Text)
    {
        //TODO(JJ): Diagnostic and error logging
        User32->CloseClipboard();
        return NULL;
    }
    
    akos__clipboard* Clipboard = &Context->Clipboard;
    akos_u64 TextLength = AKOS__String_Length(Text);
    if(TextLength > Clipboard->TextLength)
    {
        akos_u64 AllocationSize = (TextLength > (Clipboard->TextLength*2)) ? TextLength : Clipboard->TextLength*2;
        char* Str = (char*)AKOS__Malloc(AllocationSize);
        if(!Str)
        {
            //TODO(JJ): Diagnostic and error logging
            GlobalUnlock(Handle);
            User32->CloseClipboard();
            return NULL;
        }
        
        if(Clipboard->Str)
            AKOS__Free(Clipboard->Str);
        
        Clipboard->Str = Str;
        Clipboard->TextLength = AllocationSize;
    }
    
    AKOS__Memory_Copy(Clipboard->Str, Text, TextLength);
    Clipboard->Str[TextLength] = 0;
    
    GlobalUnlock(Handle);
    User32->CloseClipboard();
    
    return Clipboard->Str;
}

AK_OS_DEF void AKOS_Set_Clipboard_Text(const char* Text)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    if(!User32->OpenClipboard(NULL))
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    if(!User32->EmptyClipboard())
    {
        //TODO(JJ): Diagnostic and error logging
        User32->CloseClipboard();
        return;
    }
    
    akos_u64 TextLength = AKOS__String_Length(Text);
    HGLOBAL Handle = GlobalAlloc(GMEM_MOVEABLE, (TextLength+1)*sizeof(char));
    if(!Handle)
    {
        //TODO(JJ): diagnostic and error logging
        User32->CloseClipboard();
        return;
    }
    
    char* DstText = (char*)GlobalLock(Handle);
    if(!DstText)
    {
        //TODO(JJ): Diagnostic and error logging
        GlobalFree(Handle);
        User32->CloseClipboard();
        return;
    }
    
    AKOS__Memory_Copy(DstText, Text, TextLength*sizeof(char));
    DstText[TextLength] = 0;
    
    GlobalUnlock(Handle);
    
    User32->SetClipboardData(CF_TEXT, Handle);
    User32->CloseClipboard();
}

AK_OS_DEF akos_handle AKOS_Create_Window(const akos_window_create_info* WindowCreateInfo)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Handle = AKOS__Pool_Allocate(&Context->Windows);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__user32* User32 = &Context->User32;
    
    DWORD Style = WS_OVERLAPPEDWINDOW|WS_VISIBLE;
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, Handle);
    RECT WindowRect = {0, 0, (LONG)WindowCreateInfo->Width, (LONG)WindowCreateInfo->Height};
    User32->AdjustWindowRectEx(&WindowRect, Style, FALSE, 0);
    
    akos_u16 WindowIndex = (akos_u16)Handle;
    Window->HWND = User32->CreateWindowExA(0, AKOS__WINDOW_CLASS_NAME, WindowCreateInfo->Title, Style, CW_USEDEFAULT, CW_USEDEFAULT, 
                                           WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, 
                                           NULL, NULL, GetModuleHandle(0), (void*)(size_t)(WindowIndex));
    if(!Window->HWND)
    {
        //TODO(JJ): Diagnostic and error logging
        goto error;
    }
    
    return Handle;
    
    error:
    AKOS_Delete_Window(Handle);
    return 0;
}

AK_OS_DEF void AKOS_Delete_Window(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, Handle);
    if(Window)
    {
        User32->DestroyWindow(Window->HWND);
        AKOS__Pool_Free(&Context->Windows, Handle);
    }
}

AK_OS_DEF void* AKOS_Window_Get_Platform_Data(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, Handle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    return Window->HWND;
}

AK_OS_DEF void AKOS_Show_Window(akos_handle WindowHandle, int IsFocused)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window)
    {
        akos__user32* User32 = &Context->User32;
        USHORT Focused = IsFocused ? SW_SHOW : SW_SHOWNA;
        User32->ShowWindow(Window->HWND, Focused);
    }
}

AK_OS_DEF void AKOS_Set_Window_Pos(akos_handle WindowHandle, akos_i32 PosX, akos_i32 PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window)
    {
        akos__user32* User32 = &Context->User32;
        RECT Rect = {(LONG)PosX, (LONG)PosY, (LONG)PosX, (LONG)PosY};
        User32->AdjustWindowRectEx(&Rect, Window->Style, FALSE, Window->ExStyle);
        User32->SetWindowPos(Window->HWND, NULL, Rect.left, Rect.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
    }
}

AK_OS_DEF void AKOS_Get_Window_Pos(akos_handle WindowHandle, akos_i32* PosX, akos_i32* PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window)
    {
        akos__user32* User32 = &Context->User32;
        POINT Pos = {0, 0};
        User32->ClientToScreen(Window->HWND, &Pos);
        if(PosX) *PosX = Pos.x;
        if(PosY) *PosY = Pos.y;
    }
}

AK_OS_DEF void AKOS_Set_Window_Dim(akos_handle WindowHandle, akos_i32 Width, akos_i32 Height)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window)
    {
        akos__user32* User32 = &Context->User32;
        RECT Rect = {0, 0, (LONG)Width, (LONG)Height};
        User32->AdjustWindowRectEx(&Rect, Window->Style, FALSE, Window->ExStyle);
        User32->SetWindowPos(Window->HWND, NULL, 0, 0, Rect.right-Rect.left, Rect.bottom-Rect.top, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
    }
}

AK_OS_DEF void AKOS_Get_Window_Dim(akos_handle WindowHandle, akos_i32* Width, akos_i32* Height)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window)
    {
        akos__user32* User32 = &Context->User32;
        RECT ClientRect = {0, 0, 0, 0};
        User32->GetClientRect(Window->HWND, &ClientRect);
        if(Width) *Width = ClientRect.right-ClientRect.left;
        if(Height) *Height = ClientRect.bottom-ClientRect.top;
    }
}

AK_OS_DEF void AKOS_Set_Window_User_Data(akos_handle WindowHandle, akos_u64 UserData)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window) Window->UserData = UserData;
}

AK_OS_DEF akos_u64 AKOS_Get_Window_User_Data(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(Window) return Window->UserData;
    return 0;
}

AK_OS_DEF int AKOS_Is_Window_Focused(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    return Context->User32.GetForegroundWindow() == Window->HWND;
}

AK_OS_DEF void AKOS_Focus_Window(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    User32->BringWindowToTop(Window->HWND);
    User32->SetForegroundWindow(Window->HWND);
    User32->SetFocus(Window->HWND);
}

AK_OS_DEF int AKOS_Is_Window_Minimized(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    return Context->User32.IsIconic(Window->HWND) != 0;
}

AK_OS_DEF akos_handle AKOS_Get_Focused_Window()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__user32* User32 = &Context->User32;
    
    HWND Window = User32->GetForegroundWindow();
    if(Window)
    {
        DWORD ProcessID = GetCurrentProcessId();
        DWORD WindowProcessID;
        User32->GetWindowThreadProcessId(Window, &WindowProcessID);
        if(WindowProcessID == ProcessID)
            return AKOS__Win32_Get_Handle_From_HWND(Window);
    }
    return 0;
}

AK_OS_DEF void AKOS_Get_Cursor_Pos(akos_i32* PosX, akos_i32* PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    
    POINT Point;
    User32->GetCursorPos(&Point);
    if(PosX) *PosX = Point.x;
    if(PosY) *PosY = Point.y;
}

AK_OS_DEF void AKOS_Get_Window_Cursor_Pos(akos_handle WindowHandle, akos_i32* PosX, akos_i32* PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    POINT Point;
    if(User32->GetCursorPos(&Point) && User32->ScreenToClient(Window->HWND, &Point))
    {
        if(PosX) *PosX = Point.x;
        if(PosY) *PosY = Point.y;
    }
}

AK_OS_DEF void AKOS_Set_Cursor_Pos(akos_i32 PosX, akos_i32 PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    User32->SetCursorPos(PosX, PosY);
}

AK_OS_DEF void AKOS_Set_Window_Cursor_Pos(akos_handle WindowHandle, akos_i32 PosX, akos_i32 PosY)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    POINT Point = {PosX, PosY};
    if(User32->ClientToScreen(Window->HWND, &Point))
        User32->SetCursorPos(Point.x, Point.y);
}

AK_OS_DEF void AKOS_Set_Mouse_Capture(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    akos__user32* User32 = &Context->User32;
    
    if(WindowHandle)
    {
        akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
        if(!Window)
        {
            //TODO(JJ): Diangostic and error logging
            return;
        }
        
        User32->SetCapture(Window->HWND);
    }
    else
    {
        User32->ReleaseCapture();
    }
}

AK_OS_DEF akos_handle AKOS_Get_Mouse_Capture()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    akos__user32* User32 = &Context->User32;
    return AKOS__Win32_Get_Handle_From_HWND(User32->GetCapture());
}

AK_OS_DEF int AKOS_GL_Make_Current(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return akos_false;
    }
    
    if(Window->DeviceContext && Window->RenderContext)
    {
        akos__opengl32* OpenGL32 = &Context->OpenGL32;
        if(!OpenGL32->wglMakeCurrent(Window->DeviceContext, Window->RenderContext))
            return akos_false;
    }
    else
    {
        akos__user32* User32 = &Context->User32;
        HDC DeviceContext = User32->GetDC(Window->HWND);
        if(!DeviceContext)
        {
            //TODO(JJ): Diagnostic and error logging
            return akos_false;
        }
        
        int AttribList[] = 
        {
            AKOS__WGL_DRAW_TO_WINDOW_ARB, akos_true,
            AKOS__WGL_ACCELERATION_ARB, AKOS__WGL_FULL_ACCELERATION_ARB,
            AKOS__WGL_SUPPORT_OPENGL_ARB, akos_true, 
            AKOS__WGL_DOUBLE_BUFFER_ARB, akos_true,
            AKOS__WGL_PIXEL_TYPE_ARB, AKOS__WGL_TYPE_RGBA_ARB,
            AKOS__WGL_COLOR_BITS_ARB, 32, 
            0
        };
        
        int TargetPixelFormatIndex;
        
        akos__gdi32* GDI32 = &Context->GDI32;
        akos__wgl* WGL = &Context->WGL;
        akos__opengl32* OpenGL32 = &Context->OpenGL32;
        
        UINT NumberOfFormats;
        if(!WGL->wglChoosePixelFormatARB(DeviceContext, AttribList, 0, 1, &TargetPixelFormatIndex, &NumberOfFormats))
        {
            //TODO(JJ): Diagnostic and error logging
            User32->ReleaseDC(Window->HWND, DeviceContext);
            return akos_false;
        }
        
        PIXELFORMATDESCRIPTOR PixelFormat = {};
        if(!GDI32->DescribePixelFormat(DeviceContext, TargetPixelFormatIndex, sizeof(PixelFormat), &PixelFormat))
        {
            //TODO(JJ): Diagnostic and error logging
            User32->ReleaseDC(Window->HWND, DeviceContext);
            return akos_false;
        }
        
        if(!GDI32->SetPixelFormat(DeviceContext, TargetPixelFormatIndex, &PixelFormat))
        {
            //TODO(JJ): Diagnostic and error logging
            User32->ReleaseDC(Window->HWND, DeviceContext);
            return akos_false;
        }
        
        HGLRC RenderContext = WGL->wglCreateContextAttribsARB(DeviceContext, NULL, Context->WGLAttributes);
        if(!RenderContext)
        {
            //TODO(JJ): Diagnostic and error logging
            User32->ReleaseDC(Window->HWND, DeviceContext);
            return akos_false;
        }
        
        if(!OpenGL32->wglMakeCurrent(DeviceContext, RenderContext))
        {
            //TODO(JJ): Diagnostic and error logging
            User32->ReleaseDC(Window->HWND, DeviceContext);
            OpenGL32->wglDeleteContext(RenderContext);
            return akos_false;
        }
        
        Window->DeviceContext = DeviceContext;
        Window->RenderContext = RenderContext;
    }
    
    return akos_true;
}

AK_OS_DEF void AKOS_GL_Set_Swap_Interval(int SwapInterval)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    if(Context->WGL.wglSwapIntervalEXT) Context->WGL.wglSwapIntervalEXT(SwapInterval);
}

AK_OS_DEF void AKOS_GL_Swap_Buffers(akos_handle WindowHandle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    if(Window->DeviceContext)
    {
        akos__gdi32* GDI32 = &Context->GDI32;
        GDI32->SwapBuffers(Window->DeviceContext);
    }
}

AK_OS_DEF akos_handle AKOS_Create_Cursor(akos_u32 SystemCode)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__user32* User32 = &Context->User32;
    
    LPCSTR Str = NULL;
    switch(SystemCode)
    {
        case AKOS_CURSOR_ARROW:
        Str = IDC_ARROW;
        break;
        
        case AKOS_CURSOR_IBEAM:
        Str = IDC_IBEAM;
        break;
        
        case AKOS_CURSOR_SIZEALL:
        Str = IDC_SIZEALL;
        break;
        
        case AKOS_CURSOR_SIZENS:
        Str = IDC_SIZENS;
        break;
        
        case AKOS_CURSOR_SIZEEW:
        Str = IDC_SIZEWE;
        break;
        
        case AKOS_CURSOR_SIZENESW:
        Str = IDC_SIZENESW;
        break;
        
        case AKOS_CURSOR_SIZENWSE:
        Str = IDC_SIZENWSE;
        break;
        
        case AKOS_CURSOR_HAND:
        Str = IDC_HAND;
        break;
        
        case AKOS_CURSOR_NO:
        Str = IDC_NO;
        break;
    }
    
    if(!Str) return 0;
    
    HCURSOR Handle = User32->LoadCursorA(NULL, Str);
    if(!Handle)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos_handle Result = AKOS__Pool_Allocate(&Context->Cursors);
    if(!Result)
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    akos__cursor* Cursor = (akos__cursor*)AKOS__Pool_Get(&Context->Cursors, Result);
    Cursor->Handle = Handle;
    return Result;
}

AK_OS_DEF void AKOS_Delete_Cursor(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__cursor* Cursor = (akos__cursor*)AKOS__Pool_Get(&Context->Cursors, Handle);
    if(Cursor)
    {
        akos__user32* User32 = &Context->User32;
        User32->DestroyCursor(Cursor->Handle);
        AKOS__Pool_Free(&Context->Cursors, Handle);
    }
}

AK_OS_DEF void AKOS_Set_Cursor(akos_handle Handle)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    akos__user32* User32 = &Context->User32;
    
    if(Handle)
    {
        akos__cursor* Cursor = (akos__cursor*)AKOS__Pool_Get(&Context->Cursors, Handle);
        if(!Cursor)
        {
            //TODO(JJ): Diagnostic and error logging
            return;
        }
        
        User32->SetCursor(Cursor->Handle);
        Context->SetCursorHandle = Handle;
    }
    else
    {
        User32->SetCursor(NULL);
        Context->SetCursorHandle = 0;
    }
    
}

AK_OS_DEF akos_handle AKOS_Get_Cursor()
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return 0;
    }
    
    if(Context->SetCursorHandle)
    {
        if(AKOS__Pool_Get(&Context->Cursors, Context->SetCursorHandle))
            return Context->SetCursorHandle;
        else
            Context->SetCursorHandle = 0;
    }
    
    return 0;
}

AK_OS_DEF void AKOS_Show_Cursor(int Show)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return;
    }
    
    Context->User32.ShowCursor(Show);
}

#ifdef AK_OS_VULKAN_HELPERS

AK_OS_DEF VkSurfaceKHR AKOS_Create_Vulkan_Surface(akos_handle WindowHandle, VkInstance Instance,
                                                  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddrAK, 
                                                  VkAllocationCallbacks* Callbacks)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    akos__window* Window = (akos__window*)AKOS__Pool_Get(&Context->Windows, WindowHandle);
    if(!Window)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddrAK(Instance, "vkCreateWin32SurfaceKHR");
    if(!vkCreateWin32SurfaceKHR)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo = {};
    SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    SurfaceCreateInfo.hinstance = GetModuleHandle(0);
    SurfaceCreateInfo.hwnd = Window->HWND;
    
    VkSurfaceKHR Surface;
    if(vkCreateWin32SurfaceKHR(Instance, &SurfaceCreateInfo, Callbacks, &Surface) != VK_SUCCESS)
    {
        //TODO(JJ): Diagnostic and error logging
        return NULL;
    }
    
    return Surface;
}

#endif //AK_OS_VULKAN_HELPERS

#endif //_WIN32

AK_OS_DEF void* AKOS_Allocate(size_t Size)
{
    void* Result = AKOS_Reserve(Size);
    if(!AKOS_Commit(Result, Size))
    {
        AKOS_Release(Result);
        return NULL;
    }
    return Result;
}

AK_OS_DEF void  AKOS_Free(void* Memory)
{
    if(Memory) AKOS_Release(Memory);
}

static akos_context* AKOS__Context;
AK_OS_DEF akos_context* AKOS_Get_Context() { return AKOS__Context; }
AK_OS_DEF void AKOS_Set_Context(akos_context* Context) { AKOS__Context = Context; }

AK_OS_DEF int AKOS_Write_Entire_File(const char* Filepath, void* Data, akos_u32 WriteSize)
{
    akos_handle Handle = AKOS_Create_File(Filepath, AKOS_FILE_FLAG_WRITE);
    if(!Handle)
    {
        //TODO(JJ): Read error from create file
        return akos_false;
    }
    
    int Result = AKOS_Write_File(Handle, Data, WriteSize, AKOS_INVALID_FILE_SIZE);
    if(!Result)
    {
        //TODO(JJ): Read error from write file
    }
    
    AKOS_Delete_File(Handle);
    return Result;
}

#endif //AK_OS_IMPLEMENTATION
