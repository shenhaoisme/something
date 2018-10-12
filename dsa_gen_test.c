/*
  Digital Signature Algorithm (DSA)算法是一种公钥算法。其密钥由如下部分组成
生成一个公钥 私钥  P Q G
	1）p

              一个大素数，长度为L(64的整数倍)比特。

       2）q

              一个160比特素数。

       3）g

              g=h(p-1)/q mod p，其中h小于p-1。


整个程序只有一个函数：
声明如下：
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

              

              /* 生成密钥参数 */

              ret=DSA_generate_parameters_ex(d, 512,NULL,0,NULL,NULL,NULL);

              if(ret!=1)

              {

                     DSA_free(d);

                     return -1;

              }

              /* 生成密钥 */

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

