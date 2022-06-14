﻿#include "UpperMoniter.h"
#include<qmessagebox.h>
#include<qfiledialog.h>

QStringList get_avail_sp_() noexcept
{
	QStringList list_avail_sp;

	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			list_avail_sp.append(serial.portName());
			serial.close();
		}
	}

	return list_avail_sp;
}


void printdevice(DeviceStatus device)
{
	cout << device.getDate() << endl;
	cout << device.getDeviceAddress() << endl;
	cout << device.getDeviceCoding() << endl;
	cout << device.getEvent() << endl;
	cout << device.getEventDescription() << endl;
	cout << device.getLoop() << endl;
	cout << device.getNetaddress() << endl;
	cout << device.getTime() << endl;

}
UpperMoniter::UpperMoniter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	QStringList tableHead;
	tableHead << u8"日期" << u8"时间" << u8"事件" << u8"事件描述" << u8"网络地址" << u8"回路" << u8"设备地址";
	ui.deviceStatusTableWidget->setColumnCount(7);
	ui.deviceStatusTableWidget->setHorizontalHeaderLabels(tableHead);
	ui.baudRateComboBox->addItems(QStringList() << tr("115200") << tr("9600"));
	ui.openSerialPushButton->setCheckable(true);
	ui.openSerialPushButton->setChecked(false);
	ui.openSerialPushButton->setText(QStringLiteral("打开串口"));
	m_serialPort = new QSerialPort(); //
	connect(ui.openSerialPushButton, SIGNAL(clicked()), this, SLOT(serial_connect()));//�򿪴���
	connect(ui.queryPushButton, SIGNAL(clicked()), this, SLOT(queryAndDisplay()));//�����ѯ��ť
	connect(ui.exportPushButton, SIGNAL(clicked()), this, SLOT(getFileName()) );//���������ť
	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(serial_read()));

	ui.serialComboBox->addItems(get_avail_sp_());

}

void UpperMoniter::queryAndDisplay() {
	/*�����ǰ�������*/
	ui.deviceStatusTableWidget->clearContents();
	ui.deviceStatusTableWidget->setRowCount(m_dvec.size());
	for (int i = 0; i < m_dvec.size(); i++) {
		ui.deviceStatusTableWidget->setItem(i, 0, new QTableWidgetItem(tr(m_dvec[i].Date.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 1, new QTableWidgetItem(tr(m_dvec[i].Time.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 2, new QTableWidgetItem(tr(m_dvec[i].Event.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 3, new QTableWidgetItem(tr(m_dvec[i].EventDescription.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 4, new QTableWidgetItem(tr(m_dvec[i].Netaddress.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 5, new QTableWidgetItem(tr(m_dvec[i].Loop.c_str())));
		ui.deviceStatusTableWidget->setItem(i, 6, new QTableWidgetItem(tr(m_dvec[i].DeviceAddress.c_str())));
	}
}

void UpperMoniter::getFileName() {
	QString curPath = QCoreApplication::applicationDirPath();
	QString aFileName = QFileDialog::getExistingDirectory(this, u8"选择文件","/");
	for (size_t i = 0; i < m_dvec.size(); i++)
	{
		m_dvec[i].save2Excel(aFileName.toStdString());
	}
	QMessageBox::about(this, tr("tip"), u8"保存成功");
}

void UpperMoniter::serial_connect()
{
	QString Serial = ui.serialComboBox->currentText();
	int BaudRate = ui.baudRateComboBox->currentText().toInt();

	
	m_serialPort->setPortName(Serial);
	
	if (ui.openSerialPushButton->isCheckable())
	{
		//�򿪴���
		if (ui.openSerialPushButton->isChecked())
		{
			/*�������*/
			if(!m_serialPort->open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
			{
				qDebug()<<Serial<<"错误!";
				return;
			}
			m_serialPort->setBaudRate(BaudRate,QSerialPort::AllDirections);//���ò����ʺͶ�д����
			m_serialPort->setDataBits(QSerialPort::Data8);      //����λΪ8λ
			m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//��������
			m_serialPort->setParity(QSerialPort::NoParity); //��У��λ
			m_serialPort->setStopBits(QSerialPort::OneStop); //һλֹͣλ
			
			

			ui.openSerialPushButton->setText(QStringLiteral("关闭串口"));
		}
		//�رմ���
		else
		{
			/*�������*/
			m_serialPort->close();
			ui.openSerialPushButton->setText(QStringLiteral("打开串口"));
		}

	}
	
	//QMessageBox::about(NULL, "tip", "ok");
}

void UpperMoniter::serial_read()
{
	QByteArray hexData = m_serialPort->readAll();
	for (int i = 0; i < hexData.size(); i++)
	{
		unsigned char ch = unsigned char(hexData[i]);
		printf("%x ", ch);
	}
	cout << endl;

	cout << hexData.toStdString() << endl;
	for (int i = 0; i < hexData.size(); ++i)      //ȥ��'\0'
		if (char(hexData[i]) == 0x00)
			hexData[i] = 0xff;
	std::string strbuf=hexData.toStdString();

	//QString qstr = QString::fromStdString(strbuf);
	//QStringList qsl = qstr.split("\r\n");		//�������ݰ�  ��0x0d 0x0a��
	
	/*for(int i = 0; i< qsl.size();++i)	
	{
		QString data = qsl.at(i);
		parse_ascii(data.toStdString());
		qDebug()<<"data ="<< data<<"\r\n"; 
	}*/

	auto pos = strbuf.find("\r\n");
	while (pos!=string::npos)
	{
		auto s1 = strbuf.substr(0,pos);
		parse_ascii(s1);
		auto res_str = strbuf.substr(pos + 2);
		strbuf = res_str;
		pos = strbuf.find("\r\n");

	}
//	parse_ascii(strbuf);
	
}

DeviceStatus UpperMoniter::parse_ascii(string data)
{
	// for (int i = 0; i < sizeof(data); ++i)      //ȥ��'\0'
	// 	if (data[i] == 0x00)
	// 		data[i] = 0xff;

	// std::string b((char *)(data));
	for (size_t i = 0; i < data.size(); i++)
	{
		unsigned char ch = data[i];
		printf("%x ", ch);

	}
	DeviceData a(data);
	cout << a.Event << endl;
	DeviceStatus device;
	device.setDate(a.Date);
	device.setDeviceAddres(a.DeviceAddress);
	device.setEvent(QString::fromLocal8Bit(a.Event.c_str()).toStdString());
	device.setEventDescription(QString::fromLocal8Bit(a.EventDescription.c_str()).toStdString());
	device.setLoop(a.Loop);
	device.setNetaddress(a.NetAddress);
	device.setTime(a.Time);
	printdevice(device);
	m_dvec.push_back(device);

	return device;
}



void UpperMoniter::export_all_device()
{
}

void UpperMoniter::display_all_device()
{
}

string string2ascii(string str)
{
	QString qstr = QString::fromStdString(str);
	QStringList qsl = qstr.split(" ");
	

	return string();
}
