
#ifndef MemorySize_hpp
	#define MemorySize_hpp

	namespace pankey{

		namespace Base{

			#ifndef MemorySize(TYPE)

				using memory_size = unsigned int;

				template<class P>
				memory_size sizeOfMemory(const P* a_pointer){
					return (char *)(a_pointer + 1) - (char *)(a_pointer);
				}

				template<class P>
				memory_size sizeOfMemory(){
					P i_pointer;
					memory_size i_size = sizeOfMemory<P>(&i_pointer);
					return i_size;
				}

				template <class P>
				memory_size sizeOfArray(memory_size count) {
					return sizeOfMemory<P>() * count;
				}

				#define MemorySize(TYPE) Base::sizeOfMemory<TYPE>()
				#define ArrayMemorySize(TYPE, COUNT) Base::sizeOfArray<TYPE>(COUNT)

			#endif
		}
	}

#endif