#include"record.h"

//初始化记录表
void InitRecordList(SRecordList& SList) {
	SList.pSRecordList = (SItemRecord*)malloc(RECORDLIST_INIT_SIZE * sizeof(SItemRecord));
	if (!SList.pSRecordList) {
		printf("内存已满");
		exit(0);
	}
	SList.nListSize = RECORDLIST_INIT_SIZE;
	SList.nListLength = 0;
}