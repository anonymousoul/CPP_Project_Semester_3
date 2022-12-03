#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
#include <QStandardItemModel>
#include<QScrollBar>
#include "ui_MainWindow.h"

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
	QStandardItemModel* model = new QStandardItemModel(999, 4);
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
	int pos = 0;
	ui1->tableView->verticalScrollBar()->setSliderPosition(pos);
}

MainWindow::~MainWindow()
{
	delete ui1;
}
