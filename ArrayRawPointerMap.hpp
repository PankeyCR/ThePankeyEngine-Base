
#ifndef ArrayRawPointerMap_hpp
#define ArrayRawPointerMap_hpp

#include "RawPointerMap.hpp"

#if defined(ArrayRawPointerMap_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
	#define ArrayRawPointerMapLog(status,method,mns) pankey_Log(status,"ArrayRawPointerMap",method,mns)
#else
	#define ArrayRawPointerMapLog(status,method,mns)
#endif

namespace pankey{

template <class K,class V>
class ArrayRawPointerMap : virtual public RawPointerMap<K,V>{
    public:

		ArrayRawPointerMap(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "Constructor", "");
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "Constructor", "");
		}

		ArrayRawPointerMap(const ArrayRawPointerMap<K,V>& c_map){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "Constructor", "");
			this->setOwner(false);
			this->expandLocal(c_map.getPosition());

			for(int x = 0; x < c_map.getPosition(); x++){
				K* k = c_map.getKeyByPosition(x);
				V* v = c_map.getValueByPosition(x);
				this->addPointers(k,v);
				c_map->setRawMapEntryByPosition(x, RawMapEntry<K,V>());
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "Constructor", "");
		}

		ArrayRawPointerMap(int c_size){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "Constructor", "");
			this->expandLocal(c_size);
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "Constructor", "");
		}

		ArrayRawPointerMap(int c_size, bool c_key_own, bool c_value_own, bool c_reorder){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "Constructor", "");
			this->setKeyOwner(c_key_own);
			this->setValueOwner(c_value_own);
			this->expandLocal(c_size);
			m_reorder = c_reorder;
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "Constructor", "");
		}

		virtual ~ArrayRawPointerMap(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "Destructor", "");
			if(this->m_keys != nullptr && this->m_values != nullptr){
				ArrayRawPointerMapLog(pankey_Log_Statement, "Destructor", "this->m_keys != nullptr && this->m_values != nullptr");
				if(this->hasOwner()){
					ArrayRawPointerMapLog(pankey_Log_StartMethod, "Destructor", "this->m_owner");
					for(int x = 0; x < this->getPosition(); x++){
						if(this->m_keys[x] != nullptr && this->isKeyOwner()){
						ArrayRawPointerMapLog(pankey_Log_Statement, "Destructor", "key is deleted");
							delete this->m_keys[x];
						}
						if(this->m_values[x] != nullptr && this->isValueOwner()){
						ArrayRawPointerMapLog(pankey_Log_Statement, "Destructor", "key is deleted");
							delete this->m_values[x];
						}
					}
					ArrayRawPointerMapLog(pankey_Log_StartMethod, "Destructor", "after deleting");
				}
				this->setPosition(0);
				this->setSize(0);
				delete[] this->m_keys;
				delete[] this->m_values;
				this->m_keys = nullptr;
				this->m_values = nullptr;
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "Destructor", "");
		}

		virtual bool isEmpty()const{
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "isEmpty", "");
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "isEmpty", "");
			return this->getPosition() <= 0 || this->m_keys == nullptr || this->m_values == nullptr;
		}

		virtual RawMapEntry<K,V> addPointers(K* a_key, V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "addPointers", "");
			if(this->getPosition() >= this->getSize()){
				ArrayRawPointerMapLog(pankey_Log_Statement, "addPointers", "this->getPosition() >= this->getSize()");
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				ArrayRawPointerMapLog(pankey_Log_Statement, "addPointers", "second chance this->getPosition() >= this->getSize()");
				if(a_key != nullptr && this->isKeyOwner()){
					delete a_key;
				}
				if(a_value != nullptr && this->isValueOwner()){
					delete a_value;
				}
				return RawMapEntry<K,V>();
			}
			this->m_keys[this->getPosition()] = a_key;
			this->m_values[this->getPosition()] = a_value;
			this->incrementPosition();
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "addPointers", "");
			return RawMapEntry<K,V>(a_key, a_value);
		}

		virtual RawMapEntry<K,V> addRawMapEntry(RawMapEntry<K,V> a_map_entry){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "addRawMapEntry", "");
			if(this->isEmpty()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				if(a_map_entry.getKey() != nullptr && this->isKeyOwner()){
					a_map_entry.deleteKeyEntry();
				}
				if(a_map_entry.getValue() != nullptr && this->isValueOwner()){
					a_map_entry.deleteValueEntry();
				}
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "addRawMapEntry", "");
				return RawMapEntry<K,V>();
			}
			this->m_keys[this->getPosition()] = a_map_entry.getKey();
			this->m_values[this->getPosition()] = a_map_entry.getValue();
			this->incrementPosition();
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "addRawMapEntry", "");
			return RawMapEntry<K,V>(a_map_entry);
		}

		virtual RawMapEntry<K,V> setPointers(K* a_key, V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "setPointers", "");
			int i_index = this->getKeyIndexByPointer(a_key);
			if(i_index == -1){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setPointers", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "setPointers", "");
			return this->setValuePointerByPosition(i_index, a_value);
		}

		virtual RawMapEntry<K,V> setRawMapEntry(RawMapEntry<K,V> a_map_entry){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "setRawMapEntry", "");
			int i_index = this->getKeyIndexByPointer(a_map_entry.getKey());
			if(i_index == -1){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setRawMapEntry", "");
				return RawMapEntry<K,V>();
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "setRawMapEntry", "");
			return this->setRawMapEntryByPosition(i_index, a_map_entry);
		}

		virtual RawMapEntry<K,V> setKeyPointerByPosition(int a_position, K* a_key){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "setKeyPointerByPosition", "");
			if(a_position >= this->getPosition()){
				if(a_key != nullptr && this->isKeyOwner()){
					delete a_key;
				}
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setKeyPointerByPosition", "");
				return RawMapEntry<K,V>();
			}
			RawMapEntry<K,V> i_entry = this->getRawMapEntryByPosition(a_position);
			K* i_key = i_entry.getKey();
			if(a_key == i_key){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setKeyPointerByPosition", "");
				return i_entry;
			}
			if(this->isKeyOwner() && i_key != nullptr){
				delete i_key;
			}
			this->m_keys[a_position] = a_key;
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "setKeyPointerByPosition", "");
			return RawMapEntry<K,V>(a_key, i_entry.getValue());
		}

		virtual RawMapEntry<K,V> setValuePointerByPosition(int a_position, V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "setValuePointerByPosition", "");
			if(a_position >= this->getPosition()){
				if(a_value != nullptr && this->isValueOwner()){
					delete a_value;
				}
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setValuePointerByPosition", "");
				return RawMapEntry<K,V>();
			}
			RawMapEntry<K,V> i_entry = this->getRawMapEntryByPosition(a_position);
			V* i_value = i_entry.getValue();
			if(a_value == i_value){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setValuePointerByPosition", "");
				return i_entry;
			}
			if(this->isValueOwner() && i_value != nullptr){
				delete i_value;
			}
			this->m_values[a_position] = a_value;
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "setValuePointerByPosition", "");
			return RawMapEntry<K,V>(i_entry.getKey(), a_value);
		}

		virtual RawMapEntry<K,V> setRawMapEntryByPosition(int a_position, RawMapEntry<K,V> a_map_entry){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "setRawMapEntryByPosition", "");
			if(a_position >= this->getPosition()){
				if(a_map_entry.getKey() != nullptr && this->isKeyOwner()){
					a_map_entry.deleteKeyEntry();
				}
				if(a_map_entry.getValue() != nullptr && this->isValueOwner()){
					a_map_entry.deleteValueEntry();
				}
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "setRawMapEntryByPosition", "a_position >= this->getPosition()");
				return RawMapEntry<K,V>();
			}
			RawMapEntry<K,V> i_entry = this->getRawMapEntryByPosition(a_position);
			K* i_key = i_entry.getKey();
			V* i_value = i_entry.getValue();
			if(this->hasOwner()){
				ArrayRawPointerMapLog(pankey_Log_Statement, "setRawMapEntryByPosition", "this->isOwner()");
				if(i_key != nullptr && i_key != a_map_entry.getKey() && this->isKeyOwner()){
					ArrayRawPointerMapLog(pankey_Log_Statement, "setRawMapEntryByPosition", "i_key != nullptr && i_key != a_map_entry.getKey()");
					delete i_key;
				}
				if(i_value != nullptr && i_value != a_map_entry.getValue() && this->isValueOwner()){
					ArrayRawPointerMapLog(pankey_Log_Statement, "setRawMapEntryByPosition", "i_value != nullptr && i_value != a_map_entry.getValue()");
					delete i_value;
				}
			}
			this->m_keys[a_position] = a_map_entry.getKey();
			this->m_values[a_position] = a_map_entry.getValue();
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "setRawMapEntryByPosition", "");
			return a_map_entry;
		}

		virtual bool containPairPointers(K* a_key, V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "containPairPointers", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key && this->m_values[x] == a_value){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "containPairPointers", "");
					return true;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "containPairPointers", "");
			return false;
		}

		virtual bool containRawMapEntry(RawMapEntry<K,V> a_map_entry){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "containRawMapEntry", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_map_entry.getKey() && this->m_values[x] == a_map_entry.getValue()){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "containRawMapEntry", "");
					return true;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "containRawMapEntry", "");
			return false;
		}

		virtual bool containKeyByPointer(K* a_key){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "containKeyByPointer", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "containKeyByPointer", "");
					return true;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "containKeyByPointer", "");
			return false;
		}

		virtual bool containValueByPointer(V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "containValueByPointer", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == a_value){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "containValueByPointer", "");
					return true;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "containValueByPointer", "");
			return false;
		}

		virtual V* getValueByPointer(const K* a_key)const{
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getValueByPointer", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "getValueByPointer", "");
					return this->m_values[x];
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getValueByPointer", "");
			return nullptr;
		}

		virtual V* getValueByPosition(int a_position) const{
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getValueByPosition", "");
			if(a_position >= this->getPosition() || this->isEmpty()){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "getValueByPosition", "");
				return nullptr;
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getValueByPosition", "");
			return this->m_values[a_position];
		}

		virtual RawMapEntry<K,V> getRawMapEntryByPosition(int a_position) const{
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getRawMapEntryByPosition", "");
			if(a_position >= this->getPosition()){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "getRawMapEntryByPosition", "a_position >= this->getPosition()");
				return RawMapEntry<K,V>();
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getRawMapEntryByPosition", a_position);
			return RawMapEntry<K,V>(this->m_keys[a_position], this->m_values[a_position]);
		}

		virtual K* getKeyByPosition(int a_position) const{
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getKeyByPosition", "");
			if(a_position >= this->getPosition() || this->isEmpty()){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyByPosition", "");
				return nullptr;
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyByPosition", "");
			return this->m_keys[a_position];
		}

		virtual K* getKeyByPointer(V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getKeyByPointer", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == a_value){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyByPointer", "");
					return this->m_keys[x];
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyByPointer", "");
			return nullptr;
		}

		virtual void reset(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "reset", "");
			this->setPosition(0);
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "reset", "");
		}

		virtual void resetDelete(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "resetDelete", "");
			ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", "this->getPosition()");
			ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", this->getPosition());
			for(int x = 0; x < this->getPosition(); x++){
				ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", "this->isOwner()");
				ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", this->isOwner());
				if(this->hasOwner()){
					ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", "deleting index: ");
					ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", x);
					if(this->isKeyOwner()){
						ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", "key is deleted");
						delete this->m_keys[x];
					}
					if(this->isValueOwner()){
						ArrayRawPointerMapLog(pankey_Log_Statement, "resetDelete", "value is deleted");
						delete this->m_values[x];
					}
				}
				this->m_keys[x] = nullptr;
				this->m_values[x] = nullptr;
			}
			this->setPosition(0);
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "resetDelete", "");
		}

		virtual void resetDeleteKey(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "resetDeleteKey", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->isKeyOwner()){
					delete this->m_keys[x];
				}
				this->m_keys[x] = nullptr;
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "resetDeleteKey", "");
		}

		virtual void resetDeleteValue(){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "resetDeleteValue", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->isValueOwner()){
					delete this->m_values[x];
				}
				this->m_values[x] = nullptr;
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "resetDeleteValue", "");
		}

		virtual RawMapEntry<K,V> removeByKeyPointer(K* a_key){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "removeByKeyPointer", "");
			if(this->isEmpty()){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByKeyPointer", "");
				return RawMapEntry<K,V>();
			}
			int i_position = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_keys[x]){
					i_position = x;
					break;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByKeyPointer", "");
			return this->removeByPosition(i_position);
		}

		virtual RawMapEntry<K,V> removeByValuePointer(V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "removeByValuePointer", "");
			if(this->isEmpty()){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByValuePointer", "");
				return RawMapEntry<K,V>();
			}
			int i_position = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(a_value == this->m_values[x]){
					i_position = x;
					break;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByValuePointer", "");
			return this->removeByPosition(i_position);
		}

		virtual RawMapEntry<K,V> removeByPosition(int a_position){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "removeByPosition", "");
			if(a_position >= this->getPosition() || this->isEmpty() || a_position < 0){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByPosition", "");
				return RawMapEntry<K,V>();
			}
			K* i_key = this->m_keys[a_position];
			V* i_value = this->m_values[a_position];
			this->m_keys[a_position] = nullptr;
			this->m_values[a_position] = nullptr;
			int i_iteration = this->getPosition();
			this->decrementPosition();
			if(!this->m_reorder){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByPosition", "");
				return RawMapEntry<K,V>(i_key, i_value);
			}
			for(int x = a_position + 1; x < i_iteration; x++){
				this->m_keys[x - 1] = this->m_keys[x];
				this->m_values[x - 1] = this->m_values[x];
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "removeByPosition", "");
			return RawMapEntry<K,V>(i_key, i_value);
		}

		virtual int getKeyIndexByPointer(K* a_key){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getKeyIndexByPointer", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_keys[x]){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyIndexByPointer", x);
					return x;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getKeyIndexByPointer", "return -1");
			return -1;
		}

		virtual int getIndexByPointer(V* a_value){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "getIndexByPointer", "");
			for(int x=0; x < this->getPosition(); x++){
				if(a_value == this->m_values[x]){
					ArrayRawPointerMapLog(pankey_Log_EndMethod, "getIndexByPointer", "");
					return x;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "getIndexByPointer", "");
			return -1;
		}

		//resize length by adding more space
		virtual void expandLocal(int a_size){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "expandLocal", "");
			int i_size = this->getSize() + a_size;
			ArrayRawPointerMapLog(pankey_Log_Statement, "expandLocal", "Expanding size: ");
			ArrayRawPointerMapLog(pankey_Log_Statement, "expandLocal", i_size);
			if(i_size <= 1){
				ArrayRawPointerMapLog(pankey_Log_EndMethod, "expandLocal", "i_size <= 1");
				return;
			}
			K** nK;
			V** nV;
			nK = new K*[i_size];
			nV = new V*[i_size];
			if(this->m_keys != nullptr && this->m_values != nullptr){
				for(int x=0; x < this->getSize(); x++){
					nK[x] = this->m_keys[x];
					nV[x] = this->m_values[x];
				}
			}else if(this->m_keys != nullptr){
				for(int x=0; x < this->getSize(); x++){
					nK[x] = this->m_keys[x];
				}
				delete[] this->m_keys;
				this->m_keys = nullptr;
			}else if(this->m_values != nullptr){
				for(int x=0; x < this->getSize(); x++){
					nV[x] = this->m_values[x];
				}
				delete[] this->m_values;
				this->m_values = nullptr;
			}
			for(int x = this->getSize(); x < i_size; x++){
				nK[x] = nullptr;
				nV[x] = nullptr;
			}
			this->m_keys = nK;
			this->m_values = nV;
			this->m_size = i_size;
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "expandLocal", "");
		}
		//resize length by adding more space
		// virtual void expandLocal(int a_size){
		// 	ArrayRawPointerMapLog(pankey_Log_StartMethod, "expandLocal", "");
		// 	int i_size = this->getSize() + a_size;
		// 	ArrayRawPointerMapLog(pankey_Log_Statement, "expandLocal", "Expanding size: ");
		// 	ArrayRawPointerMapLog(pankey_Log_Statement, "expandLocal", i_size);
		// 	if(i_size <= 1){
		// 		ArrayRawPointerMapLog(pankey_Log_EndMethod, "expandLocal", "i_size <= 1");
		// 		return;
		// 	}
		// 	K** nK;
		// 	V** nV;
		// 	nK = new K*[i_size];
		// 	nV = new V*[i_size];
		// 	for(int x=0; x < this->getPosition(); x++){
		// 		nK[x] = this->m_keys[x];
		// 		nV[x] = this->m_values[x];
		// 	}
		// 	if(this->m_keys != nullptr){
		// 		delete[] this->m_keys;
		// 	}
		// 	if(this->m_values != nullptr){
		// 		delete[] this->m_values;
		// 	}
		// 	this->m_keys = nK;
		// 	this->m_values = nV;
		// 	this->m_size = i_size;
		// 	ArrayRawPointerMapLog(pankey_Log_EndMethod, "expandLocal", "");
		// }

		virtual ArrayRawPointerMap<K,V>* expand(int a_size){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "expand", "");
			int i_size = this->m_size + a_size;
			ArrayRawPointerMap<K,V> *nprimitive = new ArrayRawPointerMap<K,V>(i_size);
			for(int x = 0; x < this->getPosition(); x++){
				nprimitive->addPointers(this->m_keys[x],this->m_values[x]);
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "expand", "");
			return nprimitive;
		}

		virtual ArrayRawPointerMap<K,V>& operator=(const ArrayRawPointerMap<K,V>& a_map){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "operator=", "const ArrayRawPointerMap<K,V>&");
			this->resetDelete();
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key = a_map.getKeyByPosition(x);
				V* f_value = a_map.getValueByPosition(x);
				this->addPointers(f_key, f_value);
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "operator=", "");
			return *this;
		}

		virtual bool operator==(const ArrayRawPointerMap<K,V>& a_map){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "operator==", "const ArrayRawPointerMap<K,V>&");
			if(a_map.getPosition() != this->getPosition()){
				return false;
			}
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key_1 = a_map.getKeyByPosition(x);
				V* f_value_1 = a_map.getValueByPosition(x);
				K* f_key_2 = this->getKeyByPosition(x);
				V* f_value_2 = this->getValueByPosition(x);
				if(f_key_1 != f_key_2 || f_value_1 != f_value_2){
					return false;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_EndMethod, "operator==", "");
			return true;
		}

		virtual bool operator!=(const ArrayRawPointerMap<K,V>& a_map){
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "operator!=", "const ArrayRawPointerMap<K,V>&");
			if(a_map.getPosition() != this->getPosition()){
				return true;
			}
			for(int x = 0; x < a_map.getPosition(); x++){
				K* f_key_1 = a_map.getKeyByPosition(x);
				V* f_value_1 = a_map.getValueByPosition(x);
				K* f_key_2 = this->getKeyByPosition(x);
				V* f_value_2 = this->getValueByPosition(x);
				if(f_key_1 != f_key_2 || f_value_1 != f_value_2){
					return true;
				}
			}
			ArrayRawPointerMapLog(pankey_Log_StartMethod, "operator!=", "");
			return false;
		}

	protected:
		bool m_reorder = true;
		int m_expandSize = 5;

		K** m_keys = nullptr;
		V** m_values = nullptr;
};

}

#endif
