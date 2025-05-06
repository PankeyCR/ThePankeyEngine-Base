
#ifndef State_hpp
	#define State_hpp

	#include "Type.hpp"
	#include "InvokeMethod.hpp"

	#if defined(State_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define StateLog(status,method,mns) pankey_Log(status,"State",method,mns)
	#else
		#define StateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class State : public Type{
				public:
					State(){}
					State(const State&) = delete;

					State(State&& a_state){
						m_context = a_state.m_context;
						m_initialize = a_state.m_initialize;
						m_update = a_state.m_update;
						a_state.m_context = nullptr;
						a_state.m_initialize = nullptr;
						a_state.m_update = nullptr;
					}

					State(void* a_context, InvokeMethod<void*> a_initialize, InvokeMethod<void*,Args...> a_update){
						m_context = a_context;
						m_initialize = a_initialize;
						m_update = a_update;
					}

					void operator=(const State<Args...>&) = delete;
					void operator=(const State<Args...>&&) = delete;

					void initialize(){
						if(m_context == nullptr){
							return;
						}
						invoke<void*>(m_initialize, m_context);
					}

					void update(Args... a_args){
						if(m_context == nullptr){
							return;
						}
						invoke<void*,Args...>(m_update, m_context, a_args...);
					}

					virtual long getType()const{
						StateLog(pankey_Log_StartMethod, "getType", "");
						StateLog(pankey_Log_EndMethod, "getType", "");
						return ClassCount<State<Args...>>::get();
					}

					virtual bool istype(long a_type)const{
						StateLog(pankey_Log_StartMethod, "istypeof", "");
						StateLog(pankey_Log_EndMethod, "istypeof", "");
						return ClassCount<State<Args...>>::get() == a_type;
					}

				protected:
					void* m_context = nullptr;
					InvokeMethod<void*> m_initialize = nullptr;
					InvokeMethod<void*,Args...> m_update = nullptr;
			};

		}

	}

#endif
