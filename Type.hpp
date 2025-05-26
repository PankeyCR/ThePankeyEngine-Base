
#ifndef Type_hpp
	#define Type_hpp

	#include "ClassCount.hpp"

	#if defined(pankey_Log) && (defined(Type_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define TypeLog(status,method,mns) pankey_Log(status,"Type",method,mns)
	#else
		#define TypeLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			class Type{
				public:
					Type(){
						TypeLog(pankey_Log_StartMethod, "Constructor", "");
						TypeLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~Type(){
						TypeLog(pankey_Log_StartMethod, "Destructor", "");
						TypeLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual long getType()const{
						TypeLog(pankey_Log_StartMethod, "getType", "");
						TypeLog(pankey_Log_EndMethod, "getType", "");
						return -1;
					}

					virtual bool istype(long a_type)const{
						TypeLog(pankey_Log_StartMethod, "istype", "");
						TypeLog(pankey_Log_Statement, "istype", "My Type:");
						TypeLog(pankey_Log_Statement, "istype", this->getType());
						TypeLog(pankey_Log_Statement, "istype", "Checking Type:");
						TypeLog(pankey_Log_Statement, "istype", a_type);
						TypeLog(pankey_Log_EndMethod, "istype", "");
						return this->getType() == a_type;
					}

					template<class T>
					bool istypeof()const{
						TypeLog(pankey_Log_StartMethod, "istypeof", "");
						TypeLog(pankey_Log_Statement, "istypeof", "My Type:");
						TypeLog(pankey_Log_Statement, "istypeof", this->getType());
						TypeLog(pankey_Log_Statement, "istypeof", "Checking Type:");
						TypeLog(pankey_Log_Statement, "istypeof", ClassCount<T>::get());
						TypeLog(pankey_Log_EndMethod, "istypeof", "");
						return this->istype(ClassCount<T>::get());
					}

					template<class T>
					T& cast()const{
						TypeLog(pankey_Log_StartMethod, "cast", "");
						TypeLog(pankey_Log_EndMethod, "cast", "");
						return *((T*)this);
					}

					virtual void operator=(const Type& a_type){}
					virtual bool operator==(const Type& a_type){return this->getType() == a_type.getType();}
					virtual bool operator!=(const Type& a_type){return this->getType() != a_type.getType();}
				protected:
			};

		}

	}


		#ifndef TYPE_CLASS
			#define TYPE_CLASS(T)\
				virtual long getType()const{return pankey::Base::ClassCount<T>::get();}\
				virtual bool istype(long a_type)const{return a_type == pankey::Base::ClassCount<T>::get();}\

		#endif
	
		#ifndef TYPE_INHERIT_CLASS
			#define TYPE_INHERIT_CLASS(T,G)\
				virtual long getType()const{return pankey::Base::ClassCount<T>::get();}\
				virtual bool istype(long a_type)const{return a_type == pankey::Base::ClassCount<T>::get() || G::istypeof(a_type);}\

		#endif

		#define CREATE_TYPE(T)\
			class T : public pankey::Base::Type{\
				public:\
					T(){}\
					virtual ~T(){}\
					virtual long getType()const{return Base::ClassCount<T>::get();}\
					virtual bool istype(long a_type)const{return a_type == Base::ClassCount<T>::get();}\
			};\

#endif
