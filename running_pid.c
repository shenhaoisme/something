/*
�и�Ŀ¼����scep��pid��������fgetsȥ��ȡ���ļ���pid��ֵ��
������/proc��Ӧ����һ���� scep pidΪ���ֵ��ļ�����opendir����
ȥ�鿴���pid�ļ����еĻ���˵����������ں�̨���У����Կ��Է���
pid��!!!!
*/
static int running_pid(void)
{
    FILE *f;
    int pid = -1;

    f = fopen(SCEPD_PID_FILE, "r");
    if (f != NULL) 
    {
        /*  read pid */
        char s[32];
        if (fgets(s, sizeof(s)-1, f) != NULL) 
        {
            /* check pid is running */
            DIR *dir;
            char proc[64]="/proc/";

            if (s[strlen(s)-1]=='\n')  s[strlen(s)-1]= 0;  //���ļ��л�ȡpid
            strcat(proc, s);
            DBG_LOG("Checking [%s]", proc);
            if ((dir=opendir(proc)) != NULL)    //���Ŀ��Ŀ¼�����ڵĻ�������NULL��Ҳ����˵scep��proc���ж�Ӧ��pidֵ��
          	//���û�оͷ���NULL
            {
                pid = atoi(s);
            }
            closedir(dir);
        }
        else 
        {
            ERR_LOG( "Cannot read: %s", SCEPD_PID_FILE);
        }
        fclose(f);
    }
    return pid;
} 
