
#ifndef ErrorHandler_hpp
	#define ErrorHandler_hpp

	#ifndef pankey_ErrorHandler_set
		#define pankey_ErrorHandler_set(S) 
	#endif 

	#ifndef pankey_ErrorAlert_set
		#define pankey_ErrorAlert_set(S) 
	#endif 

	#ifndef pankey_Error_Handler
		#define pankey_Error_Handler(status,name,method,mns) false
	#endif

	#ifndef pankey_Trigger_Error_Handler
		#define pankey_Trigger_Error_Handler(a_trigger, status,name,method,mns) false
	#endif

	#ifndef pankey_Error_Handling
		#define pankey_Error_Handling(status,name,method,mns) false
	#endif

	#ifndef pankey_Trigger_Error_Handling
		#define pankey_Trigger_Error_Handling(a_trigger, status,name,method,mns) false
	#endif

	#ifndef pankey_Error_Alert
		#define pankey_Error_Alert(status,name,method,mns) 
	#endif 

	#ifndef pankey_Trigger_Error_Alert
		#define pankey_Trigger_Error_Alert(a_trigger, status,name,method,mns) 
	#endif 

	#ifndef pankey_Error_Alerting
		#define pankey_Error_Alerting(status,name,method,mns) 
	#endif 

	#ifndef pankey_Trigger_Error_Alerting
		#define pankey_Trigger_Error_Alerting(a_trigger, status,name,method,mns) 
	#endif 

	#ifndef pankey_Error_enable
		#define pankey_Error_enable(status,name,method,mns) false
	#endif

#endif