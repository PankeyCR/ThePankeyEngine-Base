
#ifndef ArrayRawMap_hpp
#define ArrayRawMap_hpp

#include "ArrayRawPointerMap.hpp"
#include "RawMap.hpp"
#include "RawMapIterator.hpp"

#if defined(ArrayRawMap_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
	#define ArrayRawMapLog(status,method,mns) pankey_Log(status,"ArrayRawMap",method,mns)
#else
	#define ArrayRawMapLog(status,method,mns)
#endif

namespace pankey{

template <class K,class V>
class ArrayRawMap : public ArrayRawPointerMap<K,V>, virtual public RawMap<K,V>{	
    public:
		
		ArrayRawMap(){
			ArrayRawMapLog(pankey_Log_StartMethod, "Constructor", "");
			ArrayRawMapLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		ArrayRawMap(const ArrayRawMap<K,V>& c_map){
			ArrayRawMapLog(pankey_Log_StartMethod, "Constructor", "");
			this->setOwner(false);
			this->expandLocal(c_map.getPosition());
			
			for(int x = 0; x < c_map.getPosition(); x++){
				K* k = c_map.getKeyByPosition(x);
				V* v = c_map.getValueByPosition(x);
				if(k != nullptr && v != nullptr){
					this->addLValues(*k,*v);
				}
				if(k != nullptr && v == nullptr){
					this->addPointer(*k,v);
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		ArrayRawMap(int c_size) : ArrayRawPointerMap<K,V>(c_size){
			ArrayRawMapLog(pankey_Log_StartMethod, "Constructor", "");
			ArrayRawMapLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		ArrayRawMap(int c_size, bool c_key_own, bool c_value_own, bool c_reorder) : ArrayRawPointerMap<K,V>(c_size, c_key_own, c_value_own, c_reorder){
			ArrayRawMapLog(pankey_Log_StartMethod, "Constructor", "");
			ArrayRawMapLog(pankey_Log_EndMethod, "Constructor", "");
		}
		
		virtual ~ArrayRawMap(){
			ArrayRawMapLog(pankey_Log_StartMethod, "Destructor", "");
			ArrayRawMapLog(pankey_Log_EndMethod, "Destructor", "");
		}
		
		virtual void addMap(const ArrayRawMap<K,V>& a_map){
			ArrayRawMapLog(pankey_Log_StartMethod, "addLValues", "");
			if(a_map.getSize() < this->getPosition() + a_map.getPosition()){
				this->expandLocal(a_map.getPosition());
			}
			for(int x = 0; x < a_map.getPosition(); x++){
				K* k = a_map.getKeyByPosition(x);
				V* v = a_map.getValueByPosition(x);
				if(k != nullptr && v != nullptr){
					this->addLValues(*k,*v);
				}
				if(k != nullptr && v == nullptr){
					this->addPointer(*k,nullptr);
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "addLValues", "");
		}
		
		virtual RawMapEntry<K,V> addLValues(K a_key, V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "addLValues", "");
			K* i_key = new K(a_key);
			V* i_value = new V(a_value);
			ArrayRawMapLog(pankey_Log_EndMethod, "addLValues", "");
			return this->addPointers(i_key, i_value);
		}
		
		virtual RawMapEntry<K,V> addPointer(K a_key, V *a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "addPointer", "");
			K* i_key = new K(a_key);
			ArrayRawMapLog(pankey_Log_EndMethod, "addPointer", "");
			return this->addPointers(i_key, a_value);
		}
		
		virtual RawMapEntry<K,V> setLValues(K a_key, V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "setLValues", "");
			int i_index = this->getKeyIndexByLValue(a_key);
			if(i_index == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "setLValues", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "setLValues", "");
			return this->setValueLValueByPosition(i_index, a_value);
		}
		
		virtual RawMapEntry<K,V> setPointer(K a_key, V *a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "setPointer", "");
			int i_index = this->getKeyIndexByLValue(a_key);
			if(i_index == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "setPointer", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "setPointer", "");
			return this->setValuePointerByPosition(i_index, a_value);
		}
		
		virtual RawMapEntry<K,V> setKeyLValueByPosition(int a_position, K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "setKeyLValueByPosition", "");
			K* i_key = new K(a_key);
			ArrayRawMapLog(pankey_Log_EndMethod, "setKeyLValueByPosition", "");
			return this->setKeyPointerByPosition(a_position, i_key);
		}
		
		virtual RawMapEntry<K,V> setValueLValueByPosition(int a_position, V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "setValueLValueByPosition", "");
			V* i_value = new V(a_value);
			ArrayRawMapLog(pankey_Log_EndMethod, "setValueLValueByPosition", "");
			return this->setValuePointerByPosition(a_position, i_value);
		}
		
