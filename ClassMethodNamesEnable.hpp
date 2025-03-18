
#ifndef ClassMethodNamesEnable_hpp
	#define ClassMethodNamesEnable_hpp

	#include "Logger_status.hpp"
	#include "InvokeMethod.hpp"
	#include "InvokeRawList.hpp"
	#include "ArrayRawMap.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		namespace Base{

			ArrayRawMap<CharArray,ArrayRawList<CharArray>> g_classmethodnamesenable_map;
		
			template<class L>
			bool ClassMethodNamesEnable(int a_status, const CharArray& a_name, const CharArray& a_method, L a_log){Serial.println("calasdfasdfadfasdfasdfasdfasdfadsfasdf");
				for(auto entry :  g_classmethodnamesenable_map){
				  CharArray f_key = entry.getKey();
				  if(f_key != a_name){
					continue;
				  }
				  ArrayRawList<CharArray> f_value = entry.getValue();
				  if(f_value.contain(a_method)){
					return true;
				  }
				}
				return false;
			}

			template<class... Args>
			void pankey_Log_Class_Method(CharArray a_class, Args... a_methods){
				ArrayRawList<CharArray> i_methods;
				i_methods.addPack(a_methods...);
				g_classmethodnamesenable_map.put(a_class,i_methods);
			}

		}

	}

	#ifndef pankey_Log_enable
		#define pankey_Log_enable(status,name,method,mns) pankey::Base::ClassMethodNamesEnable(status,name,method,mns)
	#endif

#endif 

