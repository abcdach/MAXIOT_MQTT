


sprintf(AES_SHA1_InPut,"%d                    ",rand());
printf("%s\n\r", AES_SHA1_InPut);
MySHA1_CALCULATOR_2(AES_SHA1_InPut, AES_SHA1_OutPut);
printf("SHA1_OutPut: %s\r\n\r\n",AES_SHA1_OutPut);



sprintf(AES_Temp,"FA376E383626491F");
for (i = 0; i < 16; ++i)AES_KEY[i]=AES_Temp[i];
sprintf(AES_Temp,"0123456789ABCDEF");
for (i = 0; i < 16; ++i)AES_IV[i]=AES_Temp[i];
for( i = 0; i < 16; ++i)AES_IN[i]=AES_SHA1_OutPut[i];
for (i = 0; i < 16; ++i)printf("%c", AES_IN[i]);printf("\n");
struct AES_ctx ctx;
AES_init_ctx_iv(&ctx, AES_KEY, AES_IV);
AES_CBC_encrypt_buffer(&ctx, AES_IN, 16);
sprintf(AES_Temp,"%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"
		,AES_IN[0] ,AES_IN[1] ,AES_IN[2] ,AES_IN[3]
		,AES_IN[4] ,AES_IN[5] ,AES_IN[6] ,AES_IN[7]
		,AES_IN[8] ,AES_IN[9] ,AES_IN[10],AES_IN[11]
		,AES_IN[12],AES_IN[13],AES_IN[14],AES_IN[15]);
printf("%s\n\r", AES_Temp);

usleep(2000);
STU_Sent("{\"F\":\"0\",\"X\":\"%s\"}",AES_Temp);


sprintf(AES_Temp,"FA376E383626491F");
for (i = 0; i < 16; ++i)AES_KEY[i]=AES_Temp[i];
sprintf(AES_Temp,"0123456789ABCDEF");
for (i = 0; i < 16; ++i)AES_IV[i]=AES_Temp[i];
for( i = 0; i < 16; ++i)AES_IN[i]=AES_SHA1_OutPut[15-i];
for (i = 0; i < 16; ++i)printf("%c", AES_IN[i]);printf("\n");
struct AES_ctx ctx2;
AES_init_ctx_iv(&ctx2, AES_KEY, AES_IV);
AES_CBC_encrypt_buffer(&ctx2, AES_IN, 16);
sprintf(AES_Temp,"%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"
		,AES_IN[0] ,AES_IN[1] ,AES_IN[2] ,AES_IN[3]
		,AES_IN[4] ,AES_IN[5] ,AES_IN[6] ,AES_IN[7]
		,AES_IN[8] ,AES_IN[9] ,AES_IN[10],AES_IN[11]
		,AES_IN[12],AES_IN[13],AES_IN[14],AES_IN[15]);
printf("%s\n\r", AES_Temp);



//usleep(2000);

//AES_init_ctx_iv(&ctx, AES_KEY, AES_IV);
//AES_CBC_decrypt_buffer(&ctx, AES_IN, 16);

								//for (i = 0; i < 16; ++i)printf("%c", AES_IN[i]);
								//printf("\n");
















