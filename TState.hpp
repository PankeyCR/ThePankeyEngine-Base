
#ifndef TState_hpp
	#define TState_hpp

	#include "State.hpp"

	#if defined(TState_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define TStateLog(status,method,mns) pankey_Log(status,"TState",method,mns)
	#else
		#define TStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class TState : public Type{
				public:
					TState(){}
					TState(const TState&) = delete;

					TState(TState&& a_TState){
						m_context = a_TState.m_context;
						m_initialize = a_TState.m_initialize;
						m_update = a_TState.m_update;
						a_TState.m_context = nullptr;
						a_TState.m_initialize = nullptr;
						a_TState.m_update = nullptr;
					}

					TState(void* a_context, InvokeMethod<void*> a_initialize, InvokeMethod<void*,Args...> a_update){
						m_context = a_context;
						m_initialize = a_initialize;
						m_update = a_update;
					}

					void operator=(const TState<Args...>&) = delete;
					void operator=(const TState<Args...>&&) = delete;

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

				protected:
					void* m_context = nullptr;
					InvokeMethod<void*> m_initialize = nullptr;
					InvokeMethod<void*,Args...> m_update = nullptr;
			};

		}

	}

#endif
