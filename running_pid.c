/*
有个目录保存scep的pid，所以用fgets去获取该文件中pid的值；
并且在/proc中应该有一个以 scep pid为名字的文件，用opendir函数
去查看这个pid文件，有的话，说明这个程序在后台运行，所以可以返回
pid！!!!!
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

            if (s[strlen(s)-1]=='\n')  s[strlen(s)-1]= 0;  //从文件中获取pid
            strcat(proc, s);
            DBG_LOG("Checking [%s]", proc);
            if ((dir=opendir(proc)) != NULL)    //如果目标目录不存在的话，返回NULL，也就是说scep在proc下有对应的pid值，
          	//如果没有就返回NULL
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
