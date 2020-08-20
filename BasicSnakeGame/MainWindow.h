#pragma once
#include "GameBoard.h"

namespace BasicSnakeGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		BasicSnakeGame::GameBoard^ gB;
		MainWindow(void)
		{
			InitializeComponent();
			gB = gcnew BasicSnakeGame::GameBoard;
			//gB->Left = (Width - gB->Width) / 2;
		
			gB->BackColor = Color::Black;
			gB->BorderStyle = BorderStyle::FixedSingle;
			gB->Focus();
			this->Controls->Add(gB);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(782, 753);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::MainWindow_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MainWindow_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
	};
}
