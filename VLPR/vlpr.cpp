#include "vlpr.h"
#include <QtGui/QWidget>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QGroupBox>
#include <QtGUI/QLabel>
#include <QtGUI/QAction>
#include <QtGUI/QToolBar>
#include <QtGUI/QFileDialog>
#include <QtGUI/QTextEdit>
#include <QtGUI/QSizePolicy>
#include <QtGUI/QScrollArea>
#include <QtCore/QDateTime>

VLPR::VLPR(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	//���ô���ȫ��
	ui.setupUi(this);
	this->showMaximized();

	//��ȡ��Ļ��С
	int x = this->width();
	int y = this->height();


	//��ʼ���˵���
	createActions();
    createMenus();

	//��ʼ�����ڿؼ�
	cenWidget = new QWidget(this);
	setCentralWidget(cenWidget);

	//ԭʼͼƬ��ʾ����
	groupBox1 = new QGroupBox("ԭʼͼƬ",cenWidget);
	groupBox1->setGeometry(x*0.01,y*0.01,x*0.5,y*0.6);
	scrollArea1 = new QScrollArea(groupBox1);
	scrollArea1->resize( groupBox1->width()*0.93 , groupBox1->height()*0.93 );
	scrollArea1->move(  (groupBox1->width()-scrollArea1->width() )/2,
		(groupBox1->height()-scrollArea1->height() )/2);
	scrollArea1->setBackgroundRole(QPalette::Dark);
	label1 = new QLabel(scrollArea1);
	scrollArea1->setWidget(label1);

	//Ŀ�공����ʾ����
	groupBox2 = new QGroupBox("Ŀ�공��",cenWidget);
	groupBox2->setGeometry(x*0.57,y*0.05,x*0.35,y*0.3);
	scrollArea2 = new QScrollArea(groupBox2);
	scrollArea2->resize(groupBox2->width()*0.93, groupBox2->height()*0.85);
	scrollArea2->move((groupBox2->width()-scrollArea2->width() )/2,
		(groupBox2->height()-scrollArea2->height() )/2);
	label2 = new QLabel(scrollArea2);
	scrollArea2->setBackgroundRole(QPalette::Dark);
	scrollArea2->setWidget(label2);

	//�����ַ�
	int pos_x = x*0.53;
	QString char_name[] = {"ʡ�ݼ��","���д���","�ַ�һ","�ַ���","�ַ���","�ַ���"
		,"�ַ���"};
	for(int i=0; i < 7 ;++i)
	{
		groupBox_char[i] = new QGroupBox(char_name[i], cenWidget);
		groupBox_char[i]->setGeometry(pos_x, y*0.4, x*0.06, y*0.2);
		scrollArea_char[i] = new QScrollArea(groupBox_char[i]);
		scrollArea_char[i]->resize(groupBox_char[i]->width()*0.75, groupBox_char[i]->height()*0.75);
		scrollArea_char[i]->move( (groupBox_char[i]->width()-scrollArea_char[i]->width())/2, 
			(groupBox_char[i]->height()-scrollArea_char[i]->height())/2 );
		label_char[i] = new QLabel(scrollArea_char[i]);
		scrollArea_char[i]->setBackgroundRole(QPalette::Dark);
		scrollArea_char[i]->setWidget(label_char[i]);
		pos_x+=x*0.066;
	}

	//�������
	scrollArea3 = new QScrollArea(cenWidget);
	scrollArea3->resize(x*0.5,y*0.3);
	scrollArea3->move(x*0.01,y*0.65);
	logEdit = new QTextEdit(scrollArea3);
	scrollArea3->setWidget(logEdit);
	logEdit->resize(scrollArea3->size());
	logEdit->setReadOnly(true);
	updateLog("��ӭ������Ͽ��ѧ���ƺ�ʶ��ϵͳ");
}

VLPR::~VLPR()
{

}

//������־����
void VLPR::updateLog(QString text)
{
	QDateTime time = QDateTime::currentDateTime();//��ȡϵͳʱ��
	QString t = ">"+time.toString("hh:mm:ss");
	t.append(" "+text+"\n");
	logEdit->setPlainText(logEdit->toPlainText()+t);
}

//��ʾͼƬ
void VLPR::showImg(QLabel *label,QImage img)
{
	if(label != NULL)
	{
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(label->pixmap()->size());
	}
}

