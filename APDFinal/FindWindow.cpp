#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "FindWindow.h"
#include <QScrollBar>
#include "SelectDate.h"
#include <QStandardItemModel>
#include "Row.h"


FindWindow::FindWindow(std::vector <Row> table, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::FindWindowClass())
{
	ui->setupUi(this);
	QStringList type_list;
	type_list << "�ճ�" << "�̶�" << "����" << "����" << "����";
	ui->comboBox->addItems(type_list);
	this->model = new QStandardItemModel(999, 4);
	this->selection = new QItemSelectionModel(model);
	model->setHeaderData(0, Qt::Horizontal, tr("ʱ��"));
	model->setHeaderData(1, Qt::Horizontal, tr("����"));
	model->setHeaderData(2, Qt::Horizontal, tr("���"));
	model->setHeaderData(3, Qt::Horizontal, tr("��ע"));
	ui->tableView->horizontalHeader()->setVisible(true);//��ʾ�����ر�ͷ
	ui->tableView->verticalHeader()->setVisible(false);//��ʾ������������
	ui->tableView->setAutoScroll(true);//�Զ�������
	//ui->tableView->resizeColumnsToContents(); //�������ݵ�����С
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//��������������С
	ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//ֻ��
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ģʽΪѡ����
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //����ѡ�е���
	ui->tableView->setModel(model); //ʹ��
	ui->tableView->setSelectionModel(selection);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int pos = 0;
	ui->tableView->verticalScrollBar()->setSliderPosition(pos);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(select_date()));
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(find_by_date()));
	this->table = table;
}

void FindWindow::select_date()
{
	sd = new SelectDate;
	connect(sd, SIGNAL(sendDate(QDate)), this, SLOT(receive_Date(QDate)));
	sd->show();
}

void FindWindow::find_by_date()
{
	int length = this->table.size();
	this->display_table.clear();
	for (int i = 0; i < length; i++)
	{
		if (table[i].get_Date() == this->date)
		{
			display_table.push_back(table[i]);
		}
	}
	refresh();
}

void FindWindow::refresh()
{
	int length = this->display_table.size();
	std::vector <std::string> type_info = { "�ճ�", "�̶�", "����", "����", "����" };
	for (int i = 0; i < length; i++)
	{
		this->model->setItem(i, 0, new QStandardItem(this->display_table[i].get_Date().toString()));
		this->model->setItem(i, 1, new QStandardItem(type_info[this->display_table[i].get_Type()].c_str()));
		this->model->setItem(i, 2, new QStandardItem(std::to_string(this->display_table[i].get_Amount()).c_str()));
		this->model->setItem(i, 3, new QStandardItem(this->display_table[i].get_Remark().c_str()));
	}
}

void FindWindow::receive_Date(QDate date)
{
	this->date = date;
}

FindWindow::~FindWindow()
{
	delete ui;
	delete model;
	delete selection;
}
