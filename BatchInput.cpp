#define _CRT_SECURE_NO_WARNINGS  

#include"allstruct.h"

void WriteExcel(SAthleteList& athletelist){            //�ú������ԸĳɰѲ��Ϸ����˶�Ա��Ϣд�뵽EXCEL�ļ��� 
    char chy[4]={ 'x' ,'a' ,'h','w' } ;
    int data[4]={ 1 , 3 , 6 ,9  };
    int i ;
    FILE *fp = NULL ;
    fp = fopen("E:\\error.xls","w") ;
    for (i=0 ; i<4 ;i++)
        fprintf(fp,"%c\t%d\n",chy[i],data[i] ) ;
    fclose(fp);
}

void PrintAthleteInfo(SAthlete SAthle){   
    printf("�������ݷָ�ת������SAthlete������£�\n") ; 
	printf("ID:%s  ",SAthle.szAthleteID) ; 
	printf("����:%s  ",SAthle.szAthleteName) ; 
	if(SAthle.GENDER_athleteGender ==GENDER_MALE ) printf("sex:��  ") ; 
	    else printf("sex:Ů  ") ; 
	printf("��Ժ:%s  ",SAthle.academy.szAcademyName) ;     
	printf("NumberOfItem:%d  ",SAthle.nSItemNumber) ; 
	for(int i=0;i<SAthle.nSItemNumber;i++) 
	   printf("item:%s  ",SAthle.SAthleteItem[i].szItemName) ; 
	printf("\n") ;
	
}

void DivideLine(SAthlete &SAthle,char szLine[EXCEL_MAX_CHARONELINE]){
	
	char *ptr,*retptr;
    int i=0;
    char Line[EXCEL_MAX_CHARONELINE];        //���ڴ洫����ַ�                     
    strcpy(Line,szLine);
    ptr = Line; 
    int length = 0 ;
    length = strlen(Line);
    Line[length-1] = 0;        //	ȥ����β�Ļ��з�   
    while ((retptr=strtok(ptr, "	")) != NULL) {
        i++;
        //printf("substr[%d]:%s   ,����:%d \n", i++, retptr, strlen(retptr));
        ptr = NULL;
        switch(i-1){
        	case 0 : strcpy(SAthle.szAthleteID,retptr);break;                     //���е�һ����ID 
        	case 1 : strcpy(SAthle.szAthleteName,retptr);break;                   //���еڶ��������� 
        	case 2 : if(!strcmp("��",retptr)) SAthle.GENDER_athleteGender = GENDER_MALE;       ////���е��������Ա� 
        	             else SAthle.GENDER_athleteGender = GENDER_FEMALE;   break;   
        	case 3 : strcpy(SAthle.academy.szAcademyName,retptr);break;   
        	case 4 : SAthle.nSItemNumber = atoi(retptr) ;break;   
			default : strcpy(SAthle.SAthleteItem[i-6].szItemName,retptr);break;   
		}
    }
}

void ReadExcel(){          //��EXCLE�ж�ȡ������Ϣ�����ѷ���Ҫ������ӵ��˶�Ա���� ,�Ѳ���Ҫ����˶�Ա��ӡ����
    FILE *fp;
    char szFileName[20];              //������ļ��� 
    char szLine[EXCEL_MAX_CHARONELINE];
    SAthlete SAthle;
    //�ж��ļ��Ƿ��ʧ��
    printf("������Ҫ������ļ���(���ӣ�E:\\test.xls):");
    GetString(szFileName, sizeof(szFileName));
    if ( (fp = fopen(szFileName, "rt")) == NULL ) {
        puts("Fail to open file!");
        exit(0);
    }
    SAthleteList athletelist_ok;
    InitAthleteList(athletelist_ok);
    SAthleteList athletelist_err;
    InitAthleteList(athletelist_err);
    SAthleteList athletelist;
    InitAthleteList(athletelist);
    ReadAthleteListFile(athletelist);//�����˶�Ա����Ϣ
    SItemList itemlist;
    InitItemList(itemlist);
    ReadItemListFile(itemlist);//������Ŀ����Ϣ


    SAthlete athlete;
    int length = 0 ;//�ɹ����������
    fgets(szLine, EXCEL_MAX_CHARONELINE, fp);//�ȶ����һ�У��ӵڶ��п�ʼ�ַ����ָ� 
    //ѭ����ȡ�ļ���ÿһ������
    while( fgets(szLine, EXCEL_MAX_CHARONELINE, fp) != NULL ) {
        printf("����������ݣ�%s", szLine);
        DivideLine(athlete,szLine); 
        /*
        ���ﻹ��Ҫ����˶�Ա��Ϣ�Ƿ�Ϸ����жϣ��Ϸ��˶�Ա��Ϣ��ӵ��б� 
        */
        int flag = true;//������Ϊtrue������Ŀ�Ϸ�������Ƿ���

        int nPos_ID = LocateAthlete(athletelist, athlete.szAthleteID);
        int nPos_Name = LocateAthlete(athletelist, athlete.szAthleteName);
        if (nPos_ID != -1 || nPos_Name != -1) {
            flag == false;
            AddAthlete(athletelist_err, athlete);
            printf("EndOneLine  ����˶�Ա�Ѵ���\n");
            continue;
        }

        
        int nSItemNumber = athlete.nSItemNumber;
        char* ItemName[ATHLETE_MAX_ITEM];
        for (int i = 0; i < ATHLETE_MAX_ITEM; i++) 
            ItemName[i] = (char*)malloc(25*sizeof(char));
        for (int i = 0; i < athlete.nSItemNumber; i++) {//��鱨����Ŀ�Ƿ���ڡ�
            int nPos_item = LocateItem(itemlist,athlete.SAthleteItem[i].szItemName);
            if (nPos_item == -1) {//����Ŀ������
                flag = false;
                break;//����˶�Ա�����˲����ڵ���Ŀ�����Ϸ���
            }
            else {
                strcpy_s(ItemName[i], 25, athlete.SAthleteItem[i].szItemName);
            }
            if (i >= ATHLETE_MAX_ITEM) {
                flag = false;
                break;
            }
        }
        if (!flag) {//�Ƿ�
            AddAthlete(athletelist_err, athlete);
        }
        else {//�Ϸ�
            athlete.nSItemNumber = 0;
            length++;
            for (int i = 0; i < nSItemNumber; i++) {
                int nPos_item = LocateItem(itemlist, ItemName[i]);
                SSportItem* item = &itemlist.pSItemList[nPos_item];
                
                //=======//����ֱ��ʵ�ֽ���Ŀ�����˶�Ա��//ע��Ϸ�����Ŀ��һ�����ڵ�
                athlete.SAthleteItem[i] = *item;
                athlete.nSItemNumber++;
                AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete);///������˶�Ա������Ŀ��������
                //=======
            }
            AddAthlete(athletelist, athlete);
            AddAthlete(athletelist_ok, athlete);
        }

        printf("EndOneLine\n");
    }//while
    printf("\n\t�ɹ�д��%d��\n", length);
    printf("\n\n�ɹ�д�����Ա\n");
    DisplayAthleteListInfo(athletelist_ok);
    WriteItemListFile(itemlist);
    WriteAthleteListFile(athletelist);
    printf("\n\n\t�Ƿ���Ա��\n");
    DisplayAthleteListInfo(athletelist_err);    
    //����������ر��ļ�
    fclose(fp);
	
}  
