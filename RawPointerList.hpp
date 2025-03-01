
#ifndef RawPointerList_hpp
    #define RawPointerList_hpp

    #if defined(pankey_Log) && (defined(RawPointerList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
        #define RawPointerListLog(status,method,mns) pankey_Log(status,"RawPointerList",method,mns)
    #else
        #define RawPointerListLog(status,method,mns)
    #endif

    namespace pankey{

        template <class T>
        class RawPointerList{
            public:
                virtual ~RawPointerList(){
                    RawPointerListLog(pankey_Log_StartMethod, "Destructor", "");
                    RawPointerListLog(pankey_Log_EndMethod, "Destructor", "");
                }
                
                virtual bool isEmpty()const=0;
                
                virtual void setOwner(bool a_owning){
                    RawPointerListLog(pankey_Log_StartMethod, "isOwner", "");
                    this->m_owner = a_owning;
                    RawPointerListLog(pankey_Log_EndMethod, "isOwner", "");
                }
                virtual bool isOwner()const{
                    RawPointerListLog(pankey_Log_StartMethod, "isOwner", "");
                    RawPointerListLog(pankey_Log_Statement, "isOwner", "isOwner:");
                    RawPointerListLog(pankey_Log_Statement, "isOwner", this->m_owner);
                    RawPointerListLog(pankey_Log_EndMethod, "isOwner", "");
                    return this->m_owner;
                }
                virtual void setLastIndex(int a_position){
                    RawPointerListLog(pankey_Log_StartMethod, "setLastIndex", "");
                    this->m_position = a_position;
                    RawPointerListLog(pankey_Log_EndMethod, "setLastIndex", "");
                }
                virtual int getLastIndex()const{
                    RawPointerListLog(pankey_Log_StartMethod, "getLastIndex", "");
                    RawPointerListLog(pankey_Log_EndMethod, "getLastIndex", "");
                    return this->m_position;
                }
                
                virtual void setSize(int a_size){
                    RawPointerListLog(pankey_Log_StartMethod, "setSize", "");
                    this->m_size = a_size;
                    RawPointerListLog(pankey_Log_EndMethod, "setSize", "");
                }
                virtual int getSize()const{
                    RawPointerListLog(pankey_Log_StartMethod, "getSize", "");
                    RawPointerListLog(pankey_Log_EndMethod, "getSize", "");
                    return this->m_size;
                }

                virtual bool replace(int i, int j)=0;
                
                virtual void addMove(RawPointerList<T>& a_list){
                    RawPointerListLog(pankey_Log_StartMethod, "addMove", "");
                    for(int x = 0; x < a_list.getLastIndex(); x++){
                        T* f_value = a_list.getByIndex(x);
                        this->addPointer(f_value);
                    }
                    a_list.reset();
                    RawPointerListLog(pankey_Log_EndMethod, "addMove", "");
                }
                
                virtual void addDuplicate(const RawPointerList<T>& a_list){
                    RawPointerListLog(pankey_Log_StartMethod, "addDuplicate", "");
                    for(int x = 0; x < a_list.getLastIndex(); x++){
                        T* f_value = a_list.getByIndex(x);
                        this->addPointer(f_value);
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "addDuplicate", "");
                }

                virtual T* addPointer(T* a_value)=0;
                
                virtual T* putPointer(T* a_value){
                    RawPointerListLog(pankey_Log_StartMethod, "putPointer", "");
                    if(this->containByPointer(a_value)){
                        return nullptr;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "putPointer", "");
                    return this->addPointer(a_value);
                }

                virtual T* setPointer(int a_position, T* a_value)=0;

                virtual T* insertPointer(int a_position, T* a_value)=0;

                virtual T* getByPointer(T* a_value)=0;
                virtual T* getByIndex(int x)const=0;

                virtual bool containByPointer(T* a_value)=0;
                
                virtual int getIndexByPointer(T* a_value)=0;

                virtual void reset()=0;
                virtual void clear()=0;

                virtual T* removeByPointer(T* a_value)=0;

                virtual T* removeByPosition(int a_position)=0;

                virtual bool removeDeleteByPointer(T* a_value){
                    RawPointerListLog(pankey_Log_StartMethod, "removeDeleteByPointer", "");
                    T* t = this->removeByPointer(a_value);
                    bool removed = t != nullptr;
                    if(removed && isOwner()){
                        delete t;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "removeDeleteByPointer", "");
                    return removed;
                }

                virtual bool removeDeleteByPosition(int a_position){
                    RawPointerListLog(pankey_Log_StartMethod, "removeDeleteByPosition", "");
                    T* t = this->removeByPosition(a_position);
                    bool removed = t != nullptr;
                    if(removed && isOwner()){
                        RawPointerListLog(pankey_Log_Statement, "removeDeleteByPosition", "deleting pointer");
                        delete t;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "removeDeleteByPosition", "");
                    return removed;
                }

                //special removes
                virtual bool removeFirstIndex(int a_amount)=0;
                virtual bool removeLastIndex(int a_amount)=0;
                
                virtual bool removeFirst(){
                    RawPointerListLog(pankey_Log_StartMethod, "removeFirst", "");
                    if(this->isEmpty()){
                        RawPointerListLog(pankey_Log_EndMethod, "removeFirst", "this->isEmpty()");
                        return false;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "removeFirst", "");
                    return this->removeDeleteByPosition(0);
                }

                virtual bool removeLast(){
                    RawPointerListLog(pankey_Log_StartMethod, "removeLast", "");
                    if(this->isEmpty()){
                        return false;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "removeLast", "");
                    return this->removeDeleteByPosition(this->getLastIndex() - 1);
                }

                virtual bool isInOrder(){return this->m_reorder;}
                virtual void setReorder(bool a_reorder){this->m_reorder = a_reorder;}
                virtual void reorder(){}

                virtual void expand(int a_size)=0;
                
            protected:
                
                virtual void incrementPosition(){
                    RawPointerListLog(pankey_Log_StartMethod, "incrementPosition", "");
                    this->m_position++;
                    RawPointerListLog(pankey_Log_EndMethod, "incrementPosition", "");
                }
                virtual void decrementPosition(){
                    RawPointerListLog(pankey_Log_StartMethod, "decrementPosition", "");
                    this->m_position--;
                    if(this->m_position < 0){
                        this->m_position = 0;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "decrementPosition", "");
                }
                
                virtual void incrementPosition(int a_size){
                    RawPointerListLog(pankey_Log_StartMethod, "incrementPosition", "");
                    this->m_position += a_size;
                    RawPointerListLog(pankey_Log_EndMethod, "incrementPosition", "");
                }
                virtual void decrementPosition(int a_size){
                    RawPointerListLog(pankey_Log_StartMethod, "decrementPosition", "");
                    this->m_position -= a_size;
                    if(this->m_position < 0){
                        this->m_position = 0;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "decrementPosition", "");
                }
                
                virtual void incrementSize(){
                    RawPointerListLog(pankey_Log_StartMethod, "incrementSize", "");
                    this->m_size++;
                    RawPointerListLog(pankey_Log_EndMethod, "incrementSize", "");
                }
                virtual void decrementSize(){
                    RawPointerListLog(pankey_Log_StartMethod, "decrementSize", "");
                    this->m_size--;
                    if(this->m_size < 0){
                        this->m_size = 0;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "decrementSize", "");
                }
                
                virtual void incrementSize(int a_size){
                    RawPointerListLog(pankey_Log_StartMethod, "incrementSize", "");
                    this->m_size += a_size;
                    RawPointerListLog(pankey_Log_EndMethod, "incrementSize", "");
                }
                virtual void decrementSize(int a_size){
                    RawPointerListLog(pankey_Log_StartMethod, "decrementSize", "");
                    this->m_size -= a_size;
                    if(this->m_size < 0){
                        this->m_size = 0;
                    }
                    RawPointerListLog(pankey_Log_EndMethod, "decrementSize", "");
                }

            public:
            
                virtual bool operator<(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator<", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator<", "");
                    return this->getLastIndex() < x;
                }
                
                virtual bool operator>(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator>", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator>", "");
                    return this->getLastIndex() > x;
                }
                
                virtual bool operator<=(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator<=", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator<=", "");
                    return this->getLastIndex() <= x;
                }
                
                virtual bool operator>=(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator>=", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator>=", "");
                    return this->getLastIndex() >= x;
                }
                
                virtual bool operator==(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator==", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator==", "");
                    return this->getLastIndex() == x;
                }
                
                virtual bool operator!=(int x) const{
                    RawPointerListLog(pankey_Log_StartMethod, "operator!=", "");
                    RawPointerListLog(pankey_Log_EndMethod, "operator!=", "");
                    return this->getLastIndex() != x;
                }

            protected:
                bool m_reorder = true;
                bool m_owner = true;
                int m_position = 0;
                int m_size = 0;
        };

    }

#endif