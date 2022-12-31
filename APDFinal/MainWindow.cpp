#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
#include <QScrollBar>
#include <QStandardItemModel>
#include <algorithm>
#include "FindWindow.h"
#include <string>
#include "ui_MainWindow.h"
std::vector <std::string> type_info = { "日常", "固定", "大项", "往来", "娱乐" };

Row::Row(QDate date, int type, int amount, std::string remark)
{
	this->date = date;
	this->type = type;
	this->amount = amount;
	this->remark = remark;
}
void Row::set_Date(QDate date)
{
	this->date = date;
}
QDate Row::get_Date()
{
	return this->date;
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
	model->setHeaderData(0, Qt::Horizontal, tr("时间"));
	model->setHeaderData(1, Qt::Horizontal, tr("种类"));
	model->setHeaderData(2, Qt::Horizontal, tr("金额"));
	model->setHeaderData(3, Qt::Horizontal, tr("备注"));
	ui1->tableView->horizontalHeader()->setVisible(true);//显示或隐藏表头
	ui1->tableView->verticalHeader()->setVisible(false);//显示或隐藏序列行
	ui1->tableView->setAutoScroll(true);//自动滚动条
	//ui->tableView->resizeColumnsToContents(); //根据内容调整大小
	ui1->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
	ui1->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui1->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
	ui1->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
	ui1->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //设置选中单行
	ui1->tableView->setModel(model); //使用
	ui1->tableView->setSelectionModel(selection);
	ui1->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui1->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int pos = 0;
	ui1->tableView->verticalScrollBar()->setSliderPosition(pos);
	connect(ui1->DeleteButton, SIGNAL(clicked()), this, SLOT(delete_Row()));
	connect(ui1->InsertButton, SIGNAL(clicked()), this, SLOT(slot2()));
	connect(ui1->FindButton, SIGNAL(clicked()), this, SLOT(slot_find()));
}

void MainWindow::slot2()
{
	iw = new InsertWindow;
	connect(iw, SIGNAL(sendData1(QDate, int, double, std::string)), this, SLOT(receiveData1(QDate, int, double, std::string)));
	iw->show();
}

void MainWindow::slot_find()
{
	fw = new FindWindow;
	fw->show();
}

bool cmp(Row a, Row b)
{
	if (a.get_Date() > b.get_Date())
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
		this->model->setItem(i, 0, new QStandardItem(this->table[i].get_Date().toString()));
		this->model->setItem(i, 1, new QStandardItem(type_info[this->table[i].get_Type()].c_str()));
		this->model->setItem(i, 2, new QStandardItem(std::to_string(this->table[i].get_Amount()).c_str()));
		this->model->setItem(i, 3, new QStandardItem(this->table[i].get_Remark().c_str()));
	}
}

void MainWindow::add_Row(QDate date, int type, int amount, std::string remark)
{
	Row new_row(date, type, amount, remark);
	this->table.push_back(new_row);
	std::sort(this->table.begin(), this->table.end(), cmp);
	refresh();
}

void MainWindow::receiveData1(QDate date, int type, double amount, std::string remark)
{
	add_Row(date, type, amount, remark);
}
