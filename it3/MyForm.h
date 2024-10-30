#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "function.h"
#include "SVD_hest.h"



namespace it3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			// 
			//
			
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBoxFI1;

	private: System::Windows::Forms::TextBox^ textBoxF1;

	private: System::Windows::Forms::TextBox^ textBoxA1;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBoxFD;

	private: System::Windows::Forms::TextBox^ textBoxN;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBoxFI3;

	private: System::Windows::Forms::TextBox^ textBoxFI2;

	private: System::Windows::Forms::TextBox^ textBoxF3;

	private: System::Windows::Forms::TextBox^ textBoxF2;

	private: System::Windows::Forms::TextBox^ textBoxA3;

	private: System::Windows::Forms::TextBox^ textBoxA2;
	private: System::Windows::Forms::TextBox^ textBoxNUM;
	private: System::Windows::Forms::TextBox^ textBoxP;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;



	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart3;



	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::Button^ button2;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxNUM = (gcnew System::Windows::Forms::TextBox());
			this->textBoxP = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBoxFD = (gcnew System::Windows::Forms::TextBox());
			this->textBoxN = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxFI3 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFI2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFI1 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxF3 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxF2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxF1 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxA3 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxA2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxA1 = (gcnew System::Windows::Forms::TextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(857, 587);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(116, 39);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Старт";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(17, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"n:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(30, 21);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(56, 22);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"3";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(30, 49);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(56, 22);
			this->textBox2->TabIndex = 4;
			this->textBox2->Text = L"3";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"m:";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(6, 121);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(188, 20);
			this->checkBox1->TabIndex = 6;
			this->checkBox1->Text = L"Создать новую матрицу";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(63, 82);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(56, 22);
			this->textBox3->TabIndex = 4;
			this->textBox3->Text = L"2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 85);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 16);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Порог:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBox3);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(196, 147);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"1 часть задачи";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBoxNUM);
			this->groupBox2->Controls->Add(this->textBoxP);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->textBoxFD);
			this->groupBox2->Controls->Add(this->textBoxN);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->textBoxFI3);
			this->groupBox2->Controls->Add(this->textBoxFI2);
			this->groupBox2->Controls->Add(this->textBoxFI1);
			this->groupBox2->Controls->Add(this->textBoxF3);
			this->groupBox2->Controls->Add(this->textBoxF2);
			this->groupBox2->Controls->Add(this->textBoxF1);
			this->groupBox2->Controls->Add(this->textBoxA3);
			this->groupBox2->Controls->Add(this->textBoxA2);
			this->groupBox2->Controls->Add(this->textBoxA1);
			this->groupBox2->Location = System::Drawing::Point(12, 197);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(291, 296);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"2 часть задачи";
			// 
			// textBoxNUM
			// 
			this->textBoxNUM->Location = System::Drawing::Point(35, 182);
			this->textBoxNUM->Name = L"textBoxNUM";
			this->textBoxNUM->Size = System::Drawing::Size(56, 22);
			this->textBoxNUM->TabIndex = 19;
			this->textBoxNUM->Text = L"3";
			// 
			// textBoxP
			// 
			this->textBoxP->Location = System::Drawing::Point(34, 154);
			this->textBoxP->Name = L"textBoxP";
			this->textBoxP->Size = System::Drawing::Size(56, 22);
			this->textBoxP->TabIndex = 18;
			this->textBoxP->Text = L"64";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(9, 186);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(13, 16);
			this->label16->TabIndex = 17;
			this->label16->Text = L"i:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(9, 157);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(19, 16);
			this->label15->TabIndex = 16;
			this->label15->Text = L"P:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(119, 118);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(21, 16);
			this->label14->TabIndex = 15;
			this->label14->Text = L"fd:";
			// 
			// textBoxFD
			// 
			this->textBoxFD->Location = System::Drawing::Point(145, 115);
			this->textBoxFD->Name = L"textBoxFD";
			this->textBoxFD->Size = System::Drawing::Size(56, 22);
			this->textBoxFD->TabIndex = 14;
			this->textBoxFD->Text = L"64";
			// 
			// textBoxN
			// 
			this->textBoxN->Location = System::Drawing::Point(35, 115);
			this->textBoxN->Name = L"textBoxN";
			this->textBoxN->Size = System::Drawing::Size(56, 22);
			this->textBoxN->TabIndex = 13;
			this->textBoxN->Text = L"512";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(9, 118);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(20, 16);
			this->label13->TabIndex = 12;
			this->label13->Text = L"N:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(192, 80);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(26, 16);
			this->label12->TabIndex = 11;
			this->label12->Text = L"φ3:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(192, 52);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(26, 16);
			this->label9->TabIndex = 11;
			this->label9->Text = L"φ2:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(192, 24);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 16);
			this->label6->TabIndex = 11;
			this->label6->Text = L"φ1:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(98, 80);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(20, 16);
			this->label11->TabIndex = 10;
			this->label11->Text = L"f3:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(98, 52);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(20, 16);
			this->label8->TabIndex = 10;
			this->label8->Text = L"f2:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(98, 24);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(20, 16);
			this->label5->TabIndex = 10;
			this->label5->Text = L"f1:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(2, 80);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(26, 16);
			this->label10->TabIndex = 7;
			this->label10->Text = L"A3:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(2, 52);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(26, 16);
			this->label7->TabIndex = 7;
			this->label7->Text = L"A2:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(2, 24);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(26, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"A1:";
			// 
			// textBoxFI3
			// 
			this->textBoxFI3->Location = System::Drawing::Point(224, 77);
			this->textBoxFI3->Name = L"textBoxFI3";
			this->textBoxFI3->Size = System::Drawing::Size(56, 22);
			this->textBoxFI3->TabIndex = 9;
			this->textBoxFI3->Text = L"5";
			// 
			// textBoxFI2
			// 
			this->textBoxFI2->Location = System::Drawing::Point(224, 49);
			this->textBoxFI2->Name = L"textBoxFI2";
			this->textBoxFI2->Size = System::Drawing::Size(56, 22);
			this->textBoxFI2->TabIndex = 9;
			this->textBoxFI2->Text = L"9";
			// 
			// textBoxFI1
			// 
			this->textBoxFI1->Location = System::Drawing::Point(224, 21);
			this->textBoxFI1->Name = L"textBoxFI1";
			this->textBoxFI1->Size = System::Drawing::Size(56, 22);
			this->textBoxFI1->TabIndex = 9;
			this->textBoxFI1->Text = L"9";
			// 
			// textBoxF3
			// 
			this->textBoxF3->Location = System::Drawing::Point(121, 77);
			this->textBoxF3->Name = L"textBoxF3";
			this->textBoxF3->Size = System::Drawing::Size(56, 22);
			this->textBoxF3->TabIndex = 8;
			this->textBoxF3->Text = L"4";
			// 
			// textBoxF2
			// 
			this->textBoxF2->Location = System::Drawing::Point(121, 49);
			this->textBoxF2->Name = L"textBoxF2";
			this->textBoxF2->Size = System::Drawing::Size(56, 22);
			this->textBoxF2->TabIndex = 8;
			this->textBoxF2->Text = L"6";
			// 
			// textBoxF1
			// 
			this->textBoxF1->Location = System::Drawing::Point(121, 21);
			this->textBoxF1->Name = L"textBoxF1";
			this->textBoxF1->Size = System::Drawing::Size(56, 22);
			this->textBoxF1->TabIndex = 8;
			this->textBoxF1->Text = L"3";
			// 
			// textBoxA3
			// 
			this->textBoxA3->Location = System::Drawing::Point(32, 77);
			this->textBoxA3->Name = L"textBoxA3";
			this->textBoxA3->Size = System::Drawing::Size(56, 22);
			this->textBoxA3->TabIndex = 7;
			this->textBoxA3->Text = L"5";
			// 
			// textBoxA2
			// 
			this->textBoxA2->Location = System::Drawing::Point(32, 49);
			this->textBoxA2->Name = L"textBoxA2";
			this->textBoxA2->Size = System::Drawing::Size(56, 22);
			this->textBoxA2->TabIndex = 7;
			this->textBoxA2->Text = L"4";
			// 
			// textBoxA1
			// 
			this->textBoxA1->Location = System::Drawing::Point(32, 21);
			this->textBoxA1->Name = L"textBoxA1";
			this->textBoxA1->Size = System::Drawing::Size(56, 22);
			this->textBoxA1->TabIndex = 7;
			this->textBoxA1->Text = L"1";
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(0, 29);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Legend = L"Legend1";
			series1->Name = L"1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(662, 210);
			this->chart1->TabIndex = 10;
			this->chart1->Text = L"chart1";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->chart1);
			this->groupBox3->Location = System::Drawing::Point(337, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(662, 245);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Исходный сигнал";
			// 
			// chart2
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(0, 22);
			this->chart2->Name = L"chart2";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(662, 210);
			this->chart2->TabIndex = 11;
			this->chart2->Text = L"chart3";
			// 
			// chart3
			// 
			chartArea3->Name = L"ChartArea1";
			this->chart3->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->chart3->Legends->Add(legend3);
			this->chart3->Location = System::Drawing::Point(6, 21);
			this->chart3->Name = L"chart3";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series3->Legend = L"Legend1";
			series3->Name = L"Series1";
			this->chart3->Series->Add(series3);
			this->chart3->Size = System::Drawing::Size(662, 219);
			this->chart3->TabIndex = 9;
			this->chart3->Text = L"chart1";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->chart2);
			this->groupBox4->Location = System::Drawing::Point(337, 266);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(662, 238);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"i-сингулярный вектор";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->chart3);
			this->groupBox5->Location = System::Drawing::Point(12, 499);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(662, 246);
			this->groupBox5->TabIndex = 14;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"СЗ автокорреляционной матрицы";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(845, 652);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(128, 61);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Старт!";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1025, 757);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		
	/*private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}*/
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		int n = Convert::ToInt32(textBox1->Text); // Кол-во строк
		int m = Convert::ToInt32(textBox2->Text); // Кол-во столбцов
		int threshold = Convert::ToInt32(textBox3->Text); // порог

		//dataGridView1->RowCount = n; // A
		//dataGridView1->ColumnCount = m;

		//dataGridView2->RowCount = n; // SVD
		//dataGridView2->ColumnCount = m;

		
		
		////////////////////////////////
		
		static std::vector<std::vector<float>> Matrix; // Статическая матрица A
		if (Matrix.empty() || Matrix.size() != n || Matrix[0].size() != m)
		{
			Matrix.resize(n, std::vector<float>(m));
		}



		if (checkBox1->Checked)//создание новой матрицы
		{
			srand(time(NULL));
			for (int i = 0; i < n; i++) 
			{ // заполнение матрицы случайными элементами
				for (int j = 0; j < m; j++) 
				{
					Matrix[i][j] = -1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f;
				}
			}
		}
		






		std::vector<std::vector<float>> u(n, std::vector<float>(m, 0.0f)); // инициализация нулевой матрицы u
		std::vector<std::vector<float>> v(m, std::vector<float>(m, 0.0f)); // инициализация нулевой матрицы v
		std::vector<std::vector<float>> sigma(m, std::vector<float>(m, 0.0f)); // инициализация нулевой матрицы sigma
		//std::vector<std::vector<float>> sigmaP(m, std::vector<float>(m, 0.0f));// инициализация нулевой матрицы sigmaPseudo


		
		

		std::vector<float> x(n, 0.0f);
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// заполняем вектор случайными числами в диапазоне от 0 до 100
		for (int j = 0; j < n; j++) 
		{
			x[j] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 100.0f;
		}

		std::vector<float> b(n, 0.0f);

		b = multiplyMatrixVector(Matrix, x);


		std::setlocale(LC_ALL, "Russian");
		// открываем файл для записи
		std::ofstream outFile("output.txt");

		
		



		svd(Matrix, u, v, sigma, n, m);//с помощью svd рассчёт матриц U,V,Sigma

		std::vector<std::vector<float>> sigmaP = pseudoInverseSigma(sigma, threshold);

		std::vector<std::vector<float>> A_inv = pseudoInverseMatrixUsingSVD(u, sigma, v, threshold);//псевдообартная матрица через SVD

		//for (int it = 0; it < n; it++)//Вывод матрицы SVD псевдообратной
		//{
		//	for (int jt = 0; jt < m; jt++)
		//	{
		//		dataGridView2->Rows[it]->Cells[jt]->Value = A_inv[it][jt];
		//	}

		//}



		std::vector<float> xpseudo(n, 0.0f);
		xpseudo = multiplyMatrixVector(A_inv, b);

		std::vector<float> delta(n, 0.0f);
		delta = Diff(x, xpseudo);
		double otkl = 0;
		otkl = average(delta);


		/////////////////

		if (outFile.is_open())
		{


			outFile << "Матрица A:\n";
			for (const auto& row : Matrix) {
				for (const auto& value : row) {
					outFile << value << " ";
				}
				outFile << "\n";
			}

			outFile << "вектор x" << "\n";
			for (const auto& value : x)
			{
				outFile << value << "\n";
			}

			outFile << "вектор b" << "\n";
			for (const auto& value : b)
			{
				outFile << value << "\n";
			}

			outFile << "A_inv*b (xpseudo):" << "\n";
			for (const auto& value : xpseudo)
			{
				outFile << value << "\n";
			}

			outFile << "delta:\n";
			outFile << otkl << "\n";
				
			


			outFile.close();
			std::cout << "Вектор успешно записан в файл output.txt" << std::endl;
		}
		else
		{
			std::cerr << "Не удалось открыть файл для записи" << std::endl;
		}


	}


	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{

		//2 ЧАСТЬ ЗАДАЧИ

		this->chart1->Series[0]->Points->Clear();
		this->chart2->Series[0]->Points->Clear();
		this->chart3->Series[0]->Points->Clear();



		double A1 = 0, A2 = 0, A3 = 0;
		double f1 = 0, f2 = 0, f3 = 0;
		double fi1 = 0, fi2 = 0, fi3 = 0;
		double fd = 0, dt = 0;
		int N = 0, P = 0, num = 0;

		N = System::Convert::ToDouble(textBoxN->Text);

		fd = System::Convert::ToDouble(textBoxFD->Text);
		A1 = System::Convert::ToDouble(textBoxA1->Text);
		A2 = System::Convert::ToDouble(textBoxA2->Text);
		A3 = System::Convert::ToDouble(textBoxA3->Text);
		f1 = System::Convert::ToDouble(textBoxF1->Text);
		f2 = System::Convert::ToDouble(textBoxF2->Text);
		f3 = System::Convert::ToDouble(textBoxF3->Text);
		fi1 = System::Convert::ToDouble(textBoxFI1->Text);
		fi2 = System::Convert::ToDouble(textBoxFI2->Text);
		fi3 = System::Convert::ToDouble(textBoxFI3->Text);
		P = System::Convert::ToDouble(textBoxP->Text);
		num = System::Convert::ToInt32(textBoxNUM->Text);

		std::vector<float> Signal = Gen_Sign(N, fd, A1, A2, A3, f1, f2, f3, fi1, fi2, fi3);
		for (int i = 0; i < N; i++)
		{
			dt = double(i) / fd;
			this->chart1->Series[0]->Points->AddXY(dt, Signal[i]);
		}



		std::vector<float> rxx(P, 0.0f);
		std::vector<std::vector<float>> Rxx(P, std::vector<float>(P, 0.0f));
		std::vector<std::vector<float>> U(P, std::vector<float>(P, 0.0f)); // инициализация нулевой матрицы u
		std::vector<std::vector<float>> V(P, std::vector<float>(P, 0.0f));
		std::vector<std::vector<float>> SIGMA(P, std::vector<float>(P, 0.0f));




		/*MatrixAKP(P, N, rxx, Signal, Rxx);*/

		rxx.resize(P);
		for (int i = 0; i < P; i++)  // поиск отсчетов автокорреляции
		{
			//rxx[i] = 0;
			for (int j = 0; j < (N - i); j++)
			{
				rxx[i] += Signal[j] * Signal[j + i];
			}
			rxx[i] /= (N - i);
		}

		// Rxx.resize(P);
		for (int i = 0; i < P; i++)
		{
			/*Rxx[i].resize(P);*/
			for (int j = 0; j < P; j++)
			{
				Rxx[i][j] = rxx[abs(i - j)];
			}


		}

		svd(Rxx, U, V, SIGMA, P, P);


		//for (int i = 0; i < P; i++) //сортировка СЗ и соотв СВ в порядке убывания
		//{
		//	for (int j = (i + 1); j < P; j++)
		//	{
		//		//double buff = 0;
		//		if (SIGMA[i][0] < SIGMA[j][0])
		//		{
		//			double buff = SIGMA[j][0];
		//			SIGMA[j][0] = SIGMA[i][0];
		//			SIGMA[i][0] = buff;

		//			//double buff2 = 0;
		//			for (int k = 0; k < P; k++)
		//			{
		//				double buff2 = V[j][k];
		//				V[j][k] = V[i][k];
		//				V[i][k] = buff2;
		//			}
		//		}
		//	}
		//}

		for (int i = 0; i < P; i++)
		{
			this->chart2->Series[0]->Points->AddXY(i, V[i][num]);//график СВ
		}
		
		
		//for (int i = 0; i < P; i++)
		//{
		//	this->chart2->Series[0]->Points->AddXY(i, V[num][i]);//графмк СЗ
		//	
		//}

		for (int i = 0; i < P; i++) 
		{
			this->chart3->Series[0]->Points->AddXY(i, sqrt(SIGMA[i][i]));//график СЗ
		}

	


	}
};
}
