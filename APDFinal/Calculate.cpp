#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "Calculate.h"

extern int language;

Calculate::Calculate(std::vector<Row> table, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::CalculateClass())
{
	ui->setupUi(this);
	QStringList type_list;
	if (language == 0)
	{
		type_list << "�ճ�" << "�̶�" << "����" << "����" << "����";
		ui->label->setText("��������ͳ��");
		ui->label_2->setText("��������ͳ��");
		ui->label_3->setText("�ܺ�");
		ui->label_4->setText("���");
		ui->label_5->setText("��С");
		ui->pushButton->setText("ѡ������");
		ui->pushButton_2->setText("����ͳ��");
		ui->pushButton_3->setText("����ͳ��");
	}
	else
	{
		type_list << "Daily" << "Fixed" << "Large" << "Dealings" << "Entertainment";
		ui->label->setText("Calculate By Date");
		ui->label_2->setText("Calculate By Type");
		ui->label_3->setText("Sum");
		ui->label_4->setText("Maximum");
		ui->label_5->setText("Minimum");
		ui->pushButton->setText("Choose Date");
		ui->pushButton_2->setText("Calculate By Date");
		ui->pushButton_3->setText("Calculate By Type");
	}
	ui->comboBox->addItems(type_list);
	this->table = table;
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(select_date()));
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cal_by_date()));
	connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(cal_by_type()));
}

void Calculate::select_date()
{
	sd = new SelectDate;
	connect(sd, SIGNAL(sendDate(QDate)), this, SLOT(receive_Date(QDate)));
	sd->show();
}

void Calculate::cal_by_date()
{
	int length = this->table.size();
	int sum = 0;
	int max_val = 0;
	int min_val = 9999999;
	for (int i = 0; i < length; i++)
	{
		if (table[i].get_Date() == this->date)
		{
			sum += table[i].get_Amount();
			if (max_val < table[i].get_Amount())
			{
				max_val = table[i].get_Amount();
			}
			if (min_val > table[i].get_Amount())
			{
				min_val = table[i].get_Amount();
			}
		}
	}
	if (!(sum == 0 && max_val == 0 && min_val == 9999999))
	{
		ui->label_6->setText(std::to_string(sum).c_str());
		ui->label_7->setText(std::to_string(max_val).c_str());
		ui->label_8->setText(std::to_string(min_val).c_str());
	}
	else
	{
		ui->label_6->setText("no data");
		ui->label_7->setText("no data");
		ui->label_8->setText("no data");
	}
}

void Calculate::cal_by_type()
{
	int length = this->table.size();
	int sum = 0;
	int max_val = 0;
	int min_val = 9999999;
	int type = ui->comboBox->currentIndex();
	for (int i = 0; i < length; i++)
	{
		if (table[i].get_Type() == type)
		{
			sum += table[i].get_Amount();
			if (max_val < table[i].get_Amount())
			{
				max_val = table[i].get_Amount();
			}
			if (min_val > table[i].get_Amount())
			{
				min_val = table[i].get_Amount();
			}
		}
	}
	if (!(sum == 0 && max_val == 0 && min_val == 9999999))
	{
		ui->label_6->setText(std::to_string(sum).c_str());
		ui->label_7->setText(std::to_string(max_val).c_str());
		ui->label_8->setText(std::to_string(min_val).c_str());
	}
	else
	{
		ui->label_6->setText("no data");
		ui->label_7->setText("no data");
		ui->label_8->setText("no data");
	}
}

void Calculate::receive_Date(QDate data)
{
	this->date = data;
}

Calculate::~Calculate()
{
	delete ui;
}
