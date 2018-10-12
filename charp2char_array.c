/*�����������ʦ�Ĵ���
��� char ���鵽string ���͵�ת��������
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int main() {
    int i,v;
    char bs[33];
    char b[33];
    char hs[9];
    char h[9];
    char s[4];
    char *e;

// ʮ��������ת�����ƴ���
    i=1024;
    ltoa(i,b,2);
    sprintf(bs,"%032s",b);
    printf("i=%d,bs=%s\n",i,bs);
// ʮ��������תʮ�����ƴ���
    i=1024;
    ltoa(i,h,16);
    sprintf(hs,"%08s",h);
    printf("i=%d,hs=%s\n",i,hs);
// ʮ�������ַ���ת��ʮ������
    strcpy(hs,"00000400");
    sscanf(hs,"%x",&i);
    printf("hs=%s,i=%d\n",hs,i);
// �������ַ���ת��Ϊʮ�������ַ�����
    strcpy(bs,"00000000000000000000010000000000");
    i=strtol(bs,&e,2);
    ltoa(i,h,16);
    sprintf(hs,"%08s",h);
    printf("bs=%s,hs=%s\n",bs,hs);
// �������ַ���ת��Ϊʮ��������
    strcpy(bs,"00000000000000000000010000000000");
    i=strtol(bs,&e,2);
    printf("bs=%s,i=%d\n",bs,i);
// ʮ�������ַ���ת�ɶ����ƴ�
    strcpy(hs,"00000400");
    sscanf(hs,"%x",&i);
    ltoa(i,b,2);
    sprintf(bs,"%032s",b);
    printf("hs=%s,bs=%s\n",hs,bs);
// ASC\GBK�ַ���תʮ�����ƴ�
    strcpy(s,"a��");
    i=0;
    while (1) {
        if (0==s[i]) break;
        sprintf(hs+i*2,"%02X",(unsigned char)s[i]);
        i++;
    }
    setlocale(LC_ALL,"chs");
    printf("s=%s,hs=%s\n",s,hs);
// ʮ�������ַ���ת�ɺ��֣�GBK�����ַ�(ASC)
    strcpy(hs,"61BABA");
    i=0;
    while (1) {
        if (1!=sscanf(hs+i*2,"%2x",&v)) break;
        s[i]=(char)v;
        i++;
    }
    s[i]=0;
    printf("hs=%s,s=%s\n",hs,s);

    return 0;

}
//i=1024,bs=00000000000000000000010000000000
//i=1024,hs=00000400
//hs=00000400,i=1024
//bs=00000000000000000000010000000000,hs=00000400
//bs=00000000000000000000010000000000,i=1024
//hs=00000400,bs=00000000000000000000010000000000
//s=a��,hs=61BABA
//hs=61BABA,s=a��
