#include "MainWindow.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BasicSnakeGame::MainWindow mainWindow;
	Application::Run(% mainWindow);
}

System::Void BasicSnakeGame::MainWindow::MainWindow_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	
	return System::Void();
}
