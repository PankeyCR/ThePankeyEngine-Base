
#ifndef ArrayList_hpp
	#define ArrayList_hpp

	#include "ArrayRawList.hpp"

	#if defined(pankey_Log) && (defined(ArrayList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayListLog(status,method,mns) pankey_Log(status,"ArrayList",method,mns)
	#else
		#define ArrayListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class ArrayList : protected ArrayRawList<T>, public List<T>{
				public:
					ArrayList(){
						ArrayListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayList(const ArrayList<T>& a_list) : ArrayRawList<T>(a_list){
						ArrayListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayList(int c_size, bool c_own, bool c_reordering) : ArrayRawList<T>(c_size, c_own, c_reordering){
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