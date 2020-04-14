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
	public:		 Answer(Matrix &m, std::vector<int>& where, System::String^ name)
		{
			InitializeComponent();
			this->Text = name;
			this->matrix->ColumnCount = m.getColumns() + 1;
			this->matrix->RowCount = m.getColumns();

			for (int i = 0; i < matrix->RowCount; i++) {
				for (int j = 0; j < matrix->ColumnCount - 1; j++)
					matrix->Rows[i]->Cells[j]->Value = System::Convert::ToString(Math::Round(m.getElement(i, j), 3));
				matrix->Rows[i]->Cells[matrix->Columns->Count - 1]->Value = System::Convert::ToString(Math::Round(m.getEquivalent(i), 3));
			}

			for (int i = 0; i < matrix->ColumnCount - 1; i++) {
				matrix->Columns[i]->Name = "x(" + Convert::ToString(i + 1) + ")";
			}
			matrix->Columns[matrix->ColumnCount - 1]->Name = "b";
			matrix->AutoResizeColumns();

			try {
				std::vector<double> answer;
				int type = m.backIter(where ,answer);
				int counter = 0;
				if (type == 2) {
					std::vector<int> emptyIndexesHolder;
					for (int i = 0; i < answer.size(); i++) {
						if (where[i] == -1) RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + "arbitrary real number\n";
						else RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + Convert::ToString(Math::Round(answer[i], 3)) + "\n";
					}
				}
				else if (type) {
					for (auto el : answer) {
						RTB->Text += "x(" + Convert::ToString(++counter) + ") = " + Convert::ToString(Math::Round(el, 3)) + "\n";
					}
				}
				else RTB->Text = "You're a DARK MAGE, how in the world you broke my program";
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
	private: System::Windows::Forms::DataGridView^  matrix;

	protected:

	protected:




	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::RichTextBox^  RTB;
	protected:

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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->matrix = (gcnew System::Windows::Forms::DataGridView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->RTB = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->matrix))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// matrix
			// 
			this->matrix->AllowUserToAddRows = false;
			this->matrix->AllowUserToDeleteRows = false;
			this->matrix->AllowUserToResizeColumns = false;
			this->matrix->AllowUserToResizeRows = false;
			this->matrix->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->matrix->BackgroundColor = System::Drawing::SystemColors::ActiveCaption;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->matrix->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->matrix->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->matrix->Location = System::Drawing::Point(572, 344);
			this->matrix->Name = L"matrix";
			this->matrix->ReadOnly = true;
			this->matrix->RowHeadersVisible = false;
			this->matrix->RowTemplate->Height = 28;
			this->matrix->Size = System::Drawing::Size(856, 450);
			this->matrix->StandardTab = true;
			this->matrix->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 622);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(366, 82);
			this->label2->TabIndex = 3;
			this->label2->Text = L"The Roots";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 40, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(840, 236);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(588, 91);
			this->label1->TabIndex = 4;
			this->label1->Text = L"FINAL MATRIX";
			// 
			// RTB
			// 
			this->RTB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->RTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RTB->Location = System::Drawing::Point(12, 48);
			this->RTB->Name = L"RTB";
			this->RTB->ReadOnly = true;
			this->RTB->Size = System::Drawing::Size(352, 571);
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
			this->menuStrip1->Size = System::Drawing::Size(1478, 33);
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
			this->menuToolStripMenuItem->Size = System::Drawing::Size(69, 29);
			this->menuToolStripMenuItem->Text = L"Menu";
			// 
			// infoToolStripMenuItem
			// 
			this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			this->infoToolStripMenuItem->Size = System::Drawing::Size(183, 30);
			this->infoToolStripMenuItem->Text = L"Info";
			this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Answer::infoToolStripMenuItem_Click);
			// 
			// saveToFileToolStripMenuItem
			// 
			this->saveToFileToolStripMenuItem->Name = L"saveToFileToolStripMenuItem";
			this->saveToFileToolStripMenuItem->Size = System::Drawing::Size(183, 30);
			this->saveToFileToolStripMenuItem->Text = L"Save to file";
			this->saveToFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Answer::saveToFileToolStripMenuItem_Click);
			// 
			// Answer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(1478, 844);
			this->Controls->Add(this->RTB);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->matrix);
			this->Controls->Add(this->menuStrip1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->MainMenuStrip = this->menuStrip1;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(1500, 900);
			this->Name = L"Answer";
			this->Text = L"Solution";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->matrix))->EndInit();
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
	std::ofstream out;
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
	out << "FINAL MATRIX\n" << m <<"\n Answer\n"<< answer;
}
};
}