
#ifndef ArrayList_hpp
	#define ArrayList_hpp

	#include "ArrayRawPointerList.hpp"
	#include "List.hpp"

	#if defined(pankey_Log) && (defined(ArrayList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayListLog(status,method,mns) pankey_Log(status,"ArrayList",method,mns)
	#else
		#define ArrayListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class ArrayList : protected ArrayRawPointerList<T>, virtual public List<T>{
				public:

					using ArrayRawPointerList<T>::isEmpty;

					ArrayList(){
						ArrayListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~ArrayList(){
						ArrayListLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayListLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					
			};

		}

	}

#endif