
#ifndef RawPointerMap_hpp
#define RawPointerMap_hpp

#include "RawMapEntry.hpp"

#if defined(RawPointerMap_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
	#define RawPointerMapLog(status,method,mns) pankey_Log(status,"RawPointerMap",method,mns)
#else
	#define RawPointerMapLog(status,method,mns)
#endif

namespace pankey{

template <class K,class V>
class RawPointerMap{
    public:
		virtual ~RawPointerMap(){
			RawPointerMapLog(pankey_Log_StartMethod, "Constructor", "");
			RawPointerMapLog(pankey_Log_EndMethod, "Constructor", "");
		}

		virtual bool isEmpty()const=0;

		virtual void setOwner(bool a_owning){
			RawPointerMapLog(pankey_Log_StartMethod, "setOwner", "");
			this->m_key_owner = a_owning;
			this->m_value_owner = a_owning;
			RawPointerMapLog(pankey_Log_EndMethod, "setOwner", "");
		}
		virtual bool isOwner()const{
			RawPointerMapLog(pankey_Log_StartMethod, "isOwner", "");
			RawPointerMapLog(pankey_Log_EndMethod, "isOwner", "");
			return this->m_key_owner && this->m_value_owner;
		}
		virtual bool hasOwner()const{
			RawPointerMapLog(pankey_Log_StartMethod, "isOwner", "");
			RawPointerMapLog(pankey_Log_EndMethod, "isOwner", "");
			return this->m_key_owner || this->m_value_owner;
		}

		virtual void setKeyOwner(bool a_owning){
			RawPointerMapLog(pankey_Log_StartMethod, "setKeyOwner", "");
			this->m_key_owner = a_owning;
			RawPointerMapLog(pankey_Log_EndMethod, "setKeyOwner", "");
		}
		virtual bool isKeyOwner()const{
			RawPointerMapLog(pankey_Log_StartMethod, "isKeyOwner", "");
			RawPointerMapLog(pankey_Log_EndMethod, "isKeyOwner", "");
			return this->m_key_owner;
		}

		virtual void setValueOwner(bool a_owning){
			RawPointerMapLog(pankey_Log_StartMethod, "setValueOwner", "");
			this->m_value_owner = a_owning;
			RawPointerMapLog(pankey_Log_EndMethod, "setValueOwner", "");
		}
		virtual bool isValueOwner()const{
			RawPointerMapLog(pankey_Log_StartMethod, "isValueOwner", "");
			RawPointerMapLog(pankey_Log_EndMethod, "isValueOwner", "");
			return this->m_value_owner;
		}
		virtual void setPosition(int a_position){
			RawPointerMapLog(pankey_Log_StartMethod, "setPosition", a_position);
			this->m_position = a_position;
			RawPointerMapLog(pankey_Log_EndMethod, "setPosition", "");
		}
		virtual int getPosition()const{
			RawPointerMapLog(pankey_Log_StartMethod, "getPosition", "");
			RawPointerMapLog(pankey_Log_EndMethod, "getPosition", "");
			return this->m_position;
		}

		virtual void setSize(int a_size){
			RawPointerMapLog(pankey_Log_StartMethod, "setSize", "");
			this->m_size = a_size;
			RawPointerMapLog(pankey_Log_EndMethod, "setSize", "");
		}
		virtual int getSize()const{
			RawPointerMapLog(pankey_Log_StartMethod, "getSize", "");
			RawPointerMapLog(pankey_Log_EndMethod, "getSize", "");
			return this->m_size;
		}
		
		virtual int hasAvailableSize()const{
			RawPointerMapLog(pankey_Log_StartMethod, "getSize", "");
			RawPointerMapLog(pankey_Log_EndMethod, "getSize", "");
			return this->m_position < this->m_size  && this->m_size != 0;
		}

		virtual void addMove(RawPointerMap<K,V>* a_map){
			RawPointerMapLog(pankey_Log_StartMethod, "addMove", "");
			for(int x = 0; x < a_map->getPosition(); x++){
				K* k = a_map->getKeyByPosition(x);
				V* v = a_map->getValueByPosition(x);
				this->addPointers(k,v);
				a_map->setRawMapEntryByPosition(x, RawMapEntry<K,V>());
			}
			RawPointerMapLog(pankey_Log_EndMethod, "addMove", "");
		}

