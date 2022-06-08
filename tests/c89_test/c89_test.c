#include "../../ak_os.h"

int main()
{
    akos_context* OSContext = AKOS_Create_Context();
    if(!OSContext) return -1;
    
    akos_window_create_info WindowCreateInfo = {0};
    WindowCreateInfo.Width = 1920;
    WindowCreateInfo.Height = 1080;
    WindowCreateInfo.Title = "c89_test";
    
    akos_handle MainWindow = AKOS_Create_Window(&WindowCreateInfo);
    if(!MainWindow) return -1;
    
    
    akos_b32 Running = akos_true;
    while(Running)
    {
        akos_event_list EventList = AKOS_Poll_Events();
        
        akos_u64 EventIndex;
        for(EventIndex = 0; EventIndex < EventList.Count; EventIndex++)
        {
            const akos_event* Event = EventList.Events + EventIndex;
            switch(Event->Type)
            {
                case AKOS_EVENT_TYPE_WINDOW_CLOSED:
                {
                    if(Event->Window == MainWindow)
                        Running = akos_false;
                    AKOS_Delete_Window(Event->Window);
                } break;
            }
        }
    }
    
    AKOS_Delete_Context(OSContext);
    return 0;
}

#define AK_OS_IMPLEMENTATION
#include "../../ak_os.h"  