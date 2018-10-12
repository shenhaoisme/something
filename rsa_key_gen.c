#include <openssl/rsa.h>

       int    main()

       {

              RSA                      *r;

              int                         bits=512,ret;

              unsigned long  e=RSA_3;

              BIGNUM               *bne;

 

              r = RSA_generate_key(bits,e,NULL,NULL);

              RSA_print_fp(stdout,r,11);

              RSA_free(r);

              bne=BN_new();

              ret=BN_set_word(bne,e);

              r=RSA_new();
/*调用RSA_generate_key和RSA_generate_key_ex函数生成RSA密钥，*/
              ret = RSA_generate_key_ex(r,bits,bne,NULL);

              if(ret!=1)

              {

                     printf("RSA_generate_key_ex err!\n");

                     return -1;

              }
		/*不明白的是RSA_generate_key RSA_generate_key_ex的区别：从输出看是一样的功能，虽然传入参数不同
	下面输出我自己加的
*/
		RSA_print_fp(stdout,r,11);
              RSA_free(r);

              return 0;

       }

