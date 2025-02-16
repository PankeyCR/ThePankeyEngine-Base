
#ifndef RawMapEntry_hpp
#define RawMapEntry_hpp

#if defined(RawMapEntry_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
	#define RawMapEntryLog(status,method,mns) pankey_Log(status,"RawMapEntry",method,mns)
#else
	#define RawMapEntryLog(status,method,mns)
#endif

namespace pankey{

template <class K,class V>
class RawMapEntry{
    public:
		RawMapEntry(){
			RawMapEntryLog(pankey_Log_StartMethod, "Constructor", "");
			RawMapEntryLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		RawMapEntry(K* c_key, V* c_value){
			RawMapEntryLog(pankey_Log_StartMethod, "Constructor", "");
			m_key = c_key;
			m_value = c_value;
			RawMapEntryLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		RawMapEntry(const RawMapEntry<K,V>& c_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "Constructor", "");
			m_key = c_map_entry.m_key;
			m_value = c_map_entry.m_value;
			RawMapEntryLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		RawMapEntry(RawMapEntry<K,V>&& c_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "Constructor", "");
			m_key = c_map_entry.m_key;
			m_value = c_map_entry.m_value;
			c_map_entry.m_key = nullptr;
			c_map_entry.m_value = nullptr;
			RawMapEntryLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		virtual ~RawMapEntry(){
			RawMapEntryLog(pankey_Log_StartMethod, "Destructor", "");
			RawMapEntryLog(pankey_Log_EndMethod, "Destructor", "");
		}
		
		virtual K* getKey()const{
			RawMapEntryLog(pankey_Log_StartMethod, "getKey", "");
			RawMapEntryLog(pankey_Log_EndMethod, "getKey", "");
			return this->m_key;
		}
		virtual V* getValue()const{
			RawMapEntryLog(pankey_Log_StartMethod, "getValue", "");
			RawMapEntryLog(pankey_Log_EndMethod, "getValue", "");
			return this->m_value;
		}
		
		virtual RawMapEntry& operator=(const RawMapEntry<K,V>& a_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "operator=", "");
			m_key = a_map_entry.m_key;
			m_value = a_map_entry.m_value;
			RawMapEntryLog(pankey_Log_EndMethod, "operator=", "");
			return *this;
		}
		
		virtual const RawMapEntry& operator=(RawMapEntry<K,V>&& a_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "operator=", "");
			m_key = a_map_entry.m_key;
			m_value = a_map_entry.m_value;
			a_map_entry.m_key = nullptr;
			a_map_entry.m_value = nullptr;
			RawMapEntryLog(pankey_Log_EndMethod, "operator=", "");
			return *this;
		}
		
		virtual bool operator!=(const RawMapEntry<K,V>& a_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "operator!=", "");
			RawMapEntryLog(pankey_Log_EndMethod, "operator!=", "");
			return m_key != a_map_entry.m_key && m_value != a_map_entry.m_value;
		}
		
		virtual bool operator==(const RawMapEntry<K,V>& a_map_entry){
			RawMapEntryLog(pankey_Log_StartMethod, "operator==", "");
			RawMapEntryLog(pankey_Log_EndMethod, "operator==", "");
			return m_key == a_map_entry.m_key && m_value == a_map_entry.m_value;
		}
		
		virtual bool isNull()const{
			RawMapEntryLog(pankey_Log_StartMethod, "isNull", "");
			RawMapEntryLog(pankey_Log_EndMethod, "isNull", "");
			return m_key == nullptr && m_value == nullptr;
		}
		
		virtual bool deleteEntry(){
			RawMapEntryLog(pankey_Log_StartMethod, "deleteEntry", "");
			if(m_key == nullptr && m_value == nullptr){
				RawMapEntryLog(pankey_Log_EndMethod, "deleteEntry", "");
				return false;
			}
			if(m_key != nullptr){
				delete this->m_key;
			}
			if(m_value != nullptr){
				delete this->m_value;
			}
			RawMapEntryLog(pankey_Log_EndMethod, "deleteEntry", "");
			return true;
		}
		
		virtual bool deleteKeyEntry(){
			RawMapEntryLog(pankey_Log_StartMethod, "deleteKeyEntry", "");
			if(m_key == nullptr){
				RawMapEntryLog(pankey_Log_EndMethod, "deleteKeyEntry", "");
				return false;
			}
			if(m_key != nullptr){
				delete this->m_key;
			}
			RawMapEntryLog(pankey_Log_EndMethod, "deleteKeyEntry", "");
			return true;
		}
		
		virtual bool deleteValueEntry(){
			RawMapEntryLog(pankey_Log_StartMethod, "deleteKeyEntry", "");
			if(m_value == nullptr){
				RawMapEntryLog(pankey_Log_EndMethod, "deleteEntry", "");
				return false;
			}
			if(m_value != nullptr){
				delete this->m_value;
			}
			RawMapEntryLog(pankey_Log_EndMethod, "deleteKeyEntry", "");
			return true;
		}
	
	protected:
		K* m_key = nullptr;
		V* m_value = nullptr;
};

}

#endif