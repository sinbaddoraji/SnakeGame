#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace BasicSnakeGame {

	/// <summary>
	/// Summary for GameBoard
	/// </summary>
	public ref class GameBoard : public System::Windows::Forms::UserControl
	{
	public:
		int x;
		int y;
		Graphics^ g;
		System::Collections::Generic::List<String^>^ snakeParts;

		GameBoard(void)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			DoubleBuffered = true;
		}

		void PaintPoint(int x, int y)
		{
			Rectangle r(x * 15, y * 15, 15, 15);
			g->FillRectangle(System::Drawing::Brushes::Blue, r);
		}

		void ClearGrid()
		{
			g->Clear(System::Drawing::Color::Black);
		}

		void Move(int direction);

		void StartGame();
		void PaintToGrid();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameBoard()
		{
			if (components)
			{
				delete components;
			}
		}

private: System::Windows::Forms::Timer^ gameTimer;


private: System::ComponentModel::IContainer^ components;
	protected:

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
			this->components = (gcnew System::ComponentModel::Container());
			this->gameTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// gameTimer
			// 
			this->gameTimer->Interval = 150;
			this->gameTimer->Tick += gcnew System::EventHandler(this, &GameBoard::gameTimer_Tick);
			// 
			// GameBoard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->MaximumSize = System::Drawing::Size(800, 800);
			this->MinimumSize = System::Drawing::Size(800, 800);
			this->Name = L"GameBoard";
			this->Size = System::Drawing::Size(800, 800);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameBoard::GameBoard_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void gameTimer_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void GameBoard_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
};
}
