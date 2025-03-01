
#ifndef RawMap_hpp
#define RawMap_hpp

#include "RawPointerMap.hpp"

#if defined(pankey_Log) && (defined(RawMap_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
	#define RawMapLog(status,method,mns) pankey_Log(status,"RawMap",method,mns)
#else
	#define RawMapLog(status,method,mns)
#endif

namespace pankey{

template <class K,class V>
class RawMap : virtual public RawPointerMap<K,V>{
    public:
		virtual ~RawMap(){
			RawMapLog(pankey_Log_StartMethod, "Destructor", "");
			RawMapLog(pankey_Log_EndMethod, "Destructor", "");
		}

		virtual void addCopy(const RawPointerMap<K,V>& a_map){
			RawMapLog(pankey_Log_StartMethod, "addCopy", "");
			for(int x = 0; x < a_map.getLastIndex(); x++){
				K* k = a_map.getKeyByIndex(x);
				V* v = a_map.getValueByIndex(x);
				if(k == nullptr || v == nullptr){
					continue;
				}
				this->addLValues(*k,*v);
			}
			RawMapLog(pankey_Log_EndMethod, "addCopy", "");
		}
		
		virtual RawMapEntry<K,V> addLValues(K a_key, V a_value)=0;
		virtual RawMapEntry<K,V> addPointer(K a_key, V* a_value)=0;
		
		virtual RawMapEntry<K,V> add(K a_key, V a_value){
			RawMapLog(pankey_Log_StartMethod, "add", "");
			RawMapLog(pankey_Log_EndMethod, "add", "");
			return this->addLValues(a_key, a_value);
		}

		virtual RawMapEntry<K,V> setLValues(K a_key, V a_value)=0;
		virtual RawMapEntry<K,V> setPointer(K a_key, V* a_value)=0;
		
		virtual RawMapEntry<K,V> setKeyLValueByIndex(int a_position, K a_key)=0;
		virtual RawMapEntry<K,V> setValueLValueByIndex(int a_position, V a_value)=0;
		
		virtual RawMapEntry<K,V> set(K a_key, V a_value){
			RawMapLog(pankey_Log_StartMethod, "set", "");
			RawMapLog(pankey_Log_EndMethod, "set", "");
			return this->setLValues(a_key,a_value);
		}
		
		virtual bool containKeyByLValue(K a_key)=0;
		virtual bool containValueByLValue(V a_value)=0;
		
		virtual bool contain(K a_key){
			RawMapLog(pankey_Log_StartMethod, "contain", "");
			RawMapLog(pankey_Log_EndMethod, "contain", "");
			return this->containKeyByLValue(a_key);
		}
		
		virtual K* getKeyByLValue(V a_value)const=0;
		
		virtual V* getValueByLValue(K a_key)const=0;
		
		virtual V get(K a_key)const{
			RawMapLog(pankey_Log_StartMethod, "get", "");
			V* i_value = this->getValueByLValue(a_key);
			if(i_value == nullptr){
				RawMapLog(pankey_Log_EndMethod, "get", "");
				return V();
			}
			RawMapLog(pankey_Log_EndMethod, "get", "");
			return *i_value;
		}
		virtual K getKey(int a_position){
			RawMapLog(pankey_Log_StartMethod, "getKey", "");
			K* i_key = this->getKeyByIndex(a_position);
			if(i_key == nullptr){
				RawMapLog(pankey_Log_EndMethod, "getKey", "");
				return K();
			}
			RawMapLog(pankey_Log_EndMethod, "getKey", "");
			return *i_key;
		}
		virtual V getValue(int a_position){
			RawMapLog(pankey_Log_StartMethod, "getValue", "");
			V* i_value = this->getValueByIndex(a_position);
			if(i_value == nullptr){
				RawMapLog(pankey_Log_EndMethod, "getValue", "");
				return V();
			}
			RawMapLog(pankey_Log_EndMethod, "getValue", "");
			return *i_value;
		}
		
		virtual RawMapEntry<K,V> removeByKeyLValue(K a_key)=0;
		virtual RawMapEntry<K,V> removeByValueLValue(V a_value)=0;
		
		virtual bool removeDeleteByKeyLValue(K a_key)=0;
		virtual bool removeDeleteByValueLValue(V a_value)=0;
		
		virtual bool remove(K a_key)=0;
		
		virtual RawMapEntry<K,V> putLValues(K a_key, V a_value)=0;
		virtual RawMapEntry<K,V> putPointer(K a_key, V* a_value)=0;
		
		virtual RawMapEntry<K,V> put(K a_key, V a_value){
			RawMapLog(pankey_Log_StartMethod, "put", "");
			RawMapLog(pankey_Log_EndMethod, "put", "");
			return this->putLValues(a_key, a_value);
		}
		
		virtual int getKeyIndexByLValue(K a_key)=0;
		
		virtual int getValueIndexByLValue(V a_key)=0;
		
		template<class... Args>
		void addKeyPack(Args... a_values){
			RawMapLog(pankey_Log_StartMethod, "addKeyPack", "");
			K i_array[] = {a_values...};
			for(const K& k : i_array){
				this->addPointers(new K(k), new V());
			}
			RawMapLog(pankey_Log_EndMethod, "addKeyPack", "");
		}
		
		template<class... Args>
		void addValuePack(Args... a_values){
			RawMapLog(pankey_Log_StartMethod, "addValuePack", "");
			V i_array[] = {a_values...};
			for(const V& v : i_array){
				this->addPointers(new K(), new V(v));
			}
			RawMapLog(pankey_Log_EndMethod, "addValuePack", "");
		}
		
		template<class... Args>
		void addKeyPack(V v, Args... a_values){
			RawMapLog(pankey_Log_StartMethod, "addKeyPack", "");
			K i_array[] = {a_values...};
			for(const K& k : i_array){
				this->addPointers(new K(k), new V(v));
			}
			RawMapLog(pankey_Log_EndMethod, "addKeyPack", "");
		}
		
		template<class... Args>
		void addValuePack(K k, Args... a_values){
			RawMapLog(pankey_Log_StartMethod, "addValuePack", "");
			V i_array[] = {a_values...};
			for(const V& v : i_array){
				this->addPointers(new K(k), new V(v));
			}
			RawMapLog(pankey_Log_EndMethod, "addValuePack", "");
		}
};

}

#endif