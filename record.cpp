#include"record.h"

//��ʼ����¼��
void InitRecordList(SRecordList& SList) {
	SList.pSRecordList = (SItemRecord*)malloc(RECORDLIST_INIT_SIZE * sizeof(SItemRecord));
	if (!SList.pSRecordList) {
		printf("�ڴ�����");
		exit(0);
	}
	SList.nListSize = RECORDLIST_INIT_SIZE;
	SList.nListLength = 0;
}