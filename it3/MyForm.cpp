#include "MyForm.h"

#define _USE_MATH_DEFINES 


//#include "function.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array <String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	it3::MyForm form;
	Application::Run(% form);
}


