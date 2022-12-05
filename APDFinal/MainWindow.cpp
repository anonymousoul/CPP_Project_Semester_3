#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
#include <QScrollBar>
#include <QStandardItemModel>
#include <algorithm>
#include <string>
#include "ui_MainWindow.h"
std::vector <std::string> type_info = { "�ճ�", "�̶�", "����", "����", "����" };

Row::Row(tm time, int type, int amount, std::string remark)
{
	this->time = time;
	this->type = type;
	this->amount = amount;
	this->remark = remark;
}
void Row::set_Time(tm time)
{
	this->time = time;
}
tm Row::get_Time()
{
	return this->time;
}
void Row::set_Type(int type)
{
	this->type = type;
}
int Row::get_Type()
{
	return type;
}
void Row::set_Amount(int amount)
{
	this->amount = amount;
}
int Row::get_Amount()
{
	return this->amount;
}
void Row::set_Remark(std::string remark)
{
	this->remark = remark;
}
std::string Row::get_Remark()
{
	return this->remark;
}

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent), ui1(new Ui::MainWindow)
{
	ui1->setupUi(this);
	//this->resize(QSize(800, 600));
	this->model = new QStandardItemModel(999, 4);
	this->selection = new QItemSelectionModel(model);
	model->setHeaderData(0, Qt::Horizontal, tr("ʱ��"));
	model->setHeaderData(1, Qt::Horizontal, tr("����"));
	model->setHeaderData(2, Qt::Horizontal, tr("���"));
	model->setHeaderData(3, Qt::Horizontal, tr("��ע"));
	ui1->tableView->horizontalHeader()->setVisible(true);//��ʾ�����ر�ͷ
	ui1->tableView->verticalHeader()->setVisible(false);//��ʾ������������
	ui1->tableView->setAutoScroll(true);//�Զ�������
	//ui->tableView->resizeColumnsToContents(); //�������ݵ�����С
	ui1->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//��������������С
	ui1->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui1->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//ֻ��
	ui1->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ģʽΪѡ����
	ui1->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //����ѡ�е���
	ui1->tableView->setModel(model); //ʹ��
	ui1->tableView->setSelectionModel(selection);
	ui1->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui1->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int pos = 0;
	ui1->tableView->verticalScrollBar()->setSliderPosition(pos);
	connect(ui1->pushButton_2, SIGNAL(clicked()), this, SLOT(delete_Row()));
}

bool cmp(Row a, Row b)
{
	std::time_t a_time = mktime(&a.get_Time());
	std::time_t b_time = mktime(&b.get_Time());
	if (a_time > b_time)
	{
		return true;
	}
	else
	{
		return false;
	}
}

MainWindow::~MainWindow()
{
	delete ui1;
	delete model;
	delete selection;
}

void MainWindow::delete_Row()
{
	QModelIndex curIndex = selection->currentIndex();
	model->removeRow(curIndex.row());
	int row_index = curIndex.row();
	table.erase(table.begin() + row_index);
	refresh();
}

void MainWindow::refresh()
{
	int length = table.size();
	for (int i = 0; i < length; i++)
	{
		this->model->setItem(i, 0, new QStandardItem(asctime(&this->table[i].get_Time())));
		this->model->setItem(i, 1, new QStandardItem(type_info[this->table[i].get_Type()].c_str()));
		this->model->setItem(i, 2, new QStandardItem(std::to_string(this->table[i].get_Amount()).c_str()));
		this->model->setItem(i, 3, new QStandardItem(this->table[i].get_Remark().c_str()));
	}
}

void MainWindow::add_Row(tm time, int type, int amount, std::string remark)
{
	Row new_row(time, type, amount, remark);
	this->table.push_back(new_row);
	std::sort(this->table.begin(), this->table.end(), cmp);
	refresh();
}
