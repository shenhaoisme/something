/*
  Digital Signature Algorithm (DSA)�㷨��һ�ֹ�Կ�㷨������Կ�����²������
����һ����Կ ˽Կ  P Q G
	1��p

              һ��������������ΪL(64��������)���ء�

       2��q

              һ��160����������

       3��g

              g=h(p-1)/q mod p������hС��p-1��


��������ֻ��һ��������
�������£�
int DSA_generate_parameters_ex(DSA *ret, int bits,
                               const unsigned char *seed_in, int seed_len,
                               int *counter_ret, unsigned long *h_ret,
                               BN_GENCB *cb)


*/


#include <string.h>

       #include <openssl/dsa.h>

       

       int    main()

       {

              DSA                                   *d;

              int                                ret,i;

              unsigned  char seed[20];

              int                                counter=2;

              unsigned  longh;

       

              d=DSA_new();

              for(i=0;i<20;i++)

                     memset(seed+i,i,1);

              

              /* ������Կ���� */

              ret=DSA_generate_parameters_ex(d, 512,NULL,0,NULL,NULL,NULL);

              if(ret!=1)

              {

                     DSA_free(d);

                     return -1;

              }

              /* ������Կ */

              ret=DSA_generate_key(d);

              if(ret!=1)

              {

                     DSA_free(d);

                     return -1;

              }

              DSA_print_fp(stdout,d,0);

              DSA_free(d);

              return 0;

       }