//��ͼ��
void VLPR::on_OpenImage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "./Car", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	image = cv::imread(fileName.toLocal8Bit().data(),-1);

	if(fileName != "")
	{
		QImage img=MatToQImage(image);
		showImg(label1,img);
		updateLog("�ɹ���ͼƬ "+fileName);
	}
	else
		updateLog("δ�ܳɹ���ͼƬ");
}

//��ʾԭʼͼƬ
void VLPR::on_Show_Image_clicked()
{
	showImg(label1,MatToQImage(image));
}

//ͼƬ�ҶȻ�
void VLPR::on_Gray_clicked()
{
	gray = cvtImg(image);
	showImg(label1,MatToQImage(gray));
}

//��˹ƽ���˲�
void VLPR::on_blur_clicked()
{
	gray = gaussian(gray);
	showImg(label1,MatToQImage(gray));
}

//����sobel���ӽ��б�Ե���
void VLPR::on_edgeDetect_clicked()
{
	gray = Sobel(gray);
	showImg(label1,MatToQImage(gray));
}

//ͼƬ��ֵ��
void VLPR::on_thres_clicked()
{
	thres(gray);
	showImg(label1,MatToQImage(gray));
}

//��̬ѧ����
void VLPR::dilateErode()
{
	morphology(gray);
	showImg(label1,MatToQImage(gray));
}

//��λ����
void VLPR::on_locate_clicked()
{
	car = getLocation(gray,image);
	showImg(label2,MatToQImage(car));
}

//�ַ��ָ�
void VLPR::on_charCut_clicked()
{
	charDiv(car,car_char);
	for(int i = 0; i < 7; ++i)
		showImg(label_char[i],MatToQImage(car_char[i]));
}

void VLPR::createActions() {
    // QAction: һ����, ����������, ��ͼ��, ��ݼ�, �¼�����.
    openAction = new QAction("��", this);
	QObject::connect(openAction, SIGNAL(triggered()), this, SLOT(on_OpenImage_clicked()));
	quitAction = new QAction("�ر�", this);
	QObject::connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
	grayAction = new QAction("�ҶȻ�",this);
	QObject::connect(grayAction, SIGNAL(triggered()), this, SLOT(on_Gray_clicked()));
	imgAction = new QAction("�鿴ԭͼ",this);
	QObject::connect(imgAction,  SIGNAL(triggered()), this, SLOT(on_Show_Image_clicked()));
	edgeDetectAction = new QAction("��Ե���",this);
	QObject::connect(edgeDetectAction, SIGNAL(triggered()), this, SLOT(on_edgeDetect_clicked()));
	thresAction = new QAction("��ֵ��",this);
	QObject::connect(thresAction,SIGNAL(triggered()), this, SLOT(on_thres_clicked()));
	morphologyAction = new QAction("���͸�ʴ",this);
	QObject::connect(morphologyAction,SIGNAL(triggered()),this,SLOT(dilateErode()));
	blurAction = new QAction("��˹ƽ���˲�",this);
	QObject::connect(blurAction,SIGNAL(triggered()), this, SLOT(on_blur_clicked()));
	locateAction = new QAction("��λ����",this);
	QObject::connect(locateAction,SIGNAL(triggered()),this,SLOT(on_locate_clicked()));
	charCutAction = new QAction("�ַ��ָ�",this);
	QObject::connect(charCutAction,SIGNAL(triggered()),this,SLOT(on_charCut_clicked()));
}

void VLPR::createMenus() {

	//�ļ��˵�
    fileMenu = menuBar()->addMenu("�ļ�");
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
	fileMenu->addAction(quitAction);
    fileMenu->addSeparator();

	//Ԥ����˵�
	preDeal = menuBar()->addMenu("Ԥ����");
	preDeal->addAction(imgAction);
	preDeal->addAction(grayAction);
	preDeal->addAction(blurAction);
    preDeal->addSeparator();

	//���ƶ�λ�˵�
	locateMenu = menuBar()->addMenu("���ƶ�λ");
	locateMenu->addAction(thresAction);
	locateMenu->addAction(edgeDetectAction);
	locateMenu->addAction(morphologyAction);
	locateMenu->addAction(locateAction);

	//�ַ��ָ�˵�
	divMenu = menuBar()->addMenu("�ַ��ָ�");
	divMenu->addAction(charCutAction);

	//�ַ�ʶ��˵�
	charRecoMenu = menuBar()->addMenu("�ַ�ʶ��");
}
