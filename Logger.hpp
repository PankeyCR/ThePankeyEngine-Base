/*
*	Parts of the General Logger:
*	
*	pankey_Log_set(LoggerMethod)			//Starts a method into the logger
*	pankey_Log_Split(Tittle)				//Separetes parts of the logger to adentify better a bug
*	pankey_Log_Start()						//Starts the logg
*	pankey_Log_Stop()						//Stops the logg
*	pankey_Log(status,name,method,mns)		//General logger, mns is a CharArray value
*	pankey_Logger(status,name,method,mns)	//General logger, mns is a template value
*	
*/

#ifndef Logger_hpp
	#define Logger_hpp

	#ifndef pankey_Log_set
		#define pankey_Log_set(S) 
	#endif 

	#ifndef pankey_Logger_set
		#define pankey_Log_set(S) 
	#endif 

	#ifndef pankey_Log_Split
		#define pankey_Log_Split(tittle) 
	#endif
	
	#ifndef pankey_Log_Start
		#define pankey_Log_Start() 
	#endif
	
	#ifndef pankey_Log_Stop
		#define pankey_Log_Stop() 
	#endif 

	#ifndef pankey_Log
		#define pankey_Log(status,name,method,mns) 
	#endif

	#ifndef pankey_Trigger_Log
		#define pankey_Trigger_Log(trigger,status,name,method,mns) 
	#endif

	#ifndef pankey_Logger
		#define pankey_Logger(status,name,method,mns) 
	#endif

	#ifndef pankey_Trigger_Logger
		#define pankey_Trigger_Logger(trigger,status,name,method,mns) 
	#endif

	#ifndef pankey_Log_enable
		#define pankey_Log_enable(status,name,method,mns) false
	#endif

#endif 

