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
	cv::Mat car_char[7]; //ʡ���ַ�

	QAction *openAction;//��ͼƬ
	QAction *quitAction;//�˳�ϵͳ
	QAction *grayAction;//�ҶȻ�
	QAction *imgAction;//�鿴ԭͼ
	QAction *blurAction;//ƽ���˲�
	QAction *edgeDetectAction;//��Ե���
	QAction *thresAction;//��ֵ��
	QAction *morphologyAction;//��ѧ��̬ѧ����
	QAction *locateAction;//��λ����
	QAction *charCutAction;//�ַ��ָ�
	QAction *charRecAction;//�ַ�ʶ��

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

	QGroupBox *groupBox_char[7];
	QScrollArea *scrollArea_char[7];
	QLabel *label_char[7];

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
	void on_charCut_clicked();
	void on_charRec_licked();
};

#endif // VLPR_H
