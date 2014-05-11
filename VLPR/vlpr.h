#ifndef VLPR_H
#define VLPR_H

#include <QtGui/QMainWindow>
#include "ui_vlpr.h"
#include "utility.h"

class QAction;
class QMenu;
class QDesktopWidget;
class QWidget;
class QGroupBox;
class QGridLayout;
class QLabel;
class QTextEdit;
class QScrollArea;

class VLPR : public QMainWindow
{
	Q_OBJECT

public:

	VLPR(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VLPR();
	void showImg(QLabel *label,QImage img);
	void createMenus();
	void createActions();
	void updateLog(QString text);

private:

	Ui::VLPRClass ui;
	cv::Mat image; //����ͼƬ
	cv::Mat gray; //�Ҷ�ͼ
	cv::Mat car; //��������
	cv::Mat charOne; //ʡ���ַ�
	cv::Mat charTwo; //�ؼ����ַ�
	cv::Mat charThree; //�����ַ�һ
	cv::Mat charFour; //�����ַ���
	cv::Mat charFive; //�����ַ���
	cv::Mat charSix; //�����ַ���
	cv::Mat charSeven; //�����ַ���

	QAction *openAction;//��ͼƬ
	QAction *quitAction;//�˳�ϵͳ
	QAction *grayAction;//�ҶȻ�
	QAction *imgAction;//�鿴ԭͼ
	QAction *blurAction;//ƽ���˲�
	QAction *edgeDetectAction;//��Ե���
	QAction *thresAction;//��ֵ��
	QAction *morphologyAction;//��ѧ��̬ѧ����
	QAction *locateAction;//��λ����

	QMenu *fileMenu;
	QMenu *preDeal;
	QMenu *locateMenu;
	QMenu *divMenu;
	QMenu *charRecoMenu;

	QWidget *cenWidget;

	QGroupBox *groupBox1;
	QScrollArea *scrollArea1;
	QLabel *label1;

	QGroupBox *groupBox2;
	QScrollArea *scrollArea2;
	QLabel *label2;

	QGroupBox *groupBox_01;
	QScrollArea *scrollArea_01;
	QLabel *label_01;

	QGroupBox *groupBox_02;
	QScrollArea *scrollArea_02;
	QLabel *label_02;

	QGroupBox *groupBox_03;
	QScrollArea *scrollArea_03;
	QLabel *label_03;

	QGroupBox *groupBox_04;
	QScrollArea *scrollArea_04;
	QLabel *label_04;

	QGroupBox *groupBox_05;
	QScrollArea *scrollArea_05;
	QLabel *label_05;

	QGroupBox *groupBox_06;
	QScrollArea *scrollArea_06;
	QLabel *label_06;

	QGroupBox *groupBox_07;
	QScrollArea *scrollArea_07;
	QLabel *label_07;

	QTextEdit *logEdit;
	QScrollArea *scrollArea3;

private slots:

	void on_OpenImage_clicked();
	void on_Gray_clicked();
	void on_Show_Image_clicked();
	void on_edgeDetect_clicked();
	void on_thres_clicked();
	void dilateErode();
	void on_blur_clicked();
	void on_locate_clicked();
};

#endif // VLPR_H
