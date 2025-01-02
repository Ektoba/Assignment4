#pragma once
#define SINGLE(TYPE) friend class CSingleton<TYPE>;\
					 private:\
						TYPE();\
						virtual ~TYPE() override;	
#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__, __LINE)
#endif
