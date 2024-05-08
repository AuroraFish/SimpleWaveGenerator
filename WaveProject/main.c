#include "Task.h"

void main()
{
    Task_Init();
	while(1)
	{
		Task_Key_Handle();
        Task_Display();            
	}
}
