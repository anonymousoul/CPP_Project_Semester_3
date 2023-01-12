#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "Settings.h"
extern int language;
Settings::Settings(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SettingsClass())
{
	ui->setupUi(this);
	QStringList language_list;
	language_list << "����" << "English";
	ui->comboBox->addItems(language_list);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(save()));
	refresh();
}

void Settings::save()
{
	language = ui->comboBox->currentIndex();
	refresh();
}

void Settings::refresh()
{
	if (language == 1)
	{
		ui->label->setText("Settings");
		ui->label_2->setText("Language");
		ui->pushButton->setText("Save Settings");
	}
	else
	{
		ui->label->setText("����");
		ui->label_2->setText("����");
		ui->pushButton->setText("��������");
	}
}

Settings::~Settings()
{
	delete ui;
}
