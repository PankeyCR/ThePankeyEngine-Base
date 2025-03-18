
/*
*	position = total of chars in the CharArray
*	size = total size of the array
*	length = total of chars before the endValue()
*
*
*	position = length
*
*/

#ifndef CharArray_hpp
	#define CharArray_hpp

	#include "Array.hpp"

	#define pankey_BINARY 0
	#define pankey_HEXADECIMAL 1
	#define pankey_DECIMAL 2

	#if defined(pankey_Log) && (defined(CharArray_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define CharArrayLog(status,method,mns) pankey_Log(status,"CharArray",method,mns)
	#else
		#define CharArrayLog(status,method,mns)
	#endif


	namespace pankey{

		namespace Base{

			class CharArray : public Array<char>{
				public:
					CharArray(){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "Default Constructor");
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const char* c_value){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const char* c_value");
						CharArrayLog(pankey_Log_Statement, "Constructor", "Char Array:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_value);

						this->insertLocalArrayPointer(0, c_value);

						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
							
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const Array<char>& source){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const Array<char>& source");
						int i_array_length = source.length();
						if(i_array_length > 0){
							this->createArray(i_array_length);
							this->copyPointer(source.pointer(), i_array_length);
							this->copyEndValue();
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
							CharArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						}
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const CharArray& source){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const CharArray& val");
						CharArrayLog(pankey_Log_Statement, "Constructor", "CharArray:");
						CharArrayLog(pankey_Log_Statement, "Constructor", source.pointer());
						int i_array_length = source.length();
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
						CharArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						if(i_array_length > 0){
							this->createArray(i_array_length);
							this->copyPointer(source.pointer(), i_array_length);
							this->copyEndValue();
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						}
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(CharArray&& source){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "CharArray&& source");
						int i_array_length = source.getPosition();
						if(i_array_length > 0){
							this->m_pos = source.m_pos;
							this->m_size = source.m_size;
							this->m_t_value = source.m_t_value;
							source.m_t_value = nullptr;
							source.m_pos = 0;
							source.m_size = 0;
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
							CharArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
							CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
							CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						}
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const char& c_char){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const char& c_char");
						CharArrayLog(pankey_Log_Statement, "Constructor", "Char:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_char);
						this->createArray(1);
						this->copyValue(c_char);
						this->copyEndValue();
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
						CharArrayLog(pankey_Log_Statement, "Constructor", 1);
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const bool& c_value){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const bool& i");
						CharArrayLog(pankey_Log_Statement, "Constructor", "bool:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_value);
						char* i_pointer = this->getBool(c_value);
						this->addLocalArrayPointer(i_pointer);
						delete i_pointer;
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const int& c_value){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const int& c_value");
						CharArrayLog(pankey_Log_Statement, "Constructor", "Int:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_value);
						char* i_pointer = this->getInt(c_value);
						this->addLocalArrayPointer(i_pointer);
						delete i_pointer;
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const long& c_value){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const long& c_value");
						CharArrayLog(pankey_Log_Statement, "Constructor", "Long:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_value);
						char* i_pointer = this->getLong(c_value);
						this->addLocalArrayPointer(i_pointer);
						delete i_pointer;
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					CharArray(const float& c_value){
						CharArrayLog(pankey_Log_StartMethod, "Constructor", "const float& c_value");
						CharArrayLog(pankey_Log_Statement, "Constructor", "Float:");
						CharArrayLog(pankey_Log_Statement, "Constructor", c_value);
						char* i_pointer = this->getFloat(c_value);
						this->addLocalArrayPointer(i_pointer);
						delete i_pointer;
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						CharArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						CharArrayLog(pankey_Log_Statement, "Constructor", this->getSize());
						CharArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~CharArray(){
						CharArrayLog(pankey_Log_StartMethod, "Destructor", "");
						CharArrayLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual char* pointer()const{
						CharArrayLog(pankey_Log_StartMethod, "pointer", "");
						CharArrayLog(pankey_Log_EndMethod, "pointer", "");
						return this->m_t_value;
					}

					virtual bool hasEndValue()const{
						CharArrayLog(pankey_Log_StartMethod, "hasEndValue", "");
						CharArrayLog(pankey_Log_EndMethod, "hasEndValue", "");
						return true;
					}

					virtual char endValue()const{
						CharArrayLog(pankey_Log_StartMethod, "endValue", "");
						CharArrayLog(pankey_Log_Statement, "endValue", "CharArray char void /0");
						CharArrayLog(pankey_Log_EndMethod, "endValue", "");
						return '\0';
					}

					virtual int length(void) const{
						CharArrayLog(pankey_Log_StartMethod, "length", "");
						int i_length = this->arrayLength(this->m_t_value);
						if(i_length <= 0){
							CharArrayLog(pankey_Log_EndMethod, "length", "");
							return 0;
						}
						CharArrayLog(pankey_Log_EndMethod, "length", "");
						return i_length;
					}

					virtual int getAvailableSize(int a_pos)const{
						CharArrayLog(pankey_Log_StartMethod, "getAvailableSize", "");
						CharArrayLog(pankey_Log_EndMethod, "getAvailableSize", "");
						return a_pos + 1;
					}

					virtual char* create(int a_size){
						CharArrayLog(pankey_Log_StartMethod, "create", "");
						CharArrayLog(pankey_Log_EndMethod, "create", "");
						return new char[a_size];
					}

					virtual int boolCharSize(bool a_value){
						return 1;
					}

					virtual void copyExternBool(char* a_array, bool a_position, bool a_value, int a_size){
						CharArrayLog(pankey_Log_StartMethod, "copyExternBool", "");

						CharArrayLog(pankey_Log_Statement, "copyExternBool", "a_value");
						CharArrayLog(pankey_Log_Statement, "copyExternBool", a_value);
						CharArrayLog(pankey_Log_Statement, "copyExternBool", "Array Length:");
						CharArrayLog(pankey_Log_Statement, "copyExternBool", a_size);

						if(a_array == nullptr){
							CharArrayLog(pankey_Log_EndMethod, "copyExternBool", "a_array == nullptr");
							return;
						}

						if(a_size == 1){
							if(a_value){
								a_array[a_position] = 1 + 48;
							}else{
								a_array[a_position] = 0 + 48;
							}
							CharArrayLog(pankey_Log_EndMethod, "copyExternBool", "a_size == 1");
							return;
						}

						if(a_size == 4){//true
							if(!a_value){
								a_array[a_position] = 't';
								a_array[a_position + 1] = 'r';
								a_array[a_position + 2] = 'u';
								a_array[a_position + 3] = 'e';
							}
						}

						if(a_size == 5){//false
							if(!a_value){
								a_array[a_position] = 'f';
								a_array[a_position + 1] = 'a';
								a_array[a_position + 2] = 'l';
								a_array[a_position + 3] = 's';
								a_array[a_position + 4] = 'e';
							}
						}

						CharArrayLog(pankey_Log_Statement, "copyExternBool", "Array Length:");
						CharArrayLog(pankey_Log_Statement, "copyExternBool", a_size);

						CharArrayLog(pankey_Log_EndMethod, "copyExternBool", "");
					}
					
					virtual char* getBool(bool a_value){
						CharArrayLog(pankey_Log_StartMethod, "getBool", "");
						int i_array_length = boolCharSize(a_value);
						char* i_pointer = this->createArrayClone(i_array_length);
						this->copyExternBool(i_pointer, 0, a_value, i_array_length);
						this->copyExternEndValue(i_pointer, i_array_length);
						CharArrayLog(pankey_Log_EndMethod, "getBool", "");
						return i_pointer;
					}

					virtual bool isBool() const{
						CharArrayLog(pankey_Log_StartMethod, "isBool", "");
						if(this->length() != 4 && this->length() != 5 && this->length() != 1){
							CharArrayLog(pankey_Log_EndMethod, "isBool", "Not a bool");
							return false;
						}
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a true:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "true");
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a false:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "false");
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a TRUE:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "TRUE");
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a FALSE:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "FALSE");
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a 1:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "1");
						CharArrayLog(pankey_Log_Statement, "isBool", "Is a 0:");
						CharArrayLog(pankey_Log_Statement, "isBool", (*this) == "0");
						CharArrayLog(pankey_Log_EndMethod, "isBool", "Is a bool");
						return (*this) == "true" || (*this) == "false" || (*this) == "TRUE" || (*this) == "FALSE" || (*this) == "1" || (*this) == "0";
					}

					virtual int intCharSize(int a_value)const{
						CharArrayLog(pankey_Log_StartMethod, "intCharSize", "");
						CharArrayLog(pankey_Log_Statement, "intCharSize", "");
						int i_size_val = 0;
						int x = 1;
						int add_x = 0;
						if(a_value < 0){
							a_value *= -1;
							add_x++;
						}
						for( ; x < 100; x++){
							int expn = 1;
							for(int y = 0; y < x; y++){
								expn *= 10;
							}
							if(a_value/expn < 1){
								i_size_val = x;
								break;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "intCharSize", "");
						return i_size_val + add_x;
					}
					
					virtual void copyExternInt(char* a_array, bool a_position, int a_value, int a_size){
						CharArrayLog(pankey_Log_StartMethod, "intToCharPointer", "");
						CharArrayLog(pankey_Log_Statement, "intToCharPointer", "");
						if(a_array == nullptr){
							CharArrayLog(pankey_Log_EndMethod, "intToCharPointer", "");
							return;
						}
						int position = a_position;
						bool isNegative = false;
						if(a_value < 0){
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "negative value");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "Position: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", position);
							isNegative = true;
							a_value *= -1;
							a_size--;
							a_array[position] = 45;
							position++;
						}
						int i_value_reduction = 1;
						int i_reduce_value = 1;
						int i_output_value = 1;
						for(int x = 0; x < a_size; x++){
							int exponent = 1;
							for(int y = 0; y < a_size - x - 1; y++){
								exponent *= 10;
							}
							i_value_reduction = a_value / exponent;
							if(x == 0){
								i_output_value = i_value_reduction;
							}else{
								i_output_value = i_value_reduction - i_reduce_value;
							}
							i_reduce_value = i_value_reduction * 10;
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "exponent: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", exponent);
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "value reduction: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", i_value_reduction);
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "reduce value: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", i_reduce_value);
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "output value: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", i_output_value);
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", "Position: ");
							CharArrayLog(pankey_Log_Statement, "intToCharPointer", position);
							a_array[position] = i_output_value + 48;
							position++;
						}

						CharArrayLog(pankey_Log_EndMethod, "intToCharPointer", "");
					}
					
					virtual char* getInt(int a_value){
						CharArrayLog(pankey_Log_StartMethod, "getInt", "");
						int i_array_length = intCharSize(a_value);
						char* i_pointer = this->createArrayClone(i_array_length);
						this->copyExternInt(i_pointer, 0, a_value, i_array_length);
						this->copyExternEndValue(i_pointer, i_array_length);
						CharArrayLog(pankey_Log_EndMethod, "getInt", "");
						return i_pointer;
					}
					
					virtual bool isInt() const{ 
						CharArrayLog(pankey_Log_StartMethod, "isInt", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "isInt", "Not a float");
							return false;
						}
						for(int i = 0; i < this->length(); i++){
							char f_char = this->get(i);
							if(!this->isNumber(f_char)){
								CharArrayLog(pankey_Log_EndMethod, "isInt", "Not a float");
								return false;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "isInt", "Is a float");
						return true;
					}

					virtual int longCharSize(long value)const{
						CharArrayLog(pankey_Log_StartMethod, "longCharSize", "");
						CharArrayLog(pankey_Log_Statement, "longCharSize", "");
						int i_size_val = 0;
						int x = 1;
						int add_x = 0;
						if(value < 0){
							value *= -1;
							add_x++;
						}
						for( ; x < 100; x++){
							long expn = 1;
							for(int y = 0; y < x; y++){
								expn *= 10;
							}
							if(value/expn < 1){
								i_size_val = x;
								break;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "longCharSize", "");
						return i_size_val + add_x;
					}

					virtual void copyExternLong(char* a_array, bool a_position, long a_value, int a_size){
						CharArrayLog(pankey_Log_StartMethod, "copyExternLong", "");
						CharArrayLog(pankey_Log_Statement, "copyExternLong", "a_value");
						CharArrayLog(pankey_Log_Statement, "copyExternLong", a_value);
						CharArrayLog(pankey_Log_Statement, "copyExternLong", "a_size");
						CharArrayLog(pankey_Log_Statement, "copyExternLong", a_size);
						if(a_array == nullptr){
							CharArrayLog(pankey_Log_EndMethod, "copyExternLong", "chr == nullptr");
							return;
						}
						int position = a_position;
						bool isNegative = false;
						if(a_value < 0){
							isNegative = true;
							a_value *= -1;
							a_size--;
							a_array[position] = 45;
							position++;
						}
						long n_value = 1;
						long r_value = 1;
						long s_value = 1;
						for(int x = 0; x < a_size; x++){
							long expn = 1;
							for(int y = 0; y < a_size - x - 1; y++){
								expn *= 10;
							}
							n_value = a_value / expn;
							if(x == 0){
								s_value = n_value;
							}else{
								s_value = n_value - r_value;
							}
							r_value = n_value * 10;
							a_array[position] = s_value + 48;
							position++;
						}
						
						CharArrayLog(pankey_Log_EndMethod, "copyExternLong", "");
					}
					
					virtual char* getLong(long a_value){
						CharArrayLog(pankey_Log_StartMethod, "getLong", "");
						int i_array_length = intCharSize(a_value);
						char* i_pointer = this->createArrayClone(i_array_length);
						this->copyExternInt(i_pointer, 0, a_value, i_array_length);
						this->copyExternEndValue(i_pointer, i_array_length);
						CharArrayLog(pankey_Log_EndMethod, "getLong", "");
						return i_pointer;
					}

					virtual bool isLong() const{
						CharArrayLog(pankey_Log_StartMethod, "isLong", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "isLong", "Not a long");
							return false;
						}
						if(this->getLastChar() != 'l'){
							CharArrayLog(pankey_Log_EndMethod, "isLong", "Not a long");
							return false;
						}
						for(int i = 0; i < this->length() - 1; i++){
							char f_char = this->get(i);
							if(!this->isNumber(f_char)){
								CharArrayLog(pankey_Log_EndMethod, "isLong", "Not a long");
								return false;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "isLong", "Is a long");
						return true;
					}
					
					virtual int floatCharSize(float a_value, int extra){
						CharArrayLog(pankey_Log_StartMethod, "floatCharSize", "");
						CharArrayLog(pankey_Log_Statement, "floatCharSize", "");
						int i_size_val = 0;
						int x = 1;
						int add_x = 0;
						if(a_value < 0){
							a_value *= -1;
							add_x++;
						}
						for( ; x < 100; x++){
							int expn = 1;
							for(int y = 0; y < x; y++){
								expn *= 10;
							}
							if(a_value/expn < 1){
								i_size_val = x;
								break;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "floatCharSize", "");
						return i_size_val + add_x + extra + 1;
					}

					virtual void copyExternFloat(char* a_array, bool a_position, float a_value, int a_size, int decimal_size){
						CharArrayLog(pankey_Log_StartMethod, "copyFloat", "");

						CharArrayLog(pankey_Log_Statement, "copyFloat", "a_value");
						CharArrayLog(pankey_Log_Statement, "copyFloat", a_value);
						CharArrayLog(pankey_Log_Statement, "copyFloat", "a_size");
						CharArrayLog(pankey_Log_Statement, "copyFloat", a_size);
						CharArrayLog(pankey_Log_Statement, "copyFloat", "decimal_size");
						CharArrayLog(pankey_Log_Statement, "copyFloat", decimal_size);

						if(a_array == nullptr){
							CharArrayLog(pankey_Log_EndMethod, "copyFloat", "");
							return;
						}
						int position = a_position;
						bool isNegative = false;
						CharArrayLog(pankey_Log_Statement, "copyFloat", "position");
						CharArrayLog(pankey_Log_Statement, "copyFloat", position);
						if(a_value < 0){
							CharArrayLog(pankey_Log_EndMethod, "copyFloat", "a_value < 0");
							isNegative = true;
							a_value *= -1;
							a_size--;
							a_array[position] = 45;
							position++;
						}
						CharArrayLog(pankey_Log_Statement, "copyFloat", "position");
						CharArrayLog(pankey_Log_Statement, "copyFloat", position);
						int n_value = 1;
						int r_value = 1;
						int s_value = 1;
						int i_size = a_size - decimal_size - 1;
						CharArrayLog(pankey_Log_Statement, "copyFloat", "i_size");
						CharArrayLog(pankey_Log_Statement, "copyFloat", i_size);
						for(int x = 0; x < i_size; x++){
							int expn = 1;
							for(int y = 0; y < i_size - x - 1; y++){
								expn *= 10;
							}
							n_value = a_value / expn;
							if(x == 0){
								s_value = n_value;
							}else{
								s_value = n_value - r_value;
							}
							r_value = n_value * 10;
							a_array[position] = s_value + 48;
							position++;
						}
						CharArrayLog(pankey_Log_Statement, "copyFloat", "position");
						CharArrayLog(pankey_Log_Statement, "copyFloat", position);

						a_array[position] = 46;
						position++;
						
						CharArrayLog(pankey_Log_Statement, "copyFloat", "position");
						CharArrayLog(pankey_Log_Statement, "copyFloat", position);

						n_value = 1;
						r_value = 1;
						s_value = 1;
						float i_value = a_value - (int)a_value;
						CharArrayLog(pankey_Log_Statement, "copyFloat", "i_value");
						CharArrayLog(pankey_Log_Statement, "copyFloat", i_value);
						for(int x = 0; x < decimal_size; x++){
							int expn = 10;
							for(int y = 0; y < x; y++){
								expn *= 10;
							}
							n_value = i_value * expn;
							if(x == 0){
								s_value = n_value;
							}else{
								s_value = n_value - r_value;
							}
							r_value = n_value * 10;
							a_array[position] = s_value + 48;
							position++;
						}
						CharArrayLog(pankey_Log_Statement, "copyFloat", "position");
						CharArrayLog(pankey_Log_Statement, "copyFloat", position);

						CharArrayLog(pankey_Log_Statement, "copyFloat", "Array Length:");
						CharArrayLog(pankey_Log_Statement, "copyFloat", a_size);

						CharArrayLog(pankey_Log_EndMethod, "copyFloat", "");
					}
					
					virtual char* getFloat(float a_value){
						CharArrayLog(pankey_Log_StartMethod, "getFloat", "");
						int i_array_length = floatCharSize(a_value, 4);
						char* i_pointer = this->createArrayClone(i_array_length);
						this->copyExternFloat(i_pointer, 0, a_value, i_array_length, 4);
						this->copyExternEndValue(i_pointer, i_array_length);
						CharArrayLog(pankey_Log_EndMethod, "getFloat", "");
						return i_pointer;
					}
					
					virtual bool isFloat() const{ 
						CharArrayLog(pankey_Log_StartMethod, "isFloat", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "isFloat", "Not a float");
							return false;
						}
						bool i_has_decimal_point = false;
						for(int i = 0; i < this->length(); i++){
							char f_char = this->get(i);
							if(i == this->length() - 1 && f_char == 'f'){
								CharArrayLog(pankey_Log_EndMethod, "isFloat", "last char is f");
								return true;
							}
							if(!this->isNumber(f_char) && f_char != '.'){
								CharArrayLog(pankey_Log_EndMethod, "isFloat", "Not a float");
								return false;
							}
							if(f_char == '.'){
								if(i_has_decimal_point){
									CharArrayLog(pankey_Log_EndMethod, "isFloat", "Not a float");
									return false;
								}else{
									i_has_decimal_point = true;
								}
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "isFloat", "Is a float");
						return true;
					}
					
					virtual bool isCharArray() const{
						if(this->isEmpty()){
							return false;
						}
						if(this->get(0) != '"' && this->getLastChar() != '"'){
							return false;
						}
						for(int i = 0; i < this->length(); i++){
							if(i != 0 && i != this->length() - 1){
								if(this->get(i) == '"'){
									return false;
								}
							}
						}
						return true;
					}
					
					virtual CharArray extractCharArray(){//   \"Hellow\"
						if(this->isEmpty()){
							return CharArray();
						}
						if(this->get(0) != '"' && this->getLastChar() != '"'){
							return CharArray();
						}
						CharArray i_extract = *this;
						i_extract.removeFirstIndex();
						i_extract.removeLastIndex();
						return i_extract;
					}
					
					virtual bool isNumber() const{
						if(this->isEmpty()){
							return false;
						}
						char lastChar = this->getLastChar();
						int c_size = this->length();
						if(lastChar == 'f' || lastChar == 'l'){
							c_size = this->length() - 1;
						}
						bool i_has_decimal_point = false;
						for(int i = 0; i < c_size; i++){
							char f_char = this->get(i);
							if(!this->isNumber(f_char) && f_char != '.'){
								CharArrayLog(pankey_Log_EndMethod, "isFloat", "Not a float");
								return false;
							}
							if(f_char == '.'){
								if(i_has_decimal_point){
									CharArrayLog(pankey_Log_EndMethod, "isFloat", "Not a float");
									return false;
								}else{
									i_has_decimal_point = true;
								}
							}
						}
						return true;
					}

					virtual void fix(){
						if(this->m_pos == this->getSize()){
							return;
						}
						for(int x = this->getPosition(); x < this->getSize(); x++){
							if(x == this->getSize() - 1){
								this->set(x, this->endValue());
							}else{
								this->set(x, ' ');
							}
						}
					}

					virtual CharArray addCharArray(const CharArray& a_CharArray)const{
						CharArrayLog(pankey_Log_StartMethod, "addCharArray", "const CharArray& a_CharArray");
						CharArray i_CharArray = *this;
						CharArrayLog(pankey_Log_EndMethod, "addCharArray", "");
						return i_CharArray.addLocalCharArray(a_CharArray);
					}

					virtual CharArray addLocalCharArray(const CharArray& a_CharArray){
						CharArrayLog(pankey_Log_StartMethod, "addLocalCharArray", "const CharArray& a_CharArray");
						CharArrayLog(pankey_Log_EndMethod, "addLocalCharArray", "");
						return this->insertLocalCharArray(this->getPosition(), a_CharArray);
					}

					virtual CharArray insertLocalCharArray(int a_position, const CharArray& a_CharArray){
						CharArrayLog(pankey_Log_StartMethod, "insertLocalCharArray", "const CharArray& a_CharArray");
						
						this->insertLocalArrayPointer(a_position, a_CharArray.pointer());
						
						CharArrayLog(pankey_Log_EndMethod, "insertLocalCharArray", "");
						return *this;
					}
					
					virtual CharArray addInt(const int& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addInt", "const int& a_number");
						CharArray i_CharArray = *this;
						CharArrayLog(pankey_Log_EndMethod, "addInt", "");
						return i_CharArray.addLocalInt(a_number);
					}

					virtual CharArray addLocalInt(const int& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addLocalInt", "const int& a_number");
						CharArrayLog(pankey_Log_EndMethod, "addLocalInt", "");
						return this->insertLocalInt(this->getPosition(), a_number);
					}

					virtual CharArray insertLocalInt(int a_position, const int& a_number){
						CharArrayLog(pankey_Log_StartMethod, "insertLocalInt", "const int& a_number");

						char* i_pointer = this->getInt(a_number);
						this->insertLocalArrayPointer(a_position, i_pointer);
						delete i_pointer;
						
						CharArrayLog(pankey_Log_EndMethod, "insertLocalInt", "");
						return *this;
					}
					
					virtual CharArray addFloat(const float& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addFloat", "const float& a_number");
						CharArray i_CharArray = *this;
						CharArrayLog(pankey_Log_EndMethod, "addFloat", "");
						return i_CharArray.addLocalFloat(a_number);
					}

					virtual CharArray addLocalFloat(const float& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addLocalFloat", "const float& a_number");
						CharArrayLog(pankey_Log_EndMethod, "addLocalFloat", "");
						return this->insertLocalFloat(this->getPosition(), a_number);
					}

					virtual CharArray insertLocalFloat(int a_position, const float& a_number){
						CharArrayLog(pankey_Log_StartMethod, "insertLocalFloat", "const float& a_CharArray");

						char* i_pointer = this->getFloat(a_number);
						this->insertLocalArrayPointer(a_position, i_pointer);
						delete i_pointer;

						CharArrayLog(pankey_Log_EndMethod, "insertLocalFloat", "");
						return *this;
					}
					
					virtual CharArray addLong(const long& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addLong", "const long& a_number");
						CharArray i_CharArray = *this;
						CharArrayLog(pankey_Log_EndMethod, "addLong", "");
						return i_CharArray.addLocalLong(a_number);
					}

					virtual CharArray addLocalLong(const long& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addLocalLong", "const long& a_number");
						CharArrayLog(pankey_Log_EndMethod, "addLocalLong", "");
						return this->insertLocalLong(this->getPosition(), a_number);
					}

					virtual CharArray insertLocalLong(int a_position, const long& a_number){
						CharArrayLog(pankey_Log_StartMethod, "insertLocalLong", "const long& a_CharArray");

						char* i_pointer = this->getLong(a_number);
						this->insertLocalArrayPointer(a_position, i_pointer);
						delete i_pointer;

						CharArrayLog(pankey_Log_EndMethod, "insertLocalLong", "");
						return *this;
					}
					
					virtual CharArray addBool(const bool& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addBool", "const bool& a_number");
						CharArray i_CharArray = *this;
						CharArrayLog(pankey_Log_EndMethod, "addBool", "");
						return i_CharArray.addLocalBool(a_number);
					}

					virtual CharArray addLocalBool(const bool& a_number){
						CharArrayLog(pankey_Log_StartMethod, "addLocalBool", "const bool& a_number");
						CharArrayLog(pankey_Log_EndMethod, "addLocalBool", "");
						return this->insertLocalBool(this->getPosition(), a_number);
					}

					virtual CharArray insertLocalBool(int a_position, const bool& a_number){
						CharArrayLog(pankey_Log_StartMethod, "insertLocalBool", "const bool& a_CharArray");

						char* i_pointer = this->getBool(a_number);
						this->insertLocalArrayPointer(a_position, i_pointer);
						delete i_pointer;
						
						CharArrayLog(pankey_Log_EndMethod, "insertLocalBool", "");
						return *this;
					}

					virtual bool isNumber(char a_char) const{
						CharArrayLog(pankey_Log_StartMethod, "isNumber", "");
						CharArrayLog(pankey_Log_EndMethod, "isNumber", "");
						return a_char > 47 && a_char < 58;
					}

					virtual int getNumber(char a_char) const{
						CharArrayLog(pankey_Log_StartMethod, "isNumber", "");
						CharArrayLog(pankey_Log_EndMethod, "isNumber", "");
						return a_char - 48;
					}

					virtual bool isDecimalPoint(char a_char) const{
						CharArrayLog(pankey_Log_StartMethod, "isNumber", "");
						CharArrayLog(pankey_Log_EndMethod, "isNumber", "");
						return a_char == 46;
					}

					bool toBool()const{
						CharArrayLog(pankey_Log_StartMethod, "toBool", "");
						if(this->length() == 1){
							if(this->get(0) == '1'){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "true");
								return true;
							}
							if(this->get(0) == '0'){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "false");
								return false;
							}
						}
						if(this->length() == 4){
							if((*this) == "true"){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "true");
								return true;
							}
							if((*this) == "TRUE"){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "false");
								return true;
							}
						}
						if(this->length() == 5){
							if((*this) == "false"){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "true");
								return false;
							}
							if((*this) == "FALSE"){
								CharArrayLog(pankey_Log_EndMethod, "toInt", "false");
								return false;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "toInt", "false");
						return false;
					}

					int toInt()const{
						CharArrayLog(pankey_Log_StartMethod, "toInt", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "toInt", "this->isEmpty()");
							return 0;
						}
						int i_start = 0;
						if(this->get(0) == '-'){
							i_start = 1;
						}
						int output = 0;
						int c_size = this->length();
						bool lastDecimals = false;
						for(int x = i_start; x < c_size; x++){
							char f_char = this->m_t_value[x];
							CharArrayLog(pankey_Log_StartMethod, "toInt", "f_char");
							CharArrayLog(pankey_Log_StartMethod, "toInt", f_char);
							if(this->isDecimalPoint(f_char)){
								if(lastDecimals){
									CharArrayLog(pankey_Log_EndMethod, "toInt", "allready has a decimal point");
									return 0;
								}
								lastDecimals = true;
								continue;
							}
							if(this->isNumber(f_char)){
								if(lastDecimals){
									
								}else{
									CharArrayLog(pankey_Log_Statement, "toInt", "int part");
									if(x != i_start){
										output *= 10;
									}
									output += (f_char - 48);
									CharArrayLog(pankey_Log_Statement, "toInt", "output");
									CharArrayLog(pankey_Log_Statement, "toInt", output);
								}
							}else{
								CharArrayLog(pankey_Log_EndMethod, "toInt", "");
								return 0;
							}
						}
						if(i_start == 1){
							output *= -1;
						}
						CharArrayLog(pankey_Log_EndMethod, "toInt", "");
						return output;
					}
					
					long toLong()const{
						CharArrayLog(pankey_Log_StartMethod, "toLong", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "toLong", "this->isEmpty()");
							return 0;
						}
						int i_start = 0;
						if(this->get(0) == '-'){
							i_start = 1;
						}
						long output = 0;
						int c_size = this->length();
						if(this->getLastChar() == 'l'){
							c_size -= 1;
						}
						bool lastDecimals = false;
						for(int x = i_start; x < c_size; x++){
							char f_char = this->m_t_value[x];
							CharArrayLog(pankey_Log_StartMethod, "toLong", "f_char");
							CharArrayLog(pankey_Log_StartMethod, "toLong", f_char);
							if(this->isDecimalPoint(f_char)){
								if(lastDecimals){
									CharArrayLog(pankey_Log_EndMethod, "toLong", "allready has a decimal point");
									return 0;
								}
								lastDecimals = true;
								continue;
							}
							if(this->isNumber(f_char)){
								if(lastDecimals){
									
								}else{
									CharArrayLog(pankey_Log_Statement, "toLong", "int part");
									if(x != i_start){
										output *= 10;
									}
									output += (f_char - 48);
									CharArrayLog(pankey_Log_Statement, "toLong", "output");
									CharArrayLog(pankey_Log_Statement, "toLong", output);
								}
							}else{
								CharArrayLog(pankey_Log_EndMethod, "toLong", "");
								return 0;
							}
						}
						if(i_start == 1){
							output *= -1;
						}
						CharArrayLog(pankey_Log_EndMethod, "toLong", "");
						return output;
					}
					
					float toFloat()const{
						CharArrayLog(pankey_Log_StartMethod, "toFloat", "");
						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "toFloat", "this->isEmpty()");
							return 0;
						}
						int i_start = 0;
						if(this->get(0) == '-'){
							i_start = 1;
						}
						float output = 0;
						int c_size = this->length();
						if(this->getLastChar() == 'f'){
							c_size -= 1;
						}
						bool lastDecimals = false;
						int lastDecimalPosition= 0;
						CharArrayLog(pankey_Log_Statement, "toFloat", "start of iteration");
						for(int x = i_start; x < c_size; x++){
							char f_char = this->m_t_value[x];
							CharArrayLog(pankey_Log_Statement, "toFloat", "f_char");
							CharArrayLog(pankey_Log_Statement, "toFloat", f_char);
							if(this->isDecimalPoint(f_char)){
								if(lastDecimals){
									CharArrayLog(pankey_Log_EndMethod, "toFloat", "allready has a decimal point");
									return 0;
								}
								lastDecimals = true;
								lastDecimalPosition= x;
								continue;
							}
							if(this->isNumber(f_char)){
								if(lastDecimals){
									CharArrayLog(pankey_Log_Statement, "toFloat", "has Decimal point");
									float expn = 1;
									for(int y = 0; y < x - lastDecimalPosition; y++){
										expn *= 10;
									}
									CharArrayLog(pankey_Log_Statement, "toFloat", "expn");
									CharArrayLog(pankey_Log_Statement, "toFloat", expn);
									output += ((float)(f_char - 48) / expn);
									CharArrayLog(pankey_Log_Statement, "toFloat", "output");
									CharArrayLog(pankey_Log_Statement, "toFloat", output);
								}else{
									CharArrayLog(pankey_Log_Statement, "toFloat", "int part");
									if(x != i_start){
										CharArrayLog(pankey_Log_Statement, "toFloat", "x != i_start");
										CharArrayLog(pankey_Log_Statement, "toFloat", "output *= 10");
										output *= 10;
										CharArrayLog(pankey_Log_Statement, "toFloat", "output");
										CharArrayLog(pankey_Log_Statement, "toFloat", output);
									}
									output += (f_char - 48);
									CharArrayLog(pankey_Log_Statement, "toFloat", "output += (f_char - 48)");
									CharArrayLog(pankey_Log_Statement, "toFloat", "output");
									CharArrayLog(pankey_Log_Statement, "toFloat", output);
								}
							}else{
								CharArrayLog(pankey_Log_EndMethod, "toFloat", "");
								return 0;
							}
						}
						if(i_start == 1){
							output *= -1;
						}
						CharArrayLog(pankey_Log_EndMethod, "toFloat", "");
						return output;
					}

					bool contain(const CharArray& a_char_array) const{
						CharArrayLog(pankey_Log_StartMethod, "contain", "");
						Array<int> i_capture;
						for(int x = 0; x < this->getPosition(); x++){
							CharArrayLog(pankey_Log_Statement, "contain", "main iteration: ");
							CharArrayLog(pankey_Log_Statement, "contain", x);
							char f_char = this->get(x);
							CharArrayLog(pankey_Log_Statement, "contain", "char to check: ");
							CharArrayLog(pankey_Log_Statement, "contain", f_char);
							for(int f_x = 0; f_x < i_capture.getPosition(); f_x++){
								CharArrayLog(pankey_Log_Statement, "contain", "second iteration: ");
								CharArrayLog(pankey_Log_Statement, "contain", f_x);
								int f_int = i_capture.get(f_x);
								f_int++;
								CharArrayLog(pankey_Log_Statement, "contain", "position to check: ");
								CharArrayLog(pankey_Log_Statement, "contain", f_int);
								if(a_char_array.getPosition() <= f_int){
									CharArrayLog(pankey_Log_Statement, "contain", "a_char_array.getPosition() <= f_int");
									CharArrayLog(pankey_Log_EndMethod, "contain", "");
									return true;
								}
								char f_second_char = a_char_array.get(f_int);
								CharArrayLog(pankey_Log_Statement, "contain", "second char to check: ");
								CharArrayLog(pankey_Log_Statement, "contain", f_second_char);
								if(f_char == f_second_char){
									CharArrayLog(pankey_Log_Statement, "contain", "f_char == f_second_char");
									if(a_char_array.getPosition() <= (f_int + 1)){
										CharArrayLog(pankey_Log_Statement, "contain", "a_char_array.getPosition() <= (f_int + 1)");
										CharArrayLog(pankey_Log_EndMethod, "contain", "");
										return true;
									}
									i_capture.set(f_x, f_int);
								}else{
									CharArrayLog(pankey_Log_Statement, "contain", "f_char != f_second_char");
									i_capture.remove(f_x);
								}
							}
							if(f_char == a_char_array.get(0)){
								CharArrayLog(pankey_Log_Statement, "contain", "f_char == a_char_array.get(0)");
								i_capture.addLocalValue(0);
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "contain", "");
						return false;
					}

					// RawList<CharArray>* split(char a_char, RawList<CharArray>* a_list) const{
					// 	CharArrayLog(pankey_Log_StartMethod, "split", "");
					// 	if(a_list == nullptr){
					// 		return nullptr;
					// 	}
					// 	CharArray i_CharArray;
					// 	for(int x = 0; x < this->getPosition(); x++){
					// 		CharArrayLog(pankey_Log_Statement, "split", "iteration: ");
					// 		CharArrayLog(pankey_Log_Statement, "split", x);
					// 		const char f_char = this->m_t_value[x];
					// 		CharArrayLog(pankey_Log_Statement, "split", "char: ");
					// 		CharArrayLog(pankey_Log_Statement, "split", f_char);
					// 		CharArrayLog(pankey_Log_Statement, "split", "i_CharArray: ");
					// 		CharArrayLog(pankey_Log_Statement, "split", i_CharArray);
					// 		if(f_char == a_char){
					// 			CharArrayLog(pankey_Log_Statement, "split", "f_char == a_char");
					// 			CharArrayLog(pankey_Log_Statement, "split", "i_CharArray: ");
					// 			CharArrayLog(pankey_Log_Statement, "split", i_CharArray);
					// 			if(i_CharArray.isEmpty()){
					// 				continue;
					// 			}
					// 			a_list->add(i_CharArray);
					// 			i_CharArray.clear();
					// 			CharArrayLog(pankey_Log_Statement, "split", "end for loop");
					// 			continue;
					// 		}
					// 		i_CharArray.addLocalValue(f_char);
					// 		CharArrayLog(pankey_Log_Statement, "split", "i_CharArray: ");
					// 		CharArrayLog(pankey_Log_Statement, "split", i_CharArray);
					// 		if(x == this->getPosition() - 1){
					// 			CharArrayLog(pankey_Log_Statement, "split", "x == this->getPosition() - 1");
					// 			CharArrayLog(pankey_Log_Statement, "split", "i_CharArray: ");
					// 			CharArrayLog(pankey_Log_Statement, "split", i_CharArray);
					// 			if(i_CharArray.isEmpty()){
					// 				continue;
					// 			}
					// 			a_list->add(i_CharArray);
					// 		}
					// 		CharArrayLog(pankey_Log_Statement, "split", "end for loop");
					// 	}
					// 	CharArrayLog(pankey_Log_EndMethod, "split", "");
					// 	return a_list;
					// }

					virtual char getLastChar() const{
						CharArrayLog(pankey_Log_StartMethod, "getLastChar", "");
						CharArrayLog(pankey_Log_Statement, "getLastChar", "");
						if(this->isEmpty()){
							return this->endValue();
						}
						CharArrayLog(pankey_Log_EndMethod, "getLastChar", "");
						return this->get(this->getPosition() - 1);
					}

					virtual void addLine(){
						CharArrayLog(pankey_Log_StartMethod, "addLine", "");
						this->addLocalValue('\n');
						CharArrayLog(pankey_Log_EndMethod, "addLine", "");
					}

					virtual bool isEndLine(const char& a_char) const{
						CharArrayLog(pankey_Log_StartMethod, "isEndLine", "");
						CharArrayLog(pankey_Log_EndMethod, "isEndLine", "");
						return a_char == '\n';
					}

					virtual int getOrder(CharArray a_CharArray, char a_split, char a_end){
						CharArrayLog(pankey_Log_StartMethod, "getOrder", "");
						CharArrayLog(pankey_Log_Statement, "getOrder", "");
						CharArray i_CharArray = "";
						int split_position = 0;
						bool addToCharArray = true;
						for(int x = 0; x < this->getPosition(); x++){
							// CharArrayLog(pankey_Log_Statement, "getOrder", "iteration: ");
							// CharArrayLog(pankey_Log_Statement, "getOrder", x);
							const char f_char = this->get(x);
							// CharArrayLog(pankey_Log_Statement, "getOrder", "char: ");
							// CharArrayLog(pankey_Log_Statement, "getOrder", f_char);
							// CharArrayLog(pankey_Log_Statement, "getOrder", "i_CharArray: ");
							// CharArrayLog(pankey_Log_Statement, "getOrder", i_CharArray);
							if(f_char == a_end){
								CharArrayLog(pankey_Log_Statement, "getOrder", "f_char == a_end");
								CharArrayLog(pankey_Log_Statement, "getOrder", "i_CharArray: ");
								CharArrayLog(pankey_Log_Statement, "getOrder", i_CharArray.pointer());
								i_CharArray = "";
								addToCharArray = true;
								CharArrayLog(pankey_Log_Statement, "getOrder", "end for loop");
								continue;
							}
							if(f_char == a_split){
								CharArrayLog(pankey_Log_Statement, "getOrder", "f_char == a_split");
								CharArrayLog(pankey_Log_Statement, "getOrder", "i_CharArray: ");
								CharArrayLog(pankey_Log_Statement, "getOrder", i_CharArray.pointer());
								CharArrayLog(pankey_Log_Statement, "getOrder", "split_position: ");
								CharArrayLog(pankey_Log_Statement, "getOrder", split_position);
								if(a_CharArray == i_CharArray){
									CharArrayLog(pankey_Log_Statement, "getOrder", "a_CharArray == i_CharArray");
									return split_position;
								}
								split_position++;
								i_CharArray = "";
								addToCharArray = false;
								CharArrayLog(pankey_Log_Statement, "getOrder", "end for loop");
								continue;
							}
							if(addToCharArray){
								i_CharArray.addLocalValue(f_char);
							}
							// CharArrayLog(pankey_Log_Statement, "getOrder", "i_CharArray: ");
							// CharArrayLog(pankey_Log_Statement, "getOrder", i_CharArray);
							// CharArrayLog(pankey_Log_Statement, "getOrder", "end for loop");
						}
						CharArrayLog(pankey_Log_EndMethod, "getOrder", "");
						return -1;
					}

					int getSizeNoStartNoEnd(char a_split){
						CharArrayLog(pankey_Log_StartMethod, "getSizeNoStartNoEnd", "");
						CharArrayLog(pankey_Log_Statement, "getSizeNoStartNoEnd", "~CharArray");
						int i_size = 0;
						for(int x = 0; x < length(); x++){
							char f_char = this->get(x);
							if(f_char == a_split){
								i_size++;
								continue;
							}
						}

						CharArrayLog(pankey_Log_EndMethod, "getSizeNoStartNoEnd", "");
						return i_size + 1;
					}

					int getLineSize(){
						CharArrayLog(pankey_Log_StartMethod, "getLineSize", "");
						CharArrayLog(pankey_Log_Statement, "getLineSize", "");
						int i_size = 0;
						int x_c = 0;
						for(int x = 0; x < getPosition(); x++){
							char f_char = this->get(x);
							if(f_char == '\n'){
								i_size++;
								x_c = 0;
								continue;
							}
							x_c++;
						}
						if(x_c == 0){
							return i_size;
						}
						if(x_c > 0){
							return i_size + 1;
						}
						CharArrayLog(pankey_Log_EndMethod, "getLineSize", "");
						return i_size;
					}

					CharArray getLine(int l, char end){
						CharArrayLog(pankey_Log_StartMethod, "getLine", "");
						CharArrayLog(pankey_Log_Statement, "getLine", "");
						CharArray c = "";
						int i_size = 0;
						for(int x = 0; x < length(); x++){
							char f_char = this->get(x);
							if(f_char == end){
								if(i_size == l){
									CharArrayLog(pankey_Log_EndMethod, "getLine", "");
									return c;
								}
								c = "";
								i_size++;
								continue;
							}
							c.addLocalValue(f_char);
						}

						CharArrayLog(pankey_Log_EndMethod, "getLine", "");
						return CharArray();
					}

					void removeLine(int a_line, char a_end){
						CharArrayLog(pankey_Log_StartMethod, "removeLine", "");
						CharArrayLog(pankey_Log_Statement, "removeLine", "");
						if(a_line == -1){
							CharArrayLog(pankey_Log_EndMethod, "removeLine", "");
							return;
						}
						CharArray i_newTxt;
						int xLine = 0;
						for(int x = 0; x < length(); x++){
							char f_char = this->get(x);
							if(f_char == a_end){
								xLine++;
								if(i_newTxt == ""){
									continue;
								}
								char cnewTxt = i_newTxt.get(i_newTxt.length()-1);
								if(!i_newTxt.isEmpty() && cnewTxt != a_end){
									i_newTxt.addLocalValue(a_end);
								}
								continue;
							}
							if(xLine != a_line){
								i_newTxt.addLocalValue(f_char);
							}
						}

						CharArrayLog(pankey_Log_EndMethod, "removeLine", "");
						this->clear();
						this->addLocalCharArray(i_newTxt);
					}

					void removeLine(CharArray a_txt, char a_split, char a_end){
						CharArrayLog(pankey_Log_StartMethod, "removeLine", "");
						CharArrayLog(pankey_Log_Statement, "removeLine", "~CharArray");
						int i_order = getOrder(a_txt, a_split, a_end);
						if(i_order == -1){
							CharArrayLog(pankey_Log_EndMethod, "removeLine", "");
							return;
						}
						removeLine(i_order, a_end);

						CharArrayLog(pankey_Log_EndMethod, "removeLine", "");
					}

					void writeLine(int line, CharArray txt, char end){
						CharArrayLog(pankey_Log_StartMethod, "writeLine", "");
						CharArrayLog(pankey_Log_Statement, "writeLine", "");
						CharArray newTxt = "";
						int xLine = 0;
						int xTxt = 0;
						int xText = 0;
						for(int x = 0; x < length() + txt.length(); x++){
							char ctext = get(xText);
							char ctxt = txt.get(xTxt);
							if(ctext == end){
								xLine++;
								xText++;
								newTxt.addLocalValue(end);
								continue;
							}
							if((xLine == line || xText >= length())){
								newTxt.addLocalValue(ctxt);
								xTxt++;
								if(xTxt == txt.length()){
									newTxt.addLocalValue('\n');
									xLine++;
								}
							}else{
								newTxt.addLocalValue(ctext);
								xText++;
							}
						}
						
						this->clear();
						this->addLocalCharArray(newTxt);

						CharArrayLog(pankey_Log_EndMethod, "writeLine", "");
					}

					void writeLine(CharArray cmdt, CharArray txt, char split, char end){
						CharArrayLog(pankey_Log_StartMethod, "writeLine", "");
						CharArrayLog(pankey_Log_Statement, "writeLine", "~CharArray");
						int line = getOrder(cmdt, split, end);
						if(line == -1){
							CharArrayLog(pankey_Log_EndMethod, "writeLine", "");
							return;
						}
						writeLine(line, txt, end);
						removeLine(line + 1, end);

						CharArrayLog(pankey_Log_EndMethod, "writeLine", "");
					}

					CharArray getCommand(int l, char split, char end){
						CharArrayLog(pankey_Log_StartMethod, "getCommand", "");
						CharArrayLog(pankey_Log_Statement, "getCommand", "~CharArray");
						CharArray c = "";
						bool init = true;
						int gcmd = 0;
						for(int x = 0; x < length(); x++){
							char cr = get(x);
							if(cr == end){
								if(gcmd == l){
									CharArrayLog(pankey_Log_EndMethod, "getCommand", "");
									return c;
								}
								init = true;
								gcmd++;
								c = "";
								continue;
							}
							if(init){
								if(cr == split){
									if(gcmd == l){
										CharArrayLog(pankey_Log_EndMethod, "getCommand", "");
										return c;
									}
									init = false;
									c = "";
									continue;
								}
								c.addLocalValue(cr);
							}
						}

						CharArrayLog(pankey_Log_EndMethod, "getCommand", "");
						return "";
					}

					CharArray getArgument(int l, char split, char end){
						CharArrayLog(pankey_Log_StartMethod, "getArgument", "");
						CharArrayLog(pankey_Log_Statement, "getArgument", "~CharArray");
						CharArray c = "";
						bool init = false;
						int gcmd = 0;
						for(int x = 0; x < length(); x++){
							char cr = get(x);
							if(cr == end){
								if(gcmd == l){
									CharArrayLog(pankey_Log_EndMethod, "getArgument", "");
									return c;
								}
								gcmd++;
								c = "";
								init = false;
								continue;
							}
							if(cr == split && !init){
								init = true;
								continue;
							}
							if(init && gcmd == l){
								c.addLocalValue(cr);
							}
						}
						if(gcmd == l){
							CharArrayLog(pankey_Log_EndMethod, "getArgument", "");
							return c;
						}

						CharArrayLog(pankey_Log_EndMethod, "getArgument", "");
						return CharArray();
					}
					
					virtual int getIndex(CharArray a_search){
						CharArrayLog(pankey_Log_StartMethod, "getIndex", "");
						CharArray i_CharArray;
						int i_index = 0;
						int i_CharArray_count = 0;
						for(int x = 0; x < this->getPosition(); x++){
							char f_char = this->get(x);
							CharArrayLog(pankey_Log_StartMethod, "getIndex", "f_char");
							CharArrayLog(pankey_Log_StartMethod, "getIndex", f_char);
							i_CharArray.addLocalValue(f_char);
							char f_char_search = a_search.get(i_CharArray_count);
							char f_char_record = i_CharArray.get(i_CharArray_count);
							if(f_char_search == f_char_record){
								CharArrayLog(pankey_Log_StartMethod, "getIndex", "f_char_search == f_char_record");
								if(i_CharArray_count == 0){
									i_index = x;
								}
								i_CharArray_count++;
							}else{
								i_CharArray_count = 0;
								i_CharArray.clear();
								continue;
							}
							if(a_search == i_CharArray){
								CharArrayLog(pankey_Log_StartMethod, "getIndex", "a_search == i_CharArray");
								return i_index;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "getIndex", "-1");
						return -1;
					}
					
					virtual int getIndex(int a_repetitions, CharArray a_search){
						CharArrayLog(pankey_Log_StartMethod, "getIndex", "");
						CharArray i_CharArray;
						int i_index = 0;
						int i_CharArray_count = 0;
						int i_repite_count = 0;
						for(int x = 0; x < this->getPosition(); x++){
							char f_char = this->get(x);
							CharArrayLog(pankey_Log_StartMethod, "getIndex", "f_char");
							CharArrayLog(pankey_Log_StartMethod, "getIndex", f_char);
							i_CharArray.addLocalValue(f_char);
							char f_char_search = a_search.get(i_CharArray_count);
							char f_char_record = i_CharArray.get(i_CharArray_count);
							if(f_char_search == f_char_record){
								CharArrayLog(pankey_Log_StartMethod, "getIndex", "f_char_search == f_char_record");
								if(i_CharArray_count == 0){
									i_index = x;
								}
								i_CharArray_count++;
							}else{
								i_CharArray_count = 0;
								i_CharArray.clear();
								continue;
							}
							if(a_search == i_CharArray){
								CharArrayLog(pankey_Log_StartMethod, "getIndex", "a_search == i_CharArray");
								if(i_repite_count != a_repetitions){
									CharArrayLog(pankey_Log_StartMethod, "getIndex", "i_repite_count != a_repetitions");
									i_repite_count++;
									continue;
								}
								return i_index;
							}
						}
						CharArrayLog(pankey_Log_EndMethod, "getIndex", "-1");
						return -1;
					}
					
					virtual bool removeCharArray(CharArray a_CharArray){
						CharArrayLog(pankey_Log_StartMethod, "removeCharArray", "");
						int i_index = this->getIndex(a_CharArray);
						if(i_index == -1){
							return false;
						}
						this->remove(i_index, a_CharArray.getPosition());
						CharArrayLog(pankey_Log_EndMethod, "removeCharArray", "");
						return false;
					}

					virtual bool replace(CharArray a_search, CharArray a_change){
						CharArrayLog(pankey_Log_StartMethod, "replace", "");
						CharArrayLog(pankey_Log_Statement, "replace", "a_search");
						CharArrayLog(pankey_Log_Statement, "replace", a_search.pointer());
						CharArrayLog(pankey_Log_Statement, "replace", "a_change");
						CharArrayLog(pankey_Log_Statement, "replace", a_change.pointer());
						CharArray i_CharArray;
						CharArray i_search;
						int i_search_index = 0;

						if(this->isEmpty()){
							CharArrayLog(pankey_Log_EndMethod, "replace", "this->isEmpty()");
							return false;
						}
						int i_index = this->getIndex(a_search);
						CharArrayLog(pankey_Log_Statement, "replace", "i_index");
						CharArrayLog(pankey_Log_Statement, "replace", i_index);
						if(i_index == -1){
							CharArrayLog(pankey_Log_EndMethod, "replace", "i_index == -1");
							return false;
						}
						this->remove(i_index, a_search.getPosition());
						this->insertLocalCharArray(i_index, a_change);
						CharArrayLog(pankey_Log_EndMethod, "replace", "");
						return true;
					}

					virtual CharArray& operator=(const CharArray& source){
						CharArrayLog(pankey_Log_StartMethod, "operator=", "");
						this->clear();
						CharArrayLog(pankey_Log_Statement, "operator=", "const CharArray& val");
						int i_array_length = source.length();
						if(i_array_length > 0){
							this->m_size = this->getAvailableSize(i_array_length);
							this->m_t_value = this->create(this->m_size);
							this->copyPointer(source.m_t_value, i_array_length);
							this->copyEndValue(this->getPosition());
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Length:");
							CharArrayLog(pankey_Log_Statement, "operator=", i_array_length);
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Position:");
							CharArrayLog(pankey_Log_Statement, "operator=", this->getPosition());
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Size:");
							CharArrayLog(pankey_Log_Statement, "operator=", this->getSize());
						}
						CharArrayLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual CharArray& operator=(CharArray&& source){
						this->clear();
						CharArrayLog(pankey_Log_StartMethod, "operator=", "");
						CharArrayLog(pankey_Log_Statement, "operator=", "const CharArray& val");
						int i_array_length = source.length();
						if(i_array_length > 0){
							this->m_pos = source.m_pos;
							this->m_size = source.m_size;
							this->m_t_value = source.m_t_value;
							source.m_t_value = nullptr;
							source.m_pos = 0;
							source.m_size = 0;
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Length:");
							CharArrayLog(pankey_Log_Statement, "operator=", i_array_length);
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Position:");
							CharArrayLog(pankey_Log_Statement, "operator=", this->getPosition());
							CharArrayLog(pankey_Log_Statement, "operator=", "Array Size:");
							CharArrayLog(pankey_Log_Statement, "operator=", this->getSize());
						}
						CharArrayLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual CharArray operator+=(const CharArray& a_CharArray){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalCharArray(a_CharArray);
					}

					virtual CharArray operator+=(const char* a_char){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalArrayPointer(a_char);
					}
			/*
					virtual CharArray operator+=(const char& a_char){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalValue(a_char);
					}
			*/
					virtual CharArray operator+=(const bool& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalBool(a_value);
					}

					virtual CharArray operator+=(const int& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalInt(a_value);
					}

					virtual CharArray operator+=(const long& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalLong(a_value);
					}

					virtual CharArray operator+=(const float& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+=", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalFloat(a_value);
					}

					virtual CharArray operator+(const CharArray& a_CharArray)const{
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addCharArray(a_CharArray);
					}

					virtual CharArray operator+(char* a_CharArray)const{
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addArrayPointer(a_CharArray);
					}
			/*
					virtual CharArray operator+(const char& a_CharArray){
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addValue(a_CharArray);
					}
			*/
					virtual CharArray operator+(const bool& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addBool(a_value);
					}

					virtual CharArray operator+(const int& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addInt(a_value);
					}

					virtual CharArray operator+(const long& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addLong(a_value);
					}

					virtual CharArray operator+(const float& a_value){
						CharArrayLog(pankey_Log_StartMethod, "operator+", "");
						CharArrayLog(pankey_Log_EndMethod, "operator+", "");
						return this->addFloat(a_value);
					}

					virtual CharArray operator-=(const int& a_remove){
						if(this->isEmpty()){
							return *this;
						}

						return *this;
					}

					virtual CharArray operator-(const int& a_remove){
						CharArray i_value = *this;
						i_value-=(a_remove);
						return i_value;
					}

					virtual CharArray operator--(){

						return *this;
					}

					virtual bool operator==(const CharArray& a_CharArray) const{
						if(a_CharArray.length() != this->length()){
							return false;
						}
						for(int x = 0; x < this->length(); x++){
							char f_char_1 = this->get(x);
							char f_char_2 = a_CharArray.get(x);
							if(f_char_1 != f_char_2){
								return false;
							}
						}
						return true;
					}

					virtual bool operator!=(const CharArray& a_CharArray)const{
						if(a_CharArray.length() != this->length()){
							return true;
						}
						for(int x = 0; x < this->length(); x++){
							char f_char_1 = this->get(x);
							char f_char_2 = a_CharArray.get(x);
							if(f_char_1 == f_char_2){
								return false;
							}
						}
						return true;
					}

			};

		}

	}

#endif