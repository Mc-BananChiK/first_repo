#include "HomeForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array <String^>^ args) {  // ^^ - ��� ������ ��� ��������������� �������� �������
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();  // ����������� ���������� ������

	TestAppWinForm::HomeForm home;

	Application::Run(% home);  // ��������� ����������

}