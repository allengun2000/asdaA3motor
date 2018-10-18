#pragma once
#include <windows.h>
#include<iostream>
#include <string>
#include <string.h>
namespace �����FasdaA3 {

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
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
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
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
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
		///�ǰe�ʱ���t�R�O///
		unsigned char watch_data[8] = { 0,0,0,0,0,0,0,0 };
		watch_data_make(watch_data);//����watch_data_make�R�O�ͦ��禡
		cli::array<System::Byte>^ send_watch_code_arry = gcnew cli::array< Byte >(8);//�гy�@�ӥi�����x�} send_watch_code_arry
		Marshal::Copy((IntPtr)watch_data, send_watch_code_arry, 0, 8);//�ƻs watch_data ���e�i�J send_watch_code_arry
		serialPort1->Write(send_watch_code_arry, 0, 8);//�ǰe send_watch_code_arry �i�J serialPort1
		Sleep(20);

		///�b textBox3 ���ʱ����F�^�Ǹ�T����///
		unsigned char* p_recieve_rpm1;
		unsigned char recieve_rpm_char1[9] = { 0 };
	
		int ii = 0;
		try
		{
			int lenl = 0;
			lenl = serialPort1->BytesToRead;
			p_recieve_rpm1 = recieve_rpm_char1;//���� p_recieve = recieve_rpm_char

											//��serialPort1��byte��,�h�ǰe��ƶi�Jp_revieve
			while (serialPort1->BytesToRead)
			{
				p_recieve_rpm1[ii] = serialPort1->ReadChar();
				ii++;
				if (ii == lenl)
				{
					break;
				}
			}

			unsigned int check_info1 = 256 * p_recieve_rpm1[8] + p_recieve_rpm1[7];//�ˬd��Xcrc�O�_���T
																				//�p�Gcrc���T,�h��Xrpm�ǤJtextbox1
			if (check_info1 == crc_chk(p_recieve_rpm1, 7))
			{
				rpm_info = p_recieve_rpm1[3] * 256 + p_recieve_rpm1[4];//���줸*256+�C�줸=��t

																		//�Yrpm��X���t��,�h�ΤG�ɼƭp��
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
		//�ˬd�ϥΪ̬O�_��J�]�v�MCOM
		if (this->comboBox1->Text == System::String::Empty)
		{
			MessageBox::Show("Please Select Port Settings");
		}
		else
		{
			if (!this->serialPort1->IsOpen)
			{

				//���serialPort�u�ব�쥿�� ���ব��t�� �ݥ[�J�����O��� �~�i����t��
				this->serialPort1->Encoding = System::Text::Encoding::GetEncoding(28591);
				this->serialPort1->PortName = comboBox1->Text;
				this->serialPort1->BaudRate = 57600;
				this->serialPort1->ReadTimeout = 20;
				this->serialPort1->WriteTimeout = 20;
				this->serialPort1->Open();

				ThreadStart^ serverThreadStart = gcnew ThreadStart(this, &�����FasdaA3::MyForm::motor_thread);
				motorThread = gcnew Thread(serverThreadStart);

				motorThread->Start();
				this->timer1->Enabled = true;

				MessageBox::Show("connect motor COM");
				//cli::array<System::Byte>^ LMS_baundrate_500k_manage = gcnew cli::array<Byte>{ 0x02, 0x00, 0x02, 0x00, 0x20, 0x48, 0x58, 0x08 };//���]�v
				//�]�����q�����w�q�x�}�L�k�ǰe�i�Jserialport, �]���ݥ��N���q�x�}�ഫ���i���x�},�~�i�ǰe
				unsigned char clc_data[8] = { 0,0,0,0,0,0,0,0 };
				cli::array<System::Byte>^ clc_data_array = gcnew cli::array< Byte >(8); //�гy�@�ӥi�����x�} clc_data_arry
				clc_data_make(clc_data);//�гy CLC �x�} ��ܱҰ�
				Marshal::Copy((IntPtr)clc_data, clc_data_array, 0, 8);//�ƻs clc_data �i�J clc_data_array
				serialPort1->Write(clc_data_array, 0, 8);//�ǰe clc_data_array �i�JserialPort1
				Sleep(20);//�������j20ms ����R�O�Ĭ�
			}
			else
			{
				MessageBox::Show("Motor Port is already connect");
			}
		}
	}
	public:void clc_data_make(unsigned char clc_data[8]) //�j��Ʀ��X�ާ@
	{
		clc_data[0] = 0x01;
		clc_data[1] = 0x06; //�g�J�浧�r��
		clc_data[2] = 0x02;
		clc_data[3] = 0x3c;//�g�J�q�T��w�ɥ����g�J
		clc_data[4] = 0x00;
		clc_data[5] = 0x05;//64
		clc_data[6] = 0x88;//89
		clc_data[7] = 0x7d;//99
	}
	public:void watch_data_make(unsigned char watch_data[8])
	{
		watch_data[0] = 0x01;
		watch_data[1] = 0x03; //Ū���h�զr��
		watch_data[2] = 0x00;
		watch_data[3] = 0x12;
		watch_data[4] = 0x00;
		watch_data[5] = 0x02;//09 02
		watch_data[6] = 0x64;
		watch_data[7] = 0x0e;
	}
		   ///RPM �x�} �禡
public:void rpm_send_data(unsigned char send_data[13], int rpm_value)
{
	int return_value, l_crc, h_crc;
	unsigned char rpm_send_data[4] = { 0,0,0,0 };

	//rpm ��16�i��
	rpm_send_data[1] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[0] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[3] = rpm_value % 256;
	rpm_value >>= 8;
	rpm_send_data[2] = rpm_value % 256;
	rpm_value >>= 8;


	send_data[0] = 0x01;//motor ���x���X
	send_data[1] = 0x10;//�R�O�X10 �g�J�h�զr��
	send_data[2] = 0x01;//�ǰe�a�}a 01
	send_data[3] = 0x12;//�ǰe�a�}b 12

						//��Ӧr��
	send_data[4] = 0x00;//00
	send_data[5] = 0x02;//02
	send_data[6] = 0x04;//4 byte 04

	memcpy(&send_data[7], rpm_send_data, 4);//rpm ��J�R�O��

											//crc �X�ͦ� �禡�_��
	return_value = crc_chk(send_data, 11);
	l_crc = return_value % 256;
	h_crc = return_value / 256;

	//crc ��J send_data
	send_data[11] = l_crc;
	send_data[12] = h_crc;
}
	   ///crc �ˬd�X �禡
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
	cli::array<System::Byte>^ send_data_array1 = gcnew cli::array< Byte >(13);//�гy�@�ӥi�����x�} send_data_arry
	Marshal::Copy((IntPtr)send_data, send_data_array1, 0, 13);//�ƻs send_data ���e�i�J send_data_array
	serialPort1->Write(send_data_array1, 0, 13);//�ǰe send_data_array �i�J serialPort1
	
}
private: System::Void down_Click(System::Object^  sender, System::EventArgs^  e) {
	unsigned char send_data[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

	rpm_value = -1000;
	rpm_send_data(send_data, rpm_value);
	cli::array<System::Byte>^ send_data_array1 = gcnew cli::array< Byte >(13);//�гy�@�ӥi�����x�} send_data_arry
	Marshal::Copy((IntPtr)send_data, send_data_array1, 0, 13);//�ƻs send_data ���e�i�J send_data_array
	serialPort1->Write(send_data_array1, 0, 13);//�ǰe send_data_array �i�J serialPort1
}
private: System::Void disconect_Click(System::Object^  sender, System::EventArgs^  e) {
	cli::array<System::Byte>^ send_data_array = gcnew cli::array< Byte >(13);//�гy�@�ӥi�����x�} send_data_array
	rpm_value = 0;//����F�B��
				  //�гy rpm ����R�O
	unsigned char send_data[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };//�гy rpm ����R�O
	rpm_send_data(send_data, rpm_value); //�禡�Ұ�
	Marshal::Copy((IntPtr)send_data, send_data_array, 0, 13);//�ƻs send_data �i�J send_data_array
	serialPort1->Write(send_data_array, 0, 13);//�ǰe send_data_array �i�J serialport1
	Sleep(20);//�������j20ms ����R�O�Ĭ�

	motorThread->Suspend();
	this->timer1->Enabled = false;
	this->serialPort1->Close();
	MessageBox::Show("disconnect COM");
}
};
}
