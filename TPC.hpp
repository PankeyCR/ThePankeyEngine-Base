
#ifndef TPC_hpp
	#define TPC_hpp

	#if defined(pankey_Log) && (defined(TPC_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define TPCLog(status,method,mns) pankey_Log(status,"TPC",method,mns)
	#else
		#define TPCLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{
		
			class TPC{
				public:
					TPC(){}
					virtual ~TPC(){}
					
					virtual long tpc(){
						return m_tpc;
					}

					virtual void initialize(long a_time){
						this->m_init = true;
						this->m_prev = a_time;
						this->m_now = a_time;
						this->m_tpc = 0;
					}

					virtual long generateTpc(long a_time){
						this->m_now = a_time;

						this->m_tpc = this->m_now - this->m_prev;
						this->m_prev = this->m_now;

						return this->m_tpc;
					}

					virtual long initialize_generateTpc(long a_time){
						if(!this->m_init){
							this->initialize(a_time);
						}
						return this->generateTpc(a_time);
					}

				protected:
					bool m_init = false;	

					long m_now = 0;
					long m_prev = 0;
					long m_tpc = 0;
			};

		}

	}

#endif
