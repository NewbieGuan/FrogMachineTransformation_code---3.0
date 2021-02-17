#include "Convert_thread.h"

QConvert_thread::QConvert_thread(const string source_file, const string final_file, MMach mmach, Offset offset, const int G_workpiece):
	sourceFile(source_file), finalFile(final_file), mmach(mmach), offset(offset), G_workpiece(G_workpiece)
{

}


void QConvert_thread::run() {
	//�ĵ�ת��
	enum ErrorType et = TransformFile(sourceFile, finalFile, mmach, offset, G_workpiece);
	//�����ź�
	emit ConvertFinish(et);
}