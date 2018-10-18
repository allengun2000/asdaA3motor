#include "MyForm.h"

using namespace ±±°¨¹FasdaA3;
using namespace System;
[STAThread]
int main(cli::array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
	return 0;
}