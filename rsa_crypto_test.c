#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <memory.h>
#include <string.h>
/*ʵ���˼����ݴ���
 *
 *
 *
 *
 * */
int main()
{
/**/
          RSA                      *r; /**/
        int                         bits=1024,ret,len,flen,padding,i;
        unsigned long  e = RSA_3;
        BIGNUM               *bne;
        unsigned char   *key,*p;

        BIO                      *b;
        unsigned char from[500],to[500],out[500];
        bne=BN_new();
        ret=BN_set_word(bne,e);
        r=RSA_new();
/* ����RSA_generate_key��RSA_generate_key_ex��������RSA��Կ��
 * */
              ret=RSA_generate_key_ex(r,bits,bne,NULL);
        	if(ret!=1)

              {

                     printf("RSA_generate_key_ex err!\n");

                     return -1;

              }


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

      /*RSA_PKCS1_PADDING ��ʵ����1��������������*/
                padding = RSA_PKCS1_PADDING;
                sprintf(from,"%s","shenhaoisme");
              
                flen =12; // strlen(from)

                len = RSA_private_encrypt(flen,from,to,r,padding);
                if(len <= 0)
                        return -1;
/*���ܵ�len��Ҫ��Ϊ���ܺ����Ĳ���*/
                len=RSA_public_decrypt(len,to,out,r,padding);
                
		printf("from:%s\nout:%s\n",from,out);
                
                printf("\n");
                printf("flen is %d\n",flen);
             
                RSA_free(r);

}
