#pragma once
using namespace System;
using namespace System::Windows::Forms;
ref class ProgramEntry
{
	[STAThreadAttribute]
	void Main(array<String^>^ args) {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew MainWindow());
	}
};