		virtual void addDuplicate(RawPointerMap<K,V>* a_map){
			RawPointerMapLog(pankey_Log_StartMethod, "addDuplicate", "");
			for(int x = 0; x < a_map->getPosition(); x++){
				K* k = a_map->getKeyByPosition(x);
				V* v = a_map->getValueByPosition(x);
				this->addPointers(k,v);
			}
			RawPointerMapLog(pankey_Log_EndMethod, "addDuplicate", "");
		}

		virtual RawMapEntry<K,V> addPointers(K* a_key, V* a_value)=0;
		virtual RawMapEntry<K,V> addRawMapEntry(RawMapEntry<K,V> a_map_entry)=0;

		virtual RawMapEntry<K,V> putPointers(K* a_key, V* a_value){
			RawPointerMapLog(pankey_Log_StartMethod, "putPointers", "");
			if(this->containPairPointers(a_key,a_value)){
				RawPointerMapLog(pankey_Log_EndMethod, "putPointers", "");
				return RawMapEntry<K,V>(a_key, a_value);
			}
			RawPointerMapLog(pankey_Log_EndMethod, "putPointers", "");
			return this->addPointers(a_key, a_value);
		}
		virtual RawMapEntry<K,V> putRawMapEntry(RawMapEntry<K,V> a_map_entry){
			RawPointerMapLog(pankey_Log_StartMethod, "putRawMapEntry", "");
			if(this->containRawMapEntry(a_map_entry)){
				RawPointerMapLog(pankey_Log_EndMethod, "putRawMapEntry", "");
				return RawMapEntry<K,V>(a_map_entry);
			}
			RawPointerMapLog(pankey_Log_EndMethod, "putRawMapEntry", "");
			return this->addRawMapEntry(a_map_entry);
		}

		virtual RawMapEntry<K,V> setPointers(K* a_key, V* a_value)=0;
		virtual RawMapEntry<K,V> setRawMapEntry(RawMapEntry<K,V> a_map_entry)=0;

		virtual RawMapEntry<K,V> setKeyPointerByPosition(int a_position, K* a_key)=0;
		virtual RawMapEntry<K,V> setValuePointerByPosition(int a_position, V* a_value)=0;

		virtual RawMapEntry<K,V> setRawMapEntryByPosition(int a_position, RawMapEntry<K,V> a_map_entry)=0;

		virtual bool containPairPointers(K* a_key, V* a_value)=0;
		virtual bool containRawMapEntry(RawMapEntry<K,V> a_map_entry)=0;

		virtual bool containKeyByPointer(K* a_key)=0;
		virtual bool containValueByPointer(V* a_value)=0;

		virtual RawMapEntry<K,V> getRawMapEntryByPosition(int a_position)const=0;

		virtual K* getKeyByPointer(V* a_value)=0;
		virtual K* getKeyByPosition(int a_position)const=0;

		virtual V* getValueByPointer(const K* a_key)const=0;
		virtual V* getValueByPosition(int a_position)const=0;

		virtual void reset()=0;
		virtual void resetDelete()=0;
		virtual void resetDeleteKey()=0;
		virtual void resetDeleteValue()=0;

		virtual RawMapEntry<K,V> removeByKeyPointer(K* a_key)=0;
		virtual RawMapEntry<K,V> removeByValuePointer(V* a_value)=0;
		virtual RawMapEntry<K,V> removeByPosition(int a_position)=0;

		virtual bool removeDeleteByKeyPointer(K* a_key){
			RawPointerMapLog(pankey_Log_StartMethod, "removeDeleteByKeyPointer", "");
			RawMapEntry<K,V> i_entry = this->removeByKeyPointer(a_key);
			bool removed = !i_entry.isNull();
			if(removed && this->isOwner()){
				i_entry.deleteEntry();
			}
			RawPointerMapLog(pankey_Log_EndMethod, "removeDeleteByKeyPointer", "");
			return removed;
		}

