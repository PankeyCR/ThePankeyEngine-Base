
#ifndef MethodErrorHandler_hpp
	#define MethodErrorHandler_hpp

	#include "InvokeMethod.hpp"

	namespace pankey{

		namespace Base{

			template<class E>
			class MethodErrorHandler{
				public:
					static void setHandler(InvokeMethodReturn<bool,int> a_error_handler){
						m_error_handler = a_error_handler;
					}
					
					static bool handle(int a_alert){
						return invoke(m_error_handler, a_alert);
					}

					static void setAlert(InvokeMethod<int> a_error_alert){
						m_error_alert = a_error_alert;
					}

					static void alert(int status, const CharArray& name, const CharArray& method, L mns){
						invoke(m_error_alert, a_alert);
					}
				
				protected:
					static InvokeMethodReturn<bool,int> m_error_handler;
					static InvokeMethod<int> m_error_alert;
			};

			InvokeMethodReturn<bool,int> MethodErrorHandler::m_error_handler = nullptr;
			InvokeMethod<int> MethodErrorHandler::m_error_alert = nullptr;

		}

	}

	#ifndef pankey_ErrorHandler_set
		#define pankey_ErrorHandler_set(S) MethodErrorHandler::setHandler(S);
	#endif 

	#ifndef pankey_ErrorAlert_set
		#define pankey_ErrorAlert_set(S) MethodErrorHandler::setAlert(S);
	#endif 

	#ifndef pankey_Error_Handle
		#define pankey_Error_Handle(status,name,method,mns) MethodErrorHandler::handle(a_error);
	#endif

	#ifndef pankey_Error_Alert
		#define pankey_Error_Alert(status,name,method,mns) MethodErrorHandler::alert(a_error);
	#endif 

#endif