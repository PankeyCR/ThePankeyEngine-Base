
#ifndef IntervalAppState_hpp
	#define IntervalAppState_hpp

	#include "BaseIAppState.hpp"
	#include "InvokeRawList.hpp"

	#if defined(pankey_Log) && (defined(IntervalAppState_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define IntervalAppStateLog(status,method,mns) pankey_Log(status,"IntervalAppState",method,mns)
	#else
		#define IntervalAppStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class A>
			class IntervalAppState : public BaseIAppState<A,long>{
				public:
					IntervalAppState(){}
					IntervalAppState(long a_time_limit){m_time_limit = a_time_limit;}
					virtual ~IntervalAppState(){}

					void setInterval(long a_time_limit){m_time_limit = a_time_limit;}

					void add(InvokeFunction<A> a_function){
						m_app_list.add(a_function);
					}

					void add(InvokeFunction<> a_function){
						m_list.add(a_function);
					}
					
					virtual void updateState(A& a_app, long a_tpc){
						IntervalAppStateLog(pankey_Log_StartMethod, "initialize", "");
						m_time += a_tpc;
						IntervalAppStateLog(pankey_Log_Statement, "initialize", "time:");
						IntervalAppStateLog(pankey_Log_Statement, "initialize", m_time);
						if(m_time < m_time_limit){
							IntervalAppStateLog(pankey_Log_EndMethod, "initialize", "m_time < m_time_limit");
							return;
						}
						m_time = 0;
						IntervalAppStateLog(pankey_Log_Statement, "initialize", "invoking");
						invokeAll(m_app_list, a_app);
						invokeAll(m_list);
						IntervalAppStateLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual long getType()const{
						return ClassType<IntervalAppState<A>>::getId();
					}

					virtual bool istype(long a_type)const{
						return BaseIAppState<A,long>::istype(a_type) || ClassType<IntervalAppState<A>>::getId() == a_type;
					}

				protected:
					FunctionList<A> m_app_list;
					FunctionList<> m_list;
					long m_time = 0;
					long m_time_limit = 0;
			};

		}

	}

#endif
