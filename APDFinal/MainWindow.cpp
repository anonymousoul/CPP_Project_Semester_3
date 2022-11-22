#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
#include <QStandardItemModel>
#include<QScrollBar>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent), ui1(new Ui::MainWindow)
{
	ui1->setupUi(this);
	//this->resize(QSize(800, 600));
	QStandardItemModel* model = new QStandardItemModel(999, 4);
	model->setHeaderData(0, Qt::Horizontal, tr("����"));
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