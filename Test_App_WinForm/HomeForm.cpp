#include "HomeForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array <String^>^ args) {  // ^^ - эти скопки для автоматического удаления массива
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();  // подключение визуальных стилей

	TestAppWinForm::HomeForm home;

	Application::Run(% home);  // рендеринг приложения

}