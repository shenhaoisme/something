/*
第一步：只是把一个数据加密，然后再解密，只要内容一样。
下面主要的函数
int RSA_public_encrypt(int flen, const unsigned char *from, unsigned char *to,
                       RSA *rsa, int padding)

int RSA_private_decrypt(int flen, const unsigned char *from,
                        unsigned char *to, RSA *rsa, int padding)
note：
从官方提供的代码来看，用公钥加密就要私钥解密，两个函数使用正好相反；

另外在调用这两个函数，数据长度很重要，会导致失败：


*/


#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <memory.h>

       int    main()

       {

              RSA                      *r;

              int                         bits=1024,ret,len,flen,padding,i;

              unsigned long  e = RSA_3;

              BIGNUM               *bne;

              unsigned char 	*key,*p;

              BIO                      *b;

              unsigned char from[500],to[500],out[500];

 

              bne=BN_new();

              ret=BN_set_word(bne,e);

              r=RSA_new();
/* 调用RSA_generate_key和RSA_generate_key_ex函数生成RSA密钥，
*/
              ret=RSA_generate_key_ex(r,bits,bne,NULL);

              if(ret!=1)

              {

                     printf("RSA_generate_key_ex err!\n");

                     return -1;

              }

              /* 私钥i2d */

              
/*中间这部分不动*/
              b=BIO_new(BIO_s_mem());
/*可能：r内容写到b*/
              ret=i2d_RSAPrivateKey_bio(b,r);

              key=malloc(1024);
/*将 b 中的内容读到 key中去*/

              len=BIO_read(b,key,1024);

              BIO_free(b);

              b=BIO_new_file("rsa.key","w");

              ret = i2d_RSAPrivateKey_bio(b,r);

              BIO_free(b);

              

              /* 私钥d2i */

              /* 公钥i2d */

              /* 公钥d2i */

              /* 私钥加密 */

              flen=RSA_size(r);

              printf("please select private enc padding : \n");

              printf("1.RSA_PKCS1_PADDING\n");

              printf("3.RSA_NO_PADDING\n");

              printf("5.RSA_X931_PADDING\n");

              scanf("%d",&padding);

              if(padding==RSA_PKCS1_PADDING)

                     flen-=11;

              else if(padding==RSA_X931_PADDING)

                     flen-=2;

              else if(padding==RSA_NO_PADDING)

                     flen=flen;

              else

              {

                     printf("rsa not surport !\n");

                     return -1;

              }
/*要加密的数据在这里才第一次产生*/
              for(i=0;i<flen;i++)

                     memset(&from[i],i,1);
/*用私钥加密和填充*/

              len = RSA_private_encrypt(flen,from,to,r,padding);

              if(len<=0)

              {

                     printf("RSA_private_encrypt err!\n");

                     return -1;

              }
/*到了解密的步骤了*/
/*公钥解密*/
              len=RSA_public_decrypt(len,to,out,r,padding);

              if(len<=0)

              {

                     printf("RSA_public_decrypt err!\n");

                     return -1;

              }
/*比较数据内容*/
              if(memcmp(from,out,flen))

              {

                     printf("err!\n");

                     return -1;

              }

              /* */

              printf("please select public enc padding : \n");

              printf("1.RSA_PKCS1_PADDING\n");

              printf("2.RSA_SSLV23_PADDING\n");

              printf("3.RSA_NO_PADDING\n");

              printf("4.RSA_PKCS1_OAEP_PADDING\n");

              scanf("%d",&padding);

              flen=RSA_size(r);

              if(padding==RSA_PKCS1_PADDING)

                     flen-=11;

              else if(padding==RSA_SSLV23_PADDING)

                     flen-=11;

              else if(padding==RSA_X931_PADDING)

                     flen-=2;

              else if(padding==RSA_NO_PADDING)

                     flen=flen;

              else if(padding==RSA_PKCS1_OAEP_PADDING)

                     flen=flen-2 * SHA_DIGEST_LENGTH-2 ;

              else

              {

                     printf("rsa not surport !\n");

                     return -1;

              }
/**/
/**/
              for(i=0;i<flen;i++)

                     memset(&from[i],i+1,1);

              len=RSA_public_encrypt(flen,from,to,r,padding);

              if(len<=0)

              {

                     printf("RSA_public_encrypt err!\n");

                     return -1;

              }

              len=RSA_private_decrypt(len,to,out,r,padding);

              if(len<=0)

              {

                     printf("RSA_private_decrypt err!\n");

                     return -1;

              }

              if(memcmp(from,out,flen))

              {

                     printf("err!\n");

                     return -1;

              }

              printf("test ok!\n");

              RSA_free(r);

              return 0;

       }

