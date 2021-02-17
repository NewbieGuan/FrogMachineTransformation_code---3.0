#pragma once

#include <qthread.h>
#include "CoordTransform.h"

class QConvert_thread :public QThread
{
	Q_OBJECT

private:
	string sourceFile;
	string finalFile;
	MMach mmach;
	Offset offset;
	int G_workpiece;

protected:
	void run() Q_DECL_OVERRIDE;

public:
	QConvert_thread(const string source_file, const string final_file, MMach mmach, Offset offset, const int G_workpiece);

signals:
	void ConvertFinish(int);
};