		virtual bool containKeyByLValue(K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "containKeyByLValue", "");
			for(int x = 0; x < this->getPosition(); x++){
				K* f_key = this->getKeyByPosition(x);
				if(f_key == nullptr){
					continue;
				}
				if(*f_key == a_key){
					ArrayRawMapLog(pankey_Log_EndMethod, "containKeyByLValue", "");
					return true;
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "containKeyByLValue", "");
			return false;
		}
		
		virtual bool containValueByLValue(V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "containValueByLValue", "");
			for(int x = 0; x < this->getPosition(); x++){
				V* f_value = this->getValueByPosition(x);
				if(f_value == nullptr){
					continue;
				}
				if(*f_value == a_value){
					ArrayRawMapLog(pankey_Log_EndMethod, "containValueByLValue", "");
					return true;
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "containValueByLValue", "");
			return false;
		}
		
		virtual K* getKeyByLValue(V a_value)const{
			ArrayRawMapLog(pankey_Log_StartMethod, "getKeyByLValue", "");
			for(int x = 0; x < this->getPosition(); x++){
				V* f_value = this->getValueByPosition(x);
				if(f_value == nullptr){
					continue;
				}
				if(*f_value == a_value){
					ArrayRawMapLog(pankey_Log_EndMethod, "getKeyByLValue", "");
					return this->getKeyByPosition(x);
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "getKeyByLValue", "");
			return nullptr;
		}
		
		virtual V* getValueByLValue(K a_key)const{
			ArrayRawMapLog(pankey_Log_StartMethod, "getValueByLValue", "");
			for(int x = 0; x < this->getPosition(); x++){
				K* f_key = this->getKeyByPosition(x);
				if(f_key == nullptr){
					continue;
				}
				if(*f_key == a_key){
					ArrayRawMapLog(pankey_Log_EndMethod, "getValueByLValue", "");
					return this->getValueByPosition(x);
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "getValueByLValue", "");
			return nullptr;
		}
		
		virtual RawMapEntry<K,V> removeByKeyLValue(K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "removeByKeyLValue", "");
			int i_position = this->getKeyIndexByLValue(a_key);
			if(i_position == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "removeByKeyLValue", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "removeByKeyLValue", "");
			return this->removeByPosition(i_position);
		}
		
		virtual RawMapEntry<K,V> removeByValueLValue(V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "removeByValueLValue", "");
			int i_position = this->getValueIndexByLValue(a_value);
			if(i_position == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "removeByValueLValue", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "removeByValueLValue", "");
			return this->removeByPosition(i_position);
		}
		
