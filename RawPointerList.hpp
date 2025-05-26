
#ifndef RawPointerList_hpp
    #define RawPointerList_hpp

    #if defined(pankey_Log) && (defined(RawPointerList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
        #define RawPointerListLog(status,method,mns) pankey_Log(status,"RawPointerList",method,mns)
    #else
        #define RawPointerListLog(status,method,mns)
    #endif

    namespace pankey{

		namespace Base{

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

                    virtual void length(int a_index){
                        RawPointerListLog(pankey_Log_StartMethod, "length", "");
                        this->m_index = a_index;
                        RawPointerListLog(pankey_Log_EndMethod, "length", "");
                    }

                    virtual int length()const{
                        RawPointerListLog(pankey_Log_StartMethod, "length", "");
                        RawPointerListLog(pankey_Log_EndMethod, "length", "");
                        return this->m_index;
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
                        for(int x = 0; x < a_list.length(); x++){
                            T* f_value = a_list.getPointerByIndex(x);
                            this->addPointer(f_value);
                        }
                        a_list.reset();
                        RawPointerListLog(pankey_Log_EndMethod, "addMove", "");
                    }
                    
                    virtual void addDuplicate(const RawPointerList<T>& a_list){
                        RawPointerListLog(pankey_Log_StartMethod, "addDuplicate", "");
                        for(int x = 0; x < a_list.length(); x++){
                            T* f_value = a_list.getPointerByIndex(x);
                            this->addPointer(f_value);
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "addDuplicate", "");
                    }

                    virtual T* addPointer(T* a_value)=0;
                    
                    virtual T* putPointer(T* a_value){
                        RawPointerListLog(pankey_Log_StartMethod, "putPointer", "");
                        if(this->containByPointer(a_value)){
                            return this->getPointerByPointer(a_value);
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "putPointer", "");
                        return this->addPointer(a_value);
                    }

                    virtual T* setPointer(int a_index, T* a_value)=0;

                    virtual T* insertPointer(int a_index, T* a_value)=0;

                    virtual T* getPointerByPointer(T* a_value)=0;
                    virtual T* getPointerByIndex(int x)const=0;

                    virtual bool containByPointer(T* a_value)=0;
                    
                    virtual int getIndexByPointer(T* a_value)=0;

                    virtual void reset()=0;
                    virtual void clear()=0;

                    virtual T* removePointerByPointer(T* a_value)=0;

                    virtual T* removePointerByIndex(int a_index)=0;

                    virtual bool destroyByPointer(T* a_value){
                        RawPointerListLog(pankey_Log_StartMethod, "destroyByPointer", "");
                        T* t = this->removePointerByPointer(a_value);
                        bool removed = t != nullptr;
                        if(removed && isOwner()){
                            delete t;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "destroyByPointer", "");
                        return removed;
                    }

                    virtual bool destroyByIndex(int a_index){
                        RawPointerListLog(pankey_Log_StartMethod, "destroyByIndex", "");
                        T* t = this->removePointerByIndex(a_index);
                        bool removed = t != nullptr;
                        if(removed && isOwner()){
                            RawPointerListLog(pankey_Log_Statement, "destroyByIndex", "deleting pointer");
                            delete t;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "destroyByIndex", "");
                        return removed;
                    }

                    //special removes
                    virtual bool destroyFirstIndex(int a_amount)=0;
                    virtual bool destroyLastIndex(int a_amount)=0;
                    
                    virtual T* removeFirst(){
                        RawPointerListLog(pankey_Log_StartMethod, "removeFirst", "");
                        RawPointerListLog(pankey_Log_EndMethod, "removeFirst", "");
                        return this->removePointerByIndex(0);
                    }
                    
                    virtual bool destroyFirst(){
                        RawPointerListLog(pankey_Log_StartMethod, "destroyFirst", "");
                        if(this->isEmpty()){
                            RawPointerListLog(pankey_Log_EndMethod, "destroyFirst", "this->isEmpty()");
                            return false;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "destroyFirst", "");
                        return this->destroyByIndex(0);
                    }

                    virtual T* removeLast(){
                        RawPointerListLog(pankey_Log_StartMethod, "removeLast", "");
                        RawPointerListLog(pankey_Log_EndMethod, "removeLast", "");
                        return this->removePointerByIndex(this->length() - 1);
                    }

                    virtual bool destroyLast(){
                        RawPointerListLog(pankey_Log_StartMethod, "destroyLast", "");
                        if(this->isEmpty()){
                            return false;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "destroyLast", "");
                        return this->destroyByIndex(this->length() - 1);
                    }
                    
                    virtual void destroyFromList(const RawPointerList<T>& a_list){
                        RawPointerListLog(pankey_Log_StartMethod, "destroyFromList", "");
                        for(int x = 0; x < a_list.length(); x++){
                            T* f_value = a_list.getPointerByIndex(x);
                            this->destroyByPointer(f_value);
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "destroyFromList", "");
                    }
				
					template<class... Args>
					void addPack(Args... x){
						RawPointerListLog(pankey_Log_StartMethod, "addPack", "");
						T array[] = {x...};
						for(const T& a : array){
							this->addPointer(new T(a));
						}
						RawPointerListLog(pankey_Log_EndMethod, "addPack", "");
					}
					
					template<class... Args>
					T* addWithParameters(Args... x){
						RawPointerListLog(pankey_Log_StartMethod, "addWithParameters", "");
						RawPointerListLog(pankey_Log_EndMethod, "addWithParameters", "");
						return this->addPointer(new T(x...));
					}

                    virtual bool isInOrder(){return this->m_reorder;}
                    virtual void setReorder(bool a_reorder){this->m_reorder = a_reorder;}
                    virtual void reorder(){}

                    virtual void expand(int a_size)=0;
                    
                protected:
                    
                    virtual void incrementIndex(){
                        RawPointerListLog(pankey_Log_StartMethod, "incrementIndex", "");
                        this->m_index++;
                        RawPointerListLog(pankey_Log_EndMethod, "incrementIndex", "");
                    }
                    virtual void decrementIndex(){
                        RawPointerListLog(pankey_Log_StartMethod, "decrementIndex", "");
                        this->m_index--;
                        if(this->m_index < 0){
                            this->m_index = 0;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "decrementIndex", "");
                    }
                    
                    virtual void incrementIndex(int a_size){
                        RawPointerListLog(pankey_Log_StartMethod, "incrementIndex", "");
                        this->m_index += a_size;
                        RawPointerListLog(pankey_Log_EndMethod, "incrementIndex", "");
                    }
                    virtual void decrementIndex(int a_size){
                        RawPointerListLog(pankey_Log_StartMethod, "decrementIndex", "");
                        this->m_index -= a_size;
                        if(this->m_index < 0){
                            this->m_index = 0;
                        }
                        RawPointerListLog(pankey_Log_EndMethod, "decrementIndex", "");
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
                        return this->length() < x;
                    }
                    
                    virtual bool operator>(int x) const{
                        RawPointerListLog(pankey_Log_StartMethod, "operator>", "");
                        RawPointerListLog(pankey_Log_EndMethod, "operator>", "");
                        return this->length() > x;
                    }
                    
                    virtual bool operator<=(int x) const{
                        RawPointerListLog(pankey_Log_StartMethod, "operator<=", "");
                        RawPointerListLog(pankey_Log_EndMethod, "operator<=", "");
                        return this->length() <= x;
                    }
                    
                    virtual bool operator>=(int x) const{
                        RawPointerListLog(pankey_Log_StartMethod, "operator>=", "");
                        RawPointerListLog(pankey_Log_EndMethod, "operator>=", "");
                        return this->length() >= x;
                    }
                    
                    virtual bool operator==(int x) const{
                        RawPointerListLog(pankey_Log_StartMethod, "operator==", "");
                        RawPointerListLog(pankey_Log_EndMethod, "operator==", "");
                        return this->length() == x;
                    }
                    
                    virtual bool operator!=(int x) const{
                        RawPointerListLog(pankey_Log_StartMethod, "operator!=", "");
                        RawPointerListLog(pankey_Log_EndMethod, "operator!=", "");
                        return this->length() != x;
                    }

                protected:
                    bool m_reorder = true;
                    bool m_owner = true;
                    int m_index = 0;
                    int m_size = 0;
            };

        }

    }

#endif