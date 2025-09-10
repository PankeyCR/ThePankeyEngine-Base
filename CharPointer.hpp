
#ifndef CharPointer_hpp
	#define CharPointer_hpp

	#include "MemorySize.hpp"
	#include "MemoryAllocator.hpp"
	#include "AllocatorFactory.hpp"

	#if defined(pankey_Log) && (defined(CharPointer_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define CharPointerLog(status,method,mns) pankey_Log(status,"CharPointer",method,mns)
	#else
		#define CharPointerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			class CharPointer{
				public:
					CharPointer() {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*");
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}
					CharPointer(const char* a_pointer) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*");
						memory_size i_length = strlen(a_pointer);
						create(a_pointer, i_length, AllocatorFactory(char));
						copy(a_pointer, i_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const char* a_pointer, MemoryAllocator* a_allocator) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*,MemoryAllocator");
						memory_size i_length = strlen(a_pointer);
						create(a_pointer, i_length, a_allocator);
						copy(a_pointer, i_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const char* a_pointer, memory_size a_length) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*,memory_size");
						create(a_pointer, a_length, AllocatorFactory(char));
						copy(a_pointer, a_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const char* a_pointer, memory_size a_length, MemoryAllocator* a_allocator) {
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const char*,memory_size,MemoryAllocator");
						create(a_pointer, a_length, a_allocator);
						copy(a_pointer, a_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "const CharPointer&");
						create(a_charpointer.m_pointer, a_charpointer.m_length, a_charpointer.m_allocator);
						copy(a_charpointer.m_pointer, a_charpointer.m_length);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					CharPointer(CharPointer&& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "Contructor", "CharPointer&&");
						m_pointer = a_charpointer.m_pointer;
						m_length = a_charpointer.m_length;
						m_allocator = setMemoryAllocator(a_charpointer.m_allocator);
						a_charpointer.m_pointer = nullptr;
						a_charpointer.m_length = 0;
						destroyMemoryAllocator(a_charpointer.m_allocator);
						CharPointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~CharPointer(){
						CharPointerLog(pankey_Log_StartMethod, "Destructor", "");
						deallocateArray<char>(m_allocator, m_length + 1, m_pointer);
						destroyMemoryAllocator(m_allocator);
						CharPointerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					static bool isEmpty(const char* a_pointer){
						CharPointerLog(pankey_Log_StartMethod, "strlen", "");
						if(a_pointer == nullptr){
							CharPointerLog(pankey_Log_EndMethod, "strlen", "a_pointer == nullptr");
							return true;
						}
						memory_size i_length = strlen(a_pointer);
						if(i_length == 0){
							CharPointerLog(pankey_Log_EndMethod, "strlen", "i_length == 0");
							return true;
						}
						CharPointerLog(pankey_Log_EndMethod, "strlen", "");
						return false;
					}

					static memory_size strlen(const char* a_pointer, memory_size a_max_size){
						CharPointerLog(pankey_Log_StartMethod, "strlen", "");
						if(a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "strlen", "length:");
							CharPointerLog(pankey_Log_EndMethod, "strlen", 0);
							CharPointerLog(pankey_Log_EndMethod, "strlen", "a_pointer == nullptr");
							return 0;
						}
						for(memory_size x = 0; x < a_max_size; x++){
							char f_value = a_pointer[x];
							if(f_value == '\0'){
								CharPointerLog(pankey_Log_Statement, "strlen", "length:");
								CharPointerLog(pankey_Log_EndMethod, "strlen", x);
								CharPointerLog(pankey_Log_EndMethod, "strlen", "f_value == endvalue");
								return x;
							}
						}
						CharPointerLog(pankey_Log_Statement, "strlen", "length:");
						CharPointerLog(pankey_Log_EndMethod, "strlen", 0);
						CharPointerLog(pankey_Log_EndMethod, "strlen", "");
						return 0;
					}

					static memory_size strlen(const char* a_pointer){
						return strlen(a_pointer, 100000);
					}
					
					const bool isNull()const{
						return m_pointer == nullptr;
					}
					
					const char* get() const {
						return m_pointer;
					}

					operator bool() const {
						return m_pointer == nullptr;
					}

					const char* operator()() const {
						return m_pointer;
					}

					virtual int length()const{
						return m_length;
					}

					virtual void clear(){
						CharPointerLog(pankey_Log_StartMethod, "clear", "const CharPointer&");
						if(m_pointer == nullptr){
							return;
						}
						deallocateArray<char>(m_allocator, m_length + 1, m_pointer);
						m_pointer = nullptr;
						m_length = 0;
						CharPointerLog(pankey_Log_EndMethod, "clear", "");
					}

					CharPointer& operator=(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator=", "const CharPointer&");
						this->clear();
						create(a_charpointer.m_pointer, a_charpointer.m_length, a_charpointer.m_allocator);
						copy(a_charpointer.m_pointer, a_charpointer.m_length);
						CharPointerLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					bool operator==(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(m_pointer == a_charpointer.m_pointer){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr || a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						memory_size i_length = strlen(a_charpointer.m_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_charpointer.m_pointer[x]){
								return false;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					bool operator==(const char* a_pointer){
						CharPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(m_pointer == a_pointer){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						memory_size i_length = strlen(a_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator==", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_pointer[x]){
								return false;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					bool operator!=(const CharPointer& a_charpointer){
						CharPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(m_pointer == a_charpointer.m_pointer){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr || a_charpointer.m_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						memory_size i_length = strlen(a_charpointer.m_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_charpointer.m_pointer[x]){
								return true;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}

					bool operator!=(const char* a_pointer){
						CharPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(m_pointer == a_pointer){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == a_pointer");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						memory_size i_length = strlen(a_pointer);
						if(m_length != i_length){
							CharPointerLog(pankey_Log_Statement, "operator!=", "m_length != i_length");
							CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(int x = 0; x < m_length; x++){
							if(m_pointer[x] != a_pointer[x]){
								return true;
							}
						}
						CharPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}
					
				protected:
					char* m_pointer = nullptr;
					memory_size m_length = 0;
					MemoryAllocator* m_allocator = nullptr;

					void create(const char* a_pointer, memory_size a_length, MemoryAllocator* a_allocator){
						CharPointerLog(pankey_Log_StartMethod, "create", "");
						if(a_pointer == nullptr){
							CharPointerLog(pankey_Log_Error, "create", "a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						m_allocator = setMemoryAllocator(a_allocator);
						m_pointer = allocateArray<char>(m_allocator, a_length + 1);
						if(m_pointer == nullptr){
							CharPointerLog(pankey_Log_Error, "create", "m_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						m_length = a_length;
						CharPointerLog(pankey_Log_EndMethod, "create", "");
					}

					void copy(const char* a_pointer, memory_size a_length){
						CharPointerLog(pankey_Log_StartMethod, "copy", "");
						if(m_pointer == nullptr || a_pointer == nullptr){
							CharPointerLog(pankey_Log_Error, "copy", "m_pointer == nullptr || a_pointer == nullptr");
							CharPointerLog(pankey_Log_EndMethod, "copy", "");
							return;
						}
						if(m_length != a_length){
							CharPointerLog(pankey_Log_Error, "copy", "m_length != a_length");
							CharPointerLog(pankey_Log_EndMethod, "copy", "");
							return;
						}
						for(int x = 0; x < a_length; x++){
							CharPointerLog(pankey_Log_Statement, "copy", "iteration:");
							CharPointerLog(pankey_Log_Statement, "copy", x);
							CharPointerLog(pankey_Log_Statement, "copy", "value:");
							CharPointerLog(pankey_Log_Statement, "copy", a_pointer[x]);
							m_pointer[x] = a_pointer[x];
						}
						m_pointer[a_length] = '\0';
						CharPointerLog(pankey_Log_EndMethod, "copy", "");
					}
			};

		}

	}

#endif