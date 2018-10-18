#pragma once
#include <windows.h>
#include<iostream>
#include <string>
#include <string.h>
namespace 控馬達asdaA3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;
	using namespace System::IO::Ports;
	using namespace System::Threading;
	using namespace std;
	//using namespace System;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  SentComPort;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timer1;
			 int rpm_info;
			 Thread^ motorThread;
			 int rpm_value;
	private: System::Windows::Forms::Button^  up;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  disconect;
	private: System::Windows::Forms::Button^  down;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SentComPort = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->up = (gcnew System::Windows::Forms::Button());
			this->down = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->disconect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(28, 42);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 0;
			// 
			// SentComPort
			// 
			this->SentComPort->Location = System::Drawing::Point(28, 122);
			this->SentComPort->Name = L"SentComPort";
			this->SentComPort->Size = System::Drawing::Size(75, 23);
			this->SentComPort->TabIndex = 1;
			this->SentComPort->Text = L"conect";
			this->SentComPort->UseVisualStyleBackColor = true;
			this->SentComPort->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 57600;
			this->serialPort1->ParityReplace = static_cast<System::Byte>(255);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// up
			// 
			this->up->Location = System::Drawing::Point(127, 122);
			this->up->Name = L"up";
			this->up->Size = System::Drawing::Size(75, 23);
			this->up->TabIndex = 2;
			this->up->Text = L"up";
			this->up->UseVisualStyleBackColor = true;
			this->up->Click += gcnew System::EventHandler(this, &MyForm::up_Click);
			// 
			// down
			// 
			this->down->Location = System::Drawing::Point(208, 122);
			this->down->Name = L"down";
			this->down->Size = System::Drawing::Size(75, 23);
			this->down->TabIndex = 3;
			this->down->Text = L"down";
			this->down->UseVisualStyleBackColor = true;
			this->down->Click += gcnew System::EventHandler(this, &MyForm::down_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(329, 122);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"label1";
			// 
			// disconect
			// 
			this->disconect->Location = System::Drawing::Point(28, 152);
			this->disconect->Name = L"disconect";
			this->disconect->Size = System::Drawing::Size(75, 23);
			this->disconect->TabIndex = 5;
			this->disconect->Text = L"disconect";
			this->disconect->UseVisualStyleBackColor = true;
			this->disconect->Click += gcnew System::EventHandler(this, &MyForm::disconect_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(490, 455);
			this->Controls->Add(this->disconect);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->down);
			this->Controls->Add(this->up);
			this->Controls->Add(this->SentComPort);
			this->Controls->Add(this->comboBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		cli::array<System::String^>^ Port = SerialPort::GetPortNames();
		this->comboBox1->Items->AddRange(Port);
	}
void motor_thread()
{
	while (true)
	{
		///傳送監控轉速命令///
		unsigned char watch_data[8] = { 0,0,0,0,0,0,0,0 };
		watch_data_make(watch_data);//執行watch_data_make命令生成函式
		cli::array<System::Byte>^ send_watch_code_arry = gcnew cli::array< Byte >(8);//創造一個可控的矩陣 send_watch_code_arry
		Marshal::Copy((IntPtr)watch_data, send_watch_code_arry, 0, 8);//複製 watch_data 內容進入 send_watch_code_arry
		serialPort1->Write(send_watch_code_arry, 0, 8);//傳送 send_watch_code_arry 進入 serialPort1
		Sleep(20);

		///在 textBox3 中監控馬達回傳資訊的值///
		unsigned char* p_recieve_rpm1;
		unsigned char recieve_rpm_char1[9] = { 0 };
	
		int ii = 0;
		try
		{
			int lenl = 0;
			lenl = serialPort1->BytesToRead;
			p_recieve_rpm1 = recieve_rpm_char1;//指標 p_recieve = recieve_rpm_char

											//當serialPort1有byte值,則傳送資料進入p_revieve
			while (serialPort1->BytesToRead)
			{
				p_recieve_rpm1[ii] = serialPort1->ReadChar();
				ii++;
				if (ii == lenl)
				{
					break;
				}
			}

			unsigned int check_info1 = 256 * p_recieve_rpm1[8] + p_recieve_rpm1[7];//檢查算出crc是否正確
																				//如果crc正確,則算出rpm傳入textbox1
			if (check_info1 == crc_chk(p_recieve_rpm1, 7))
			{
				rpm_info = p_recieve_rpm1[3] * 256 + p_recieve_rpm1[4];//高位元*256+低位元=轉速

																		//若rpm算出為負數,則用二補數計算
				if (rpm_info > 32767)
				{
					rpm_info = -(65535 - rpm_info + 1);
				}
			}
		}
		catch (TimeoutException^)
		{
			rpm_info = 99999;
		}
	}
}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//檢查使用者是否輸入包率和COM
		if (this->comboBox1->Text == System::String::Empty)
		{
			MessageBox::Show("Please Select Port Settings");
		}
		else
		{
			if (!this->serialPort1->IsOpen)
			{

				//原先serialPort只能收到正值 不能收到負值 需加入此指令更改 才可收到負值
				this->serialPort1->Encoding = System::Text::Encoding::GetEncoding(28591);
				this->serialPort1->PortName = comboBox1->Text;
				this->serialPort1->BaudRate = 57600;
				this->serialPort1->ReadTimeout = 20;
				this->serialPort1->WriteTimeout = 20;
				this->serialPort1->Open();

				ThreadStart^ serverThreadStart = gcnew ThreadStart(this, &控馬達asdaA3::MyForm::motor_thread);
				motorThread = gcnew Thread(serverThreadStart);

				motorThread->Start();
				this->timer1->Enabled = true;

				MessageBox::Show("connect motor COM");
				//cli::array<System::Byte>^ LMS_baundrate_500k_manage = gcnew cli::array<Byte>{ 0x02, 0x00, 0x02, 0x00, 0x20, 0x48, 0x58, 0x08 };//更改包率
				//因為普通的未定義矩陣無法傳送進入serialport, 因此需先將普通矩陣轉換成可控矩陣,才可傳送
				unsigned char clc_data[8] = { 0,0,0,0,0,0,0,0 };
				cli::array<System::Byte>^ clc_data_array = gcnew cli::array< Byte >(8); //創造一個可控的矩陣 clc_data_arry
				clc_data_make(clc_data);//創造 CLC 矩陣 函示啟動
				Marshal::Copy((IntPtr)clc_data, clc_data_array, 0, 8);//複製 clc_data 進入 clc_data_array
				serialPort1->Write(clc_data_array, 0, 8);//傳送 clc_data_array 進入serialPort1
				Sleep(20);//中間間隔20ms 防止命令衝突
			}
			else
			{
				MessageBox::Show("Motor Port is already connect");
			}
		}
	}
	public:void clc_data_make(unsigned char clc_data[8]) //強制數位輸出操作
	{
		clc_data[0] = 0x01;
		clc_data[1] = 0x06; //寫入單筆字組
		clc_data[2] = 0x02;
		clc_data[3] = 0x3c;//寫入通訊協定時必須寫入
		clc_data[4] = 0x00;
		clc_data[5] = 0x05;//64
		clc_data[6] = 0x88;//89
		clc_data[7] = 0x7d;//99
	}
	public:void watch_data_make(unsigned char watch_data[8])
	{
		watch_data[0] = 0x01;
		watch_data[1] = 0x03; //讀取多組字組
		watch_data[2] = 0x00;
		watch_data[3] = 0x12;
		watch_data[4] = 0x00;
		watch_data[5] = 0x02;//09 02
		watch_data[6] = 0x64;
		watch_data[7] = 0x0e;
	}
		   ///RPM 矩陣 函式
