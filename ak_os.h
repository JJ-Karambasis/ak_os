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
    AKOS_EVENT_TYPE_WINDOW_CLOSED
};

enum 
{
    AKOS_FILE_FLAG_READ  = (1 << 0),
    AKOS_FILE_FLAG_WRITE = (1 << 1)
};

typedef struct akos_context akos_context;
typedef akos_u64 akos_handle;
typedef int32_t akos_thread_callback(void* UserData);
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
} akos_event;

typedef struct akos_event_list
{
    akos_u64          Count;
    const akos_event* Events;
} akos_event_list;

AK_OS_DEF void* AKOS_Reserve(size_t Size);
AK_OS_DEF bool  AKOS_Commit(void* Memory, size_t Size);
AK_OS_DEF void  AKOS_Decommit(void* Memory, size_t Size);
AK_OS_DEF void  AKOS_Release(void* Memory);

AK_OS_DEF void* AKOS_Allocate(size_t Size);
AK_OS_DEF void  AKOS_Free(void* Memory);

AK_OS_DEF uint32_t AKOS_Get_Current_Thread_ID();

AK_OS_DEF bool AKOS_Directory_Exists(const char* Directory);
AK_OS_DEF bool AKOS_Create_Directory(const char* Directory);

AK_OS_DEF akos_context* AKOS_Create_Context();
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
AK_OS_DEF void AKOS_Timer_Set(akos_handle Handle, uint64_t Ticks, akos_timer_callback* TimerCallback, void* UserData);
AK_OS_DEF void AKOS_Timer_Wait(akos_handle Handle);

AK_OS_DEF akos_handle AKOS_Create_File(const char* Filepath, akos_u64 Flags);
AK_OS_DEF akos_u64 AKOS_Get_File_Size(akos_handle Handle);
AK_OS_DEF bool AKOS_Read_File( akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset);
AK_OS_DEF bool AKOS_Write_File(akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset);
AK_OS_DEF void AKOS_Delete_File(akos_handle Handle);

AK_OS_DEF bool AKOS_Write_Entire_File(const char* Filepath, void* Data, akos_u32 WriteSize);

AK_OS_DEF akos_event_list AKOS_Poll_Events();

AK_OS_DEF akos_handle AKOS_Create_Window(const akos_window_create_info* WindowCreateInfo);
AK_OS_DEF void AKOS_Delete_Window(akos_handle WindowHandle);
AK_OS_DEF void* AKOS_Window_Get_Platform_Data(akos_handle WindowHandle);

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
} akos__user32;

typedef struct akos__window
{
    HWND HWND;
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

typedef struct akos_context
{
    akos__arena PermanentStorage;
    akos__arena TransientStorage;
    akos__user32 User32;
    
    akos__pool Windows;
    akos__pool Threads;
    akos__pool Mutexes;
    akos__pool Files;
    akos__pool Events;
    akos__pool Timers;
    
    akos__event_manager EventManager;
} akos_context;

AK_OS_DEF void* AKOS_Reserve(size_t Size)
{
    void* Result = VirtualAlloc(0, Size, MEM_RESERVE, PAGE_READWRITE);
    return Result;
}

AK_OS_DEF bool  AKOS_Commit(void* Memory, size_t Size)
{
    bool Result = VirtualAlloc(Memory, Size, MEM_COMMIT, PAGE_READWRITE) != NULL;
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

AK_OS_DEF uint32_t AKOS_Get_Current_Thread_ID()
{
    return GetCurrentThreadId();
}

AK_OS_DEF bool AKOS_Directory_Exists(const char* Directory)
{
    DWORD Attrib = GetFileAttributes(Directory);
    return (Attrib != INVALID_FILE_ATTRIBUTES && Attrib & FILE_ATTRIBUTE_DIRECTORY);
}

AK_OS_DEF bool AKOS_Create_Directory(const char* Directory)
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

AK_OS_DEF akos_context* AKOS_Create_Context()
{
    akos__arena ContextArena = AKOS__Create_Arena(1024*1024);
    akos_context* Context = AKOS__Push_Struct(&ContextArena, akos_context);
    if(!Context)
    {
        //TODO(JJ): Diagnostic and error logging
        AKOS__Delete_Arena(&ContextArena);
        return NULL;
    }
    
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
    
    AKOS_Set_Context(Context);
    return Context;
    
    error:
    AKOS_Delete_Context(Context);
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

AK_OS_DEF void AKOS_Timer_Set(akos_handle Handle, uint64_t TicksToWait, akos_timer_callback* TimerCallback, void* UserData)
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
        uint64_t TicksPerHundredSecond = AKOS_Performance_Frequency()/10000000;
        
        akos_u16 TimerIndex = (akos_u16)Handle;
        
        LARGE_INTEGER TimerValue;
        TimerValue.QuadPart = -((int64_t)TicksToWait/(int64_t)TicksPerHundredSecond);
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
    
    int32_t ReadAndWrite = Flags == (AKOS_FILE_FLAG_READ|AKOS_FILE_FLAG_WRITE);
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

AK_OS_DEF bool AKOS_Read_File(akos_handle Handle,  void* Data, akos_u32 DataSize, akos_u64 Offset)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(!File)
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    if(!(File->Flags & AKOS_FILE_FLAG_READ))
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
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
        return false;
    }
    
    if(BytesRead != DataSize)
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    return true;
}

AK_OS_DEF bool AKOS_Write_File(akos_handle Handle, void* Data, akos_u32 DataSize, akos_u64 Offset)
{
    akos_context* Context = AKOS_Get_Context();
    if(!Context) 
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    akos__file* File = (akos__file*)AKOS__Pool_Get(&Context->Files, Handle);
    if(!File)
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    if(!(File->Flags & AKOS_FILE_FLAG_WRITE))
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
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
        return false;
    }
    
    if(BytesWritten != DataSize)
    {
        //TODO(JJ): Diagnostic and error logging
        return false;
    }
    
    return true;
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
        switch(Message.message)
        {
            case WM_QUIT:
            {
                //TODO(JJ): Delete context resources here
                int x = 0;
            } break;
            
            default:
            {
                User32->TranslateMessage(&Message);
                User32->DispatchMessage(&Message);
            } break;
        }
    }
    
    akos_event_list EventList = AKOS__Get_Event_List(&Context->EventManager);
    return EventList;
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

AK_OS_DEF bool AKOS_Write_Entire_File(const char* Filepath, void* Data, akos_u32 WriteSize)
{
    akos_handle Handle = AKOS_Create_File(Filepath, AKOS_FILE_FLAG_WRITE);
    if(!Handle)
    {
        //TODO(JJ): Read error from create file
        return false;
    }
    
    bool Result = AKOS_Write_File(Handle, Data, WriteSize, AKOS_INVALID_FILE_SIZE);
    if(!Result)
    {
        //TODO(JJ): Read error from write file
    }
    
    AKOS_Delete_File(Handle);
    return Result;
}

#endif //AK_OS_IMPLEMENTATION
