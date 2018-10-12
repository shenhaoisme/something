#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <memory.h>
#include <string.h>
/*实现了简单数据传输
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
/* 调用RSA_generate_key和RSA_generate_key_ex函数生成RSA密钥，
 * */
              ret=RSA_generate_key_ex(r,bits,bne,NULL);
        	if(ret!=1)

              {

                     printf("RSA_generate_key_ex err!\n");

                     return -1;

              }


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

      /*RSA_PKCS1_PADDING 其实就是1，定义填充的类型*/
                padding = RSA_PKCS1_PADDING;
                sprintf(from,"%s","shenhaoisme");
              
                flen =12; // strlen(from)

                len = RSA_private_encrypt(flen,from,to,r,padding);
                if(len <= 0)
                        return -1;
/*加密的len。要作为解密函数的参数*/
                len=RSA_public_decrypt(len,to,out,r,padding);
                
		printf("from:%s\nout:%s\n",from,out);
                
                printf("\n");
                printf("flen is %d\n",flen);
             
                RSA_free(r);

}
