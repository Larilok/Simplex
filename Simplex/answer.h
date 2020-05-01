#pragma once
#include "about.h"
#include <fstream>
#include <vcclr.h>
#include <cstring>
#include "main.h"
#include <string>
#include <sstream>

namespace Simplex {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void Str2CharPtr(String ^str, char* chrPtr)
	{
		// Pin memory so GC can't move it while native function is called
		pin_ptr<const wchar_t> wchPtr = PtrToStringChars(str);

		// Convert wchar_t* to char*
		size_t  convertedChars = 0;
		size_t  sizeInBytes = ((str->Length + 1) * 2);

		wcstombs_s(&convertedChars, chrPtr, sizeInBytes, wchPtr, sizeInBytes);
	}


	/// <summary>
	/// Summary for Answer
	/// </summary>
	public ref class Answer : public System::Windows::Forms::Form
	{
	public:

	static int GaussAm = 0, Jorge_GaussAm = 0, Givens_Rotation = 0;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  menuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  infoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToFileToolStripMenuItem;
	public:		 Answer(Matrix &m, std::stringstream& logs, std::vector<size_t>& basis_indexes)
		{
			InitializeComponent();
			this->Text = "Full solution";
			try {
				const std::string& tmp = logs.str();
				const char* cstr = tmp.c_str();
				RTB->Text += gcnew System::String(cstr);
				//std::vector<Fraction> answer;
				//int type = m.backIter(basis_indexes ,answer);
				//int counter = 0;
				//if (type == 2) {
				//	std::vector<int> emptyIndexesHolder;
				//	for (int i = 0; i < answer.size(); i++) {
				//		if (where[i] == -1) RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + "arbitrary real number\n";
				//		else RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + Convert::ToString(answer[i]) + "\n";
				//	}
				//}
				//else if (type) {
				//	for (auto el : answer) {
				//		RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + Convert::ToString(el) + "\n";
				//	}
				//}
				//else RTB->Text = "You're a DARK MAGE, how in the world you broke my program";
			}
			catch (std::exception e) {
				RTB->Text = Convert::ToString(e.what());
			}
			catch (...) {
				RTB->Text = "Unexpected error";
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Answer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  RTB;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->RTB = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// RTB
			// 
			this->RTB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->RTB->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->RTB->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->RTB->Location = System::Drawing::Point(15, 50);
			this->RTB->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->RTB->Name = L"RTB";
			this->RTB->ReadOnly = true;
			this->RTB->Size = System::Drawing::Size(717, 490);
			this->RTB->TabIndex = 5;
			this->RTB->Text = L"";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->menuToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(784, 24);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// menuToolStripMenuItem
			// 
			this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->infoToolStripMenuItem,
					this->saveToFileToolStripMenuItem
			});
			this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
			this->menuToolStripMenuItem->Size = System::Drawing::Size(50, 22);
			this->menuToolStripMenuItem->Text = L"Menu";
			// 
			// infoToolStripMenuItem
			// 
			this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			this->infoToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->infoToolStripMenuItem->Text = L"Info";
			this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Answer::infoToolStripMenuItem_Click);
			// 
			// saveToFileToolStripMenuItem
			// 
			this->saveToFileToolStripMenuItem->Name = L"saveToFileToolStripMenuItem";
			this->saveToFileToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->saveToFileToolStripMenuItem->Text = L"Save to file";
			this->saveToFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Answer::saveToFileToolStripMenuItem_Click);
			// 
			// Answer
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->RTB);
			this->Controls->Add(this->menuStrip1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"Answer";
			this->Text = L"Solution";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

private: System::Void infoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	about^info = gcnew about();
	info->ShowDialog();
}
private: System::Void saveToFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	/*std::ofstream out;
	char outputFile[20];
	Str2CharPtr(this->Text, outputFile);
	
	Matrix m(matrix->RowCount, matrix->ColumnCount - 1);
	m.copy(matrix);

	int index;
	if (strcmp(outputFile,"Gauss")) {
		index = ++GaussAm;
	}
	else if (strcmp(outputFile, "Gauss_Jordan")) {
		index = ++Jorge_GaussAm;
	}
	else index = ++Givens_Rotation;

	char answer[256];
	std::string outFile(outputFile);

	std::string s;
	std::stringstream outt;
	outt << index;
	s = outt.str();
	out.open(outFile+ "("+ s +")"+".txt", std::fstream::out);
	Str2CharPtr(this->RTB->Text, answer);
	out << "FINAL MATRIX\n" << m <<"\n Answer\n"<< answer;*/
}
};
}