		virtual bool removeDeleteByKeyLValue(K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "removeDeleteByKeyLValue", "");
			int i_position = this->getKeyIndexByLValue(a_key);
			if(i_position == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "removeDeleteByKeyLValue", "");
				return false;
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "removeDeleteByKeyLValue", "");
			return this->removeDeleteByPosition(i_position);
		}
		
		virtual bool removeDeleteByValueLValue(V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "removeDeleteByValueLValue", "");
			int i_position = this->getValueIndexByLValue(a_value);
			if(i_position == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "removeDeleteByValueLValue", "");
				return false;
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "removeDeleteByValueLValue", "");
			return this->removeDeleteByPosition(i_position);
		}
		
		virtual bool remove(K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "remove", "");
			int i_position = this->getKeyIndexByLValue(a_key);
			if(i_position == -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "remove", "");
				return false;
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "remove", "");
			return this->removeDeleteByPosition(i_position);
		}
		
		virtual RawMapEntry<K,V> putLValues(K a_key, V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "putLValues", "");
			int index = this->getKeyIndexByLValue(a_key);
			if(index != -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "putLValues", "index != -1");
				return this->getRawMapEntryByPosition(index);
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "putLValues", "");
			return this->addLValues(a_key, a_value);
		}
		
		virtual RawMapEntry<K,V> putPointer(K a_key, V* a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "putPointer", "");
			int index = this->getKeyIndexByLValue(a_key);
			if(index != -1){
				ArrayRawMapLog(pankey_Log_EndMethod, "putLValues", "index != -1");
				return this->getRawMapEntryByPosition(index);
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "putPointer", "");
			return this->addPointer(a_key, a_value);
		}
		
		virtual int getKeyIndexByLValue(K a_key){
			ArrayRawMapLog(pankey_Log_StartMethod, "getKeyIndexByLValue", "");
			for(int x=0; x < this->getPosition(); x++){
				K* i_key = this->getKeyByPosition(x);
				if(i_key == nullptr){
					continue;
				}
				if(a_key == *i_key){
					ArrayRawMapLog(pankey_Log_EndMethod, "getKeyIndexByLValue", x);
					return x;
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "getKeyIndexByLValue", "");
			return -1;
		}
		
		virtual int getValueIndexByLValue(V a_value){
			ArrayRawMapLog(pankey_Log_StartMethod, "getValueIndexByLValue", "");
			for(int x=0; x < this->getPosition(); x++){
				V* i_value = this->getValueByPosition(x);
				if(i_value == nullptr){
					continue;
				}
				if(a_value == *i_value){
					ArrayRawMapLog(pankey_Log_EndMethod, "getValueIndexByLValue", "");
					return x;
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "getValueIndexByLValue", "");
			return -1;
		}
	
		////////////////////////////////////////////operator part///////////////////////////////////////////////
		
		
		virtual ArrayRawMap<K,V>& operator=(const ArrayRawMap<K,V>& a_map){
			ArrayRawMapLog(pankey_Log_StartMethod, "operator=", "");
			this->resetDelete();
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key = this->getKeyByPosition(x);
				V* f_value = this->getValueByPosition(x);
				if(f_key == nullptr || f_value == nullptr){
					continue;
				}
				this->addLValues(*f_key, *f_value);
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "operator=", "");
			return *this;
		}
		
		virtual bool operator==(const ArrayRawMap<K,V>& a_map){
			ArrayRawMapLog(pankey_Log_StartMethod, "operator==", "");
			if(this->getPosition() != a_map.getPosition()){
				return false;
			}
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key_1 = a_map.getKeyByPosition(x);
				V* f_value_1 = a_map.getValueByPosition(x);
				K* f_key_2 = this->getKeyByPosition(x);
				V* f_value_2 = this->getValueByPosition(x);
				if(f_key_1 == f_key_2 && f_value_1 == f_value_2){
					continue;
				}
				if(f_key_1 != nullptr && f_key_2 != nullptr && f_value_1 != nullptr && f_value_2 != nullptr){
					if(*f_key_1 != *f_key_2 || *f_value_1 != *f_value_2){
						return false;
					}
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "operator==", "");
			return true;
		}
		
		virtual bool operator!=(const ArrayRawMap<K,V>& a_map){
			ArrayRawMapLog(pankey_Log_StartMethod, "operator!=", "");
			if(this->getPosition() != a_map.getPosition()){
				return true;
			}
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key_1 = a_map.getKeyByPosition(x);
				V* f_value_1 = a_map.getValueByPosition(x);
				K* f_key_2 = this->getKeyByPosition(x);
				V* f_value_2 = this->getValueByPosition(x);
				if(f_key_1 == f_key_2 && f_value_1 == f_value_2){
					continue;
				}
				if(f_key_1 != nullptr && f_key_2 != nullptr && f_value_1 != nullptr && f_value_2 != nullptr){
					if(*f_key_1 != *f_key_2 || *f_value_1 != *f_value_2){
						return true;
					}
				}
			}
			ArrayRawMapLog(pankey_Log_EndMethod, "operator!=", "");
			return false;
		}
	
		////////////////////////////////////////////Iterator part///////////////////////////////////////////////
		
		virtual RawMapIterator<K,V> begin(){
			ArrayRawMapLog(pankey_Log_StartMethod, "begin", this->getPosition());
			ArrayRawMapLog(pankey_Log_EndMethod, "begin", "");
			return RawMapIterator<K,V>(this, 0, this->getPosition());
		}
		virtual RawMapIterator<K,V> end(){
			ArrayRawMapLog(pankey_Log_StartMethod, "end", this->getPosition());
			ArrayRawMapLog(pankey_Log_EndMethod, "end", "");
			return RawMapIterator<K,V>(this, this->getPosition() - 1, this->getPosition());
		}
		
	protected:
};

}

#endif