public:void rpm_send_data(unsigned char send_data[13], int rpm_value)
{
	int return_value, l_crc, h_crc;
	unsigned char rpm_send_data[4] = { 0,0,0,0 };

	//rpm 轉16進位
	rpm_send_data[1] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[0] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[3] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[2] = rpm_value % 256;
	rpm_value >>= 8;


	send_data[0] = 0x01;//motor 機台號碼
	send_data[1] = 0x10;//命令碼10 寫入多組字組
	send_data[2] = 0x01;//傳送地址a 01
	send_data[3] = 0x12;//傳送地址b 12

						//兩個字元
	send_data[4] = 0x00;//00
	send_data[5] = 0x02;//02
	send_data[6] = 0x04;//4 byte 04

	memcpy(&send_data[7], rpm_send_data, 4);//rpm 放入命令中

											//crc 碼生成 函式起動
	return_value = crc_chk(send_data, 11);
	l_crc = return_value % 256;
	h_crc = return_value / 256;

	//crc 放入 send_data
	send_data[11] = l_crc;
	send_data[12] = h_crc;
}
	   ///crc 檢查碼 函式
unsigned int crc_chk(unsigned char* data, unsigned char length)
	   {
		   int j;
		   unsigned int reg_crc = 0xFFFF;
		   while (length--)
		   {
			   reg_crc ^= *data++;
			   for (j = 0; j<8; j++)
			   {
				   if (reg_crc & 0x01)
				   {
					   reg_crc = (reg_crc >> 1) ^ 0xA001;
				   }
				   else
				   {
					   reg_crc = (reg_crc >> 1);
				   }
			   }
		   }
		   return reg_crc;
	   }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		
		label1->Text = rpm_info.ToString();

}
private: System::Void up_Click(System::Object^  sender, System::EventArgs^  e) {

	unsigned char send_data[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

	rpm_value = 1000;
	rpm_send_data(send_data, rpm_value);
	cli::array<System::Byte>^ send_data_array1 = gcnew cli::array< Byte >(13);//創造一個可控的矩陣 send_data_arry
	Marshal::Copy((IntPtr)send_data, send_data_array1, 0, 13);//複製 send_data 內容進入 send_data_array
	serialPort1->Write(send_data_array1, 0, 13);//傳送 send_data_array 進入 serialPort1
	
}
private: System::Void down_Click(System::Object^  sender, System::EventArgs^  e) {
	unsigned char send_data[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

	rpm_value = -1000;
	rpm_send_data(send_data, rpm_value);
	cli::array<System::Byte>^ send_data_array1 = gcnew cli::array< Byte >(13);//創造一個可控的矩陣 send_data_arry
	Marshal::Copy((IntPtr)send_data, send_data_array1, 0, 13);//複製 send_data 內容進入 send_data_array
	serialPort1->Write(send_data_array1, 0, 13);//傳送 send_data_array 進入 serialPort1
}
private: System::Void disconect_Click(System::Object^  sender, System::EventArgs^  e) {
	cli::array<System::Byte>^ send_data_array = gcnew cli::array< Byte >(13);//創造一個可控的矩陣 send_data_array
	rpm_value = 0;//停止馬達運動
				  //創造 rpm 控制命令
	unsigned char send_data[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };//創造 rpm 控制命令
	rpm_send_data(send_data, rpm_value); //函式啟動
	Marshal::Copy((IntPtr)send_data, send_data_array, 0, 13);//複製 send_data 進入 send_data_array
	serialPort1->Write(send_data_array, 0, 13);//傳送 send_data_array 進入 serialport1
	Sleep(20);//中間間隔20ms 防止命令衝突

	motorThread->Suspend();
	this->timer1->Enabled = false;
	this->serialPort1->Close();
	MessageBox::Show("disconnect COM");
}
};
}