		virtual bool removeDeleteByValuePointer(V* a_value){
			RawPointerMapLog(pankey_Log_StartMethod, "removeDeleteByValuePointer", "");
			RawMapEntry<K,V> i_entry = this->removeByValuePointer(a_value);
			bool removed = !i_entry.isNull();
			if(removed && this->isOwner()){
				i_entry.deleteEntry();
			}
			RawPointerMapLog(pankey_Log_EndMethod, "removeDeleteByValuePointer", "");
			return removed;
		}

		virtual bool removeDeleteByPosition(int a_position){
			RawPointerMapLog(pankey_Log_StartMethod, "removeDeleteByPosition", "");
			RawMapEntry<K,V> i_entry = this->removeByPosition(a_position);
			bool removed = !i_entry.isNull();
			if(removed && isOwner()){
				i_entry.deleteEntry();
			}
			RawPointerMapLog(pankey_Log_EndMethod, "removeDeleteByPosition", "");
			return removed;
		}

		virtual int getKeyIndexByPointer(K* a_key){
			RawPointerMapLog(pankey_Log_StartMethod, "getKeyIndexByPointer", "");
			if(this->isEmpty()){
				RawPointerMapLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "");
				return -1;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->getKeyByPosition(x)){
					RawPointerMapLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "");
					return x;
				}
			}
			RawPointerMapLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "");
			return -1;
		}

		virtual int getValueIndexByPointer(V* a_value){
			RawPointerMapLog(pankey_Log_StartMethod, "getValueIndexByPointer", "");
			if(this->isEmpty()){
				RawPointerMapLog(pankey_Log_EndMethod, "getValueIndexByPointer", "");
				return -1;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(a_value == this->getValueByPosition(x)){
					RawPointerMapLog(pankey_Log_EndMethod, "getValueIndexByPointer", "");
					return x;
				}
			}
			RawPointerMapLog(pankey_Log_EndMethod, "getValueIndexByPointer", "");
			return -1;
		}

	protected:

		virtual void incrementPosition(){
			RawPointerMapLog(pankey_Log_StartMethod, "incrementPosition", this->m_position);
			this->m_position++;
			RawPointerMapLog(pankey_Log_EndMethod, "incrementPosition", this->m_position);
		}
		virtual void decrementPosition(){
			RawPointerMapLog(pankey_Log_StartMethod, "decrementPosition", this->m_position);
			this->m_position--;
			if(this->m_position < 0){
				this->m_position = 0;
			}
			RawPointerMapLog(pankey_Log_EndMethod, "decrementPosition", this->m_position);
		}

		virtual void incrementPosition(int a_size){
			RawPointerMapLog(pankey_Log_StartMethod, "incrementPosition", this->m_position);
			this->m_position += a_size;
			RawPointerMapLog(pankey_Log_EndMethod, "incrementPosition", this->m_position);
		}
		virtual void decrementPosition(int a_size){
			RawPointerMapLog(pankey_Log_StartMethod, "decrementPosition", this->m_position);
			this->m_position -= a_size;
			if(this->m_position < 0){
				this->m_position = 0;
			}
			RawPointerMapLog(pankey_Log_EndMethod, "decrementPosition", this->m_position);
		}
		
		virtual bool isEqualKey(K* a_key_1, K* a_key_2){
			if(a_key_1 != nullptr && a_key_2 != nullptr){
				if(*a_key_1 != *a_key_2){
					return false;
				}
			}else{
				if((a_key_1 != nullptr || a_key_2 != nullptr) && (a_key_1 != a_key_2)){
					return false;
				}
			}
			return true;
		}
		
		virtual bool isEqualValue(V* a_value_1, V* a_value_2){
			if(a_value_1 != nullptr && a_value_2 != nullptr){
				if(*a_value_1 != *a_value_2){
					return false;
				}
			}else{
				if((a_value_1 != nullptr || a_value_2 != nullptr) && (a_value_1 != a_value_2)){
					return false;
				}
			}
			return true;
		}
		
	protected:
		bool m_key_owner = true;
		bool m_value_owner = true;
		int m_position = 0;
		int m_size = 0;
};

}

#endif
