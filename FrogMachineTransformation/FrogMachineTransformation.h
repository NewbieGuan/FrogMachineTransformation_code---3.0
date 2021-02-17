#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrogMachineTransformation.h"
#include <math.h>
#include <armadillo>
#include <qfile.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qvariant.h>
#include <qcombobox.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qsettings.h>
#include <qpixmap.h>
#include "Dialog_add.h"
#include "Dialog_amend.h"
#include "Dialog_password.h"
#include "Dialog_change_password.h"
#include "CoordTransform.h"
#include "Convert_thread.h"

#pragma execution_character_set("utf-8")

extern QString keypath;

struct Machine_data
{
	double l1;
	double l2;
	double l3;
	double l4;
};
Q_DECLARE_METATYPE(Machine_data)

class FrogMachineTransformation : public QMainWindow
{
	Q_OBJECT

public:
	FrogMachineTransformation(QWidget *parent = Q_NULLPTR);
	~FrogMachineTransformation();

public slots:
	void on_pB_cout_clicked();
	void on_cB_head_clicked(bool checked);
	void on_cbB_Machine_activated(const QString &arg1);
	void on_pB_add_clicked();
	void on_pB_amend_clicked();
	void on_pB_remove_clicked();
	void on_pB_password_clicked();
	void on_pB_openfile_clicked();
	void on_pB_convert_clicked();

private:
	Ui::FrogMachineTransformationClass *ui;
	QMap<QString, Machine_data> machines;
	QString dirpath;
	QLabel *information;
	QLabel *parameter_1, *parameter_2, *parameter_3, *parameter_4, *parameter_5;

	/*
	L1：机床归零后，主轴旋转中心到旋转轴C的X方向距离。
	L2：机床归零后，旋转轴A到旋转轴C的Y方向距离。（正对机床，A轴在C轴左侧值为正，右侧值为负，理想情况此值为0）
	L3：机床归零后，主轴轴线到A轴的Y方向距离。（正对机床，主轴轴线在A轴左侧值为正，右侧值为负，理想情况此值为0）
	L4：机床归零后，主轴端面到旋转轴A的Z方向距离。
	Xw：工件坐标系原点相对于机床坐标系的X方向偏置。
	Yw：工件坐标系原点相对于机床坐标系的Y方向偏置。
	Zw：工件坐标系原点相对于机床坐标系的Z方向偏置。
	Xm：机床处于工件坐标系零点时的X方向偏置。
	Ym：机床处于工件坐标系零点时的X方向偏置。
	Zm：机床处于工件坐标系零点时的X方向偏置。
	La1：直角铣头的Z方向长度。
	La2：直角铣头的Y方向长度。
	Lc：刀具长度。
	R：新坐标系下使用的刀具半径。
	A：A轴旋转角度。
	C：C轴旋转角度。
	x_1：工件坐标系下的X轴坐标值或增量。
	y_1：工件坐标系下的Y轴坐标值或增量。
	z_1：工件坐标系下的Z轴坐标值或增量。
	x_2：新坐标系下的X轴坐标值或增量。
	y_2：新坐标系下的Y轴坐标值或增量。
	z_2：新坐标系下的Z轴坐标值或增量。
	*/

	double L1, L2, L3, L4, Xw, Yw, Zw, Xm, Ym, Zm, La1, La2, Lc, R, A, C, x_1, y_1, z_1;
	bool angle_head, direction, command_mode;

	int G_workpiece;//工件坐标系

	//公用数据初始化
	void iniShared();
	//初始化函数
	void iniUI();
	//初始化comboBox并显示第一项
	void get_machine_data();
	//信号与槽的连接
	void iniSignalSlots();
	//初始化ToolButton说明
	void iniParameter();
	//获取机床数据路径
	void get_data_path();
	//打开数据文件初始化comboBox
	void inicomboBox();
	//更新机床数据文件内容
	void update_data();
	//弹出密码框并判断密码是否正确 0：错误 1：正确 2：取消
	int is_pw_correct();
	//重写过滤器
	bool eventFilter(QObject *watched, QEvent *event);

private slots:
	//收到文件转换完成信号
	void ReceiveFinishSig(int);
};

