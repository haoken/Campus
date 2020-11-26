#define _CRT_SECURE_NO_WARNINGS  

#include"allstruct.h"

void WriteExcel(SAthleteList& athletelist){            //该函数可以改成把不合法的运动员信息写入到EXCEL文件中 
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
    printf("该行数据分割转化存在SAthlete结果如下：\n") ; 
	printf("ID:%s  ",SAthle.szAthleteID) ; 
	printf("姓名:%s  ",SAthle.szAthleteName) ; 
	if(SAthle.GENDER_athleteGender ==GENDER_MALE ) printf("sex:男  ") ; 
	    else printf("sex:女  ") ; 
	printf("书院:%s  ",SAthle.academy.szAcademyName) ;     
	printf("NumberOfItem:%d  ",SAthle.nSItemNumber) ; 
	for(int i=0;i<SAthle.nSItemNumber;i++) 
	   printf("item:%s  ",SAthle.SAthleteItem[i].szItemName) ; 
	printf("\n") ;
	
}

void DivideLine(SAthlete &SAthle,char szLine[EXCEL_MAX_CHARONELINE]){
	
	char *ptr,*retptr;
    int i=0;
    char Line[EXCEL_MAX_CHARONELINE];        //用于存传入的字符                     
    strcpy(Line,szLine);
    ptr = Line; 
    int length = 0 ;
    length = strlen(Line);
    Line[length-1] = 0;        //	去掉结尾的换行符   
    while ((retptr=strtok(ptr, "	")) != NULL) {
        i++;
        //printf("substr[%d]:%s   ,长度:%d \n", i++, retptr, strlen(retptr));
        ptr = NULL;
        switch(i-1){
        	case 0 : strcpy(SAthle.szAthleteID,retptr);break;                     //表中第一个是ID 
        	case 1 : strcpy(SAthle.szAthleteName,retptr);break;                   //表中第二个是姓名 
        	case 2 : if(!strcmp("男",retptr)) SAthle.GENDER_athleteGender = GENDER_MALE;       ////表中第三个是性别 
        	             else SAthle.GENDER_athleteGender = GENDER_FEMALE;   break;   
        	case 3 : strcpy(SAthle.academy.szAcademyName,retptr);break;   
        	case 4 : SAthle.nSItemNumber = atoi(retptr) ;break;   
			default : strcpy(SAthle.SAthleteItem[i-6].szItemName,retptr);break;   
		}
    }
}

void ReadExcel(){          //从EXCLE中读取参赛信息，并把符合要求的增加到运动员表中 ,把不合要求的运动员打印出来
    FILE *fp;
    char szFileName[20];              //导入的文件名 
    char szLine[EXCEL_MAX_CHARONELINE];
    SAthlete SAthle;
    //判断文件是否打开失败
    printf("请输入要导入的文件名(例子：E:\\test.xls):");
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
    ReadAthleteListFile(athletelist);//所有运动员的信息
    SItemList itemlist;
    InitItemList(itemlist);
    ReadItemListFile(itemlist);//所有项目的信息


    SAthlete athlete;
    int length = 0 ;//成功加入的人数
    fgets(szLine, EXCEL_MAX_CHARONELINE, fp);//先读完第一行，从第二行开始字符串分割 
    //循环读取文件的每一行数据
    while( fgets(szLine, EXCEL_MAX_CHARONELINE, fp) != NULL ) {
        printf("读入的行数据：%s", szLine);
        DivideLine(athlete,szLine); 
        /*
        这里还需要完成运动员信息是否合法的判断，合法运动员信息添加到列表。 
        */
        int flag = true;//如果结果为true则报名项目合法，否则非法。

        int nPos_ID = LocateAthlete(athletelist, athlete.szAthleteID);
        int nPos_Name = LocateAthlete(athletelist, athlete.szAthleteName);
        if (nPos_ID != -1 || nPos_Name != -1) {
            flag == false;
            AddAthlete(athletelist_err, athlete);
            printf("EndOneLine  这个运动员已存在\n");
            continue;
        }

        
        int nSItemNumber = athlete.nSItemNumber;
        char* ItemName[ATHLETE_MAX_ITEM];
        for (int i = 0; i < ATHLETE_MAX_ITEM; i++) 
            ItemName[i] = (char*)malloc(25*sizeof(char));
        for (int i = 0; i < athlete.nSItemNumber; i++) {//检查报名项目是否存在。
            int nPos_item = LocateItem(itemlist,athlete.SAthleteItem[i].szItemName);
            if (nPos_item == -1) {//该项目不存在
                flag = false;
                break;//这个运动员报名了不存在的项目，不合法，
            }
            else {
                strcpy_s(ItemName[i], 25, athlete.SAthleteItem[i].szItemName);
            }
            if (i >= ATHLETE_MAX_ITEM) {
                flag = false;
                break;
            }
        }
        if (!flag) {//非法
            AddAthlete(athletelist_err, athlete);
        }
        else {//合法
            athlete.nSItemNumber = 0;
            length++;
            for (int i = 0; i < nSItemNumber; i++) {
                int nPos_item = LocateItem(itemlist, ItemName[i]);
                SSportItem* item = &itemlist.pSItemList[nPos_item];
                
                //=======//这里直接实现将项目加入运动员中//注意合法的项目是一定存在的
                athlete.SAthleteItem[i] = *item;
                athlete.nSItemNumber++;
                AddAthlete(*itemlist.pSItemList[nPos_item].pAthleteList, athlete);///将这个运动员加入项目报名表中
                //=======
            }
            AddAthlete(athletelist, athlete);
            AddAthlete(athletelist_ok, athlete);
        }

        printf("EndOneLine\n");
    }//while
    printf("\n\t成功写入%d人\n", length);
    printf("\n\n成功写入的人员\n");
    DisplayAthleteListInfo(athletelist_ok);
    WriteItemListFile(itemlist);
    WriteAthleteListFile(athletelist);
    printf("\n\n\t非法人员：\n");
    DisplayAthleteListInfo(athletelist_err);    
    //操作结束后关闭文件
    fclose(fp);
	
}  
