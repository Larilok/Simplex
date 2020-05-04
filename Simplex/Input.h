#pragma once
#include "Matrix.h"
#include "answer.h"
#include "about.h"

namespace Simplex {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Input
	/// </summary>
	public ref class Input : public System::Windows::Forms::Form
	{
	public:
		Input(void)
		{
			InitializeComponent();
		}

	protected:
		~Input()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ restrictions_table;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ infoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;

	private: System::Windows::Forms::NumericUpDown^ VariablesNum;
	private: System::Windows::Forms::NumericUpDown^ RestrictionsNum;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ targetFunction;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::RadioButton^ min_b;

	private: System::Windows::Forms::RadioButton^ max_b;

	private: System::Windows::Forms::Label^ label4;

	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Input::typeid));
			   System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			   System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			   System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			   this->VariablesNum = (gcnew System::Windows::Forms::NumericUpDown());
			   this->restrictions_table = (gcnew System::Windows::Forms::DataGridView());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->RestrictionsNum = (gcnew System::Windows::Forms::NumericUpDown());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->targetFunction = (gcnew System::Windows::Forms::DataGridView());
			   this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			   this->min_b = (gcnew System::Windows::Forms::RadioButton());
			   this->max_b = (gcnew System::Windows::Forms::RadioButton());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VariablesNum))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->restrictions_table))->BeginInit();
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RestrictionsNum))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetFunction))->BeginInit();
			   this->groupBox2->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // VariablesNum
			   // 
			   resources->ApplyResources(this->VariablesNum, L"VariablesNum");
			   this->VariablesNum->BackColor = System::Drawing::SystemColors::InactiveCaption;
			   this->VariablesNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			   this->VariablesNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			   this->VariablesNum->Name = L"VariablesNum";
			   this->VariablesNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			   this->VariablesNum->ValueChanged += gcnew System::EventHandler(this, &Input::VariablesNum_ValueChanged);
			   // 
			   // restrictions_table
			   // 
			   this->restrictions_table->AllowUserToAddRows = false;
			   this->restrictions_table->AllowUserToDeleteRows = false;
			   this->restrictions_table->AllowUserToResizeColumns = false;
			   this->restrictions_table->AllowUserToResizeRows = false;
			   dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			   dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			   dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			   dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			   dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			   dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			   this->restrictions_table->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			   this->restrictions_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			   dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			   dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			   dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			   dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			   dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			   this->restrictions_table->DefaultCellStyle = dataGridViewCellStyle2;
			   resources->ApplyResources(this->restrictions_table, L"restrictions_table");
			   this->restrictions_table->Name = L"restrictions_table";
			   this->restrictions_table->RowHeadersVisible = false;
			   this->restrictions_table->RowTemplate->Height = 28;
			   this->restrictions_table->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			   this->restrictions_table->StandardTab = true;
			   this->restrictions_table->CellValidating += gcnew System::Windows::Forms::DataGridViewCellValidatingEventHandler(this, &Input::restrictions_table_CellValidating);
			   // 
			   // label2
			   // 
			   resources->ApplyResources(this->label2, L"label2");
			   this->label2->Name = L"label2";
			   // 
			   // button1
			   // 
			   resources->ApplyResources(this->button1, L"button1");
			   this->button1->BackColor = System::Drawing::SystemColors::HotTrack;
			   this->button1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			   this->button1->Name = L"button1";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &Input::button1_Click);
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->infoToolStripMenuItem });
			   resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			   this->menuStrip1->Name = L"menuStrip1";
			   // 
			   // infoToolStripMenuItem
			   // 
			   this->infoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			   this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			   resources->ApplyResources(this->infoToolStripMenuItem, L"infoToolStripMenuItem");
			   // 
			   // aboutToolStripMenuItem
			   // 
			   this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			   resources->ApplyResources(this->aboutToolStripMenuItem, L"aboutToolStripMenuItem");
			   this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Input::aboutToolStripMenuItem_Click);
			   // 
			   // RestrictionsNum
			   // 
			   resources->ApplyResources(this->RestrictionsNum, L"RestrictionsNum");
			   this->RestrictionsNum->BackColor = System::Drawing::SystemColors::InactiveCaption;
			   this->RestrictionsNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			   this->RestrictionsNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			   this->RestrictionsNum->Name = L"RestrictionsNum";
			   this->RestrictionsNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			   this->RestrictionsNum->ValueChanged += gcnew System::EventHandler(this, &Input::restrictionNum_ValueChanged);
			   // 
			   // label3
			   // 
			   resources->ApplyResources(this->label3, L"label3");
			   this->label3->Name = L"label3";
			   // 
			   // label1
			   // 
			   resources->ApplyResources(this->label1, L"label1");
			   this->label1->Name = L"label1";
			   // 
			   // targetFunction
			   // 
			   this->targetFunction->AllowUserToAddRows = false;
			   this->targetFunction->AllowUserToDeleteRows = false;
			   this->targetFunction->AllowUserToResizeColumns = false;
			   this->targetFunction->AllowUserToResizeRows = false;
			   resources->ApplyResources(this->targetFunction, L"targetFunction");
			   dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			   dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			   dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			   dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			   dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			   dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			   this->targetFunction->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle3;
			   this->targetFunction->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->targetFunction->Name = L"targetFunction";
			   this->targetFunction->RowHeadersVisible = false;
			   this->targetFunction->RowTemplate->Height = 28;
			   this->targetFunction->StandardTab = true;
			   this->targetFunction->CellValidating += gcnew System::Windows::Forms::DataGridViewCellValidatingEventHandler(this, &Input::targetFunction_CellValidating);
			   // 
			   // groupBox2
			   // 
			   resources->ApplyResources(this->groupBox2, L"groupBox2");
			   this->groupBox2->Controls->Add(this->min_b);
			   this->groupBox2->Controls->Add(this->max_b);
			   this->groupBox2->Name = L"groupBox2";
			   this->groupBox2->TabStop = false;
			   // 
			   // min_b
			   // 
			   resources->ApplyResources(this->min_b, L"min_b");
			   this->min_b->Name = L"min_b";
			   this->min_b->UseVisualStyleBackColor = true;
			   // 
			   // max_b
			   // 
			   resources->ApplyResources(this->max_b, L"max_b");
			   this->max_b->Checked = true;
			   this->max_b->Name = L"max_b";
			   this->max_b->TabStop = true;
			   this->max_b->UseVisualStyleBackColor = true;
			   // 
			   // label4
			   // 
			   resources->ApplyResources(this->label4, L"label4");
			   this->label4->Name = L"label4";
			   // 
			   // Input
			   // 
			   resources->ApplyResources(this, L"$this");
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->targetFunction);
			   this->Controls->Add(this->restrictions_table);
			   this->Controls->Add(this->groupBox2);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->RestrictionsNum);
			   this->Controls->Add(this->VariablesNum);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Name = L"Input";
			   this->Load += gcnew System::EventHandler(this, &Input::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VariablesNum))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->restrictions_table))->EndInit();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RestrictionsNum))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetFunction))->EndInit();
			   this->groupBox2->ResumeLayout(false);
			   this->groupBox2->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		int init_columns = 2;
		int init_rows = 4;
		VariablesNum->Value = init_columns;	// значения Up/Down
		RestrictionsNum->Value = init_rows-1;

		restrictions_table->ColumnCount = init_columns;		// начальное число столбцов и строк
		restrictions_table->RowCount = init_rows-1;
		targetFunction->ColumnCount = init_columns + 1;
		targetFunction->RowCount = init_rows - 3;

		for (int i = 0; i < restrictions_table->ColumnCount; i++) {
			restrictions_table->Columns[i]->Name = "x(" + Convert::ToString(i + 1) + ")";
			targetFunction->Columns[i]->Name = "x(" + Convert::ToString(i + 1) + ")";
		}
		targetFunction->Columns[targetFunction->ColumnCount - 1]->Name = "C";

		DataGridViewComboBoxColumn^ c = gcnew DataGridViewComboBoxColumn();
		c->DisplayStyle = DataGridViewComboBoxDisplayStyle(1);
		c->FlatStyle = FlatStyle(0);
		c->Items->AddRange(">=", "=", "<=");
		c->HeaderText = " ";
		c->Name = "Comparer";
	
		restrictions_table->Columns->AddRange(c, gcnew DataGridViewTextBoxColumn());
		restrictions_table->Columns[restrictions_table->ColumnCount - 1]->Name = "b";

		for (size_t i = 0; i < restrictions_table->RowCount; i++)
		{
			restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 2]->Value = "<=";
		}
		
		restrictions_table->AutoResizeColumns();	//выравнивание ячеек
		targetFunction->AutoResizeColumns();
		restrictions_table->AutoResizeRows();
		targetFunction->AutoResizeRows();

		about^ info = gcnew about();
		info->ShowDialog();
	}

	private: System::Void VariablesNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		NumericUpDown^ o = (NumericUpDown^)sender;
		int thisValue = (int)o->Value;
		int lastValue = (o->Tag == nullptr) ? 0 : (int)o->Tag;
		o->Tag = thisValue;

		if (lastValue > thisValue)
			for (size_t i = 0; i < lastValue - thisValue; i++)
			{
				restrictions_table->Columns->RemoveAt(lastValue - 1 - i);
				targetFunction->Columns->RemoveAt(lastValue - 1 - i);
			}
		else {
			DataGridViewTextBoxColumn^ c,^ d;
			for (size_t i = 1; i < (thisValue - lastValue) +1; i++) {
				c = gcnew DataGridViewTextBoxColumn();
				d = gcnew DataGridViewTextBoxColumn();
				c->Name = "x(" + Convert::ToString(lastValue + i) + ")";
				d->Name = "x(" + Convert::ToString(lastValue + i) + ")";
				restrictions_table->Columns->Insert(lastValue + i -1, c);
				targetFunction->Columns->Insert(lastValue+ i- 1, d);
			}
		}

		restrictions_table->AutoResizeColumns();	//выравнивание ячеек
		targetFunction->AutoResizeColumns();	//выравнивание ячеек
	}

	private: System::Void restrictionNum_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		NumericUpDown^ o = (NumericUpDown^)sender;
		int thisValue = (int)o->Value;
		int lastValue = (o->Tag == nullptr) ? 0 : (int)o->Tag;
		o->Tag = thisValue;

		if (lastValue > thisValue)
			for (size_t i = 0; i < lastValue - thisValue; i++)
				restrictions_table->Rows->RemoveAt(lastValue - 1 - i);
		else {
			DataGridViewRow^ c;
			for (size_t i = 1; i < (thisValue - lastValue) + 1; i++) {
				c = gcnew DataGridViewRow();
				restrictions_table->Rows->Insert(lastValue, c);
				if (restrictions_table->ColumnCount - 2 > 0) restrictions_table->Rows[lastValue]->Cells[restrictions_table->ColumnCount - 2]->Value = "<=";
			}
		}

		restrictions_table->AutoResizeRows();	//выравнивание ячеек
		targetFunction->AutoResizeRows();	//выравнивание ячеек
	}


	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string buffer;
		for (size_t i = 0; i < restrictions_table->RowCount; i++)
		{
			Matrix::Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 1]->Value), buffer);
			if (buffer[0] == '-') {
				buffer.erase(buffer.begin());
				String^ a = gcnew String(buffer.c_str());
				restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 1]->Value = a;
				for (std::size_t j = 0; j < restrictions_table->ColumnCount - 2; j++) {
					Matrix::Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[j]->Value), buffer);
					if (buffer[0] == '-') {
						buffer.erase(buffer.begin());
						restrictions_table->Rows[i]->Cells[j]->Value = gcnew String(buffer.c_str());
					}
					else {
						buffer.insert(buffer.begin(), '-');
						restrictions_table->Rows[i]->Cells[j]->Value = gcnew String(buffer.c_str());
					}
				}
				Matrix::Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 2]->Value), buffer);
				if (buffer == "<=")
					restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 2]->Value = gcnew String(">=");

				if (buffer == ">=")
					restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 2]->Value = gcnew String("<=");
			}
			
		}
		std::vector<size_t> variables;
		std::vector<size_t> basis_index;
		std::stringstream logs;
		Matrix m(restrictions_table, targetFunction, variables, basis_index);

		if (min_b->Checked) {
			m.simplex_solution(logs, false, variables, basis_index);
		}
		if (max_b->Checked) {
			m.simplex_solution(logs, true, variables, basis_index);
		}
		Answer^ ans = gcnew Answer(m, logs, basis_index);
		ans->Show();

	}

	private: System::Void restrictions_table_CellValidating(System::Object^  sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^  e) {
		if (restrictions_table->Rows[e->RowIndex]->IsNewRow) return;
		if (e->ColumnIndex == restrictions_table->ColumnCount - 2) return;
		if (e->FormattedValue->ToString() == "") return;

		std::string buffer;
		Matrix::Str2CharPtr(System::Convert::ToString(e->FormattedValue), buffer);
		for (size_t i = 0; i < buffer.size(); ++i) {
			if (i != 0 && (buffer[i] - 48) > 9 && buffer[i] != '/' || i == 0 && (buffer[i] - 48) > 9 && buffer[i] != '-')
			{
				MessageBox::Show("Please, check your input");
				e->Cancel = true;
				break;
			}
		}
	}

	private: System::Void targetFunction_CellValidating(System::Object^ sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^ e) {
		if (targetFunction->Rows[e->RowIndex]->IsNewRow) return;
		if (e->FormattedValue->ToString() == "") return;

		std::string buffer;
		Matrix::Str2CharPtr(System::Convert::ToString(e->FormattedValue), buffer);
		for (size_t i = 0; i < buffer.size(); ++i) {
			if (i != 0 && (buffer[i] - 48) > 9 && buffer[i] != '/' || i == 0 && (buffer[i] - 48) > 9 && buffer[i] != '-')
			{
				MessageBox::Show("Please, check your input");
				e->Cancel = true;
				break;
			}
		}
	}

	private: System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		about^ info = gcnew about();
		info->ShowDialog();
	}

};
}
