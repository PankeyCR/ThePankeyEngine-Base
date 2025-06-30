
#ifndef unique_ptr_hpp
	#define unique_ptr_hpp

	namespace pankey{

		namespace Base{

			template<class T>
			class unique_ptr{
				public:
					unique_ptr(){}

					unique_ptr(const unique_ptr& a_unique) = delete;

					unique_ptr(unique_ptr&& a_unique){
						m_pointer = a_unique.m_pointer;
						a_unique.m_pointer = nullptr;
					}

					unique_ptr(T* a_pointer){
						m_pointer = a_pointer;
					}

					virtual ~unique_ptr(){
						delete m_pointer;
					}

					unique_ptr& operator=(const unique_ptr&) = delete;

					unique_ptr& operator=(unique_ptr&& a_unique){
						if(this == &a_unique){
							return *this;
						}
						if(m_pointer != a_unique.m_pointer){
							delete m_pointer;
							m_pointer = a_unique.m_pointer;
							a_unique.m_pointer = nullptr;
						}
						return *this;
					}

					explicit operator bool() const{
						return m_pointer != nullptr;
					}

					T* get() const{
						return m_pointer;
					}

					T* operator->() const{
						return m_pointer;
					}

					T& operator*() const{
						return *m_pointer;
					}

					bool operator==(T* a_pointer){
						return m_pointer == a_pointer;
					}

					bool operator==(const unique_ptr<T>& a_unique){
						return m_pointer == a_unique.m_pointer;
					}

					bool operator!=(T* a_pointer){
						return m_pointer != a_pointer;
					}

					bool operator!=(const unique_ptr<T>& a_unique){
						return m_pointer != a_unique.m_pointer;
					}

					void release(){
						m_pointer = nullptr;
					}
				protected:
					T* m_pointer = nullptr;
			};

		}

	}

#endif