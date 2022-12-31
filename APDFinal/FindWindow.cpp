#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "FindWindow.h"
#include <QScrollBar>
#include <QStandardItemModel>

FindWindow::FindWindow(QWidget *parent)
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
}

FindWindow::~FindWindow()
{
	delete ui;
	delete model;
	delete selection;
}
