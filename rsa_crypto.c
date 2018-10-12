/*
��һ����ֻ�ǰ�һ�����ݼ��ܣ�Ȼ���ٽ��ܣ�ֻҪ����һ����
������Ҫ�ĺ���
int RSA_public_encrypt(int flen, const unsigned char *from, unsigned char *to,
                       RSA *rsa, int padding)

int RSA_private_decrypt(int flen, const unsigned char *from,
                        unsigned char *to, RSA *rsa, int padding)
note��
�ӹٷ��ṩ�Ĵ����������ù�Կ���ܾ�Ҫ˽Կ���ܣ���������ʹ�������෴��

�����ڵ������������������ݳ��Ⱥ���Ҫ���ᵼ��ʧ�ܣ�


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
/* ����RSA_generate_key��RSA_generate_key_ex��������RSA��Կ��
*/
              ret=RSA_generate_key_ex(r,bits,bne,NULL);

              if(ret!=1)

              {

                     printf("RSA_generate_key_ex err!\n");

                     return -1;

              }

              /* ˽Կi2d */

              
/*�м��ⲿ�ֲ���*/
              b=BIO_new(BIO_s_mem());
/*���ܣ�r����д��b*/
              ret=i2d_RSAPrivateKey_bio(b,r);

              key=malloc(1024);
/*�� b �е����ݶ��� key��ȥ*/

              len=BIO_read(b,key,1024);

              BIO_free(b);

              b=BIO_new_file("rsa.key","w");

              ret = i2d_RSAPrivateKey_bio(b,r);

              BIO_free(b);

              

              /* ˽Կd2i */

              /* ��Կi2d */

              /* ��Կd2i */

              /* ˽Կ���� */

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
/*Ҫ���ܵ�����������ŵ�һ�β���*/
              for(i=0;i<flen;i++)

                     memset(&from[i],i,1);
/*��˽Կ���ܺ����*/

              len = RSA_private_encrypt(flen,from,to,r,padding);

              if(len<=0)

              {

                     printf("RSA_private_encrypt err!\n");

                     return -1;

              }
/*���˽��ܵĲ�����*/
/*��Կ����*/
              len=RSA_public_decrypt(len,to,out,r,padding);

              if(len<=0)

              {

                     printf("RSA_public_decrypt err!\n");

                     return -1;

              }
/*�Ƚ���������*/
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

